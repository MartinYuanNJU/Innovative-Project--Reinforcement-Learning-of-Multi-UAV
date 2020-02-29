import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DataLabel
{
    public long mrTime;// man read time
    public long meTime;// mechanical time
    public String str;

    static private Pattern pattern1;
    static private Pattern pattern2;

    static void init(){
        pattern1 = Pattern.compile("[0-9.\\-]+");
        pattern2 = Pattern.compile("[a-z_]+");
    }

    DataLabel(String input)
    {
        Matcher matcher = pattern1.matcher(input);
        boolean check = matcher.find();
        assert(check);
        mrTime = Long.valueOf(matcher.group(0));
        check = matcher.find();
        assert(check);
        meTime = Long.valueOf(matcher.group(0));
        matcher = pattern2.matcher(input);
        check = matcher.find();
        assert(check);
        str = String.valueOf(matcher.group(0));
    }
}
