package task_2;

public class FileEntry {
    String name;
    String extension;
    int size; // in KB
    int startPosition;

    public FileEntry(String name, String extension, int size, int startPosition) {
        this.name = name;
        this.extension = extension;
        this.size = size;
        this.startPosition = startPosition;
    }

    @Override
    public String toString() {
        return name + "." + extension + " [" + size + "KB] at " + startPosition;
    }
}
