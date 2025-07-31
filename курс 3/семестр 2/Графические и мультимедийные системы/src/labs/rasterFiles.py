import struct

import numpy as np
from PIL import Image


class rasterFiles:
    """
    Класс для работы с растровыми файлами форматов BMP и пользовательского .FIO (здесь .LGO).
    Предоставляет функциональность для чтения заголовков, попиксельной обработки и сохранения изображений.
    """

    # Определение пользовательского формата заголовка для формата .FIO (Лабораторная работа 1).
    # FIO_HEADER_FORMAT: Строка формата для struct.pack/unpack.
    # '<2s16sI4I' означает:
    #   <   - little-endian (порядок байтов от младшего к старшему)
    #   2s  - 2 байта для типа файла (например, 'BM' для BMP)
    #   16s - 16 байт для комментария
    #   I   - беззнаковое целое (4 байта) для размера растра
    #   4I  - четыре беззнаковых целых (по 4 байта каждое) для смещения данных, ширины, высоты, количества пикселей
    FIO_HEADER_FORMAT = '<2s16sI4I'
    # HEADER_SIZE: Вычисляем размер заголовка в байтах на основе определенного формата.
    HEADER_SIZE = struct.calcsize(FIO_HEADER_FORMAT)

    def __read_bmp_header(self, file_path):
        """
        Читает и извлекает ключевую информацию из заголовка BMP-файла.

        Args:
            file_path (str): Путь к BMP-файлу.

        Returns:
            dict: Словарь с информацией о заголовке BMP:
                  'file_type', 'comment', 'raster_size', 'data_offset',
                  'width', 'height', 'pixel_count'.
        """
        with open(file_path, 'rb') as f:
            # Перейти к смещению ширины и высоты (байты 18-25 в BMP заголовке)
            f.seek(18)
            # Считать 8 байт (по 4 байта на каждое) для ширины и высоты
            width, height = struct.unpack('<II', f.read(8))

            # Перейти к смещению данных (байт 10 в BMP заголовке)
            f.seek(10)
            # Считать 4 байта для смещения данных растра от начала файла
            data_offset = struct.unpack('<I', f.read(4))[0]

            # Перейти к размеру растровых данных (байт 34 в BMP заголовке)
            f.seek(34)
            # Считать 4 байта для размера растровых данных
            raster_size = struct.unpack('<I', f.read(4))[0]

            # Если raster_size = 0 (что бывает в некоторых BMP), пересчитать размер вручную.
            # Формула учитывает выравнивание строк по 4 байта: ((ширина * глубина_цвета_в_байтах + 3) & ~3) * высота
            # Для 24-битного BMP (3 байта на пиксель): (ширина * 3 + 3) & ~3
            if raster_size == 0:
                raster_size = ((width * 3 + 3) & ~3) * height

            # Общее количество пикселей в изображении
            pixel_count = width * height
            return {
                'file_type': 'BM',  # Тип файла для BMP
                'comment': '',  # В BMP нет стандартного поля для комментария в этом месте
                'raster_size': raster_size,
                'data_offset': data_offset,
                'width': width,
                'height': height,
                'pixel_count': pixel_count
            }

    def __apply_color_dodge(self, base, blend):
        """
        Применяет алгоритм наложения Color Dodge к двум изображениям.
        Формула: Result = Base / (255 - Blend + 1).
        Осветляет базовое изображение, используя значения пикселей накладываемого изображения.

        Args:
            base (numpy.ndarray): Массив пикселей базового изображения (float32).
            blend (numpy.ndarray): Массив пикселей накладываемого изображения (float32).

        Returns:
            numpy.ndarray: Результирующий массив пикселей после применения Color Dodge (uint8).
        """
        # Предотвращаем деление на ноль: если blend_pixel == 255, 255 - blend + 1 будет 1.
        # Добавляем 1 к 255 - blend, чтобы избежать деления на ноль, если blend = 255.
        # Значения blend_pixel = 255 (белый) не меняют базовое изображение.
        # Значения blend_pixel = 0 (черный) делают базовое изображение полностью белым.
        result = base / (255 - blend + 1)
        # Ограничение значений, чтобы избежать переполнения (значения не должны превышать 255).
        result[result > 255] = 255
        return np.uint8(result)

    def __modify_image(self, base_img_path, blend_img_path, output_path):
        """
        Открывает два BMP-изображения, применяет к ним эффект Color Dodge
        и сохраняет результат в новый BMP-файл.

        Args:
            base_img_path (str): Путь к базовому BMP-изображению.
            blend_img_path (str): Путь к BMP-изображению для наложения.
            output_path (str): Путь для сохранения результирующего BMP-файла.
        """
        # Открытие и преобразование изображений в формат RGB для единообразия.
        base_img = Image.open(base_img_path).convert('RGB')
        blend_img = Image.open(blend_img_path).convert('RGB')

        # Изменить размер blend_img, чтобы он соответствовал размеру base_img.
        # Это необходимо для корректного попиксельного наложения.
        # Image.LANCZOS - высококачественный фильтр для изменения размера.
        blend_img = blend_img.resize(base_img.size, Image.LANCZOS)

        # Преобразовать изображения в массивы numpy для эффективных манипуляций с пикселями.
        # Используем float32 для предотвращения потери точности при делении.
        base_array = np.array(base_img, dtype=np.float32)
        blend_array = np.array(blend_img, dtype=np.float32)

        # Применить алгоритм Color Dodge к массивам пикселей.
        result_array = self.__apply_color_dodge(base_array, blend_array)
        # Преобразовать результирующий массив обратно в объект изображения PIL.
        result_img = Image.fromarray(result_array.astype('uint8'))
        # Сохранить модифицированное изображение в указанный путь.
        result_img.save(output_path)

    def __save_to_fio(self, output_path, data, header):
        """
        Сохраняет растровые данные изображения и заголовок в пользовательский формат .FIO.

        Args:
            output_path (str): Путь для сохранения файла .FIO.
            data (bytes): Бинарные растровые данные изображения.
            header (dict): Словарь с информацией о заголовке для записи.
        """
        with open(output_path, 'wb') as f:
            # Упаковать поля заголовка в бинарный формат согласно FIO_HEADER_FORMAT.
            # .encode('utf-8') для строк, .ljust(16, '\x00') для выравнивания комментария.
            header_data = struct.pack(
                self.FIO_HEADER_FORMAT,
                header['file_type'].encode('utf-8'),
                header['comment'].ljust(16, '\x00').encode('utf-8'),
                header['raster_size'],
                header['data_offset'],
                header['width'],
                header['height'],
                header['pixel_count']
            )
            # Записать упакованный заголовок в файл.
            f.write(header_data)
            # Записать сырые растровые данные изображения после заголовка.
            f.write(data)

    def open_fio(self, file_path, output_bmp_path):
        """
        Открывает файл пользовательского формата .FIO (здесь .LGO),
        выводит его заголовок и сохраняет растровые данные в BMP-файл.

        Args:
            file_path (str): Путь к файлу .FIO.
            output_bmp_path (str): Путь для сохранения извлеченного BMP-файла.
        """
        with open(file_path, 'rb') as f:
            # Считать данные заголовка из файла .FIO.
            header_data = f.read(self.HEADER_SIZE)
            # Распаковать бинарные данные заголовка согласно FIO_HEADER_FORMAT.
            header = struct.unpack(self.FIO_HEADER_FORMAT, header_data)

            # Вывод информации из заголовка для пользователя.
            print('Тип файла:', header[0].decode('utf-8'))
            print('Комментарий:', header[1].decode('utf-8').strip('\x00'))  # Удаляем нулевые байты
            print('Размер растра:', header[2])
            print('Смещение данных:', header[3])
            print('Ширина:', header[4])
            print('Высота:', header[5])
            print('Количество пикселей:', header[6])

            # Перейти к смещению данных растра, указанному в заголовке.
            f.seek(header[3])
            # Считать растровые данные согласно размеру, указанному в заголовке.
            raster_data = f.read(header[2])

            # Проверка и коррекция размера данных:
            # Ожидаемый размер для RGB изображения = ширина * высота * 3 байта/пиксель.
            expected_size = header[4] * header[5] * 3

            # Если считанные данные меньше ожидаемого размера, дополняем их нулевыми байтами.
            if len(raster_data) < expected_size:
                print(f"Размер данных меньше ожидаемого! Добавляем {expected_size - len(raster_data)} байт.")
                raster_data += b'\x00' * (expected_size - len(raster_data))
            # Если считанные данные больше ожидаемого размера, обрезаем их.
            elif len(raster_data) > expected_size:
                print(f"Размер данных больше ожидаемого! Обрезаем на {len(raster_data) - expected_size} байт.")
                raster_data = raster_data[:expected_size]

            # Создание объекта изображения PIL из бинарных растровых данных.
            # 'RGB' указывает на формат пикселей, (width, height) - размеры.
            img = Image.frombytes('RGB', (header[4], header[5]), raster_data)
            # Сохранение полученного изображения в BMP-файл.
            img.save(output_bmp_path)
            print(f"Изображение сохранено в {output_bmp_path}")

            # Открытие сохраненного BMP для визуализации (показывает изображение в стандартном просмотрщике).
            img.show()
            print("Изображение визуализировано.")

    def open_bmp(self, base_img_path, blend_img_path):
        """
        Открывает два BMP-изображения, обрабатывает их (применяя Color Dodge),
        сохраняет результат в BMP и пользовательский формат .FIO (здесь .LGO).

        Args:
            base_img_path (str): Путь к базовому BMP-изображению.
            blend_img_path (str): Путь к BMP-изображению для наложения.
        """
        # Пути для сохранения результирующих файлов.
        output_fio_path = 'result.LGO'
        output_bmp_path = 'result.bmp'

        # Открыть и отобразить исходные изображения для предварительного просмотра.
        base_img = Image.open(base_img_path)
        base_img.show()

        blend_img = Image.open(blend_img_path)
        blend_img.show()

        # Вывести информацию о заголовке базового изображения, используя приватный метод.
        base_header_info = self.__read_bmp_header(base_img_path)
        print("\nИнформация о заголовке базового изображения:")
        print('Тип файла:', base_header_info['file_type'])
        print('Комментарий:', base_header_info['comment'])
        print('Размер растра:', base_header_info['raster_size'])
        print('Смещение данных:', base_header_info['data_offset'])
        print('Ширина:', base_header_info['width'])
        print('Высота:', base_header_info['height'])
        print('Количество пикселей:', base_header_info['pixel_count'])

        # Вывести информацию о заголовке изображения для наложения.
        blend_header_info = self.__read_bmp_header(blend_img_path)
        print("\nИнформация о заголовке изображения для наложения:")
        print('Тип файла:', blend_header_info['file_type'])
        print('Комментарий:', blend_header_info['comment'])
        print('Размер растра:', blend_header_info['raster_size'])
        print('Смещение данных:', blend_header_info['data_offset'])
        print('Ширина:', blend_header_info['width'])
        print('Высота:', blend_header_info['height'])
        print('Количество пикселей:', blend_header_info['pixel_count'])

        # Изменить и сохранить изображение с использованием Color Dodge.
        # Результат сохраняется во временный BMP-файл, который затем будет использован.
        self.__modify_image(base_img_path, blend_img_path, output_bmp_path)
        # Открыть результирующее изображение для получения его растровых данных.
        result_img = Image.open(output_bmp_path)
        # Получить сырые байты пикселей из результирующего изображения.
        raster_data = result_img.tobytes()

        # Создать словарь с информацией для заголовка файла .FIO (здесь .LGO).
        fio_header = {
            'file_type': 'LGO',  # Пользовательский тип файла
            'comment': 'Color Dodge',  # Комментарий, описывающий примененную операцию
            'raster_size': len(raster_data),  # Размер растровых данных в байтах
            'data_offset': self.HEADER_SIZE,  # Смещение данных после заголовка
            'width': result_img.width,
            'height': result_img.height,
            'pixel_count': result_img.width * result_img.height
        }
        # Сохранить результирующие растровые данные и заголовок в файл .FIO.
        self.__save_to_fio(output_fio_path, raster_data, fio_header)

        # Сохранить результат в формате BMP (если еще не сохранен или для подтверждения)
        # и отобразить его для пользователя.
        result_img.save(output_bmp_path)
        result_img.show()  # Отображение окончательного результата
        print(f"Обработанное изображение сохранено как '{output_bmp_path}' и '{output_fio_path}'.")
