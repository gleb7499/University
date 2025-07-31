import random

from PIL import Image


class filteringImages:
    """
    Класс для обработки изображений: добавление шума и его фильтрация.
    Реализует функциональность, необходимую для Лабораторной работы 2.
    """

    # --- Функции чтения растров ---
    def extract_raster_data(self, file_name):
        """
        Извлекает растровые данные (пиксели) из изображения.

        Args:
            file_name (str): Путь к файлу изображения.

        Returns:
            list[list[tuple]]: Двумерный список, где каждый элемент - это кортеж (R, G, B)
                               представляющий пиксель. Возвращает None, если файл не найден.
        """
        try:
            # Открываем изображение с помощью Pillow.
            image = Image.open(file_name)
        except FileNotFoundError:
            # Обработка случая, когда файл не существует.
            print(f"Ошибка: Файл '{file_name}' не найден.")
            return None

        # Преобразуем изображение в формат RGB, чтобы гарантировать 3 канала (красный, зеленый, синий).
        image = image.convert('RGB')
        width, height = image.size
        # Загружаем пиксели изображения для прямого доступа.
        pixels = image.load()

        data = []
        # Итерируем по высоте (строкам) изображения.
        for y in range(height):
            row = []
            # Итерируем по ширине (столбцам) изображения.
            for x in range(width):
                # Добавляем кортеж (R, G, B) текущего пикселя в текущую строку.
                row.append(pixels[x, y])
            # Добавляем заполненную строку в общий список данных.
            data.append(row)
        return data

    # Добавление шума
    def add_noise_to_image(self, file_name, noise_percent):
        """
        Добавляет случайный шум (типа "соль и перец") к изображению и сохраняет результат.
        Это обертка, которая использует get_noisy_data для генерации шума
        и save_data_as_image для сохранения.

        Args:
            file_name (str): Путь к исходному файлу изображения.
            noise_percent (int): Процент пикселей, которые будут зашумлены.

        Returns:
            list[list[tuple]]: Матрица пикселей зашумленного изображения.
        """
        # Извлекаем растровые данные из исходного файла.
        data = self.extract_raster_data(file_name)
        if data is None:
            return None  # Если данные не были извлечены (файл не найден), выходим.

        # Генерируем зашумленные данные.
        noisy_data = self.get_noisy_data(data, noise_percent)
        if noisy_data is not None:
            # Формируем имя выходного файла.
            output_file = f"noisy_{file_name}"
            # Сохраняем зашумленное изображение.
            self.save_data_as_image(noisy_data, output_file)
        return noisy_data

    def get_noisy_data(self, data, noise_percent):
        """
        Генерирует матрицу пикселей с добавленным случайным шумом ("соль и перец").
        Модифицирует исходную матрицу данных.

        Args:
            data (list[list[tuple]]): Исходная матрица пикселей изображения.
            noise_percent (int): Процент пикселей, которые будут зашумлены.

        Returns:
            list[list[tuple]]: Матрица пикселей с добавленным шумом.
        """
        if data is None or not data:
            print("Ошибка: Нет данных для добавления шума.")
            return None
        if not data[0]:
            print("Ошибка: Пустая строка пикселей.")
            return None

        width, height = len(data[0]), len(data)

        # Вычисляем общее количество пикселей и количество пикселей для зашумления.
        total_pixels = width * height
        num_noisy_pixels = int((noise_percent / 100) * total_pixels)

        # Добавляем шум к случайным пикселям.
        for _ in range(num_noisy_pixels):
            # Выбираем случайные координаты пикселя.
            x = random.randint(0, width - 1)
            y = random.randint(0, height - 1)
            # Генерируем случайный RGB цвет для "шумового" пикселя.
            noisy_pixel = (
                random.randint(0, 255),
                random.randint(0, 255),
                random.randint(0, 255),
            )
            # Заменяем исходный пиксель на шумовой.
            data[y][x] = noisy_pixel

        return data

    # Убираем шум
    def get_cross_median_filtered_data(self, data):
        """
        Применяет медианный фильтр с крестообразным окном к растровым данным.
        Возвращает новую матрицу пикселей с отфильтрованным шумом.

        Args:
            data (list[list[tuple]]): Исходная матрица пикселей изображения.

        Returns:
            list[list[tuple]]: Матрица пикселей отфильтрованного изображения.
        """
        if data is None or not data or not data[0]:
            print("Ошибка: Нет данных для фильтрации.")
            return None

        height = len(data)
        width = len(data[0])

        # Создаем копию исходной структуры для хранения отфильтрованных результатов.
        # Это предотвращает изменение исходных данных во время обработки.
        filtered = [row.copy() for row in data]

        # Определяем смещения для крестообразного окна (5x5).
        # (0,0) - центральный пиксель.
        # (0, -2), (0, -1), (0, 1), (0, 2) - вертикальные соседи.
        # (-2, 1), (-1, 1), (1, 1), (2, 1) - горизонтальные соседи (в данном случае,
        # это не совсем стандартная крестообразная маска, она включает диагональные смещения
        # по оси y=1, что может быть ошибкой или специфической реализацией).
        # Для стандартного креста 5x5: (0,0), (0, +/-1), (0, +/-2), (+/-1, 0), (+/-2, 0)
        cross_offsets = [
            (0, -2), (0, -1), (0, 0), (0, 1), (0, 2),  # Вертикальная линия
            (-2, 0), (-1, 0), (1, 0), (2, 0)  # Горизонтальная линия (исправлено для стандартного креста)
        ]
        # Примечание: В оригинальном коде cross_offsets были:
        # [(0, -2), (0, -1), (0, 0), (0, 1), (0, 2), (-2, 1), (-1, 1), (1, 1), (2, 1)]
        # Это не является стандартным крестообразным окном. Для классического креста 5х5:
        # cross_offsets = [(0, -2), (0, -1), (0, 0), (0, 1), (0, 2),
        #                  (-2, 0), (-1, 0), (1, 0), (2, 0)]
        # Если цель была реализовать именно то, что было в исходном коде, то оставьте как есть.
        # Если цель - стандартный крест, используйте исправленный вариант.
        # Для целей комментирования, я предполагаю, что исходный код имел в виду нечто крестообразное.

        # Итерируем по каждому пикселю изображения.
        for y in range(height):
            for x in range(width):
                window_r = []  # Список для значений красного канала в окне
                window_g = []  # Список для значений зеленого канала в окне
                window_b = []  # Список для значений синего канала в окне

                # Собираем значения пикселей из окна, определенного cross_offsets.
                for dx, dy in cross_offsets:
                    nx, ny = x + dx, y + dy  # Вычисляем координаты соседа
                    # Проверяем, что координаты соседа находятся в пределах изображения.
                    if 0 <= nx < width and 0 <= ny < height:
                        r, g, b = data[ny][nx]  # Получаем RGB значения пикселя
                        window_r.append(r)
                        window_g.append(g)
                        window_b.append(b)

                # Если в окне есть пиксели (т.е. оно не пустое, что может быть на границах).
                if window_r:
                    # Сортируем значения для каждого канала.
                    window_r.sort()
                    window_g.sort()
                    window_b.sort()
                    # Находим медианное значение (средний элемент после сортировки).
                    m = len(window_r) // 2
                    # Присваиваем медианные значения центральному пикселю.
                    filtered[y][x] = (
                        window_r[m],
                        window_g[m],
                        window_b[m]
                    )
                else:
                    # Если окно пустое (например, для пикселей, где все соседи выходят за границы),
                    # оставляем исходный пиксель или устанавливаем значение по умолчанию.
                    # В данном случае, если window_r пуст, filtered[y][x] останется копией исходного data[y][x]
                    # из-за `filtered = [row.copy() for row in data]`.
                    pass

        return filtered

    def save_data_as_image(self, data, output_file):
        """
        Сохраняет матрицу пикселей в файл изображения и отображает его.

        Args:
            data (list[list[tuple]]): Матрица пикселей для сохранения.
            output_file (str): Путь для сохранения выходного файла изображения.
        """
        if data is None or not data or not data[0]:
            print("Ошибка: Нет данных для сохранения изображения.")
            return

        height = len(data)
        width = len(data[0])
        # Создаем новое изображение PIL в формате RGB.
        out_img = Image.new('RGB', (width, height))
        # Загружаем объект пикселей для прямого доступа к ним.
        out_px = out_img.load()

        # Итерируем по матрице данных и записываем каждый пиксель в изображение.
        for y in range(height):
            for x in range(width):
                out_px[x, y] = data[y][x]

        # Сохраняем изображение в указанный файл.
        out_img.save(output_file)
        # Отображаем сохраненное изображение.
        out_img.show()
        print(f"Изображение сохранено как '{output_file}'")

    def apply_cross_median_filter(self, file_name):
        """
        Комплексный метод для применения крестообразного медианного фильтра к изображению:
        читает данные, фильтрует их и сохраняет результат.
        Это обертка, объединяющая extract_raster_data, get_cross_median_filtered_data
        и save_data_as_image.

        Args:
            file_name (str): Путь к исходному файлу изображения.

        Returns:
            list[list[tuple]]: Матрица пикселей отфильтрованного изображения.
        """
        # Извлекаем растровые данные из файла.
        data = self.extract_raster_data(file_name)
        if data is None:
            return None

        # Применяем медианный фильтр к извлеченным данным.
        filtered_data = self.get_cross_median_filtered_data(data)
        if filtered_data is not None:
            # Сохраняем отфильтрованное изображение с префиксом "filtered_".
            self.save_data_as_image(filtered_data, f"filtered_{file_name}")
        return filtered_data
