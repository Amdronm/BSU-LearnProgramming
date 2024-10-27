package examplekr;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Data <T extends Comparable<T>> {
    private Set<T> data;

    public Data() {
        data = new TreeSet<T>();
    }

    public Data(Set<T> set) {
        this.data = set;
    }

    public void parseFromFile(File file) throws Exception {
        try (Scanner in = new Scanner(file)) {
            while (in.hasNext()) {
                // T t = in.next();
            }
        } catch (FileNotFoundException e) {
            throw new Exception("No such file!");
        } catch (InputMismatchException e) {
            throw new Exception("Wrong token in file");
        }
    }

    public Set<T> getData() {
        return data;
    }

    public void setData(Set<T> data) {
        this.data = data;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (T i : data) {
            sb.append(i.toString() + "\n");
        }
        return sb.toString();
    }

    public T getMin() {
        T res = data.stream().min(new Comparator<T>() {
            @Override
            public int compare(T o1, T o2) {
                return o1.compareTo(o2);
            }
        }).get();
        return res;
    }
}
