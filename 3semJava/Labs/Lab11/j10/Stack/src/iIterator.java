public interface iIterator<T> {
    public void first();
    public void next();
    public boolean isDone();
    public T getItem();
}
