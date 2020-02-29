/*
import java.util.*;


public class Complex
{
    private double a, b;//复数的实部和虚部

    //private final double delta=1e-20;
    public Complex(double a, double b) {
        this.a = a;
        this.b = b;
    }

    public void Change(double a, double b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public String toString() {
        if (b > 0.0) {
            if (a == 0.0)
                return b + "*i";
            else
                return a + "+" + b + "*i";
        } else if (b < 0.0) {
            if (a == 0.0)
                return b + "*i";
            else
                return a + "" + b + "*i";//注意
        } else
            return a + "";//要加"",这样就可以返回一个String类型的值了
    }

    public Complex plus(Complex Z) {
        double aa = this.a + Z.a;
        double bb = this.b + Z.b;
        return new Complex(aa, bb);
    }

    public Complex minus(Complex Z) {
        double aa = this.a - Z.a;
        double bb = this.b - Z.b;
        return new Complex(aa, bb);
    }

    public Complex multiply(Complex Z) {
        double aa = this.a * Z.a - this.b * Z.b;
        double bb = this.b * Z.a + this.a * Z.b;
        return new Complex(aa, bb);
    }

    public Complex divide(Complex Z) {
        Z.Change(Z.a, -Z.b);
        Complex ZZ = this.multiply(Z);
        ZZ.a /= (Z.a * Z.a + Z.b * Z.b);
        ZZ.b /= (Z.a * Z.a + Z.b * Z.b);
        return ZZ;
    }

    public static void main(String args[])
    {
        Scanner cin=new Scanner(System.in);
        double []x=new double[10];
        double a;
        int i=0;
        System.out.println("Implement Here");
        while(i<10&&cin.hasNext())
        {
            a=cin.nextDouble();
            x[i]=a;
            i++;
        }
        System.out.println("Input Data");
        for(int j=0;j<10;j++)
            System.out.println(x[j]);
        FastFourierTransform FFt=new FastFourierTransform();
        Complex []outcome=new Complex[10];
        for(int j=0;j<10;j++)
            outcome[j]=new Complex(0,0);
        outcome=FFt.FFT(x);
        System.out.println("After FFT");
        for(int j=0;j<10;j++)
            System.out.println(outcome[j]);
    }
}
*/