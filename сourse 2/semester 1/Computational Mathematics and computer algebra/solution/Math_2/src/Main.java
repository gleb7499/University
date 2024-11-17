import java.lang.Math;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите a -> ");
        int a = scanner.nextInt();
        System.out.print("Введите b -> ");
        int b = scanner.nextInt();
        System.out.print("Введите c -> ");
        int c = scanner.nextInt();
        System.out.print("Введите d -> ");
        int d = scanner.nextInt();
        System.out.print("Введите x0 -> ");
        float x0 = scanner.nextFloat();
        float x1 = 0f;
        int i = 1;
        boolean flag = false;
        do
        {
            if (flag)
            {
                x0 = x1;
            }
            x1 = (a*(float)Math.pow(x0, 3) + b*(float)Math.pow(x0, 2) + d) / (-c);
            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("x" + i + ": " + x1);
            flag = true;
            ++i;
        } while (Math.abs(x1 - x0) > 0.001);
        System.out.println("Тогда x = " + (Math.round(x0 * 100.0) / 100.0) + ", т. к. |x" + (i-1) + " - x" + (i-2) + "| = " + Math.abs(x1 - x0) + " < 0.001");
    }
}