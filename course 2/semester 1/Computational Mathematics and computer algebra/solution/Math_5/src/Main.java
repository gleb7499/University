import java.lang.Math;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        float x0, x1, x2 = 0, x3 = 0, c0;
        Scanner scanner = new Scanner(System.in);
        int i = 3;
        System.out.print("Введите a -> ");
        int a = scanner.nextInt();
        System.out.print("Введите b -> ");
        int b = scanner.nextInt();
        System.out.print("Введите c -> ");
        int c = scanner.nextInt();
        System.out.print("Введите d -> ");
        int d = scanner.nextInt();
        System.out.print("Введите a0: ");
        float a0 = scanner.nextFloat();
        System.out.print("Введите b0: ");
        float b0 = scanner.nextFloat();
        if (form(a0, a, b, c, d)*form_der_2(a0, a, b) > 0)
        {
            System.out.println(form(a0, a, b, c, d)*form_der_2(a0, a, b) + " > 0");
            x0 = a0;
            c0 = a0;
            x1 = b0;
        } else
        {
            System.out.println(form(a0, a, b, c, d)*form_der_2(a0, a, b) + " <= 0");
            x0 = b0;
            c0 = b0;
            x1 = a0;
        }
        System.out.println("x0 = " + x0 + "\t\tc0 = " + c0 + "\t\tx1 = " + x1);
        boolean flag = false;
        do
        {
            if (flag)
            {
                x0 = x2;
                x1 = x3;
            }
            x2 = x0 - (form(x0, a, b, c, d) / form_der(x0, a, b, c));
            x3 = x1 - ((form(x1, a, b, c, d)*(c0-x1)) / (form(c0, a, b, c, d) - form(x1, a, b, c, d)));
            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("x" + (i-1) + ": " + x2 + "\t\tx" + i + ": " + x3);
            flag = true;
            i += 2;
        } while (Math.abs(x3 - x2) > 0.01);
        System.out.println("|x" + (i-2) + " - x" + (i-3) + "| = " + Math.abs(x3 - x2) + " < 0.01");
        System.out.println("x = " + (Math.round(((x2 + x3) / 2) * 100.0) / 100.0));
    }
    public static float form(float x, int a, int b, int c, int d)
    {
        return a*(float)Math.pow(x, 3) + b*(float)Math.pow(x, 2) + c*x + d;
    }
    public static float form_der(float x, int a, int b, int c)
    {
        return 3*a*(float)Math.pow(x, 2) + 2*b*x + c;
    }
    public static float form_der_2(float x, int a, int b)
    {
        return 6*a*x + 2*b;
    }
}