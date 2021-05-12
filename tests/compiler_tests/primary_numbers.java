class PrimeCheck {
    public static boolean IsPrime(int x) {
        if (x <= 1)
            return false;

        int i;
        i = 2;
        while (i * i <= x) {
            if (x % i == 0) {
                return false;
            }
            i = i + 1;
        }
        return true;
    }
}

class SieveOfEratosthenes {
    int size;
    boolean[] is_prime;

    public void Prepare(int size) {
        this.size = size;
        is_prime = new boolean[size];

        is_prime[0] = false;
        is_prime[1] = false;
        int i;
        i = 2;
        while (i <= size) {
            is_prime[i] = true;
            i = i + 1;
        }

        i = 2;
        while (i <= size) {
            if (is_prime[i]) {
                int j;
                j = 2;
                while (j * i <= size) {
                    is_prime[i * j] = false;
                    j = j + 1;
                }
            }
            i = i + 1;
        }
    }

    public boolean IsPrime(int x) {
        assert (x <= size);
        return is_prime[x];
    }
}

class Main {
    public static void main() {
        assert (PrimeCheck.IsPrime(3));
        assert (PrimeCheck.IsPrime(5));
        assert (PrimeCheck.IsPrime(7));
        assert (!PrimeCheck.IsPrime(12));
        assert (PrimeCheck.IsPrime(1000 * 1000 * 1000 + 7)); // Yea, prime
        assert (PrimeCheck.IsPrime(1000 * 1000 * 1000 + 9)); // prime too
        assert (!PrimeCheck.IsPrime(1000 * 1000 * 1000 + 11)); // not prime :(

        SieveOfEratosthenes sieve;
        sieve = new SieveOfEratosthenes();

        int N;
        N = 1 * 1000 * 1000;
        sieve.Prepare(N);


        int i;
        i = 0;

        while (i <= N) {
            assert (PrimeCheck.IsPrime(i) == sieve.IsPrime(i));
            i = i + 1;
        }
    }
}