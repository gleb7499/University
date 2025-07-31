package task_1;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Catalog {
    private final List<Entry> history = new ArrayList<>();

    public static class Entry {
        private final String reader;
        private final String bookTitle;
        private final LocalDate date;

        public Entry(String reader, String bookTitle, LocalDate date) {
            this.reader = reader;
            this.bookTitle = bookTitle;
            this.date = date;
        }

        @Override
        public String toString() {
            return date + ": " + reader + " взял \"" + bookTitle + "\"";
        }
    }

    public void addEntry(String r, String t, LocalDate d) {
        history.add(new Entry(r, t, d));
    }

    public void removeLast() {
        if (!history.isEmpty()) history.removeLast();
    }

    public void printHistory() {
        history.forEach(System.out::println);
    }
}
