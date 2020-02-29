import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DataACC {
    public long mrTime;// man read time
    public long meTime;// mechanical time
    public double x;
    public double y;
    public double z;

    static private Pattern pattern;

    static void init(){pattern = Pattern.compile("[0-9.\\-]+");}

    DataACC(String input){
        Matcher matcher = pattern.matcher(input);
        boolean check = matcher.find();
        assert(check);
        mrTime = Long.valueOf(matcher.group(0));
        check = matcher.find();
        assert(check);
        meTime = Long.valueOf(matcher.group(0));
        check = matcher.find();
        assert(check);
        x = Double.valueOf(matcher.group(0));
        check = matcher.find();
        assert(check);
        y = Double.valueOf(matcher.group(0));
        check = matcher.find();
        assert(check);
        z = Double.valueOf(matcher.group(0));
    }
}