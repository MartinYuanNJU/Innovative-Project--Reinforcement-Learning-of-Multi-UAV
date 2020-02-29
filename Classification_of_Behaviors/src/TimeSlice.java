public class TimeSlice {
    long start;
    long end;
    String label;

    TimeSlice(long start, String label){
        this.start = start;
        this.end = -1;
        this.label = label;
    }

    void setEnd(long end){
        this.end = end;
    }
}
