class Main {
    public static void main() {
        int x;
        x = 2;
        assert (x == 2);

        {
            assert (x == 2);
            int x;
            x = 15;
            assert (x == 15);
        }
        assert (x == 2);

    }
}