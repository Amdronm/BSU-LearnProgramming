/**
   A program to print a multiplication table
*/

package MultTableV2;

public class MultTable2 {
    public static void main(String[] args) {
        System.out.printf("    y | 1y | 2y | 3y | 4y | 5y %n" + 
        "  ----|----|----|----|----|----%n");
        for (int i = 1; i <= 10; i++) {
            System.out.printf("  %3d", i);
            for (int j = 1; j <= 5; j++) {
                System.out.printf(" |%3d", i * j);
            }
            System.out.println();
        }
    }
}