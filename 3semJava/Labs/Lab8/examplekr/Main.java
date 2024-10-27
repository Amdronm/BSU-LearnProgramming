package examplekr;

import java.io.File;

public class Main {
    public static void main(String[] args) {
        Data<Double> data = new Data<>();
        try {
            data.parseFromFile(new File("3semJava\\Labs\\Lab8\\examplekr\\in.txt"), Double::parseDouble);
            System.out.println(data.toString());
        } catch (Exception e) {
            System.out.println("Something wrong: " + e.getMessage());
        }
    }
}