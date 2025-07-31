import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.LinkedHashSet;
import java.util.Set;

public class task_1 {
    public static void deleteDuplicate(String file) {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(file))) {
            String line;
            Set<String> set = new LinkedHashSet<>();
            while ((line = bufferedReader.readLine()) != null) {
                set.addAll(Arrays.asList(line.split(" ")));
            }
            System.out.println(String.join(" ", set));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        System.out.println("\t\tarticle_1.txt\n");
        deleteDuplicate("article_1.txt");
        System.out.println("\n\t\tarticle_2.txt\n");
        deleteDuplicate("article_2.txt");
    }
}