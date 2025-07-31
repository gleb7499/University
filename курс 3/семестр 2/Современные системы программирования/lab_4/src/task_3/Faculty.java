package task_3;

import java.util.ArrayList;
import java.util.List;

class Faculty {
    private final String name;
    private final List<Applicant> applicants = new ArrayList<>();

    public Faculty(String name) {
        this.name = name;
    }

    public void registerApplicant(Applicant applicant) {
        applicants.add(applicant);
    }

    public void showAdmittedApplicants() {
        System.out.println("Зачисленные на факультет " + name + ":");
        for (Applicant a : applicants) {
            if (a.isAdmitted()) {
                System.out.println("- " + a.getName() + ", средний балл: " + a.getAverageScore());
            }
        }
    }
}
