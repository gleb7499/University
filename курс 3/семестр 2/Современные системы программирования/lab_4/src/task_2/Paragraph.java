package task_2;

public class Paragraph {
    private final String text;

    public Paragraph(String t) {
        text = t;
    }

    public void print() {
        System.out.println(text);
    }

    public int length() {
        return text.length();
    }
}