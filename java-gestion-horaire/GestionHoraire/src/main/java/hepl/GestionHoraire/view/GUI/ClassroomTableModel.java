package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.Classroom;

import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
import java.util.List;


/**
 * Modèle de tableau pour l'affichage des locaux
 * Cette classe gère l'affichage des salles de classe dans un JTable
 */
public class ClassroomTableModel extends AbstractTableModel
{

    //---------------ATTRIBUTS---------------

    // Liste des salles de classe à afficher dans le tableau
    private List<Classroom> classrooms;

    // Noms des colonnes du tableau (correspond aux propriétés d'une salle)
    private final String[] columnNames = {"ID", "Nom", "Capacité"};

    //---------------CONSTRUCTEUR---------------

    /**
     * Constructeur avec une liste de locaux
     * Permet d'initialiser le modèle avec des données existantes
     * @param classrooms Liste des locaux à afficher
     */
    public ClassroomTableModel(List<Classroom> classrooms) {
        this.classrooms = new ArrayList<>(classrooms);
    }

    //---------------MÉTHODES AbstractTableModel---------------

    /**
     * Retourne le nombre de lignes dans le tableau
     * Implémentation de l'interface AbstractTableModel
     * @return Nombre de salles dans la liste
     */
    @Override
    public int getRowCount() {
        return classrooms.size();
    }

    /**
     * Retourne le nombre de colonnes dans le tableau
     * Implémentation de l'interface AbstractTableModel
     * @return Nombre de colonnes fixé (3)
     */
    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    /**
     * Retourne le nom de la colonne à l'index spécifié
     * Permet d'afficher les en-têtes dans le JTable
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
    public Class getColumnClass(int columnIndex)
    {
        return switch (columnIndex) {
            case 0, 2 -> Integer.class;
            default -> String.class;
        };
    }

    /**
     * Retourne la valeur à afficher dans une cellule spécifique
     * Méthode centrale pour alimenter le JTable avec les données
     * @param rowIndex Index de ligne (correspond à un local)
     * @param columnIndex Index de colonne (correspond à une propriété)
     * @return Valeur à afficher dans la cellule
     */
    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Classroom classroom = classrooms.get(rowIndex);

        switch (columnIndex) {
            case 0 : return  classroom.getId();
            case 1 : return  classroom.getName();
            case 2 : return  classroom.getSeatingCapacity();
            default : return  null;  // Ne dois jamais arriver si la structure est respectée
        }
    }

    /**
     * Indique si une cellule est éditable
     * Dans notre application, on ne modifie pas directement les cellules
     * @param rowIndex Index de ligne
     * @param columnIndex Index de colonne
     * @return false pour toutes les cellules (non éditables)
     */
    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        // Les cellules ne sont pas éditables directement dans le tableau.
        return false;
    }

    //---------------MÉTHODES D'ACCÈS---------------

    /**
     * Retourne le local à un index spécifique
     * Utilisé pour récupérer un local sélectionné dans la table
     * @param rowIndex Index de ligne dans le tableau
     * @return L'objet Classroom correspondant
     */
    public Classroom getClassroomAt(int rowIndex) {
        return classrooms.get(rowIndex);
    }
}