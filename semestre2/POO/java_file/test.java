public class test{

    public String nomdutest;
    public int nb_test;

    public test(String name, int nb)
    {
        this.nomdutest = name;
        this.nb_test = nb;
    }



    public static void main(String[] args){
        test montest = new test("Wola je suis un test", 3);
        System.out.println(montest.nomdutest);
        System.out.println("et le num : " + montest.nb_test);
    }
}