class Main {
  public static void main() {
    int[] array;
    array = new int[3];
    array[0] = 0;
    array[1] = 1;
    array[2] = 2;

    int[] array_same;
    array_same = array;

    assert (array[0] == 0);
    assert (array[1] == 1);
    assert (array[2]== 2);

    assert (array_same[0] == 0);
    assert (array_same[1] == 1);
    assert (array_same[2] == 2);

    array_same[0] = 5;
    assert (array_same[0] == 5);
    assert (array[0] == 5);

    array[1] = 10;
    assert (array[1] == 10 && array_same[1] == array[1]);
  }
}