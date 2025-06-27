package hepl.GestionHoraire.model.entity;


import java.io.Serializable;

public class Timing implements Serializable
{
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------
    private String day;
    private Time start;
    private Time duration;

    public static final String MONDAY = "Lundi";
    public static final String TUESDAY = "Mardi";
    public static final String WEDNESDAY = "Mercredi";
    public static final String THURSDAY = "Jeudi";
    public static final String FRIDAY = "Vendredi";
    public static final String SATURDAY = "Samedi";
    public static final String SUNDAY = "Dimanche";

    //---------------constructeur---------------

    // Constructeur defaut
    public Timing() {
        day = MONDAY;
        start = new Time();
        duration = new Time();
    }

    public Timing(String day, Time start, Time duration) {
        this.day = day;
        this.start = start;
        this.duration = duration;
    }


    //---------------accesseurs---------------

    //get
    public String getDay() {
        return day;
    }

    public Time getStart() {
        return start;
    }

    public Time getDuration() {
        return duration;
    }

    //set
    public void setDay(String day) {
        this.day = day;
    }

    public void setStart(Time start) {
        this.start = start;
    }

    public void setDuration(Time duration) {
        this.duration = duration;
    }


    //---------------methode---------------

    @Override
    public String toString() {
        return "Timing [day="+ day + ", start=" + start +  ", duration=" + duration + "]";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Timing other = (Timing) obj;
        return day.equals(other.day) &&
                start.equals(other.start) &&
                duration.equals(other.duration);
    }
}
