package task_3;

import java.util.ArrayList;
import java.util.List;

class Applicant {
    private final String name;
    private final List<Exam> exams = new ArrayList<>();

    public Applicant(String name) {
        this.name = name;
    }

    public void addExam(Exam exam) {
        exams.add(exam);
    }

    public double getAverageScore() {
        return exams.stream().mapToInt(Exam::getScore).average().orElse(0);
    }

    public String getName() {
        return name;
    }

    public boolean isAdmitted() {
        return getAverageScore() >= 60;
    }
}