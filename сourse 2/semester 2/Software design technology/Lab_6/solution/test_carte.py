import pytest
from selenium.common import NoSuchElementException
from selenium.webdriver.common.by import By

with open('logo-carte.svg', 'r') as file:
    logo_check = file.read()

list_check = {
    'contacts': 'ООО «КартэБай», info@carte.by, УНП 391821330\nЗарегистрировано 05.10.2018 Администрацией\nОктябрьского района г. Витебска\n210015 Витебск, ул. Гоголя 14, оф. 804А\nР\С BY19ALFA30122395030010270000\nв ЗАО «Альфа-Банк», Минск,\nул. Сугранова, 43-47\n\nРегистрация в торговом реестре\n№482303 от 18.05.2020',
    'numbers': ('+375 (29) 555-05-05', '+375 (44) 555-05-05'),
    'timework': (('Пн', '08:55 − 23:59'), ('Вт', '08:55 − 23:59'), ('Ср', '08:55 − 23:59'), ('Чт', '08:55 − 23:59'),
                 ('Пт', '08:55 − 01:00'), ('Сб', '08:55 − 01:00'), ('Вс', '08:55 − 23:59')),
    'logo': logo_check}


class Test:
    @pytest.mark.smoke
    def test_contacts(self, browser_2):
        elem = browser_2.find_element(By.CSS_SELECTOR, '.team__xlab').text
        assert elem == list_check["contacts"], "Контактные данные некорректны!"
        print("Проверка контактов пройдена")

    @pytest.mark.regression
    def test_numbers_and_worktime(self, browser):
        numbers = browser.find_elements(By.CSS_SELECTOR, '.mp-phone.no-decoration')
        assert numbers[0].text == list_check['numbers'][0] and numbers[1].text == list_check['numbers'][1], "Номер телефона некорректный!"
        browser.find_element(By.CSS_SELECTOR, '.mp-tabs').click()
        timework = browser.find_elements(By.CSS_SELECTOR, 'div.mp-tab-contents.mp-tab-worktime *')
        for _ in range(0, 7):
            day, time = timework[_].get_attribute('data-week'), timework[_].text
            assert day == list_check['timework'][_][0] and time == list_check['timework'][_][1], "Расписание работы некорректно!"
        browser.find_element(By.CSS_SELECTOR, '.vr__close').click()
        print("Проверка номеров телефонов и графика работы пройдена")

    @pytest.mark.skip()
    def test_logo(self, browser):
        logo = browser.find_element(By.CSS_SELECTOR, '.header__logo-img').get_attribute('src')
        browser.execute_script(f"window.open('{logo}', 'logo');")
        browser.switch_to.window('logo')
        logo = browser.find_element(By.TAG_NAME, 'svg').get_attribute('outerHTML')
        assert logo == list_check['logo'], "Логотипы отличаются!"
        print("Проверка логотипа пройдена")
        browser.close()
        browser.switch_to.window(browser.window_handles[0])

    login_success = False
    head_us_name_available = True

    @pytest.mark.parametrize('authorization', [
        pytest.param(('+375333567280', 'Hrjt_609'), id='+375333567280, Hrjt_609'),
        pytest.param(('+375292090169', 'KOLUM250'), id='+375292090169, KOLUM250'),
        pytest.param(('+375333563448', 'Gkeb2005'), id='+375333563448, Gkeb2005')
    ])
    @pytest.mark.xfail
    def test_authorization(self, browser, authorization):
        login, password = authorization
        if Test.login_success:
            browser.get('https://carte.by/auth/?logout')
            Test.head_us_name_available = True
        if Test.head_us_name_available:
            browser.find_element(By.CSS_SELECTOR, '.header__user-name').click()
        Test.head_us_name_available = False
        log_input = browser.find_element(By.CSS_SELECTOR, '.auth__input.auth__input--login')
        log_input.clear()
        log_input.send_keys(login)
        pass_input = browser.find_element(By.CSS_SELECTOR, '.auth__input.auth__input--password')
        pass_input.clear()
        pass_input.send_keys(password)
        browser.find_element(By.CSS_SELECTOR, '.auth__submit.btload.btload--white').click()
        try:
            browser.find_element(By.CSS_SELECTOR, '.header__user-avatar ')
            print("Вход был выполнен")
            Test.login_success = True
        except NoSuchElementException:
            Test.login_success = False
            raise Exception("Попытка входа в аккаунт не удалась!")

    def test_logo_display(self, browser):
        try:
            logo_element = browser.find_element(By.CSS_SELECTOR, '.header__logo-img')
            assert logo_element.is_displayed(), "Логотип не отображается на странице"
            print("Логотип отображается на странице")
        except NoSuchElementException:
            assert False, "Логотип не найден на странице"

