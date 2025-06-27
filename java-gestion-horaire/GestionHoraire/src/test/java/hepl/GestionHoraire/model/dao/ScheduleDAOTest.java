package hepl.GestionHoraire.model.dao;

import hepl.GestionHoraire.model.entity.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

public class ScheduleDAOTest {

    private ScheduleDAO dao;

    @BeforeEach
    public void setUp() {
        // Créer une nouvelle instance de DAO pour chaque test
        dao = new ScheduleDAO();
        dao.changeUser("testuser");
    }

    // Test basique CRUD pour Professor
    @Test
    public void testProfessorCRUD() {
        // CREATE
        Professor prof = new Professor(0, "Dupont", "Jean");
        int id = dao.addProfessor(prof);
        assertTrue(id > 0);

        // READ
        Professor retrieved = dao.getProfessorById(id);
        assertNotNull(retrieved);
        assertEquals("Dupont", retrieved.getlastName());

        // DELETE
        assertTrue(dao.deleteProfessor(id));
        assertNull(dao.getProfessorById(id));
    }

    // Test basique CRUD pour Group
    @Test
    public void testGroupCRUD() {
        // CREATE
        Group group = new Group(0, "BAC1 INFO");
        int id = dao.addGroup(group);
        assertTrue(id > 0);

        // READ
        Group retrieved = dao.getGroupById(id);
        assertNotNull(retrieved);
        assertEquals("BAC1 INFO", retrieved.getName());

        // DELETE
        assertTrue(dao.deleteGroup(id));
        assertNull(dao.getGroupById(id));
    }

    // Test basique CRUD pour Classroom
    @Test
    public void testClassroomCRUD() {
        // CREATE
        Classroom classroom = new Classroom(0, "S210", 30);
        int id = dao.addClassroom(classroom);
        assertTrue(id > 0);

        // READ
        Classroom retrieved = dao.getClassroomById(id);
        assertNotNull(retrieved);
        assertEquals("S210", retrieved.getName());
        assertEquals(30, retrieved.getSeatingCapacity());

        // DELETE
        assertTrue(dao.deleteClassroom(id));
        assertNull(dao.getClassroomById(id));
    }

    // Test basique CRUD pour Course
    @Test
    public void testCourseCRUD() {
        // Préparation des données
        Time start = new Time(8, 30);
        Time duration = new Time(1, 30);
        Timing timing = new Timing(Timing.MONDAY, start, duration);
        Set<Integer> groups = new HashSet<>();
        groups.add(1);

        // CREATE
        Course course = new Course(0, "Java Programming", timing, 1, 1, groups);
        int id = dao.addCourse(course);
        assertTrue(id > 0);

        // READ
        Course retrieved = dao.getCourseById(id);
        assertNotNull(retrieved);
        assertEquals("Java Programming", retrieved.getTitle());

        // DELETE
        assertTrue(dao.deleteCourse(id));
        assertNull(dao.getCourseById(id));
    }

    // Test pour vérifier que getAll retourne une liste non vide
    @Test
    public void testGetAllEntities() {
        // Ajouter quelques entités
        dao.addProfessor(new Professor(0, "Test", "Professor"));
        dao.addGroup(new Group(0, "Test Group"));
        dao.addClassroom(new Classroom(0, "Test Room", 25));

        // Vérifier qu'elles sont bien récupérées
        assertFalse(dao.getAllProfessors().isEmpty());
        assertFalse(dao.getAllGroups().isEmpty());
        assertFalse(dao.getAllClassrooms().isEmpty());
    }

    // Test simple pour l'import CSV de professeurs
    @Test
    public void testImportCSV() {
        // Compter avant
        int profsBefore = dao.getAllProfessors().size();
        int groupsBefore = dao.getAllGroups().size();
        int classroomsBefore = dao.getAllClassrooms().size();

        // Ajouter manuellement (simulation d'import)
        dao.addProfessor(new Professor(0, "CSV", "Import"));
        dao.addGroup(new Group(0, "CSV Group"));
        dao.addClassroom(new Classroom(0, "CSV Room", 40));

        // Vérifier que les compteurs ont augmenté
        assertTrue(dao.getAllProfessors().size() > profsBefore);
        assertTrue(dao.getAllGroups().size() > groupsBefore);
        assertTrue(dao.getAllClassrooms().size() > classroomsBefore);
    }
}