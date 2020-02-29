import java.util.Vector;

public class FeatureGenerator {

    public static double[][] SpectralCentroid(double[][] powerSpectrums,double samplingRate){

        int dimension = 1;
        double[][] feature = new double[powerSpectrums.length][dimension];
        int count = 0;

        for(double[] powerSpectrum : powerSpectrums){

            double total = 0.0;
            double weightedTotal = 0.0;
            int length = powerSpectrum.length;

            for(int bin = 0; bin<length; ++bin){
                weightedTotal += bin * powerSpectrum[bin];
                total += powerSpectrum[bin];
            }

            if(total != 0.0)
                feature = Statistics.assign1Dto2DArray(feature, new double[]{weightedTotal/total},count);
            else
                feature = Statistics.assign1Dto2DArray(feature, new double[]{0.0},count);

            ++count;
        }

        return feature;

    }

    public static double[][] SpectraRolloff(double[][] powerSpectrums, double samplingRate,double cutoff_temp){

        final double cutoff = cutoff_temp;
        int dimension = 1;
        int length = powerSpectrums.length;

        double[][] feature = new double[length][dimension];

        for(int i=0; i<length; ++i){

            double[] powerSpectrum = powerSpectrums[i];

            double total = 0.0;
            int loop = powerSpectrum.length;

            for(int bin = 0; bin<loop; ++bin)
                total += powerSpectrum[bin];

            double threshold = total * cutoff;

            total = 0.0;
            int point = 0;

            for(int bin = 0; bin < loop; ++bin){
                total += powerSpectrum[bin];

                if(total >= threshold){
                    point = bin;
                    bin = loop;
                }
            }

            feature = Statistics.assign1Dto2DArray(feature,new double[]{((double)point)/((double)loop)},i);
        }

        return feature;
    }

    static class Statistics
    {
        public static double[][] assign1Dto2DArray(double[][] twoDArray, double[] data, int index) {
            int length = data.length;
            for(int i=0; i<length; ++i)
                twoDArray[index][i] = data[i];
            return twoDArray;
        }
    }

    public static double[] array2energy(double[] array) {
        double[] energy_array=new double[array.length];
        for(int i=0;i<array.length;i++) {
            energy_array[i]=array[i]*array[i];
        }
        return energy_array;
    }

    public static double spectral_centroid(double[] array) {
        double sc=1;
        double num=0;
        double[] new_array=array2energy(array);
        for (int i = 0; i < array.length; i++) {
            num=new_array[i];
            sc*=num;
        }
        sc=Math.pow(sc,1.0/(double)array.length);
        return sc;
    }

    public static double spectral_variance(double[] array) {
        double[] new_array=array2energy(array);
        double sm=spectral_mean(new_array);
        double sv=0;
        for(int i=0;i<new_array.length;i++) {
            sv+=(new_array[i]-sm)*(new_array[i]-sm);
        }
        sv=sv/(double)new_array.length;
        return sv;
    }

    public static double spectral_mean(double[] array) {
        double[] new_array=array2energy(array);
        double sum=0;
        for(int i=0;i<new_array.length;i++) {
            sum+=new_array[i];
        }
        double mean=sum/(double)new_array.length;
        return mean;
    }

    public static double spectral_skewness(double[] array) {
        double[] new_array=array2energy(array);
        double sm=spectral_mean(new_array);
        double son=0;
        for(int i=0;i<new_array.length;i++) {
            son+=Math.pow(new_array[i]-sm,3.0);
        }
        son=son/(double)new_array.length;
        double mom=0;
        for(int i=0;i<new_array.length;i++) {
            mom+=Math.pow(new_array[i]-sm,2.0);
        }
        mom=mom/(double)new_array.length;
        mom=Math.pow(mom,3.0/2.0);

        return son/mom;
    }

    public static double bandwidth(double[] array)  {
        double max=array[0];
        int max_index=0;
        for(int i=0;i<array.length;i++) {
            if(array[i]>max) {
                max=array[i];
                max_index=i;
            }
        }
        double db=Math.pow(max,1.0/2.0)/2.0;
        int front_index=0;
        double front_sub=array[0]-db;
        int behind_index=0;
        double behind_sub=array[max_index]-db;
        for(int i=0;i<array.length;i++) {
            if(i<max_index) {
                if(array[i]-db<front_sub)
                    front_index=i;
            }else {
                if(array[i]-db<behind_sub)
                    behind_index=i;
            }
        }
        return (double)behind_index-front_index;
    }

    static public double[][] getAllFeature(int start, int end, Vector<DataACC> f){
        double[] dataX = new double[end-start];
        double[] dataY = new double[end-start];
        double[] dataZ = new double[end-start];

        for(int i=start;i < end;i++){
            dataX[i-start] = f.get(i).x;
            dataY[i-start] = f.get(i).y;
            dataZ[i-start] = f.get(i).z;
        }
        //System.out.println("@@@"+dataX.length);

        double[][] result = new double[3][5];

        result[0][0] = spectral_centroid(dataX);
        result[0][1] = spectral_variance(dataX);
        result[0][2] = spectral_mean(dataX);
        result[0][3] = spectral_skewness(dataX);
        result[0][4] = bandwidth(dataX);

        result[1][0] = spectral_centroid(dataY);
        result[1][1] = spectral_variance(dataY);
        result[1][2] = spectral_mean(dataY);
        result[1][3] = spectral_skewness(dataY);
        result[1][4] = bandwidth(dataY);

        result[2][0] = spectral_centroid(dataZ);
        result[2][1] = spectral_variance(dataZ);
        result[2][2] = spectral_mean(dataZ);
        result[2][3] = spectral_skewness(dataZ);
        result[2][4] = bandwidth(dataZ);

        return result;
    }

}
