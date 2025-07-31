from PIL import Image

# Импортируем класс filteringImages из модуля src.labs.filteringImages
# Этот класс содержит методы для чтения растровых данных, добавления шума и фильтрации.
from src.labs.filteringImages import filteringImages


class outlineSelection:
    """
    Класс для выделения контуров на изображениях.
    Реализует функциональность, необходимую для Лабораторной работы 3.
    """

    def __init__(self):
        """
        Конструктор класса outlineSelection.
        Инициализирует объект класса filteringImages для использования его методов.
        """
        self.filteringImages = filteringImages()

    def __original(self, file_name):
        """
        Обрабатывает исходное изображение для выделения контуров.
        Последовательность шагов: извлечение данных -> преобразование в оттенки серого
        -> контрастирование/выделение контуров -> бинаризация -> сохранение.

        Args:
            file_name (str): Путь к исходному файлу изображения.
        """
        # 1. Извлечение растровых данных изображения в формате RGB.
        data = self.filteringImages.extract_raster_data(file_name)
        if data is None:
            print(f"Не удалось извлечь данные из файла {file_name} для оригинального изображения.")
            return

        # 2. Преобразование RGB-изображения в оттенки серого.
        gray_data = self.__rgb_to_grayscale(data)
        # 3. Применение оператора контрастирования для выделения потенциальных контуров.
        outline = self.__extract_outline(gray_data)
        # 4. Выделение контурного препарата (бинаризация) с использованием итеративного порога.
        control = self.__extract_contour(outline)
        # 5. Сохранение результата в новый файл с префиксом "original_".
        self.__create_new_files("original_" + file_name, control)
        print(f"Контур оригинального изображения сохранен как 'result_original_{file_name}'")

    def __filtered(self, file_name):
        """
        Обрабатывает отфильтрованное изображение для выделения контуров.
        Последовательность шагов: извлечение данных -> фильтрация шума ->
        преобразование в оттенки серого -> контрастирование/выделение контуров ->
        бинаризация -> сохранение.

        Args:
            file_name (str): Путь к исходному файлу изображения.
        """
        # 1. Извлечение растровых данных.
        data = self.filteringImages.extract_raster_data(file_name)
        if data is None:
            print(f"Не удалось извлечь данные из файла {file_name} для фильтрованного изображения.")
            return

        # 2. Удаление шума с использованием медианного фильтра из filteringImages.
        filtered_data = self.filteringImages.get_cross_median_filtered_data(data)
        if filtered_data is None:
            print(f"Не удалось отфильтровать данные для файла {file_name}.")
            return

        # 3. Контрастирование изображения (преобразование в оттенки серого).
        gray_data = self.__rgb_to_grayscale(filtered_data)
        # 4. Выделение контуров.
        outline = self.__extract_outline(gray_data)
        # 5. Выделение контурного препарата (бинаризация).
        control = self.__extract_contour(outline)
        # 6. Формирование нового файла с префиксом "filtered_".
        self.__create_new_files("filtered_" + file_name, control)
        print(f"Контур отфильтрованного изображения сохранен как 'result_filtered_{file_name}'")

    def __noisy(self, file_name, noise_percent):
        """
        Обрабатывает зашумленное изображение для выделения контуров.
        Последовательность шагов: извлечение данных -> добавление шума ->
        преобразование в оттенки серого -> контрастирование/выделение контуров ->
        бинаризация -> сохранение.

        Args:
            file_name (str): Путь к исходному файлу изображения.
            noise_percent (int): Процент шума для добавления.
        """
        # 1. Извлечение растровых данных.
        data = self.filteringImages.extract_raster_data(file_name)
        if data is None:
            print(f"Не удалось извлечь данные из файла {file_name} для зашумленного изображения.")
            return

        # 2. Добавление шума к изображению.
        noisy_data = self.filteringImages.get_noisy_data(data, noise_percent)
        if noisy_data is None:
            print(f"Не удалось добавить шум к изображению {file_name}.")
            return

        # 3. Контрастирование изображения (преобразование в оттенки серого).
        gray_data = self.__rgb_to_grayscale(noisy_data)
        # 4. Выделение контуров.
        outline = self.__extract_outline(gray_data)
        # 5. Выделение контурного препарата (бинаризация).
        control = self.__extract_contour(outline)
        # 6. Формирование нового файла с префиксом "noisy_".
        self.__create_new_files("noisy_" + file_name, control)
        print(f"Контур зашумленного изображения сохранен как 'result_noisy_{file_name}'")

    def __noisyFiltered(self, file_name, noise_percent):
        """
        Обрабатывает зашумленное и затем отфильтрованное изображение для выделения контуров.
        Последовательность шагов: извлечение данных -> добавление шума ->
        удаление шума -> преобразование в оттенки серого ->
        контрастирование/выделение контуров -> бинаризация -> сохранение.

        Args:
            file_name (str): Путь к исходному файлу изображения.
            noise_percent (int): Процент шума для добавления перед фильтрацией.
        """
        # 1. Извлечение растровых данных.
        data = self.filteringImages.extract_raster_data(file_name)
        if data is None:
            print(f"Не удалось извлечь данные из файла {file_name} для зашумленного и отфильтрованного изображения.")
            return

        # 2. Добавление шума.
        noisy_data = self.filteringImages.get_noisy_data(data, noise_percent)
        if noisy_data is None:
            print(f"Не удалось добавить шум к изображению {file_name}.")
            return

        # 3. Удаление шума с использованием медианного фильтра.
        filtered_data = self.filteringImages.get_cross_median_filtered_data(noisy_data)
        if filtered_data is None:
            print(f"Не удалось отфильтровать зашумленные данные для файла {file_name}.")
            return

        # 4. Контрастирование изображения (преобразование в оттенки серого).
        gray_data = self.__rgb_to_grayscale(filtered_data)
        # 5. Выделение контуров.
        outline = self.__extract_outline(gray_data)
        # 6. Выделение контурного препарата (бинаризация).
        control = self.__extract_contour(outline)
        # 7. Формирование нового файла с префиксом "noisyFiltered_".
        self.__create_new_files("noisyFiltered_" + file_name, control)
        print(f"Контур зашумленного и отфильтрованного изображения сохранен как 'result_noisyFiltered_{file_name}'")

    def extract_outline(self, file_name):
        """
        Основной публичный метод для запуска процесса выделения контуров
        и сравнительного анализа на различных состояниях изображения.
        Запрашивает у пользователя процент шума.

        Args:
            file_name (str): Путь к исходному файлу изображения.
        """
        try:
            noise_percent = int(input("Введите процент шума (для зашумленных изображений) -> "))
            if not (0 <= noise_percent <= 100):
                print("Процент шума должен быть в диапазоне от 0 до 100.")
                return
        except ValueError:
            print("Некорректный ввод для процента шума. Пожалуйста, введите целое число.")
            return

        # Выделение контуров на исходном изображении.
        self.__original(file_name)
        # Выделение контуров на отфильтрованном исходном изображении.
        self.__filtered(file_name)
        # Выделение контуров на зашумленном изображении.
        self.__noisy(file_name, noise_percent)
        # Выделение контуров на зашумленном и затем отфильтрованном изображении.
        self.__noisyFiltered(file_name, noise_percent)
        print("Процесс выделения контуров завершен для всех вариантов.")

    def __rgb_to_grayscale(self, data_rgb):
        """
        Преобразует RGB-изображение в оттенки серого.
        Использует стандартную формулу для перевода RGB в яркость (luminance).

        Args:
            data_rgb (list[list[tuple]]): Двумерный список пикселей RGB (R, G, B).

        Returns:
            list[list[int]]: Двумерный список пикселей в оттенках серого (0-255).
        """
        if data_rgb is None or not data_rgb or not data_rgb[0]:
            print("Ошибка: Нет RGB данных для преобразования в оттенки серого.")
            return None

        grayscale = []
        for row in data_rgb:
            gray_row = []
            for pixel in row:
                r, g, b = pixel
                # Формула для преобразования RGB в оттенки серого (luminance method).
                gray = int(0.299 * r + 0.587 * g + 0.114 * b)
                gray_row.append(gray)
            grayscale.append(gray_row)
        return grayscale

    def __extract_outline(self, data):
        """
        Применяет оператор контрастирования (свертку с маской) для выделения контуров.
        Использует пользовательскую курсовую маску.

        Args:
            data (list[list[int]]): Двумерный список пикселей изображения в оттенках серого.

        Returns:
            list[list[int]]: Двумерный список, представляющий контуры после свертки и нормализации.
        """
        if data is None or not data or not data[0]:
            print("Ошибка: Нет данных для извлечения контуров.")
            return None

        Height = len(data)
        Width = len(data[0])

        # Инициализация матрицы для хранения результатов свертки.
        G = [[0] * Width for _ in range(Height)]

        # Определение курсовой маски (ядра свертки).
        # Эта маска чувствительна к изменениям яркости и используется для обнаружения краев.
        # В данном случае это не стандартная маска "северо-запад", а скорее обобщенный оператор.
        kernel = [
            [1, 1, 1],
            [1, -2, -1],
            [1, -1, -1]
        ]

        # 1) Свёртка с маской:
        # Итерируем по пикселям изображения, исключая границы, так как ядро 3x3.
        for i in range(1, Height - 1):
            for j in range(1, Width - 1):
                s = 0  # Сумма произведений элементов ядра на соответствующие пиксели.
                # Итерируем по элементам ядра (окно 3x3 вокруг текущего пикселя).
                for dy in range(-1, 2):
                    for dx in range(-1, 2):
                        # Прибавляем произведение элемента ядра на значение пикселя.
                        s += kernel[dy + 1][dx + 1] * data[i + dy][j + dx]
                # Берем абсолютное значение, так как контуры - это сила изменения, а не направление.
                G[i][j] = abs(s)

        # 2) Нормализация:
        # Находим максимальное значение в результирующей матрице G.
        max_g = 0
        if Height > 0 and Width > 0:  # Проверка на пустые данные
            max_g = max(max(row) for row in G)

        # Нормализуем значения в G к диапазону 0-255.
        # Это делает изображение более контрастным и пригодным для дальнейшей бинаризации.
        if max_g > 0:  # Избегаем деления на ноль, если изображение однородное.
            for i in range(Height):
                for j in range(Width):
                    G[i][j] = G[i][j] * 255 // max_g

        return G

    def __extract_contour(self, data):
        """
        Выделяет контурный препарат (бинаризует изображение) с использованием
        итеративного алгоритма для поиска оптимального порога (метод, похожий на метод Оцу).

        Args:
            data (list[list[int]]): Двумерный список пикселей изображения в оттенках серого.

        Returns:
            list[list[int]]: Бинарное изображение, где 0 - контур, 255 - фон.
        """
        if data is None or not data or not data[0]:
            print("Ошибка: Нет данных для выделения контурного препарата.")
            return None

        # --- 1. Находим размеры изображения ---
        height = len(data)
        width = len(data[0])

        # --- 2. Итеративный поиск порога ---
        # 2.1. Начальный порог — середина диапазона яркости (0-255).
        T_old = 255 // 2

        while True:
            # Инициализация сумм и счетчиков для двух классов пикселей (ниже/выше порога).
            sum1 = 0  # Сумма яркостей пикселей <= T_old
            count1 = 0  # Количество пикселей <= T_old
            sum2 = 0  # Сумма яркостей пикселей > T_old
            count2 = 0  # Количество пикселей > T_old

            # Распределение пикселей по двум классам на основе текущего порога T_old.
            for y in range(height):
                for x in range(width):
                    v = data[y][x]
                    if v <= T_old:
                        sum1 += v
                        count1 += 1
                    else:
                        sum2 += v
                        count2 += 1

            # Если один из классов пуст, это означает, что все пиксели находятся
            # по одну сторону от порога, и дальнейшая итерация бессмысленна.
            if count1 == 0 or count2 == 0:
                break

            # Вычисление средних значений яркости для каждого класса.
            mu1 = sum1 // count1
            mu2 = sum2 // count2

            # Вычисление нового порога как среднего арифметического средних значений классов.
            T_new = (mu1 + mu2) // 2

            # Проверяем сходимость: если новый порог равен старому, алгоритм сошелся.
            if T_new == T_old:
                break
            # Обновляем старый порог для следующей итерации.
            T_old = T_new

        # Оптимальный порог найден.
        threshold = T_old

        # --- 4. Пороговое преобразование в бинарное изображение ---
        result = []
        for y in range(height):
            row = []
            for x in range(width):
                # Если яркость пикселя больше порога, это считается контуром (черный цвет).
                if data[y][x] > threshold:
                    row.append(0)  # контур (черный)
                # В противном случае, это фон (белый цвет).
                else:
                    row.append(255)  # фон (белый)
            result.append(row)

        return result

    def __create_new_files(self, file_name, control):
        """
        Сохраняет бинарное изображение (контурный препарат) в файл в градациях серого.

        Args:
            file_name (str): Базовое имя файла для сохранения (будет добавлен префикс "result_").
            control (list[list[int]]): Двумерный список пикселей бинарного изображения.
        """
        if control is None or not control or not control[0]:
            print(f"Ошибка: Нет данных для сохранения файла {file_name}.")
            return

        height = len(control)
        width = len(control[0])

        # Создание объекта изображения PIL в градациях серого ('L' - 8-битное пиксельное изображение).
        image = Image.new('L', (width, height))

        # Преобразование двумерного массива пикселей в одномерный список,
        # который требуется методом putdata() PIL.
        pixels = []
        for row in control:
            for value in row:
                # Убедимся, что значение пикселя находится в допустимом диапазоне 0-255.
                if value < 0:
                    value = 0
                elif value > 255:
                    value = 255
                pixels.append(value)

        # Добавление пикселей в изображение PIL.
        image.putdata(pixels)

        # Сохранение изображения в файл.
        image.save(f"result_{file_name}")
        print(f"Файл 'result_{file_name}' успешно создан.")
