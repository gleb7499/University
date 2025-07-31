package task_1;

import java.time.LocalDate;

// Демонстрация
public class Main {
    public static void main(String[] args) {
        Catalog cat = new Catalog();
        cat.addEntry("Иванов И.И.", "Java в примерах", LocalDate.of(2025, 5, 1));
        cat.addEntry("Петров П.П.", "Алгоритмы", LocalDate.now());
        cat.printHistory();
        cat.removeLast();
        cat.printHistory();
    }
}