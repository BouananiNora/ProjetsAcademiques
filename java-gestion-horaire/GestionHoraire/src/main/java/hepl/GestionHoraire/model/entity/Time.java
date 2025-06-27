package hepl.GestionHoraire.model.entity;
import java.io.Serializable;

public class Time implements Serializable
{
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------

    private int hour;
    private int minute;

    //---------------constructeur---------------

    // Constructeur defaut
    public Time() {
        hour = 0;
        minute = 0;
    }

    // Constructeur init
    public Time(int hour, int minute) {
        this.hour = hour;
        this.minute = minute;
    }

    //---------------accesseurs---------------

    //get
    public int getHour() {
        return hour;
    }

    public int getMinute() {
        return minute;
    }

    //set
    public void setHour(int hour) {
        this.hour = hour;
    }

    public void setMinute(int minute) {
        this.minute = minute;
    }

    //---------------methode---------------

    @Override
    public String toString() {
        return "Time [hour=" + hour + ", minute=" + minute + "]";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Time other = (Time) obj;
        return hour == other.hour && minute == other.minute;
    }

}
