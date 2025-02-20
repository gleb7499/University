import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import java.awt.*;
import java.lang.Math;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        float x0 = 0f, x1 = 0f, a1 = 0f, b1 = 0f;
        final float E = 0.01f;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите a -> ");
        int a = scanner.nextInt();
        System.out.print("Введите b -> ");
        int b = scanner.nextInt();
        System.out.print("Введите c -> ");
        int c = scanner.nextInt();
        System.out.print("Введите d -> ");
        int d = scanner.nextInt();
        System.out.print("Введите a1 -> ");
        float a0 = scanner.nextFloat();
        System.out.print("Введите b1 -> ");
        float b0 = scanner.nextFloat();
        DefaultTableModel model = new DefaultTableModel();
        model.addColumn("k");
        model.addColumn("ak");
        model.addColumn("bk");
        model.addColumn("xk");
        model.addColumn("знак");
        int i = 1;
        boolean flag = false;
        boolean zn;
        do {
            if (flag)
            {
                b0 = b1;
                a0 = a1;
                x1 = x0;
            }
            x0 = (a0 + b0) / 2;
            zn = form(x0, a, b, c, d) * form(a0, a, b, c, d) < 0;
            model.addRow(new Object[]{i, a0, b0, x0, zn ? "-" : "+"});
            if (zn)
            {
                b1 = x0;
                a1 = a0;
            } else
            {
                b1 = b0;
                a1 = x0;
            }
            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("x" + i + " = " + x0 + "\tf(x" + i + ") = " + form(x0, a, b, c, d) + "\tf(a" + i + ") * f(x" + i + ") " + (zn ? "< 0\tb" + (i+1) + " = x" + i + ", a" + (i+1) + " = a" + i : ">=" + " 0\ta" + (i+1) + " = " + "x" + i + ", b" + (i+1) + " = " + "b" + i));
            flag = true;
            ++i;
        } while (Math.abs(x1 - x0) > E);
        System.out.println("[Таблица!]\nТогда x = " + (Math.round(x0 * 100.0) / 100.0) + ", т. к. |x" + (i-1) + " - x" + (i-2) + "| = " + Math.abs(x1 - x0) + " < " + E);
        JTable table = new JTable(model);
        JTableHeader header = table.getTableHeader();
        header.setFont(new Font("Times New Roman ", Font.BOLD, 35));
        table.setFont(new Font("Times New Roman", Font.PLAIN, 35));
        table.setRowHeight(35);
        JScrollPane scrollPane = new JScrollPane(table);
        JFrame frame = new JFrame();
        frame.setTitle("Таблица");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.add(scrollPane);
        frame.pack();
        frame.setVisible(true);
    }
    public static float form(float x, int a, int b, int c, int d)
    {
        return a*(float)Math.pow(x, 3) + b*(float)Math.pow(x, 2) + c*x + d;
    }
}