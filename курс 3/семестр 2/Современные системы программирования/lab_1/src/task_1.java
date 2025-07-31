public class task_1 {
    public static boolean comparison(int[] list) {
        for (int i : list) {
            if (i != list[0]) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        int[] list_1 = {4, 2, 4, 2, 2};
        System.out.println(comparison(list_1) ? "равны" : "не равны");
        int[] list_2 = {2, 2, 2, 2, 2};
        System.out.println(comparison(list_2) ? "равны" : "не равны");
    }
}