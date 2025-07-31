package task_3;

public class Main {
    public static void main(String[] args) {
        Faculty faculty = new Faculty("Информатика");
        Teacher teacher = new Teacher("Сидоров С.С.");

        Applicant a1 = new Applicant("Алексей");
        a1.addExam(new Exam("Математика", 70, teacher));
        a1.addExam(new Exam("Физика", 80, teacher));

        Applicant a2 = new Applicant("Никита");
        a2.addExam(new Exam("Математика", 50, teacher));
        a2.addExam(new Exam("Физика", 55, teacher));

        faculty.registerApplicant(a1);
        faculty.registerApplicant(a2);

        faculty.showAdmittedApplicants();
    }
}
