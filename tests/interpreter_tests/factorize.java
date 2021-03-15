class Arithmetic {
  public static void main () {
    int x;
    int i;

    x = 101123;
    i = 2;

    while (i * i <= x) {
        while (x % i == 0) {
            System.out.println (i);
            x = x / i;
        }
        i = i + 1;
    }
    if (x > 1) {
        System.out.println (x);
    }
  }
}