import task_2.FloppyDiskSimulator;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String filename = "src/task_2/files.txt"; // Имя файла с командами

        FloppyDiskSimulator simulator = new FloppyDiskSimulator();

        try {
            System.out.println("== Загрузка данных из файла ==");
            simulator.loadFromFile(filename);
        } catch (IOException e) {
            System.out.println("Ошибка при чтении файла: " + e.getMessage());
            return;
        }

        System.out.println("\n== Текущее состояние диска ==");
        simulator.printStatus();
    }
}
