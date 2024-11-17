from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.common.exceptions import NoSuchElementException
from selenium.common.exceptions import TimeoutException

browser = webdriver.Chrome()
wait = WebDriverWait(browser, 4)
try:
    browser.get('https://github.com/topics')
    while True:
        try:
            lead_more_butt = browser.find_element(By.CSS_SELECTOR, '[class="ajax-pagination-btn btn mt-4 py-2 color-border-default f6 width-full"]')
            lead_more_butt.click()
            wait.until(EC.staleness_of(lead_more_butt))
        except (TimeoutException, NoSuchElementException):
            break

    with open("links.txt", 'a+', encoding='utf-8') as file:
        file.truncate(0)
        Found = browser.find_elements(By.CSS_SELECTOR, '[class="no-underline flex-1 d-flex flex-column"]')
        for found in Found:
            file.write(found.get_attribute('href') + '\n')
except Exception as ex:
    print(ex)
finally:
    browser.close()
    browser.quit()
