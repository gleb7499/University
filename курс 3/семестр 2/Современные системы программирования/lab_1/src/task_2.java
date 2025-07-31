import java.util.Random;
import java.util.Scanner;

public class task_2 {
    public static double[][] random(double a, double b, int size) {
        Random random = new Random();
        double[][] matrix = new double[size][];
        for (int i = 0; i < size; ++i) {
            double[] row = new double[size];
            for (int g = 0; g < size; ++g) {
                row[g] = random.nextDouble(b - a) + a;
            }
            matrix[i] = row;
        }
        return matrix;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("MIN диапазона -> ");
        double a = scanner.nextDouble();
        System.out.print("MAX диапазона -> ");
        double b = scanner.nextDouble();
        System.out.print("Размер массива -> ");
        int size = scanner.nextInt();

        double[][] matrix = random(a, b, size);

        for (double[] i : matrix) {
            for (double g : i) {
                System.out.printf("%f\t", g);
            }
            System.out.print("\n");
        }
    }
}
