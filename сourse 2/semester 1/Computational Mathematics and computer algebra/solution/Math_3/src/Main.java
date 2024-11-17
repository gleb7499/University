import java.lang.Math;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        float x0, x1 = 0f, c0, a0, b0;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите a -> ");
        int a = scanner.nextInt();
        System.out.print("Введите b -> ");
        int b = scanner.nextInt();
        System.out.print("Введите c -> ");
        int c = scanner.nextInt();
        System.out.print("Введите d -> ");
        int d = scanner.nextInt();
        System.out.print("Введите a0: ");
        a0 = scanner.nextFloat();
        System.out.print("Введите b0: ");
        b0 = scanner.nextFloat();
        if (form(a0, a, b, c, d)*form_der_2(a0, a, b) > 0)
        {
            System.out.println(form(a0, a, b, c, d)*form_der_2(a0, a, b) + " > 0");
            c0 = a0;
            x0 = b0;
        } else
        {
            System.out.println(form(a0, a, b, c, d)*form_der_2(a0, a, b) + " <= 0");
            c0 = b0;
            x0 = a0;
        }
        System.out.println("x0 = " + x0 + "\t\tc = " + c0);
        int i = 1;
        boolean flag = false;
        do
        {
            if (flag)
            {
                x0 = x1;
            }
            x1 = x0 - ((form(x0, a, b, c, d)*(c0-x0)) / (form(c0, a, b, c, d) - form(x0, a, b, c, d)));
            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("x" + i + ": " + x1);
            flag = true;
            ++i;
        } while (Math.abs(x1 - x0) > 0.001);
        System.out.println("Тогда x = " + (Math.round(x1 * 100.0) / 100.0) + ", т. к. |x" + (i-1) + " - x" + (i-2) + "| = " + Math.abs(x1 - x0) + " < 0.001");
    }
    public static float form(float x, int a, int b, int c, int d)
    {
        return a*(float)Math.pow(x, 3) + b*(float)Math.pow(x, 2) + c*x + d;
    }
    public static float form_1(float x, int a, int b, int c)
    {
        return 3*a*(float)Math.pow(x, 2) + 2*b*x + c;
    }
    public static float form_der_2(float x, int a, int b)
    {
        return 6*a*x + 2*b;
    }
}