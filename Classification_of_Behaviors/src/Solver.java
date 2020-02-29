import java.io.*;
import java.lang.String;
import java.io.IOException;
import java.util.Vector;

public class Solver {

    static Vector <Vector<DataACC>> accFile=new Vector <Vector<DataACC>>(1000);
    static Vector <Vector<DataACC>> acclFile=new Vector <Vector<DataACC>>(1000);
    static Vector <Vector<DataACC>> gyroFile=new Vector <Vector<DataACC>>(1000);
    static Vector <Vector<DataLabel>> labelFile=new Vector <Vector<DataLabel>>(1000);

    static public void init()
    {
        DataACC.init();
        DataLabel.init();
    }

    static public void accFile_add(Vector <DataACC> singleFile)
    {
        accFile.add(singleFile);
    }

    static public void acclFile_add(Vector <DataACC> singleFile)
    {
        acclFile.add(singleFile);
    }

    static public void gyroFile_add(Vector <DataACC> singleFile)
    {
        gyroFile.add(singleFile);
    }

    static public void lableFile_add(Vector <DataLabel> singleFile)
    {
        labelFile.add(singleFile);
    }

    static public void WangLiang()
    {
        //初始化
        init();

        //文件读入
        ReadAllFile.EnterFolder();

        int accFileSize=accFile.size();
        int acclFileSize=acclFile.size();
        int gyroFileSize=gyroFile.size();
        int labelFileSize=labelFile.size();

        Vector <Vector<TimeSlice>> timeSliceVector = new Vector<Vector<TimeSlice>>();
        for(int i=0;i<labelFileSize;i++)
        {
            System.out.print("Processing time slice for filegroup ");
            System.out.println(i+1);
            timeSliceVector.add(DisposeData.getTimeSliceVector(labelFile.get(i)));
        }

        Vector<Vector<TimeSlice>> winSliceVector = new Vector<Vector<TimeSlice>>();
        for(int i=0;i < labelFileSize;i++){
            System.out.print("Processing window for filegroup ");
            System.out.println(i+1);
            winSliceVector.add(DisposeData.getWindow(timeSliceVector.get(i), 0.5, 320));
        }

        Vector<FeatureStruct> feature = new Vector<FeatureStruct>();
        for(int i=0;i < labelFileSize;i++){
            System.out.print("Generating feature for filegroup ");
            System.out.println(i+1);
            DisposeData.getFeature(feature, accFile.get(i), acclFile.get(i), gyroFile.get(i), winSliceVector.get(i));
        }

        System.out.println("Generating arff file");

        //生成文件
        CreateArff createArff = new CreateArff(true, "WangLiang", "WangLiang");

        String[] fileName = {"acc_", "accl_", "gyro_"};
        String[] axis = {"x_", "y_", "z_"};
        String[] attribute = {"spectral_centroid", "spectral_variance", "spectral_mean", "spectral_skewness", "bandwidth"};

        for(int i=0;i < 3;i++){
            for(int j=0;j < 3;j++){
                for(int k=0;k < 5;k++){
                    createArff.addAttirbute(fileName[i]+axis[j]+attribute[k], "numeric");
                }
            }
        }
        createArff.addAttirbute("class", "{activity_walk, activity_stand, activity_down_stair, activity_up_stair, activity_sit}");

        createArff.startData();
        int featureLen = feature.size();
        for(int i=0;i < featureLen;i++){
            createArff.addData(feature.get(i).getAllFeature());
        }

        createArff.finished();

        System.out.println("Generating arff file finished");
    }
}
