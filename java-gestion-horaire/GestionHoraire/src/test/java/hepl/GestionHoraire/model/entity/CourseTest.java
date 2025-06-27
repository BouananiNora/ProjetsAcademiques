package hepl.GestionHoraire.model.entity;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.HashSet;
import java.util.Set;
import static org.junit.jupiter.api.Assertions.*;

public class CourseTest
{
    private Course course;
    private Time start;
    private Time duration;
    private Timing timing;
    private Set<Integer> groupsIds;
    private Set<Integer> retrievedGroups;
    private Set<Integer> newGroups;

    @BeforeEach
    public void setUp()
    {
        start = new Time(8, 30);
        duration = new Time(1, 30);
        timing = new Timing(Timing.MONDAY, start, duration);

        groupsIds = new HashSet<>();
        groupsIds.add(101);
        groupsIds.add(102);

        course = new Course(3, "Programmation Java", timing, 10, 5, groupsIds);

    }

    @Test
    public void testGetCode() {
        assertEquals(3, course.getCode());
    }

    @Test
    public void testGetTitle() {
        assertEquals("Programmation Java", course.getTitle());
    }

    @Test
    public void testGetTiming() {
        assertEquals(timing, course.getTiming());
    }

    @Test
    public void testGetProfessorId() {
        assertEquals(10, course.getProfessorId());
    }

    @Test
    public void testGetClassroomId() {
        assertEquals(5, course.getClassroomId());
    }

    @Test
    public void testGetGroupsIds() {
        retrievedGroups = course.getGroupsIds();
        assertEquals(2, retrievedGroups.size());
    }

    @Test
    public void testSetCode() {
        course.setCode(4);
        assertEquals(4, course.getCode());
    }

    @Test
    public void testSetTitle() {
        course.setTitle("Labo C/Linux");
        assertEquals("Labo C/Linux", course.getTitle());
    }

    @Test
    public void testSetTiming() {
        start = new Time(10, 30);
        duration = new Time(0, 90);
        timing = new Timing(Timing.TUESDAY, start, duration);
        course.setTiming(timing);
        assertEquals(timing, course.getTiming());
    }

    @Test
    public void testSetProfessorId() {
        course.setProfessorId(11);
        assertEquals(11, course.getProfessorId());
    }

    @Test
    public void testSetClassroomId() {
        course.setClassroomId(6);
        assertEquals(6, course.getClassroomId());
    }

    @Test
    public void testSetGroupsIds() {
        newGroups = new HashSet<>();
        newGroups.add(201);
        newGroups.add(202);
        newGroups.add(203);

        course.setGroupsIds(newGroups);

        retrievedGroups = course.getGroupsIds();
        assertEquals(3, retrievedGroups.size());
    }

    @Test
    public void testAddGroupId() {
        course.addGroupId(103);
        groupsIds = course.getGroupsIds();
        assertEquals(3, groupsIds.size());
    }

    @Test
    public void testToString() {
        String expected = "Course [code=3, title=Programmation Java, timing=" + timing.toString()
                + ", professorId=10, classroomId=5, groupsIds=" + groupsIds.toString() + "]";
        assertEquals(expected, course.toString());
    }

    @Test
    public void testEquals() {
        // Même cours avec même timing - devrait être égal
        Course sameCourse = new Course(3, "Programmation Java", timing, 10, 5, groupsIds);

        // Cours avec timing différent - ne devrait pas être égal
        Time diffStart = new Time(9, 30);
        Time diffDuration = new Time(1, 0);
        Timing diffTiming = new Timing(Timing.WEDNESDAY, diffStart, diffDuration);
        Course differentCourse = new Course(3, "Programmation Java", diffTiming, 10, 5, groupsIds);

        assertTrue(course.equals(sameCourse));
        assertFalse(course.equals(differentCourse));

    }
}

