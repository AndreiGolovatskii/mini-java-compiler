class Factorial {
  public static void main () {
    System.out.println (new Fac ().ComputeFac(10));
  }
}

class Fac {
  public int ComputeFac (int num) {
    assert (num > -1);
    int num_aux;
    if (num == 0)
      num_aux = 1;
    else
      num_aux = num * this.ComputeFac (num-1);
    return num_aux;
  }
}