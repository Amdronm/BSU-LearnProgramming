package unicontrol;

public class Postgraduate extends Student {
    private Academic supervisor;

    public Postgraduate(String name, String login, String email, Academic superviser) {
        super(name, login, email);
        this.supervisor = superviser;
    }

    public Academic getSupervisor() {
        return supervisor;
    }

    public void setSupervisor(Academic supervisor) {
        this.supervisor = supervisor;
    }

    @Override
    public String toString() {
        return "Postgraduate(" + super.toString() + supervisor.toString() + ")";
    }
}
