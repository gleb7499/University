function solv1() {
    var exit = 0;
    while (exit != 1) {
        var firstnum = prompt("Введите число 1 (Q - для выхода): ");
        if (firstnum.toLowerCase() === "q") {
            exit = 1;
            break;
        }
        if (isNaN(firstnum)) {
            alert("Введенное значение не является числом. Пожалуйста, введите снова.");
            continue;
        }
        let secondnum = prompt("Введите число 2 (Q - для выхода): ");
        if (secondnum.toLowerCase() === "q") {
            exit = 1;
            break;
        }
        if (isNaN(secondnum)) {
            alert("Введенное значение не является числом. Пожалуйста, введите снова.");
            continue;
        }

        if (firstnum > secondnum) {
            alert("Первое число (" + firstnum + ") больше второго (" + secondnum + ").");
        }
        else if (firstnum < secondnum) {
            alert("Второе число (" + secondnum + ") больше первого (" + firstnum + ").");
        }
        else if (firstnum == secondnum) {
            alert("Числа равны (" + firstnum + ").");
        }
    }
}
function solv2() {
    try {
        var floorCount = prompt("Введите количество этажей (от 1 до 20):");
        var entranceCount = prompt("Введите количество подъездов (от 1 до 15):");
        var apartmentsPerFloor = prompt("Введите количество квартир на лестничной площадке (от 1 до 5): ");
        var requestedApartment = prompt("Введите номер квартиры:");
        if (floorCount < 1 || floorCount > 20 || entranceCount < 1 || entranceCount > 15 || apartmentsPerFloor < 1 || apartmentsPerFloor > 5) {
            throw "Ошибка: некорректные значения характеристик дома.";
        }
        var totalApartments = floorCount * entranceCount * apartmentsPerFloor;
        if (requestedApartment < 1 || requestedApartment > totalApartments) {
            throw "Ошибка: запрашиваемая квартира не существует в этом доме.";
        }
        var entranceNumber = Math.ceil(requestedApartment / (apartmentsPerFloor * floorCount));
        alert("Квартира находится в подъезде номер: " + entranceNumber);
    }
    catch (error) {
        alert(error);
    }
}
function solv() {
    try {
        var month = prompt("Введите номер месяца (от 1 до 12):");
        var day = prompt("Введите число в этом месяце (от 1 до 31):");
        if (month < 1 || month > 12 || day < 1 || day > 31 || isNaN(month) || isNaN(day)) {
            throw ("Ошибка: введены некорректные значения.");
        }
        else {
            var date = new Date(2022, month - 1, day);
            var dayOfWeek = date.getDay();
            var daysOfWeek = ["воскресенье", "понедельник", "вторник", "среда", "четверг", "пятница", "суббота"];
            var dayName = daysOfWeek[dayOfWeek];
            alert("День недели для " + day + " числа " + month + " месяца - " + dayName + ".");
        }
    }
    catch (error) {
        alert(error)
    }
}
function solv4() {
    try {
        var num1 = parseInt(prompt("Введите первое число: "));
        var num2 = parseInt(prompt("Введите второе число: "));
        if (isNaN(num1) || isNaN(num2)) {
            throw ("Введено не число")
        }
        if (num1 % 2 == 0 && num2 % 2 == 0) {
            alert("Произведение чисел равно: " + (num1 * num2))
            return num1 * num2;
        }
        else if (num1 % 2 !== 0 && num2 % 2 !== 0) {
            alert("Сумма чисел равна: " + (num1 + num2));
            return num1 + num2
        }
        else if (num1 % 2 !== 0 && num2 % 2 == 0) {
            alert("Четное число: " + num2);
            return num2
        }
        else {
            alert("Нечетное число: " + num2)
            return num2
        }
    }
    catch (error) {
        alert(error);
    }
}
function solv5() {
    try {
        function sum() {
            var numbers = [];
            function addNumber(number) {
                if (isNaN(number)) {
                    throw ("Введено не число");
                }
                numbers.push(number);
            }
            function calculateSum() {
                var sum = 0;
                for (var i = 0; i < numbers.length; i++) {
                    sum += numbers[i];
                }
                return sum;
            }
            return {
                addNumber: addNumber,
                calculateSum: calculateSum
            };
        }
        var calculator = sum();
        var amount = parseInt(prompt("Введите количество чисел: "));
        for (var i = 0; i < amount; i++) {
            var number = parseInt(prompt("Введите число " + (i + 1) + ": "));
            calculator.addNumber(number);
        }
        var result = calculator.calculateSum();
        alert("Сумма введенных чисел: " + result);
    } catch (error) {
        alert(error);
    }
}
function solv6() {
    try {
        var start = parseInt(prompt("Введите начальное значение: "));
        var finish = parseInt(prompt("Введите конечное значение: "));
        var step = parseInt(prompt("Введите шаг (по умолчанию 1): ") || 1);
        if (step == 0 || ((start > finish) && step > 0)) {
            throw ("Некорректные значения");
        }
        var result = [];
        if (step > 0) {
            for (var i = start; i <= finish; i += step) {
                result.push(i);
            }
        }
        else {
            for (var i = start; i >= finish; i += step) {
                result.push(i);
            }
        }
        alert(result);
    } catch (error) {
        alert(error);
    }
}
function solv7() {
    function createMatrix(rows, columns) {
        var matrix = [];
        for (var i = 0; i < rows; i++) {
            var row = [];
            for (var j = 0; j < columns; j++) {
                row.push(Math.floor(Math.random() * 101));
            }
            matrix.push(row);
        }
        return matrix;
    }
    function sumMatrices(matrix1, matrix2) {
        var result = [];
        for (var i = 0; i < matrix1.length; i++) {
            var row = [];
            for (var j = 0; j < matrix1[i].length; j++) {
                row.push(matrix1[i][j] + matrix2[i][j]);
            }
            result.push(row);
        }
        return result;
    }
    try {
        var rows = parseInt(prompt("Введите количество строк матрицы: "));
        var columns = parseInt(prompt("Введите количество столбцов матрицы: "));
        var matrix1 = createMatrix(rows, columns);
        var matrix1String = "Первая матрица:\n";
        for (var i = 0; i < matrix1.length; i++) {
            matrix1String += matrix1[i].join(" ") + "\n";
        }
        alert(matrix1String);
        var matrix2 = createMatrix(rows, columns);
        var matrix2String = "Вторая матрица:\n";
        for (var i = 0; i < matrix2.length; i++) {
            matrix2String += matrix2[i].join(" ") + "\n";
        }
        alert(matrix2String);
        var sum = sumMatrices(matrix1, matrix2);
        var sumString = "Сумма двух матриц:\n";
        for (var i = 0; i < sum.length; i++) {
            sumString += sum[i].join(", ") + "\n";
        }
        alert(sumString);
    } catch (error) {
        alert(error);
    }
}
function solv8() {
    function mergeUniqueArrays(...arrays) {
        for (var i = 0; i < arrays.length; i++) {
            if (!Array.isArray(arrays[i]) || arrays[i].some(Array.isArray)) {
                throw (`Функция работает только с одномерными массивами. Размерность массива ${i + 1}: ${arrays[i].length}`);
            }
        }
        const elementCount = {};
        arrays.forEach(array => {
            array.forEach(element => {
                if (elementCount[element]) {
                    elementCount[element]++;
                } else {
                    elementCount[element] = 1;
                }
            });
        });
        return Object.keys(elementCount).filter(key => elementCount[key] === 1).map(Number);
    }
    try {
        var array1 = prompt("Введите первый массив: ");
        var array2 = prompt("Введите второй массив: ");
        var inputArray1 = JSON.parse(array1);
        var inputArray2 = JSON.parse(array2);
        var result1 = mergeUniqueArrays(inputArray1, inputArray2);
        alert(result1);
    }
    catch (error) {
        alert(error)
    }
}
function solv9() {
    function flattenArray(arr) {
        if (!Array.isArray(arr)) {
            throw ("Ошибка: Переданный аргумент не является массивом.");
        }
        function flattenHelper(arr, result) {
            arr.forEach(element => {
                if (Array.isArray(element)) {
                    flattenHelper(element, result);
                } else {
                    result.push(element);
                }
            });
        }
        var flattenedArray = [];
        flattenHelper(arr, flattenedArray);
        return flattenedArray;
    }
    try {
        var array = prompt("Введите массив: ");
        var inputArray = JSON.parse(array)
        var result = flattenArray(inputArray);
        alert(result);
    }
    catch (error) {
        alert(error)
    }
}
function solv10() {
    function removeDuplicates(input, repeats) {
        if (!Array.isArray(input)) {
            input = input.split('');
        }
        var count = {};
        input.forEach(element => {
            count[element] = (count[element] || 0) + 1;
        });
        var result = [];
        for (var key in count) {
            if (count.hasOwnProperty(key) && count[key] < repeats) {
                result.push(key);
            }
        }
        return result;
    }
    var firstResult = removeDuplicates([1, 2, 1, 5, 1, 5, 1, 4], 3);
    alert(firstResult);
    var secondResult = removeDuplicates("miru mir", 2);
    alert(secondResult);
}