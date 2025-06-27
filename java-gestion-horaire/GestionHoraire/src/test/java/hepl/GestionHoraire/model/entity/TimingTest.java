package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TimingTest
{
    private Timing timing;
    private Time start;
    private Time duration;
    private Time newStart;
    private Time newDuration;

    @BeforeEach
    public void setUp() {
        start = new Time(8, 30);
        duration = new Time(1, 30);
        timing = new Timing(Timing.MONDAY, start, duration);

    }

    @Test
    public void testGetDay() {
        assertEquals(Timing.MONDAY, timing.getDay());
    }

    @Test
    public void testGetStart() {
        assertEquals(start, timing.getStart());
    }

    @Test
    public void testGetDuration() {
        assertEquals(duration, timing.getDuration());
    }

    @Test
    public void testSetDay() {
        timing.setDay(Timing.TUESDAY);
        assertEquals(Timing.TUESDAY, timing.getDay());
    }

    @Test
    public void testSetStart() {
        newStart = new Time(9, 45);
        timing.setStart(newStart);
        assertEquals(newStart, timing.getStart());
    }

    @Test
    public void testSetDuration() {
        newDuration = new Time(2, 0);
        timing.setDuration(newDuration);
        assertEquals(newDuration, timing.getDuration());
    }

    @Test
    public void testToString() {
        String expected = "Timing [day=Lundi, start=Time [hour=8, minute=30], duration=Time [hour=1, minute=30]]";
        assertEquals(expected, timing.toString());
    }

    @Test
    public void testEquals() {
        // Même Timing (mêmes jour, heure de début, durée)
        Timing sameTiming = new Timing(Timing.MONDAY, start, duration);

        // Timing différent
        Timing differentTiming = new Timing(Timing.TUESDAY, newStart, newDuration);

        assertTrue(timing.equals(sameTiming));
        assertFalse(timing.equals(differentTiming));
    }
}




