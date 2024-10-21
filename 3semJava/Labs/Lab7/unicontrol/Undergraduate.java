package unicontrol;

public class Undergraduate extends Student {
    private Academic tutor;

    Undergraduate(String name, String login, String email, Academic tutor) {
        super(name, login, email);
        this.tutor = tutor;
    }

    public Academic getTutor() {
        return tutor;
    }

    public void setTutor(Academic tutor) {
        this.tutor = tutor;
    }

    @Override
    public String toString() {
        return "Undergraduate(" + super.toString() + tutor.toString() + ")";
    }
}