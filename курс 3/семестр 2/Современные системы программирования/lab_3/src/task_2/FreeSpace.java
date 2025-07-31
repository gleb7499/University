package task_2;

public class FreeSpace {
    int start;
    int size;

    public FreeSpace(int start, int size) {
        this.start = start;
        this.size = size;
    }

    @Override
    public String toString() {
        return "Free [" + size + "KB] at " + start;
    }
}

