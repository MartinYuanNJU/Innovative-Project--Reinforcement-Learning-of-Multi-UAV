import java.io.*;
import java.lang.String;
import java.util.Vector;

public class ReadAllFile {

    public static File[] getCurFilesList(String filePath) {
        File path = new File(filePath);
        File[] listFiles = path.listFiles(new java.io.FileFilter() {

            @Override
            public boolean accept(File pathname) {
                if (pathname.isFile())
                    return true;
                else
                    return false;
            }
        });

        return listFiles;
    }

    public static void EnterFolder() {
        String filePath = "data";
        File[] fileList = getCurFilesList(filePath);

        for (File file : fileList)
        {
            String filename="data/";
            filename=filename+file.getName();
            if(filename.contains("DS_Store"))
                continue;
            System.out.print("Reading file: ");
            System.out.println(filename);
            if(filename.contains("label"))
            {
                File input=new File(filename);
                Vector <DataLabel> one_label_file=new Vector<DataLabel>(1000);
                try {
                    BufferedReader reader = new BufferedReader(new FileReader(input));
                    String line="";
                    do {
                        line = reader.readLine();
                        if(line==null)
                            break;
                        DataLabel singleLine=new DataLabel(line);
                        one_label_file.add(singleLine);
                    }while(line!=null);
                }
                catch (FileNotFoundException e)
                {
                    e.printStackTrace();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
                Solver.lableFile_add(one_label_file);
            }
            else if(filename.contains("gyro"))
            {
                File input=new File(filename);
                Vector <DataACC> one_gyro_file=new Vector<DataACC>(300000);
                try {
                    BufferedReader reader = new BufferedReader(new FileReader(input));
                    String line="";
                    do {
                        line = reader.readLine();
                        if(line==null)
                            break;
                        DataACC singleLine=new DataACC(line);
                        one_gyro_file.add(singleLine);
                    }while(line!=null);
                }
                catch (FileNotFoundException e)
                {
                    e.printStackTrace();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
                Solver.gyroFile_add(one_gyro_file);
            }
            else if(filename.contains("accl"))
            {
                File input=new File(filename);
                Vector <DataACC> one_accl_file=new Vector<DataACC>(300000);
                try {
                    BufferedReader reader = new BufferedReader(new FileReader(input));
                    String line="";
                    do {
                        line = reader.readLine();
                        //System.out.println(line);
                        if(line==null)
                            break;
                        DataACC singleLine=new DataACC(line);
                        one_accl_file.add(singleLine);
                    }while(line!=null);
                }
                catch (FileNotFoundException e)
                {
                    e.printStackTrace();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
                Solver.acclFile_add(one_accl_file);
            }
            else
            {
                File input=new File(filename);
                Vector <DataACC> one_acc_file=new Vector<DataACC>(300000);
                try {
                    BufferedReader reader = new BufferedReader(new FileReader(input));
                    String line="";
                    do {
                        line = reader.readLine();
                        if(line==null)
                            break;
                        DataACC singleLine=new DataACC(line);
                        one_acc_file.add(singleLine);
                    }while(line!=null);
                }
                catch (FileNotFoundException e)
                {
                    e.printStackTrace();
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
                Solver.accFile_add(one_acc_file);
            }
        }
    }
}
