package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.time.LocalDate;
import static org.junit.jupiter.api.Assertions.*;

public class EventTest
{
    private Event event;
    private Time start;
    private Time duration;
    private Timing t;
    private LocalDate eventDate;
    private LocalDate newDate;

    @BeforeEach
    public void setUp() {
        event = new Event(1, "Theorie C++");

        start = new Time(8, 30);
        duration = new Time(1, 30);
        t = new Timing(Timing.MONDAY, start, duration);
        event.setTiming(t);

        eventDate = LocalDate.of(2024, 5, 15);
        event.setEventDate(eventDate);
    }

    @Test
    public void testGetCode() {
        assertEquals(1, event.getCode());
    }

    @Test
    public void testGetTitle() {
        assertEquals("Theorie C++", event.getTitle());
    }

    @Test
    public void testGetTiming() {
         start = new Time(8, 30);
         duration = new Time(1, 30);
         t = new Timing(Timing.MONDAY, start, duration);
        assertEquals(t, event.getTiming());
    }

    @Test
    public void testGetEventDate() {
        assertEquals(eventDate, event.getEventDate());
    }


    @Test
    public void testSetCode() {
        event.setCode(2);
        assertEquals(2, event.getCode());
    }

    @Test
    public void testSetTitle() {
        event.setTitle("Labo C/Linux");
        assertEquals("Labo C/Linux", event.getTitle());
    }

    @Test
    public void testSetTiming() {
        start = new Time(10, 30);
        duration = new Time(0, 90);
        t = new Timing(Timing.TUESDAY, start, duration);
        event.setTiming(t);
        assertEquals(t, event.getTiming());
    }

    @Test
    public void testSetEventDate() {
        newDate = LocalDate.of(2024, 6, 1);
        event.setEventDate(newDate);
        assertEquals(newDate, event.getEventDate());
    }


    @Test
    public void testEquals() {
        // Même Event (mêmes id, lastName et firstName)
        Event sameEvent = new Event(1, "Theorie C++");

        // Event différent
        Event differentEvent = new Event(2, "Labo C/Linux");

        assertTrue(event.equals(sameEvent));
        assertFalse(event.equals(differentEvent));
    }

    @Test
    public void testToString() {
        String expected = "Event [code=1, title=Theorie C++, timing=Timing [day=Lundi, start=Time [hour=8, minute=30], duration=Time [hour=1, minute=30]], eventDate=2024-05-15]";
        assertEquals(expected, event.toString());
    }
}
