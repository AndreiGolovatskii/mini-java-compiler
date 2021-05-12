class Proxy {
    int[] Member;
    public void Init(int cnt) {
        member = new int[cnt];
    }
    public int[] GetMember() {
        return Member;
    }
    public int[] GetMemberToo() {
        return this.Member;
    }
    public int[] GetMemberTooToo() {
        return GetMember();
    }
}

class Main {
    public static void main () {
        Proxy proxy;
        proxy.Init(100 + 1);
        proxy.GetMember()[5] = -5;
        proxy.GetMemberToo()[4] = -4;
        proxy.GetMemberTooToo();
    }
}