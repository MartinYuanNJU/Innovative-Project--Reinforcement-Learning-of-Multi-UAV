import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class CreateArff {
    private File file;
    private FileWriter filewrite;
    private BufferedWriter bufferedWriter;

    private boolean isStartDateWriting;

    public int attributeNum;

    public CreateArff(boolean is_new_file, String filepath, String relation) {
        file = new File(filepath+".arff");
        assert((file.exists() && is_new_file)
                || (!file.exists() && !is_new_file));



        try {
            if(is_new_file)
                file.createNewFile();

            assert(file.exists());
            filewrite = new FileWriter(file.getAbsoluteFile());
            bufferedWriter = new BufferedWriter(filewrite);
            bufferedWriter.write("@relation \""+relation+"\"");
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

        attributeNum = 0;
        isStartDateWriting = false;
    }

    public void addAttirbute(String name, String type) {
        assert(!isStartDateWriting);

        attributeNum++;
        try {
            bufferedWriter.write("@attribute '"+name+"' "+type);
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void startData() {
        try {
            bufferedWriter.write("@data");
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        isStartDateWriting = true;
    }

    public void addData(String[] data){
        assert(data.length == attributeNum);
        assert(isStartDateWriting);

        int len = data.length;
        try {
            for(int i=0;i < len;i++){
                if(i < len-1)
                    bufferedWriter.write(data[i]+",");
                else
                    bufferedWriter.write(data[i]);
            }
            bufferedWriter.newLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void finished() {
        try {
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
