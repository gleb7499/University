from src.labs.filteringImages import filteringImages
from src.labs.outlineSelection import outlineSelection
from src.labs.rasterFiles import rasterFiles

# Точка входа в программу
if __name__ == '__main__':
    # Инициализация объектов для каждой лабораторной работы.
    # Это позволяет использовать функционал, определенный в соответствующих модулях.

    # Лабораторная работа 1: Работа с растровыми файлами (BMP и пользовательский .LGO)
    rasterFiles = rasterFiles()
    # Лабораторная работа 2: Добавление шума и фильтрация изображений
    filteringImages = filteringImages()
    # Лабораторная работа 3: Выделение контуров на изображениях
    outlineSelection = outlineSelection()

    # Основной цикл программы, предоставляющий пользователю меню выбора действий.
    while True:
        # Вывод меню для пользователя с доступными операциями.
        choice = input(
            "\nВыберите действие:\n"
            "1 - Открыть BMP, обработать и сохранить в .FIO\n"
            "2 - Открыть .FIO, вывести заголовок и сохранить в .BMP\n"
            "3 - Добавить шум на изображение\n"
            "4 - Фильтрация шума\n"
            "5 - Выделить контур изображения\n"
            "6 - Выход\n"
            "Ваш выбор: "
        )

        # Обработка выбора пользователя
        if choice == '1':
            # Задание 1 (ЛР1): Открытие двух BMP-изображений, применение эффекта Color Dodge
            # и сохранение результата в пользовательский формат .FIO (здесь .LGO).
            base_img_path = input("Введите путь к базовому изображению (.BMP): ")
            blend_img_path = input("Введите путь к изображению для наложения (.BMP): ")
            rasterFiles.open_bmp(base_img_path, blend_img_path)
        elif choice == '2':
            # Задание 2 (ЛР1): Открытие файла пользовательского формата .FIO (здесь .LGO),
            # вывод его заголовка и сохранение растровых данных в BMP-файл.
            fio_path = input("Введите путь к файлу .LGO: ")
            output_bmp_path = 'result_from_fio.bmp'  # Имя файла для сохранения результата
            rasterFiles.open_fio(fio_path, output_bmp_path)
        elif choice == '3':
            # Задание 3 (ЛР2): Добавление шума к изображению.
            # Пользователь указывает путь к файлу и процент шума.
            file_name = input("Введите путь к файлу: ")
            noise_percent = int(input("Введите процент шума: "))
            filteringImages.add_noise_to_image(file_name, noise_percent)
        elif choice == '4':
            # Задание 4 (ЛР2): Фильтрация шума с использованием медианного фильтра.
            # Пользователь указывает путь к файлу.
            file_name = input("Введите путь к файлу: ")
            filteringImages.apply_cross_median_filter(file_name)
        elif choice == '5':
            # Задание 5 (ЛР3): Выделение контуров на изображении.
            # Программа применяет выделение контуров к исходному, зашумленному и отфильтрованному изображениям.
            file_name = input("Введите путь к файлу: ")
            outlineSelection.extract_outline(file_name)
        elif choice == '6':
            # Выход из программы.
            print("Выход из программы.")
            break
        else:
            # Обработка неверного ввода пользователя.
            print("Неверный выбор. Попробуйте снова.")
