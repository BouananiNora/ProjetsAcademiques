package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;


public class ClassroomTest
{
    private Classroom classroom;

    @BeforeEach
    public void setUp() {
        classroom = new Classroom(1, "AN", 100);
    }

    @Test
    public void testGetId() {
        assertEquals(1, classroom.getId());
    }

    @Test
    public void testGetName() {
        assertEquals("AN", classroom.getName());
    }

    @Test
    public void testGetSeatingCapacity() {
        assertEquals(100, classroom.getSeatingCapacity());
    }


    @Test
    public void testSetId() {
        classroom.setId(2);
        assertEquals(2, classroom.getId());
    }

    @Test
    public void testSetName() {
        classroom.setName("AE");
        assertEquals("AE", classroom.getName());
    }

    @Test
    public void testSetseatingCapacity() {
        classroom.setSeatingCapacity(150);
        assertEquals(150, classroom.getSeatingCapacity());
    }


    @Test
    public void testToString() {
        String expected = "Classroom [id=1, name=AN, seatingCapacity=100]";
        assertEquals(expected, classroom.toString());
    }

    @Test
    public void testEquals() {
        // Même Classroom (mêmes id, name et seatingCapacity)
        Classroom sameClassroom = new Classroom(1, "AN", 100);

        // Classroom différent
        Classroom differentClassroom = new Classroom(2, "AE", 150);

        assertTrue(classroom.equals(sameClassroom));
        assertFalse(classroom.equals(differentClassroom));
    }
}
