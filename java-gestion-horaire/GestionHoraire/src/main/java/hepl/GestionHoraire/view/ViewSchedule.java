package hepl.GestionHoraire.view;

import hepl.GestionHoraire.controller.Controller;
import hepl.GestionHoraire.model.entity.*;
import java.util.List;

public interface ViewSchedule
{
    // Configuration du contrôleur
    void setController(Controller controller);

    // Affichage des entités
    void displayProfessors(List<Professor> professors);
    void displayGroups(List<Group> groups);
    void displayClassrooms(List<Classroom> classrooms);
    void displayCourses(List<Course> courses);

    // Boîtes de dialogue pour l'ajout/modification
    Professor promptForNewProfessor();
    Group promptForNewGroup();
    Classroom promptForNewClassroom();
    Course promptForNewCourse(List<Professor> professors, List<Classroom> classrooms, List<Group> groups);

    // Sélection d'entités à supprimer
    int promptForProfessorId();
    int promptForGroupId();
    int promptForClassroomId();
    int promptForCourseId();

    // Messages
    void showMessage(String message);
    void showErrorMessage(String message);

    // Authentification
    boolean showLoginDialog();
    void logout();
    String getAuthenticatedUser();

    // Démarrage
    void run();

}