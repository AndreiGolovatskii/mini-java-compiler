class Fib {
  public static int Fib(int x) {
    if (x == 1) {
      return 1;
    }
    if (x == 0) {
      return 0;
    }
    return Fib(x - 1) + Fib(x - 2);
  }
}

class Main {
  public static void main() {
     assert (Fib.Fib(5) == 5);
     assert (Fib.Fib(6) == 8);

     int x;
     x = Fib.Fib(0);
     assert (x == 0);

     assert (Fib.Fib(20) == 6765);
  }
}