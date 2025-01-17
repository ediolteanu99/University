package com.poo.labvisitor.task2;

import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;

/**
 * Counter for java files of a given directory using java.nio API
 */
public class JavaFilesVisitor extends SimpleFileVisitor<Path> {

    private ArrayList<Path> javaFiles = new ArrayList<>();

    public final ArrayList<Path> getJavaFiles() {
        return javaFiles;
    }

    // TODO - override the visitFile(Path file, BasicFileAttributes attr) method of the SimpleFileVisitor
    // add to javaFiles all the Java related files: the ones with .java and .class extensions

    @Override
    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
        if ((file != null) && ((file.toString().endsWith(".java")) || (file.toString().endsWith(".class")))) {
            javaFiles.add(file);
        }
        return FileVisitResult.CONTINUE;
    }

    public static void main(String[] args) {

        Path startingDir = Paths.get(".");
        JavaFilesVisitor filesVisitor = new JavaFilesVisitor();

        // TODO
        // use Files.walkFileTree
        // obtain the list of files and print some info about them (e.g. size and path)
        try {
            Files.walkFileTree(startingDir, filesVisitor);
        } catch (IOException exception) {
            exception.printStackTrace();
        }

        for (Path path : filesVisitor.getJavaFiles()) {
            System.out.println(path.getFileName());
            System.out.println(path.toFile().length());
            System.out.println();
        }
    }
}
