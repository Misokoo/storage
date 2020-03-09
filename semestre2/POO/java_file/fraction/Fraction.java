public class Fraction {
    // attributs
    private int num;
    private int den;

    // constructeur
    public Fraction (int num,int den) {
        this.num=num;
        this.den=den;
    }
    // multiplication
    public Fraction multiplie(Fraction f)  {
        Fraction res = new Fraction(num*f.num,den*f.den);
        return res;
    }
    // addition
    Fraction addition(Fraction f)  {
        Fraction res = new Fraction(num*f.den+f.num*den , den*f.den);
        return res;
    }
    // affiche
    public void affiche () { 
        System.out.println(num + "\n-\n" + den);  
    }
    private int _pgcd (int a, int b) {
        int r = a % b;
        if (r == 0)
            return b;
        else
            return _pgcd (b, r);
    }
    // pgcd
    private int pgcd () {
        return _pgcd (num,den);
    }
    // simplification
    public Fraction simplifie() {
        int divcommun = this.pgcd();
        Fraction res = new Fraction( num/divcommun, den/divcommun );
        return res;
    }

    // main
    static public void main (String args [] ) {
        Fraction f1 = new Fraction(1,2); 
        Fraction f2 = new Fraction(3,5);

        Fraction f3;
        f3 = f1.addition(f2);
        f3.affiche();

        Fraction f4;
        f4 = f1.multiplie(f3);
        f4.affiche();
    }
}