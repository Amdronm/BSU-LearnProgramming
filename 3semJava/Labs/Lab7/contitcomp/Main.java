// 1)	Реализовать возможность добавления данных в диалоговом окне.
// Реализовать команду Файл–Открыть. При открытии данные отображаются 
// в одной компоненте, при обработке данных – в другой.
// 10.	Дан файл, содержащий сведения об игрушках: название, стоимость и возрастные границы детей, 
// для которых игрушка предназначена. Построить список игрушек по возрастанию стоимости, 
// которые подходят детям заданных возрастных границ.


package contitcomp;

public class Main {
    public static void main(String[] args) {
        MyFrame fr = new MyFrame("Toy contaner&iterator&comparator");
        fr.setDefaultCloseOperation(MyFrame.EXIT_ON_CLOSE);
        fr.setBounds(600, 300, 800, 600);
        fr.setVisible(true);        
    }
}
