package hepl.GestionHoraire.controller;

public abstract class ControllerActions
{
    // Actions pour les professeurs
    public static final String ADD_PROFESSOR = "Ajouter un professeur";
    public static final String DELETE_PROFESSOR = "Supprimer un professeur";

    // Actions pour les groupes
    public static final String ADD_GROUP = "Ajouter un groupe";
    public static final String DELETE_GROUP = "Supprimer un groupe";

    // Actions pour les locaux
    public static final String ADD_CLASSROOM = "Ajouter un local";
    public static final String DELETE_CLASSROOM = "Supprimer un local";

    // Actions pour les cours
    public static final String PLAN_COURSE = "Planifier un cours";
    public static final String DELETE_COURSE = "Supprimer un cours";

    // Actions pour les sessions
    public static final String LOGIN = "Login";
    public static final String LOGOUT = "Logout";

    // Actions pour le fichier
    public static final String SAVE = "Enregistrer";
    public static final String EXIT = "Quitter";

    //Action pour importer
    public static final String IMPORT_PROFESSORS = "Importer professeurs";
    public static final String IMPORT_GROUPS = "Importer groupes";
    public static final String IMPORT_CLASSROOMS = "Importer locaux";
}