package task_2;

import java.util.ArrayList;
import java.util.List;

public class Page {
    private final List<Paragraph> paras = new ArrayList<>();

    public void addPara(Paragraph p) {
        paras.add(p);
    }

    public void removePara(int idx) {
        paras.remove(idx);
    }

    public void printPage() {
        for (int i = 0; i < paras.size(); i++) {
            System.out.printf("Абзац %d: ", i + 1);
            paras.get(i).print();
        }
    }
}
