package hepl.GestionHoraire.view.GUI;

import java.io.File;
import javax.swing.filechooser.FileFilter;

/**
 * Classe FiltreFichiers - Filtre personnalisé pour les boîtes de dialogue de sélection de fichiers
 *
 * Cette classe permet de filtrer les fichiers affichés dans un JFileChooser
 * en fonction de leurs extensions. Utile pour limiter la sélection aux fichiers
 * d'un certain type (.csv, .txt, etc.)
 */
public class FiltreFichiers extends FileFilter
{
    //---------------ATTRIBUTS---------------

    // Tableau contenant les extensions acceptées
    private String[] extensions;

    // Description qui apparaît dans la liste déroulante des filtres
    String description;

    //---------------CONSTRUCTEUR---------------

    /**
     * Constructeur qui initialise le filtre avec des extensions et une description
     * @param e Tableau des extensions à accepter (par ex: ".csv", ".txt")
     * @param d Description du filtre (par ex: "Fichiers CSV")
     */
    public FiltreFichiers(String[] e, String d)
    {
        // Création d'un nouveau tableau pour stocker les extensions en minuscules
        extensions = new String [e.length];

        // Conversion de toutes les extensions en minuscules pour une comparaison insensible à la casse
        for (int i=0; i<e.length; i++)
            extensions[i] = e[i].toLowerCase();

        description = d;
    }

    //---------------MÉTHODES---------------

    /**
     * Détermine si un fichier doit être accepté par le filtre
     * Cette méthode est appelée automatiquement par JFileChooser pour chaque fichier
     *
     * @param f Le fichier à tester
     * @return true si le fichier est un répertoire ou s'il a une extension acceptée
     */
    @Override
    public boolean accept(File f)
    {
        // Toujours accepter les répertoires pour permettre la navigation
        if (f.isDirectory()) { return true; }

        // Récupère le nom du fichier en minuscules
        String nom = f.getName().toLowerCase();

        // Vérifie si le nom du fichier se termine par une des extensions acceptées
        for (int i=0; i<extensions.length; i++)
            if (nom.endsWith(extensions[i])) return true;

        // Si aucune extension ne correspond, le fichier est rejeté
        return false;
    }

    /**
     * Retourne la description du filtre
     * Cette description apparaît dans la liste déroulante des filtres du JFileChooser
     *
     * @return La description du filtre
     */
    @Override
    public String getDescription()
    {
        return description;
    }
}