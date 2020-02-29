import org.apache.commons.math3.complex.Complex;
import org.apache.commons.math3.transform.DftNormalization;
import org.apache.commons.math3.transform.FastFourierTransformer;
import org.apache.commons.math3.transform.TransformType;

import java.security.AccessControlContext;
import java.util.Vector;

public class DisposeData {
    static Vector<TimeSlice> getTimeSliceVector(Vector<DataLabel> labels){
        int labelLen = labels.size();
        boolean isStart = false;
        TimeSlice cur = null;
        String activity_label = null;
        Vector<TimeSlice> result = new Vector<TimeSlice>();
        for(int i=0;i < labelLen;i++){
            String label = labels.get(i).str;
            //start标签处理
            if(label.equals("start")){
                assert isStart==false;
                assert activity_label != null;
                assert cur == null;
                isStart = true;
                cur = new TimeSlice(labels.get(i).meTime, activity_label);
            }
            //activity标签处理
            else if(label.contains("activity_")){
                activity_label = label;
                //如果已经有start了则添加到result
                if(isStart){
                    assert cur != null;
                    cur.setEnd(labels.get(i).meTime);
                    result.add(cur);
                    //生成新的TimeSlice
                    cur = new TimeSlice(labels.get(i).meTime, activity_label);
                }
            }
            //stop标签处理
            else if(label.equals("stop")){
                assert activity_label != null;
                assert cur != null;
                isStart = false;
                cur.setEnd(labels.get(i).meTime);
                result.add(cur);
                cur = null;
            }
        }

        return result;
    }

    static Vector<TimeSlice> getWindow(Vector<TimeSlice> src, double overlapRate, long winSize) {
        assert(winSize > 0);
        assert(overlapRate > 0 && overlapRate < 1);

        Vector<TimeSlice> result = new Vector<TimeSlice>();
        TimeSlice cur = null;
        long curStart = 0, curEnd = 0;
        long end = 0;

        int timeSlicesSize = src.size();
        assert (timeSlicesSize > 0);
        for(int i = 0; i < timeSlicesSize; i++) {
            String label = src.get(i).label;
            curStart = src.get(i).start;
            curEnd = curStart + winSize;
            end = src.get(i).end;
            while(curEnd <= end) {
                cur = new TimeSlice(curStart, label);
                cur.setEnd(curEnd);
                result.add(cur);
                curStart += (long)((1 - overlapRate) * winSize);
                curEnd = curStart + winSize;
            }
        }
        return result;
    }

    static void getFeature(Vector<FeatureStruct> feature, Vector<DataACC> acc, Vector<DataACC> accl, Vector<DataACC> gyro, Vector<TimeSlice> win){
        Vector<FeatureStruct> result = new Vector<FeatureStruct>();

        //记录前一个窗口开始的order，方便后面回溯
        int accOrder = 0;
        int acclOrder = 0;
        int gyroOrder = 0;

        int winSize = win.size();
        for(int i=0;i < winSize;i++){
            long start = win.get(i).start;
            long end = win.get(i).end;

            //acc处理
            while(acc.get(accOrder).meTime < start) accOrder++;
            int accEnd;
            for(accEnd=accOrder;acc.get(accEnd).meTime < end;accEnd++);
            //accl处理
            while(accl.get(acclOrder).meTime < start) acclOrder++;
            int acclEnd;
            for(acclEnd=acclOrder;accl.get(acclEnd).meTime < end;acclEnd++);
            //gyro处理
            while(gyro.get(gyroOrder).meTime < start) gyroOrder++;
            int gyroEnd;
            for(gyroEnd=gyroOrder;gyro.get(gyroEnd).meTime < end;gyroEnd++);

            if(accEnd-accOrder == 0 || acclEnd-acclOrder == 0 || gyroEnd-gyroOrder == 0){
                System.out.println("@@@"+accEnd+" "+accOrder+"###"+acclOrder+" "+acclEnd+"$$$"+gyroOrder+" "+gyroEnd);
            }

            feature.add(new FeatureStruct(
                    new double[][][]{FeatureGenerator.getAllFeature(accOrder, accEnd, acc),
                            FeatureGenerator.getAllFeature(acclOrder, acclEnd, accl),
                            FeatureGenerator.getAllFeature(gyroOrder, gyroEnd, gyro)}, win.get(i).label));
        }
    }


    static Complex[] FFT(double[] inputData) {
        FastFourierTransformer fft = new FastFourierTransformer(DftNormalization.STANDARD);
        return fft.transform(inputData, TransformType.FORWARD);
    }

    static double[] transformTimeToFrequency(double[] inputData){
        int len = inputData.length;
        int needLen = 1;
        for(;needLen*2 < len;needLen *= 2);
        double[] fftData = new double[needLen];
        System.arraycopy(inputData, 0, fftData, 0, needLen);
        Complex[] comRes = FFT(fftData);

        int comResLen = comRes.length;
        double[] result = new double[comResLen];
        for(int i=0;i < comResLen;i++){
            result[i] = comRes[i].getReal();
        }

        return result;
    }
}
