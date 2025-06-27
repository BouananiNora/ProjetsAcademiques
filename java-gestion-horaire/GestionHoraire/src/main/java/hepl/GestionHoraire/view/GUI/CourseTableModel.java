package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.*;

import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Modèle de tableau pour l'affichage des cours
 * Cette classe permet d'afficher les données des cours dans un JTable
 */
public class CourseTableModel extends AbstractTableModel {

    //---------------ATTRIBUTS---------------

    // Liste des cours à afficher dans le tableau
    private List<Course> courses;

    // Noms des colonnes du tableau
    private final String[] columnNames = {"ID", "Jour", "Heure", "Durée", "Local", "Titre", "Professeur", "Groupes"};

    // Ces maps permettent de convertir les ID stockés dans Course en noms lisibles
    private Map<Integer, Professor> professorsMap;
    private Map<Integer, Classroom> classroomsMap;
    private Map<Integer, Group> groupsMap;

    //---------------CONSTRUCTEUR---------------

    /**
     * Constructeur avec une liste de cours (sans références)
     * Initialise le modèle avec la liste fournie mais sans les maps de référence
     * @param courses Liste des cours à afficher
     */
    public CourseTableModel(List<Course> courses) {
        // On crée une copie de la liste pour éviter les problèmes de référence
        this.courses = new ArrayList<>(courses);
        this.professorsMap = null;
        this.classroomsMap = null;
        this.groupsMap = null;
    }

    //---------------MÉTHODES DE CONFIGURATION---------------

    /**
     * Définit les maps de référence pour la résolution des noms
     * Cette méthode est essentielle pour afficher des noms au lieu des IDs
     * @param professors Map des professeurs (id -> professeur)
     * @param classrooms Map des locaux (id -> local)
     * @param groups Map des groupes (id -> groupe)
     */
    public void setReferenceMaps(Map<Integer, Professor> professors,
                                 Map<Integer, Classroom> classrooms,
                                 Map<Integer, Group> groups) {
        this.professorsMap = professors;
        this.classroomsMap = classrooms;
        this.groupsMap = groups;
    }

    //---------------MÉTHODES DE AbstractTableModel---------------

    /**
     * Retourne le nombre de lignes dans le tableau
     * @return Nombre de cours dans la liste
     */
    @Override
    public int getRowCount() {
        return courses.size();
    }

    /**
     * Retourne le nombre de colonnes dans le tableau
     * @return Nombre de colonnes définies dans columnNames
     */
    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    /**
     * Retourne le nom de la colonne à l'index spécifié
     * Permet d'afficher des en-têtes compréhensibles dans le JTable
     * @param column Index de colonne
     * @return Nom de la colonne
     */
    @Override
    public String getColumnName(int column) {
        return columnNames[column];
    }

    /**
     * Retourne la classe des données de la colonne
     * Important pour le rendu correct des données (formatage)
     * @param columnIndex Index de colonne
     * @return Classe des données (Integer ou String)
     */
    @Override
    public Class getColumnClass(int columnIndex) {
        if (columnIndex == 0) {
            return Integer.class;
        }
        return String.class;
    }

    /**
     * Retourne la valeur à afficher dans une cellule spécifique
     * Méthode centrale du modèle qui renvoie les données pour chaque cellule
     * @param rowIndex Index de ligne (correspond à un cours)
     * @param columnIndex Index de colonne (correspond à une propriété)
     * @return Valeur à afficher dans la cellule
     */
    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        // Récupère le cours correspondant à la ligne demandée
        Course course = courses.get(rowIndex);

        // Selon la colonne, retourne la valeur appropriée
        switch (columnIndex) {
            case 0: // ID
                return course.getCode();

            case 1: // Jour
                if (course.getTiming() != null) {
                    return course.getTiming().getDay();
                }
                return "";

            case 2: // Heure
                if (course.getTiming() != null && course.getTiming().getStart() != null) {
                    Time start = course.getTiming().getStart();
                    return start.getHour() + ":" + start.getMinute();
                }
                return "";

            case 3: // Durée
                if (course.getTiming() != null && course.getTiming().getDuration() != null) {
                    Time duration = course.getTiming().getDuration();
                    return duration.getHour() + ":" + duration.getMinute();
                }
                return "";

            case 4: // Local
                // Relation 1-1 : un cours a un seul local
                if (classroomsMap != null && classroomsMap.containsKey(course.getClassroomId())) {
                    return classroomsMap.get(course.getClassroomId()).getName();
                }
                return "Local #" + course.getClassroomId();

            case 5: // Titre
                return course.getTitle();

            case 6: // Professeur
                // Relation 1-1 : un cours a un seul professeur
                if (professorsMap != null && professorsMap.containsKey(course.getProfessorId())) {
                    Professor prof = professorsMap.get(course.getProfessorId());
                    return prof.getlastName() + " " + prof.getfirstName();
                }
                return "Prof #" + course.getProfessorId();

            case 7: // Groupes
                // Relation 1-n : un cours peut avoir plusieurs groupes
                if (groupsMap != null)
                {
                    StringBuffer groups = new StringBuffer();

                    // Parcourt tous les groupes du cours
                    for (Integer groupId : course.getGroupsIds()) {
                        // Ajoute une virgule entre les groupes, sauf pour le premier
                        if (groups.length() > 0) {
                            groups.append(", ");
                        }

                        // Cherche le groupe dans la map et ajoute son nom
                        Group group = groupsMap.get(groupId);
                        if (group != null) {
                            groups.append(group.getName());
                        } else {
                            groups.append("Groupe #").append(groupId);
                        }
                    }
                    return groups.toString();
                }
                return course.getGroupsIds().toString();

            default:
                return null;  // Ne devrait jamais arriver si la structure est respectée
        }
    }

    /**
     * Indique si une cellule est éditable
     * Dans notre application, les cours ne sont pas modifiables directement
     * @param rowIndex Index de ligne
     * @param columnIndex Index de colonne
     * @return false pour toutes les cellules (non éditables)
     */
    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        // Les cours ne sont pas directement éditables dans le tableau
        return false;
    }

    //---------------MÉTHODES D'ACCÈS---------------

    /**
     * Retourne le cours à l'index spécifié
     * Utilisé pour récupérer un cours sélectionné dans la table
     * @param rowIndex Index de ligne
     * @return Le cours correspondant à la ligne
     */
    public Course getCourseAt(int rowIndex) {
        return courses.get(rowIndex);
    }
}