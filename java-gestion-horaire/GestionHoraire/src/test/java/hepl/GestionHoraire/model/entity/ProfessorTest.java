package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class ProfessorTest
{

    private Professor professor;

    @BeforeEach
    public void setUp() {
        professor = new Professor(1, "Dupont", "Jean");
    }

    @Test
    public void testGetId() {
        assertEquals(1, professor.getId());
    }

    @Test
    public void testGetlastName() {
        assertEquals("Dupont", professor.getlastName());
    }

    @Test
    public void testGetfirstName() {
        assertEquals("Jean", professor.getfirstName());
    }


    @Test
    public void testSetId() {
        professor.setId(2);
        assertEquals(2, professor.getId());
    }

    @Test
    public void testSetlastName() {
        professor.setlastName("Martin");
        assertEquals("Martin", professor.getlastName());
    }

    @Test
    public void testSetfirstName() {
        professor.setfirstName("Pierre");
        assertEquals("Pierre", professor.getfirstName());
    }


    @Test
    public void testToString() {
        String expected = "Professor [id=1, lastName=Dupont, firstName=Jean]";
        assertEquals(expected, professor.toString());
    }

    @Test
    public void testEquals() {
        // Même Professor (mêmes id, lastName et firstName)
        Professor sameProfessor = new Professor(1, "Dupont", "Jean");

        // Professor différent
        Professor differentProfessor = new Professor(2, "Martin", "Pierre");

        assertTrue(professor.equals(sameProfessor));
        assertFalse(professor.equals(differentProfessor));
    }
}