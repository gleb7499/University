import java.io.*;

public class Split {
    public static void main(String[] args) throws IOException {
        int numLines = 10;
        int numBytes = -1;
        boolean useNumericSuffix = false;
        String inputFile = "-";
        String outputPrefix = "x";

        for (int i = 0; i < args.length; i++) {
            switch (args[i]) {
                case "-l":
                case "--lines":
                    numLines = Integer.parseInt(args[++i]);
                    break;
                case "-b":
                case "--bytes":
                    numBytes = parseSize(args[++i]);
                    break;
                case "-d":
                case "--numericsuffixes":
                    useNumericSuffix = true;
                    break;
                default:
                    if (inputFile.equals("-")) {
                        inputFile = args[i];
                    } else {
                        outputPrefix = args[i];
                    }
                    break;
            }
        }

        BufferedReader reader;
        if (inputFile.equals("-")) {
            reader = new BufferedReader(new InputStreamReader(System.in));
        } else {
            reader = new BufferedReader(new FileReader(inputFile));
        }

        if (numBytes > 0) {
            splitByBytes(reader, outputPrefix, numBytes, useNumericSuffix);
        } else {
            splitByLines(reader, outputPrefix, numLines, useNumericSuffix);
        }

        reader.close();
    }

    private static void splitByLines(BufferedReader reader, String outputPrefix, int numLines, boolean useNumericSuffix) throws IOException {
        String line;
        int fileIndex = 0;
        int lineCount = 0;
        BufferedWriter writer = null;

        while ((line = reader.readLine()) != null) {
            if (lineCount % numLines == 0) {
                if (writer != null) writer.close();
                writer = new BufferedWriter(new FileWriter(outputPrefix + getSuffix(fileIndex++, useNumericSuffix) + ".txt"));
            }
            writer.write(line);
            writer.newLine();
            lineCount++;
        }

        if (writer != null) writer.close();
    }

    private static void splitByBytes(BufferedReader reader, String outputPrefix, int numBytes, boolean useNumericSuffix) throws IOException {
        char[] buffer = new char[numBytes];
        int fileIndex = 0;
        int bytesRead;
        BufferedWriter writer = null;

        while ((bytesRead = reader.read(buffer)) != -1) {
            if (writer != null) writer.close();
            writer = new BufferedWriter(new FileWriter(outputPrefix + getSuffix(fileIndex++, useNumericSuffix) + ".txt"));
            writer.write(buffer, 0, bytesRead);
        }

        if (writer != null) writer.close();
    }

    private static String getSuffix(int fileIndex, boolean useNumericSuffix) {
        if (useNumericSuffix) {
            return String.format("%02d", fileIndex);
        } else {
            return String.valueOf((char) ('a' + fileIndex / 26)) + String.valueOf((char) ('a' + fileIndex % 26));
        }
    }

    private static int parseSize(String size) {
        char lastChar = size.charAt(size.length() - 1);
        int factor;
        switch (lastChar) {
            case 'b':
                factor = 1;
                break;
            case 'k':
                factor = 1024;
                break;
            case 'm':
                factor = 1024 * 1024;
                break;
            default:
                return Integer.parseInt(size);
        }
        return Integer.parseInt(size.substring(0, size.length() - 1)) * factor;
    }
}
