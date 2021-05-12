// Test translation to IR
class Assertion {
  public static void simple() {
    assert (true && true);
    assert (1 == 1);
    assert (2 == 2);
    assert (256 == 256);
    assert (-1 == -1);
  }
}