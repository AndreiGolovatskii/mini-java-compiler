class Main {
  public static void main() {
    assert (2 + 2 == 4);
    assert (2 - 2 == 0);
    assert (2 + 0 == 2);
    assert (2 * 2 == 4);
    assert (2 * -2 == -4);
    assert (-2 * -2 == 4);
    assert (2 % 2 == 0);
    assert (6 % 3 == 0);
    assert (3 % 2 == 1);
    assert (5 % 2 == 1);

    assert (2 * 2 <= 5);
    assert (3 * 3 > 5);
    assert (5 % 2 == 1);
    assert (!(5 % 2 == 0));

    assert (0 == 0);
    assert (1 > 0);
    assert (-1 < 0);
    assert (0 > -1);
    assert (0 >= 0);
    assert (0 <= 0);

  }
}