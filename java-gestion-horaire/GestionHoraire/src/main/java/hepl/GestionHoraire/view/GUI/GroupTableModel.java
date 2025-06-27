package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.Group;

import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
import java.util.List;


/**
 * Modèle de tableau pour l'affichage des groupes
 * Cette classe gère l'affichage des groupes dans un JTable
 */
public class GroupTableModel extends AbstractTableModel
{

    //---------------ATTRIBUTS---------------

    // Liste des groupes à afficher dans le tableau
    private List<Group> groups;

    // Noms des colonnes du tableau (correspond aux propriétés d'un groupe)
    private final String[] columnNames = {"ID", "Nom"};

    //---------------CONSTRUCTEUR---------------

    /**
     * Constructeur avec une liste de groupes
     * Permet d'initialiser le modèle avec des données existantes
     * @param groups Liste des groupes à afficher
     */
    public GroupTableModel(List<Group> groups) {
        this.groups = new ArrayList<>(groups);
    }

    //---------------MÉTHODES AbstractTableModel---------------

    /**
     * Retourne le nombre de lignes dans le tableau
     * Implémentation de l'interface AbstractTableModel
     * @return Nombre de groupes dans la liste
     */
    @Override
    public int getRowCount() {
        return groups.size();
    }

    /**
     * Retourne le nombre de colonnes dans le tableau
     * Implémentation de l'interface AbstractTableModel
     * @return Nombre de colonnes fixé (2)
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
    public Class getColumnClass(int columnIndex) {
        if (columnIndex == 0) {
            return Integer.class;
        }
        return String.class;
    }

    /**
     * Retourne la valeur à afficher dans une cellule spécifique
     * Méthode centrale pour alimenter le JTable avec les données
     * @param rowIndex Index de ligne (correspond à un groupe)
     * @param columnIndex Index de colonne (correspond à une propriété)
     * @return Valeur à afficher dans la cellule
     */
    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Group group = groups.get(rowIndex);

        switch (columnIndex) {
            case 0: return group.getId();
            case 1: return group.getName();
            default:
                return null;  // Ne devrait jamais arriver si la structure est respectée
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
        // Les cellules ne sont pas éditables directement dans le tableau
        return false;
    }

    //---------------MÉTHODES D'ACCÈS---------------

    /**
     * Retourne le groupe à un index spécifique
     * Utilisé pour récupérer un groupe sélectionné dans la table
     * @param rowIndex Index de ligne dans le tableau
     * @return L'objet Group correspondant
     */
    public Group getGroupAt(int rowIndex) {
        return groups.get(rowIndex);
    }
}