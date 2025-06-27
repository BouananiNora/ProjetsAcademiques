package hepl.GestionHoraire.model.dao;

import hepl.GestionHoraire.model.DataAccessLayer;
import hepl.GestionHoraire.model.entity.*;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

/**
 * Cette classe implémente l'interface DataAccessLayer et gère le stockage des données
 * de l'application. Elle utilise des listes pour stocker les entités en mémoire.
 * Le pattern DAO (Data Access Object) est utilisé ici pour séparer la logique de persistence
 * du reste de l'application.
 */
public class ScheduleDAO implements DataAccessLayer
{

    //--------------------VARIABLES--------------------

    // Stockage en mémoire des entités
    private List<Professor> professors;
    private List<Group> groups;
    private List<Classroom> classrooms;
    private List<Course> courses;

    // Compteurs pour générer des IDs uniques
    private static int nextProfessorId = 1;
    private static int nextGroupId = 1;
    private static int nextClassroomId = 1;
    private static int nextCourseId = 1;

    // Utilisateur actuel - permet d'isoler les données par utilisateur
    private String currentUser;

    //--------------------CONSTRUCTEUR--------------------

    /**
     * Constructeur simple qui initialise les collections vides.
     * Ne charge pas automatiquement les données.
     */
    public ScheduleDAO() {
        professors = new ArrayList<>();
        groups = new ArrayList<>();
        classrooms = new ArrayList<>();
        courses = new ArrayList<>();
        this.currentUser = "default";
    }

    //--------------------GESTION UTILISATEUR--------------------

    /**
     * Change l'utilisateur actuel et charge ses données.
     * Cette méthode est un exemple de "context switching" où on change
     * complètement l'état du DAO en fonction de l'utilisateur.
     */
    public void changeUser(String username) {
        // Sauvegarder les données de l'utilisateur actuel si nécessaire
        if (!this.currentUser.equals("default")) {
            saveData();
        }

        // Changer l'utilisateur
        this.currentUser = username;


        while(!professors.isEmpty()) {
            professors.remove(0);
        }
        while(!groups.isEmpty()) {
            groups.remove(0);
        }
        while(!classrooms.isEmpty()) {
            classrooms.remove(0);
        }
        while(!courses.isEmpty()) {
            courses.remove(0);
        }

        // Réinitialiser les compteurs
        nextProfessorId = 1;
        nextGroupId = 1;
        nextClassroomId = 1;
        nextCourseId = 1;

        // Charger les données du nouvel utilisateur
        loadData();
    }

    //--------------------OPERATIONS PROFESSEURS (CRUD)--------------------

    /**
     * Ajoute un professeur à la liste et lui attribue un ID.
     * C'est un exemple d'opération CREATE du CRUD.
     */
    @Override
    public int addProfessor(Professor professor) {
        professor.setId(nextProfessorId++);
        professors.add(professor);
        return professor.getId();
    }

    /**
     * Supprime un professeur selon son ID.
     * Exemple d'opération DELETE du CRUD.
     */
    @Override
    public boolean deleteProfessor(int id) {
        boolean removed = false;
        for (int i = 0; i < professors.size(); i++) {
            Professor p = professors.get(i);
            if (p.getId() == id) {
                professors.remove(i);
                removed = true;
                break;
            }
        }
        return removed;
    }

    /**
     * Récupère un professeur selon son ID.
     * Exemple d'opération READ du CRUD.
     */
    @Override
    public Professor getProfessorById(int id) {
        for (Professor p : professors) {
            if (p.getId() == id) {
                return p;
            }
        }
        return null;
    }

    /**
     * Récupère tous les professeurs.
     * READ du CRUD (mais pour une collection).
     */
    @Override
    public List<Professor> getAllProfessors() {
        return new ArrayList<>(professors);
    }

    //--------------------OPERATIONS GROUPES (CRUD)--------------------

    /**
     * Ajoute un groupe et lui attribue un ID unique.
     */
    @Override
    public int addGroup(Group group) {
        group.setId(nextGroupId++);
        groups.add(group);
        return group.getId();
    }

    /**
     * Supprime un groupe selon son ID.
     */
    @Override
    public boolean deleteGroup(int id) {
        boolean removed = false;
        for (int i = 0; i < groups.size(); i++) {
            Group g = groups.get(i);
            if (g.getId() == id) {
                groups.remove(i);
                removed = true;
                break;
            }
        }
        return removed;
    }

    /**
     * Récupère un groupe selon son ID.
     */
    @Override
    public Group getGroupById(int id) {
        for (Group g : groups) {
            if (g.getId() == id) {
                return g;
            }
        }
        return null;
    }

    /**
     * Récupère tous les groupes.
     */
    @Override
    public List<Group> getAllGroups() {
        return new ArrayList<>(groups);
    }

    //--------------------OPERATIONS SALLES (CRUD)--------------------

    /**
     * Ajoute une salle de classe et lui attribue un ID unique.
     */
    @Override
    public int addClassroom(Classroom classroom) {
        classroom.setId(nextClassroomId++);
        classrooms.add(classroom);
        return classroom.getId();
    }

    /**
     * Supprime une salle de classe selon son ID.
     */
    @Override
    public boolean deleteClassroom(int id) {
        boolean removed = false;
        for (int i = 0; i < classrooms.size(); i++) {
            Classroom c = classrooms.get(i);
            if (c.getId() == id) {
                classrooms.remove(i);
                removed = true;
                break;
            }
        }
        return removed;
    }

    /**
     * Récupère une salle de classe selon son ID.
     */
    @Override
    public Classroom getClassroomById(int id) {
        for (Classroom c : classrooms) {
            if (c.getId() == id) {
                return c;
            }
        }
        return null;
    }

    /**
     * Récupère toutes les salles de classe.
     */
    @Override
    public List<Classroom> getAllClassrooms() {
        return new ArrayList<>(classrooms);
    }

    //--------------------OPERATIONS COURS (CRUD)--------------------

    /**
     * Ajoute un cours et lui attribue un ID unique.
     */
    @Override
    public int addCourse(Course course) {
        course.setCode(nextCourseId++);
        courses.add(course);
        return course.getCode();
    }

    /**
     * Supprime un cours selon son ID.
     */
    @Override
    public boolean deleteCourse(int id) {
        boolean removed = false;
        for (int i = 0; i < courses.size(); i++) {
            Course c = courses.get(i);
            if (c.getCode() == id) {
                courses.remove(i);
                removed = true;
                break;
            }
        }
        return removed;
    }

    /**
     * Récupère un cours selon son ID.
     */
    @Override
    public Course getCourseById(int id) {
        for (Course c : courses) {
            if (c.getCode() == id) {
                return c;
            }
        }
        return null;
    }

    /**
     * Récupère tous les cours.
     */
    @Override
    public List<Course> getAllCourses() {
        return new ArrayList<>(courses);
    }

    //--------------------PERSISTANCE DES DONNEES--------------------

    /**
     * Sauvegarde les données en fichiers.
     * Cette méthode utilise la sérialisation Java pour stocker
     * les objets dans des fichiers binaires.
     */
    @Override
    public void saveData() {
        try {
            // Création d'un répertoire data s'il n'existe pas
            File dataDir = new File("data");
            if (!dataDir.exists()) {
                dataDir.mkdir();
            }

            // Création d'un sous-répertoire pour l'utilisateur
            File userDir = new File("data/" + currentUser);
            if (!userDir.exists()) {
                userDir.mkdir();
            }

            // Sauvegarde des professeurs
            FileOutputStream fosProfessors = new FileOutputStream("data/" + currentUser + "/professors.dat");
            ObjectOutputStream oosProfessors = new ObjectOutputStream(fosProfessors);
            oosProfessors.writeObject(professors);
            oosProfessors.close();
            fosProfessors.close();

            // Sauvegarde des groupes
            FileOutputStream fosGroups = new FileOutputStream("data/" + currentUser + "/groups.dat");
            ObjectOutputStream oosGroups = new ObjectOutputStream(fosGroups);
            oosGroups.writeObject(groups);
            oosGroups.close();
            fosGroups.close();

            // Sauvegarde des salles de classe
            FileOutputStream fosClassrooms = new FileOutputStream("data/" + currentUser + "/classrooms.dat");
            ObjectOutputStream oosClassrooms = new ObjectOutputStream(fosClassrooms);
            oosClassrooms.writeObject(classrooms);
            oosClassrooms.close();
            fosClassrooms.close();

            // Sauvegarde des cours
            FileOutputStream fosCourses = new FileOutputStream("data/" + currentUser + "/courses.dat");
            ObjectOutputStream oosCourses = new ObjectOutputStream(fosCourses);
            oosCourses.writeObject(courses);
            oosCourses.close();
            fosCourses.close();

            // Sauvegarde des compteurs d'ID
            Properties idProps = new Properties();
            idProps.put("nextProfessorId", String.valueOf(nextProfessorId));
            idProps.put("nextGroupId", String.valueOf(nextGroupId));
            idProps.put("nextClassroomId", String.valueOf(nextClassroomId));
            idProps.put("nextCourseId", String.valueOf(nextCourseId));

            FileOutputStream fosIds = new FileOutputStream("data/" + currentUser + "/ids.properties");

            // Écrire chaque propriété manuellement
            for (java.util.Enumeration e = idProps.keys(); e.hasMoreElements();) {
                String key = (String) e.nextElement();
                String value = idProps.getProperty(key);
                String line = key + "=" + value + "\n";
                fosIds.write(line.getBytes());
            }

            fosIds.close();

        } catch (IOException e) {
            System.err.println("Erreur lors de la sauvegarde des données : " + e.getMessage());
            e.printStackTrace();
        }
    }

    /**
     * Charge les données depuis les fichiers sauvegardés.
     * Utilise la désérialisation Java pour recréer les objets
     * depuis les fichiers binaires.
     */
    @Override
    public void loadData() {
        try {
            // Vérification des répertoires
            File dataDir = new File("data");
            if (!dataDir.exists()) {
                return; // Pas de données à charger
            }

            File userDir = new File("data/" + currentUser);
            if (!userDir.exists()) {
                return; // Pas de données pour cet utilisateur
            }

            // Chargement des professeurs
            File profFile = new File("data/" + currentUser + "/professors.dat");
            if (profFile.exists()) {
                FileInputStream fisProfessors = new FileInputStream(profFile);
                ObjectInputStream oisProfessors = new ObjectInputStream(fisProfessors);
                professors = (List<Professor>) oisProfessors.readObject();
                oisProfessors.close();
                fisProfessors.close();
            }

            // Chargement des groupes
            File groupFile = new File("data/" + currentUser + "/groups.dat");
            if (groupFile.exists()) {
                FileInputStream fisGroups = new FileInputStream(groupFile);
                ObjectInputStream oisGroups = new ObjectInputStream(fisGroups);
                groups = (List<Group>) oisGroups.readObject();
                oisGroups.close();
                fisGroups.close();
            }

            // Chargement des salles de classe
            File classroomFile = new File("data/" + currentUser + "/classrooms.dat");
            if (classroomFile.exists()) {
                FileInputStream fisClassrooms = new FileInputStream(classroomFile);
                ObjectInputStream oisClassrooms = new ObjectInputStream(fisClassrooms);
                classrooms = (List<Classroom>) oisClassrooms.readObject();
                oisClassrooms.close();
                fisClassrooms.close();
            }

            // Chargement des cours
            File courseFile = new File("data/" + currentUser + "/courses.dat");
            if (courseFile.exists()) {
                FileInputStream fisCourses = new FileInputStream(courseFile);
                ObjectInputStream oisCourses = new ObjectInputStream(fisCourses);
                courses = (List<Course>) oisCourses.readObject();
                oisCourses.close();
                fisCourses.close();
            }

            // Chargement des compteurs d'ID
            File idFile = new File("data/" + currentUser + "/ids.properties");
            if (idFile.exists()) {
                Properties idProps = new Properties();
                FileInputStream fisIds = new FileInputStream(idFile);
                idProps.load(fisIds);  // J'utilise load ici car c'est plus simple et fiable
                fisIds.close();

                nextProfessorId = Integer.parseInt(idProps.getProperty("nextProfessorId", "1"));
                nextGroupId = Integer.parseInt(idProps.getProperty("nextGroupId", "1"));
                nextClassroomId = Integer.parseInt(idProps.getProperty("nextClassroomId", "1"));
                nextCourseId = Integer.parseInt(idProps.getProperty("nextCourseId", "1"));
            }

        } catch (Exception e) {
            System.err.println("Erreur lors du chargement des données : " + e.getMessage());
            e.printStackTrace();
        }
    }

    //--------------------IMPORTATION CSV--------------------

    /**
     * Importe des professeurs depuis un fichier CSV.
     * Traite les en-têtes et crée un objet Professor pour chaque ligne.
     */
    @Override
    public boolean importProfessorsFromCSV(String filename) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(filename));
            String line;

            // Ignorer la première ligne si c'est un en-tête
            line = reader.readLine();
            if (line.toLowerCase().contains("nom") || line.toLowerCase().contains("prenom")) {
                // C'est un en-tête, on lit la ligne suivante
                line = reader.readLine();
            }

            // Traiter toutes les lignes
            while (line != null) {
                String[] data = line.split(";");
                if (data.length >= 2) {
                    // Créer un nouveau professeur avec ID temporaire = 0
                    Professor prof = new Professor(0, data[0], data[1]);

                    // La méthode addProfessor va attribuer un nouvel ID
                    addProfessor(prof);
                }

                // Lire la ligne suivante
                line = reader.readLine();
            }

            reader.close();
            saveData();
            return true;
        } catch (IOException e) {
            System.err.println("Erreur lors de l'importation des professeurs : " + e.getMessage());
            return false;
        }
    }

    /**
     * Importe des groupes depuis un fichier CSV.
     * Similaire à importProfessorsFromCSV mais adapté aux groupes.
     */
    @Override
    public boolean importGroupsFromCSV(String filename) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(filename));
            String line;

            line = reader.readLine();
            if (line.toLowerCase().contains("nom") || line.toLowerCase().contains("groupe")) {
                line = reader.readLine();
            }

            while (line != null) {
                String[] data = line.split(";");
                if (data.length >= 1) {
                    Group group = new Group(0, data[0]);

                    addGroup(group);
                }

                line = reader.readLine();
            }

            reader.close();
            saveData();
            return true;
        } catch (IOException e) {
            System.err.println("Erreur lors de l'importation des groupes : " + e.getMessage());
            return false;
        }
    }

    /**
     * Importe des salles de classe depuis un fichier CSV.
     * Traite la capacité des salles en la convertissant en entier.
     */
    @Override
    public boolean importClassroomsFromCSV(String filename) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(filename));
            String line;

            line = reader.readLine();
            if (line.toLowerCase().contains("nom") || line.toLowerCase().contains("capacité") ||
                    line.toLowerCase().contains("local")) {
                line = reader.readLine();
            }

            while (line != null) {
                String[] data = line.split(";");
                if (data.length >= 2) {
                    String name = data[0];
                    int capacity = 0;

                    try {
                        capacity = Integer.parseInt(data[1]);
                    } catch (NumberFormatException e) {
                        System.err.println("Erreur de format pour la capacité: " + data[1]);
                        capacity = 0; // Valeur par défaut
                    }

                    Classroom classroom = new Classroom(0, name, capacity);

                    addClassroom(classroom);
                }

                line = reader.readLine();
            }

            reader.close();
            saveData();
            return true;
        } catch (IOException e) {
            System.err.println("Erreur lors de l'importation des locaux : " + e.getMessage());
            return false;
        }
    }
}