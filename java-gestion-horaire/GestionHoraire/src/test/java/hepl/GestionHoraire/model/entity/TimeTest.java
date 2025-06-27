package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TimeTest
{
    private Time time;

    @BeforeEach
    public void setUp() {
        time = new Time(14, 30);

    }

    @Test
    public void testGetHour() {
        assertEquals(14, time.getHour());
    }

    @Test
    public void testGetMinute() {
        assertEquals(30, time.getMinute());
    }


    @Test
    public void testSetHour() {
        time.setHour(10);
        assertEquals(10, time.getHour());
    }

    @Test
    public void testSetMinute() {
        time.setMinute(50);
        assertEquals(50, time.getMinute());
    }

    @Test
    public void testToString() {
        String expected = "Time [hour=14, minute=30]";
        assertEquals(expected, time.toString());
    }

    @Test
    public void testEquals() {
        // Même Time (mêmes hour,minute)
        Time sameTime = new Time(14, 30);

        // Time différent
        Time differentTime = new Time(10, 50);

        assertTrue(time.equals(sameTime));
        assertFalse(time.equals(differentTime));
    }
}

