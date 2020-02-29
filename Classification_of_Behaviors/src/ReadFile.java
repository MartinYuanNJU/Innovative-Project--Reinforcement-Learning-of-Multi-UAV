import java.io.*;
import java.lang.String;
import java.io.File;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileWriter;


public class ReadFile
{
    public static void cin_txt()
    {
        DataACC []dataacc=new DataACC[20];
        File input = new File("data/2016-07-08_13-05-39-acc.txt");
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(input));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String line="";
        int count=0;
        do {
            try {
                line=reader.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            dataacc[count]=new DataACC(line);
            System.out.println(dataacc[count].mrTime);
            System.out.println(dataacc[count].meTime);
            System.out.println(dataacc[count].x);
            System.out.println(dataacc[count].y);
            System.out.println(dataacc[count].z);
            System.out.println("-----------------------------\n");
            count++;
        }while(count<20&&line!=null);
    }
}
