import java.lang.String;

public class FeatureStruct {
    double[][][] data = new double[3][3][5];
    String label;
    /*
    double spectral_centroid;
    double spectral_variance;
    double spectral_mean;
    double spectral_skewness;
    double bandwidth;
    */
    //static int featureNum;

    FeatureStruct(double[][][] data, String label){
        this.data = data;
        this.label = label;
    }


    String[] getAllFeature(){
        String[] result = new String[3*3*5+1];

        for(int i=0;i < 3;i++){
            for(int j=0;j < 3;j++){
                for(int k=0;k < 5;k++){
                    result[i*3*5+j*5+k] = String.valueOf(data[i][j][k]);
                }
            }
        }

        result[3*3*5] = label;
        return result;
    }

    //static public void setFeatureNum(int featureNum){FeatureStruct.featureNum = featureNum;}
}
