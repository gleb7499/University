package task_2;

public class Main {
    public static void main(String[] args) {
        Page page = new Page();
        page.addPara(new Paragraph("Первый абзац."));
        page.addPara(new Paragraph("Второй абзац, чуть длиннее."));
        page.printPage();
    }
}
