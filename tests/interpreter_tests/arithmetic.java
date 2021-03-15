class Arithmetic {
  public static void main () {
    assert (-1 - -1 == 0);
    assert (2 + 3 * 2 == 8);
    assert (2 + 4 / 2 == 4);
    assert (2 - 4 / 2 == 0);
    assert (2 + 4 % 3 == 3);
    assert (1 + 2 < 2 + 3);
    assert (1 <= 1 && 1 < 2);
    assert (1 > 2 || 3 > 2);
  }
}