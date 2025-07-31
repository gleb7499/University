import java.util.Scanner;

public class task_3 {
    public static String swapStringCase(String str) {
        StringBuilder result = new StringBuilder();
        for (char i : str.toCharArray()) {
            result.append(Character.isUpperCase(i) ? Character.toLowerCase(i) : Character.toUpperCase(i));
        }
        return result.toString();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите строку -> ");
        String str = scanner.nextLine();
        System.out.printf("%s", swapStringCase(str));
    }
}
