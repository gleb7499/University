import csv
import requests
from bs4 import BeautifulSoup

def filename_generator():
    i = 1
    while True:
        yield f'exercise_{i}.csv'
        i += 1

def task_generator():
    tasks = 1
    while True:
        yield tasks
        tasks += 1

task = task_generator()
filename = filename_generator()

soup = BeautifulSoup(requests.get("https://start.ru/series").text, 'lxml')
# 1
found = soup.find('span')
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Имя тега', 'Значение тега'])
    writer.writerow([found.name, found.text])
print(f"Задание № {next(task)} выполнено\n")
# 2
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Имя тега', 'Значение ID', 'Значение тега'])
    found = soup.find(id=str(5))
    writer.writerow([found.name, found.get('id'), found.text])
print(f"Задание № {next(task)} выполнено\n")
# 3
found = soup.find(class_='VideoList_videoCatalog-title-alias__KWugQ')
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Имя тега', 'Имена классов', 'Значение тега'])
    writer.writerow([found.name, found.get('class'), found.text])
print(f"Задание № {next(task)} выполнено\n")

soup = BeautifulSoup(requests.get('https://www.ivi.ru/new/movie-new').text, 'lxml')
# 4
found = soup.find(lambda tag: 'name' in tag.attrs)
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Имя тега', 'Значение атрибута', 'Значение тега'])
    writer.writerow([found.name, found.get('name'), found.text])
print(f"Задание № {next(task)} выполнено\n")
# 5
found = soup.select_one('div .nbl-picture')
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Составной селектор', 'Имя тега', 'Значение тега'])
    writer.writerow(['div .nbl-picture', found.name, found.text])
print(f"Задание № {next(task)} выполнено\n")
# 6
found = soup.select_one('div > .nbl-icon.nbl-icon_avatar_20.nbl-button__nbl-icon')
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Составной селектор', 'Имя тега', 'Значение тега'])
    writer.writerow(['div > .nbl-icon.nbl-icon_avatar_20.nbl-button__nbl-icon', found.name, found.text])
print(f"Задание № {next(task)} выполнено\n")

soup = BeautifulSoup(requests.get('https://www.kufar.by/l').text, 'lxml')
# 7
found = soup.select_one('.swiper-slide.style_slide__mZ_c0')
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(['Составной селектор', 'Имя тега', 'Значение тега'])
    writer.writerow(['.swiper-slide.style_slide__mZ_c0', found.name, found.text])
print(f"Задание № {next(task)} выполнено\n")
# 8
found = soup.select('ul li:nth-child(n) #safety')
with open(next(filename), 'w', newline='', encoding='cp1251') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(["Селектор", "Значения тегов"])
    writer.writerow(['ul li:nth-child(n) #safety', found[0].text])
print(f"Задание № {next(task)} выполнено\n")