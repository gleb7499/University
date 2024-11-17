import pytest
from selenium import webdriver
from selenium.webdriver.common.by import By


@pytest.fixture(scope="class")
def browser():
    browser = webdriver.Chrome()
    browser.get('https://carte.by/')
    browser.implicitly_wait(2)
    yield browser
    browser.close()
    browser.quit()


@pytest.fixture(scope="function")
def browser_2(browser):
    browser.find_element(By.CSS_SELECTOR, '.header__nav-name.header__phone').click()
    browser.implicitly_wait(2)
    elem = browser.find_element(By.CSS_SELECTOR, '.footer__meta a').get_attribute('href')
    browser.execute_script(f"window.open('{elem}', 'contacts');")
    browser.switch_to.window("contacts")
    yield browser
    browser.close()
    browser.switch_to.window(browser.window_handles[0])
