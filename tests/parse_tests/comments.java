//this is single-line comment

/*
 and it's comment too
 // it may contain all kind of symbols
 /*
    *
    *

//
    ** //
    * /
    *
    /
    except comment close combination:
*/
class Factorial {
    // // // also comments can be everywhere
    public static void main (/* this */) {
        // comment
        System.out.println (new Fac ().ComputeFac(/* num */10));
    }
    // also comment
}

class Fac {
    public int ComputeFac (int /* */ num) {
        assert (num > -1); // and this is a comment
        int num_aux;
        if (num == 0)
            num_aux = 1;
            /* */ // and comment that says that previous comment is empty
        else
            num_aux = num * this.ComputeFac (num - 1);
        return num_aux;
    }
}

/* the end! */