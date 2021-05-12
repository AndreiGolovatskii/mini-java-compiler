class Data {
    int member_x;
    int member_y;
    Data member_data;

    public void Swap() {
        int tmp;
        tmp = member_x;
        member_x = member_y;
        member_y = tmp;
    }

    public Data Copy() {
        Data res;
        res = new Data();
        res.member_x = member_x;
        res.member_y = member_y;
        res.member_data = member_data;

        return res;
    }
}

class Main {
    public static void main() {
       Data struct1;
       Data struct1_dub;

       struct1 = new Main();
       struct1_dub = struct1;

       struct1.member_x = 0;
       struct1_dub.member_y = 1;

       struct1.Swap();
       assert (struct1.member_x == 1);
       assert (struct1.member_y == 0);

       struct1.member_data = struct1_dub;
       assert (struct1_dub == struct1);
       assert (struct1_dub.member_x == struct1.member_data.member_x);


       Data copy;
       copy = struct1.Copy();

       assert (copy.member_x == struct1.member_x);
       copy.member_x = struct1.member_x + 1;
       assert (copy.member_x != struct1.member_x);

       assert (copy.member_data == struct1.member_data);
    }
}