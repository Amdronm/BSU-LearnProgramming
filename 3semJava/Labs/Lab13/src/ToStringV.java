public class ToStringV implements Visitor {
    private StringBuilder sb = new StringBuilder("this is result of visitor: ");

    @Override
    public void visit(MyInt e) {
        sb.append(e.toString());
        sb.append(' ');
    }

    public String getResult() {
        return sb.toString();
    }
}
