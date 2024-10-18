package Series;

// Создать абстрактный класс Series (прогрессия) с методами:
//     • вычисления j-го элемента прогрессии (абстрактный);
//     • вычисления суммы прогрессии (не абстрактный);
//     • toString, возвращает строку с элементами прогрессии (не абстрактный);
//     • сохранения прогрессии в файл (не абстрактный);

// Определить производные классы: Liner (арифметическая прогрессия) и Exponential (геометрическая прогрессия). Реализовать вывод элементов и суммы прогрессии в файл.

// Реализовать оконное приложение с удобным интерфейсом (выбор прогрессии, выбор имени файла и т.п.), в т.ч. отображения на окне первых n элементов.

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public abstract class Series {

    private double initElem;
    private double step;

    public double getInitElem() {
        return initElem;
    }
    
    public double getStep() {
        return step;
    }

    public void setInitElem(double initElem) {
        this.initElem = initElem;
    }

    public void setStep(double step) {
        this.step = step;
    }

    public  Series(double initElem, double step) {
        this.initElem = initElem;
        this.step = step;
    }

    public abstract double calculateJElement(int j);

    public double calculateSum(int j) {
        double sum = 0;
        for (int i = 0; i < j; i++) {
            sum += calculateJElement(i);
        }
        return sum;
    }

    @Override
    public String toString() {
        StringBuilder st = new StringBuilder();
        for (int i = 0; i < 10; i++) {
            st.append(String.format("%.2f", calculateJElement(i)) + " ");
        }
        return st.toString();
    }

    public String toString(int j) {
        StringBuilder st = new StringBuilder();
        for (int i = 0; i < j; i++) {
            st.append(String.format("%.2f", calculateJElement(i)) + " ");
        }
        return st.toString();
    }

    public void saveToFile(File output) throws FileNotFoundException {
        PrintWriter out = new PrintWriter(output);
        out.write(this.toString());
        out.close();
    }
}