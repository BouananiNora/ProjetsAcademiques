package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class GroupTest
{
    private Group group;

    @BeforeEach
    public void setUp() {
        group = new Group(1, "INFO2 D201");
    }

    @Test
    public void testGetId() {
        assertEquals(1, group.getId());
    }

    @Test
    public void testGetName() {
        assertEquals("INFO2 D201", group.getName());
    }


    @Test
    public void testSetId() {
        group.setId(2);
        assertEquals(2, group.getId());
    }

    @Test
    public void testSetName() {
        group.setName("INFO2 R202");
        assertEquals("INFO2 R202", group.getName());
    }

    @Test
    public void testToString() {
        String expected = "Group [id=1, name=INFO2 D201]";
        assertEquals(expected, group.toString());
    }

    @Test
    public void testEquals() {
        // Même group (mêmes id, name)
        Group sameGroup = new Group(1, "INFO2 D201");

        // Group différent
        Group differentGroup = new Group(2, "INFO2 R202");

        assertTrue(group.equals(sameGroup));
        assertFalse(group.equals(differentGroup));
    }
}
