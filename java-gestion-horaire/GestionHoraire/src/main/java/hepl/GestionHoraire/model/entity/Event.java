package hepl.GestionHoraire.model.entity;

import java.time.LocalDate;
import java.io.Serializable;
public class Event implements Identifiable, Serializable
{
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------

    private int code;
    private String title;
    private Timing timing;
    private LocalDate eventDate;
    private static int currentCode = 1;

    //---------------constructeur---------------

    // Constructeur defaut
    public Event() {
        this.code = currentCode;
        title = "";
        timing = null;
        eventDate = LocalDate.now();
    }

    // Constructeur init
    public Event(int code, String title) {
        this.code = code;
        this.title = title;
        this.timing = null;
        this.eventDate = LocalDate.now();
    }


    //---------------accesseurs---------------

    //get
    @Override
    public int getId() {
        return this.code;
    }

    public int getCode() {
        return code;
    }

    public String getTitle() {
        return title;
    }

    public Timing getTiming() {
        return timing;
    }

    public LocalDate getEventDate() {
        return eventDate;
    }

    //set
    public void setCode(int code) {
        this.code = code;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setTiming(Timing timing) {
        this.timing = timing;
    }

    public void setEventDate(LocalDate eventDate) {
        this.eventDate = eventDate;
    }

    //---------------methode---------------

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Event other = (Event) obj;
        return code == other.code;
    }

    @Override
    public String toString() {
        return "Event [code=" + code + ", title=" + title + ", timing=" + timing + ", eventDate=" + eventDate + "]";
    }
}