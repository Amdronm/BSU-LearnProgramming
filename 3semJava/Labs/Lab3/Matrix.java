import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Matrix {
    public static void main(String[] args) {
        try {
            if (args.length != 1) {
                throw new MyOwnException("Wrong amount of arguments");
            }
            Scanner in = new Scanner(new File(args[0]));
            double[][] matrix = getMatrix(in);
            if (matrix.length == 0) {
                throw new MyOwnException("Equations have not been built!");
            }
            double[] answerVector = solveEquations(matrix);
            printVector(answerVector);
            in.close();
        }
        catch (MyOwnException e) {
            System.err.println(e.getMessage());
        }
        catch (FileNotFoundException e) {
            System.err.println(e.getMessage());
        }
    }

    public static double[][] getMatrix(Scanner in) throws MyOwnException {
        int m = in.nextInt();
        int n = m + 1;
        double[][] matrix = new double[m][n];
        try {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (!in.hasNext()) {
                        throw new MyOwnException("There is no element!");
                    }
                    if (!in.hasNextDouble()) {
                        throw new MyOwnException("It is not double!");
                    }
                    matrix[i][j] = in.nextDouble();
                }
            }
            if (in.hasNext()) {
                throw new MyOwnException("There are another elements!");
            }
            return matrix;
        }
        catch (MyOwnException e) {
            System.err.println(e.getMessage());
        }
        return new double[0][0];
    }

    public static void printVector(double[] vector) {
        for (int i = 0; i < vector.length; i++) {
            System.out.printf("%6.2f ", vector[i]);
        }
        System.out.println();
    }

    public static double[] solveEquations(double[][] matrix) {
        double e = 0.00001;
        double[] answer = new double[matrix.length];
        int m = matrix.length;
        int n = matrix[0].length;
        for (int i = 0, j = 0; i < m; i++, j++) {
            if (Math.abs(matrix[i][j]) < e) {
                for (int k = 0; k < m; k++) {
                    if (Math.abs(matrix[k][j]) > e) {
                        double[] tmp = new double[n];
                        tmp = matrix[i];
                        matrix[i] = matrix[k];
                        matrix[k] = tmp;
                        break;
                    }
                }
            }
            double fstmul = 1. / matrix[i][j];
            for (int k = j; k < n; k++) {
                matrix[i][k] *= fstmul;
            }
            for (int ii = i + 1; ii < m; ii++) {
                double[] sub = new double[n];
                for (int k = j; k < n; k++) {
                    sub[k] = matrix[ii][j] * matrix[i][k];
                }
                for (int k = j; k < n; k++) {
                    matrix[ii][k] -= sub[k];
                }
            }
        }

        for (int j = n - 2, i = m - 1; j >= 0; j--, i--) {
            for (int ii = i - 1; ii >= 0; ii--) {
                double[] sub = new double[n];
                for (int k = j; k < n; k++) {
                    sub[k] = matrix[ii][j] * matrix[i][k];
                }
                for (int k = j; k < n; k++) {
                    matrix[ii][k] -= sub[k];
                }
            }            
        }
        for (int i = 0; i < m; i++) {
            answer[i] = matrix[i][n - 1];
        }
        return answer;
    }
}