package hepl.GestionHoraire.model;

import hepl.GestionHoraire.model.entity.*;
import java.util.List;

public interface DataAccessLayer {

    //user
    public void changeUser(String username);

    // Professors
    int addProfessor(Professor professor);
    boolean deleteProfessor(int id);
    Professor getProfessorById(int id);
    List<Professor> getAllProfessors();

    // Groups
    int addGroup(Group group);
    boolean deleteGroup(int id);
    Group getGroupById(int id);
    List<Group> getAllGroups();

    // Classrooms
    int addClassroom(Classroom classroom);
    boolean deleteClassroom(int id);
    Classroom getClassroomById(int id);
    List<Classroom> getAllClassrooms();

    // Courses
    int addCourse(Course course);
    boolean deleteCourse(int id);
    Course getCourseById(int id);
    List<Course> getAllCourses();

    // Sauvegarde/Chargement des données
    void saveData();
    void loadData();

    // Méthodes pour l'import/export
    boolean importProfessorsFromCSV(String filename);
    boolean importGroupsFromCSV(String filename);
    boolean importClassroomsFromCSV(String filename);



}