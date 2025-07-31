package task_1;

import java.util.Arrays;

public class Plenty {
    private final int[] plenty;
    private int count = 0;

    public Plenty(int size) {
        if (size < 1) {
            throw new IllegalArgumentException("Размер списка должен быть >= 1");
        }
        this.plenty = new int[size];
    }

    public void push_back(int element) {
        if (count < plenty.length) {
            plenty[count++] = element;
        } else {
            System.out.println("В множестве нет места!");
        }
    }

    public int pop_back() {
        if (count == 0) {
            throw new IllegalStateException("Множество пусто!");
        }
        int result = plenty[--count];
        plenty[count] = 0;
        return result;
    }

    public Plenty concat(Plenty... sets) {
        int totalSize = this.count;
        for (Plenty set : sets) {
            totalSize += set.count;
        }

        Plenty result = new Plenty(totalSize);

        for (int i = 0; i < count; i++) {
            result.push_back(plenty[i]);
        }

        for (Plenty set : sets) {
            for (int i = 0; i < set.count; i++) {
                result.push_back(set.plenty[i]);
            }
        }

        return result;
    }

    @Override
    public String toString() {
        return Arrays.toString(Arrays.copyOf(plenty, count));
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        Plenty other = (Plenty) o;
        return count == other.count && Arrays.equals(Arrays.copyOf(plenty, count), Arrays.copyOf(other.plenty, other.count));
    }
}
