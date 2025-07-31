package task_3;

class Exam {
    private final String subject;
    private final int score;
    private final Teacher teacher;

    public Exam(String subject, int score, Teacher teacher) {
        this.subject = subject;
        this.score = score;
        this.teacher = teacher;
    }

    public int getScore() {
        return score;
    }
}
