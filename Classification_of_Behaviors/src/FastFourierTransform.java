import org.apache.commons.math3.complex.Complex;
import org.apache.commons.math3.transform.DftNormalization;
import org.apache.commons.math3.transform.FastFourierTransformer;
import org.apache.commons.math3.transform.TransformType;

import java.util.Scanner;

public class FastFourierTransform
{
    public Complex[] FFT(double[] inputData){
        FastFourierTransformer fft = new FastFourierTransformer(DftNormalization.STANDARD);
        return fft.transform(inputData, TransformType.FORWARD);
    }

    /*public static void main(String args[])
    {
        Scanner cin=new Scanner(System.in);
        double []x=new double[8];
        double a;
        int i=0;
        System.out.println("Implement Here");
        while(i<8&&cin.hasNext())
        {
            a=cin.nextDouble();
            x[i]=a;
            i++;
        }
        System.out.println("Input Data");
        for(int j=0;j<8;j++)
            System.out.println(x[j]);
        FastFourierTransform FFt=new FastFourierTransform();
        Complex []outcome=new Complex[8];
        for(int j=0;j<8;j++)
            outcome[j]=new Complex(0,0);
        outcome=FFt.FFT(x);
        System.out.println("After FFT");
        for(int j=0;j<8;j++)
            System.out.println(outcome[j].getReal());
    }*/

    /*
    public Complex[] fft(Complex[] x) {
        int n = x.length;

        // 因为exp(-2i*n*PI)=1，n=1时递归原点
        if (n == 1){
            return x;
        }

        // 如果信号数为奇数，使用dft计算
        if (n % 2 != 0) {
            return dft(x);
        }

        // 提取下标为偶数的原始信号值进行递归fft计算
        Complex[] even = new Complex[n / 2];
        for (int k = 0; k < n / 2; k++) {
            even[k] = x[2 * k];
        }
        Complex[] evenValue = fft(even);

        // 提取下标为奇数的原始信号值进行fft计算
        // 节约内存
        Complex[] odd = even;
        for (int k = 0; k < n / 2; k++) {
            odd[k] = x[2 * k + 1];
        }
        Complex[] oddValue = fft(odd);

        // 偶数+奇数
        Complex[] result = new Complex[n];
        for (int k = 0; k < n / 2; k++) {
            // 使用欧拉公式e^(-i*2pi*k/N) = cos(-2pi*k/N) + i*sin(-2pi*k/N)
            double p = -2 * k * Math.PI / n;
            //System.out.print("@@@ "+p);
            Complex m = new Complex(Math.cos(p), Math.sin(p));
            System.out.println("!!! "+m+" $$$ "+oddValue[k]);
            result[k] = evenValue[k].plus(m.multiply(oddValue[k]));
            // exp(-2*(k+n/2)*PI/n) 相当于 -exp(-2*k*PI/n)，其中exp(-n*PI)=-1(欧拉公式);
            result[k + n / 2] = evenValue[k].minus(m.multiply(oddValue[k]));
            System.out.println("@@@ "+result[k]+" ### "+result[k + n / 2]);
        }
        return result;
    }

    public Complex[] dft(Complex[] x) {
        int n = x.length;

        // 1个信号exp(-2i*n*PI)=1
        if (n == 1)
            return x;

        Complex[] result = new Complex[n];
        for (int i = 0; i < n; i++) {
            result[i] = new Complex(0, 0);
            for (int k = 0; k < n; k++) {
                //使用欧拉公式e^(-i*2pi*k/N) = cos(-2pi*k/N) + i*sin(-2pi*k/N)
                double p = -2 * k * Math.PI / n;
                Complex m = new Complex(Math.cos(p), Math.sin(p));
                result[i].plus(x[k].multiply(m));
            }
        }
        return result;
    }
    */
}
