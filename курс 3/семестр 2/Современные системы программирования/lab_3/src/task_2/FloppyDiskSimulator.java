package task_2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class FloppyDiskSimulator {
    private static final int DISK_SIZE = 1440;
    private final List<FileEntry> files = new ArrayList<>();
    private final List<FreeSpace> freeSpaces = new ArrayList<>();

    public FloppyDiskSimulator() {
        freeSpaces.add(new FreeSpace(0, DISK_SIZE));
    }

    public void addFile(String name, String extension, int size) {
        for (int i = 0; i < freeSpaces.size(); i++) {
            FreeSpace space = freeSpaces.get(i);
            if (space.size >= size) {
                files.add(new FileEntry(name, extension, size, space.start));
                if (space.size == size) {
                    freeSpaces.remove(i);
                } else {
                    space.start += size;
                    space.size -= size;
                }
                System.out.println("Added: " + name + "." + extension);
                return;
            }
        }

        System.out.println("ERROR: Not enough space for " + name + "." + extension);
    }

    public void deleteFile(String fullName) {
        for (int i = 0; i < files.size(); i++) {
            FileEntry f = files.get(i);
            if ((f.name + "." + f.extension).equals(fullName)) {
                freeSpaces.add(new FreeSpace(f.startPosition, f.size));
                files.remove(i);
                mergeFreeSpaces();
                System.out.println("Deleted: " + fullName);
                return;
            }
        }
        System.out.println("ERROR: File not found - " + fullName);
    }

    private void mergeFreeSpaces() {
        freeSpaces.sort(Comparator.comparingInt(a -> a.start));
        for (int i = 0; i < freeSpaces.size() - 1; ) {
            FreeSpace current = freeSpaces.get(i);
            FreeSpace next = freeSpaces.get(i + 1);
            if (current.start + current.size == next.start) {
                current.size += next.size;
                freeSpaces.remove(i + 1);
            } else {
                i++;
            }
        }
    }

    public void printStatus() {
        System.out.println("\nFiles on disk:");
        for (FileEntry file : files) {
            System.out.println("  " + file);
        }
        System.out.println("Free spaces:");
        for (FreeSpace space : freeSpaces) {
            System.out.println("  " + space);
        }
        System.out.println("---------------");
    }

    public void loadFromFile(String filename) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line;
        while ((line = reader.readLine()) != null) {
            String[] parts = line.trim().split(" ");
            if (parts[0].equalsIgnoreCase("ADD")) {
                String[] nameParts = parts[1].split("\\.");
                String name = nameParts[0];
                String ext = nameParts[1];
                int size = Integer.parseInt(parts[2]);
                addFile(name, ext, size);
            } else if (parts[0].equalsIgnoreCase("DELETE")) {
                deleteFile(parts[1]);
            }
        }
        reader.close();
    }
}

