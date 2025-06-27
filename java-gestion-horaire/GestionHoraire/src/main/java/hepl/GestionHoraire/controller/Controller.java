package hepl.GestionHoraire.controller;

import hepl.GestionHoraire.model.DataAccessLayer;
import hepl.GestionHoraire.model.entity.*;
import hepl.GestionHoraire.view.ViewSchedule;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Classe Controller - C'est le contrôleur de mon application MVC
 *
 * Cette classe gère:
 * - Les événements qui viennent de l'interface utilisateur
 * - Les opérations sur les données via le modèle
 * - La mise à jour de l'interface suite aux changements
 */
public class Controller implements ActionListener
{
    //-------------- ATTRIBUTS --------------//

    //Le modèle qui gère l'accès aux données
    private DataAccessLayer model;

    // La vue qui affiche l'interface utilisateur
    private ViewSchedule view;

    // Variable qui indique si l'utilisateur est connecté
    private boolean authenticated = false;

    // Nom de l'utilisateur connecté (ou null si personne n'est connecté)
    private String currentUser = null;

    //-------------- CONSTRUCTEUR --------------//

    /**
     * Constructeur qui initialise le contrôleur
     *
     * On reçoit le modèle et la vue en paramètres au lieu de les créer directement
     * ce qui permet plus de flexibilité
     */
    public Controller(DataAccessLayer model, ViewSchedule view) {
        // Sauvegarde des références
        this.model = model;
        this.view = view;

        // On indique à la vue qui est son contrôleur
        this.view.setController(this);
    }

    //-------------- MÉTHODES PRINCIPALES --------------//

    /**
     * Méthode pour démarrer l'application
     *
     * Cette méthode fait:
     * 1. La première connexion
     * 2. Configure les données pour l'utilisateur
     * 3. Charge les données
     * 4. Lance l'interface
     */
    public void run() {
        // On demande d'abord à l'utilisateur de se connecter
        authenticated = view.showLoginDialog();

        // Si l'utilisateur annule, on quitte
        if (!authenticated) {
            System.exit(0);
        }

        // On récupère le nom d'utilisateur
        currentUser = view.getAuthenticatedUser();

        // On charge les données de cet utilisateur spécifique
        if (model != null) {
            model.changeUser(currentUser);
        }

        // On charge les données dans l'interface
        refreshAllData();

        // On démarre l'interface
        view.run();
    }

    /**
     * Méthode qui recharge toutes les données
     *
     * Utile après connexion ou après certaines actions
     */
    private void refreshAllData() {
        // Charge les professeurs
        view.displayProfessors(model.getAllProfessors());

        // Charge les groupes d'étudiants
        view.displayGroups(model.getAllGroups());

        // Charge les locaux
        view.displayClassrooms(model.getAllClassrooms());

        // Charge les cours planifiés
        view.displayCourses(model.getAllCourses());
    }

    //-------------- GESTION DES ÉVÉNEMENTS --------------//

    /**
     * Méthode appelée quand l'utilisateur clique sur un bouton
     *
     * Cette méthode traite tous les événements (comme les clics)
     * selon le type d'action demandée.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        // Récupère le type d'action
        String command = e.getActionCommand();

        //-------------- GESTION DES IMPORTS --------------//

        // Traitement spécial pour les imports qui contiennent un chemin de fichier
        // Format: "ACTION:nom_du_fichier"
        String[] parts = command.split(":", 2);

        if (parts.length > 1) {
            // Si on veut importer des professeurs
            if (parts[0].equals(ControllerActions.IMPORT_PROFESSORS)) {
                String filename = parts[1]; // Nom du fichier à importer

                // On essaie d'importer
                if (model.importProfessorsFromCSV(filename)) {
                    // Mise à jour si ça a marché
                    view.displayProfessors(model.getAllProfessors());
                    view.showMessage("Professeurs importés avec succès !");
                } else {
                    view.showErrorMessage("Échec de l'importation des professeurs !");
                }
                return;
            }

            // Si on veut importer des groupes
            if (parts[0].equals(ControllerActions.IMPORT_GROUPS)) {
                String filename = parts[1];
                if (model.importGroupsFromCSV(filename)) {
                    view.displayGroups(model.getAllGroups());
                    view.showMessage("Groupes importés avec succès !");
                } else {
                    view.showErrorMessage("Échec de l'importation des groupes !");
                }
                return;
            }

            // Si on veut importer des locaux
            if (parts[0].equals(ControllerActions.IMPORT_CLASSROOMS)) {
                String filename = parts[1];
                if (model.importClassroomsFromCSV(filename)) {
                    view.displayClassrooms(model.getAllClassrooms());
                    view.showMessage("Locaux importés avec succès !");
                } else {
                    view.showErrorMessage("Échec de l'importation des locaux !");
                }
                return;
            }
        }

        //-------------- TRAITEMENT DES ACTIONS --------------//

        // Switch qui gère les différentes actions
        switch (command) {
            //-------------- PROFESSEURS --------------//

            // Si on veut ajouter un prof
            case ControllerActions.ADD_PROFESSOR:
                // On demande les infos
                Professor newProfessor = view.promptForNewProfessor();

                // Si l'utilisateur n'a pas annulé
                if (newProfessor != null) {
                    // On l'ajoute dans la base de données
                    model.addProfessor(newProfessor);

                    // On met à jour l'affichage
                    view.displayProfessors(model.getAllProfessors());
                    view.showMessage("Professeur ajouté avec succès !");
                }
                break;

            // Si on veut supprimer un prof
            case ControllerActions.DELETE_PROFESSOR:
                // On demande quel prof
                int profToDeleteId = view.promptForProfessorId();

                // Si l'ID est valide
                if (profToDeleteId > 0) {
                    // On essaie de supprimer
                    if (model.deleteProfessor(profToDeleteId)) {
                        // Mise à jour si ok
                        view.displayProfessors(model.getAllProfessors());
                        view.showMessage("Professeur supprimé avec succès !");
                    } else {
                        view.showErrorMessage("Impossible de supprimer le professeur !");
                    }
                }
                break;

            //-------------- GROUPES --------------//

            // Si on veut ajouter un groupe
            case ControllerActions.ADD_GROUP:
                // On demande les infos
                Group newGroup = view.promptForNewGroup();

                // Si l'utilisateur n'a pas annulé
                if (newGroup != null) {
                    // On ajoute en base
                    model.addGroup(newGroup);

                    // On met à jour l'affichage
                    view.displayGroups(model.getAllGroups());
                    view.showMessage("Groupe ajouté avec succès !");
                }
                break;

            // Si on veut supprimer un groupe
            case ControllerActions.DELETE_GROUP:
                // On demande quel groupe
                int groupToDeleteId = view.promptForGroupId();

                // Si l'ID est valide
                if (groupToDeleteId > 0) {
                    // On essaie de supprimer
                    if (model.deleteGroup(groupToDeleteId)) {
                        // Mise à jour si ça a marché
                        view.displayGroups(model.getAllGroups());
                        view.showMessage("Groupe supprimé avec succès !");
                    } else {
                        view.showErrorMessage("Impossible de supprimer le groupe !");
                    }
                }
                break;

            //-------------- LOCAUX --------------//

            // Si on veut ajouter un local
            case ControllerActions.ADD_CLASSROOM:
                // On demande les infos
                Classroom newClassroom = view.promptForNewClassroom();

                // Si l'utilisateur n'a pas annulé
                if (newClassroom != null) {
                    // On ajoute en base
                    model.addClassroom(newClassroom);

                    // On met à jour l'affichage
                    view.displayClassrooms(model.getAllClassrooms());
                    view.showMessage("Local ajouté avec succès !");
                }
                break;

            // Si on veut supprimer un local
            case ControllerActions.DELETE_CLASSROOM:
                // On demande quel local
                int classroomToDeleteId = view.promptForClassroomId();

                // Si l'ID est valide
                if (classroomToDeleteId > 0) {
                    // On essaie de supprimer
                    if (model.deleteClassroom(classroomToDeleteId)) {
                        // Mise à jour si ça a marché
                        view.displayClassrooms(model.getAllClassrooms());
                        view.showMessage("Local supprimé avec succès !");
                    } else {
                        view.showErrorMessage("Impossible de supprimer le local !");
                    }
                }
                break;

            //-------------- COURS --------------//

            // Si on veut planifier un cours
            case ControllerActions.PLAN_COURSE:
                // On demande toutes les infos
                // (on a besoin des listes pour proposer des choix à l'utilisateur)
                Course newCourse = view.promptForNewCourse(
                        model.getAllProfessors(),
                        model.getAllClassrooms(),
                        model.getAllGroups()
                );

                // Si l'utilisateur n'a pas annulé
                if (newCourse != null) {
                    // On ajoute en base
                    model.addCourse(newCourse);

                    // On met à jour l'affichage
                    view.displayCourses(model.getAllCourses());
                    view.showMessage("Cours planifié avec succès !");
                }
                break;

            // Si on veut supprimer un cours
            case ControllerActions.DELETE_COURSE:
                // On demande quel cours
                int courseToDeleteId = view.promptForCourseId();

                // Si l'ID est valide
                if (courseToDeleteId > 0) {
                    // On essaie de supprimer
                    if (model.deleteCourse(courseToDeleteId)) {
                        // Mise à jour si ça a marché
                        view.displayCourses(model.getAllCourses());
                        view.showMessage("Cours supprimé avec succès !");
                    } else {
                        view.showErrorMessage("Impossible de supprimer le cours !");
                    }
                }
                break;

            //-------------- SESSIONS --------------//

            // Si on veut se connecter
            case ControllerActions.LOGIN:
                // On garde l'état précédent pour comparaison
                boolean previouslyAuthenticated = authenticated;
                String previousUser = currentUser;

                // On essaie de se connecter
                authenticated = view.showLoginDialog();

                // Si connecté
                if (authenticated) {
                    // On récupère le nom
                    currentUser = view.getAuthenticatedUser();

                    // Si c'est un nouvel utilisateur
                    if (!previouslyAuthenticated || !currentUser.equals(previousUser)) {
                        // On change d'utilisateur dans le modèle
                        if (model != null) {
                            model.changeUser(currentUser);
                        }

                        // On recharge les données
                        refreshAllData();
                    }
                }
                break;

            // Si on veut se déconnecter
            case ControllerActions.LOGOUT:
                // On sauvegarde avant
                if (authenticated) {
                    model.saveData();
                }

                // On se déconnecte
                authenticated = false;
                currentUser = null;

                // On informe la vue
                view.logout();
                break;

            //-------------- FICHIERS --------------//

            // Si on veut sauvegarder
            case ControllerActions.SAVE:
                // On sauvegarde les données
                model.saveData();

                // On informe l'utilisateur
                view.showMessage("Données sauvegardées avec succès !");
                break;

            // Si on veut quitter
            case ControllerActions.EXIT:
                System.exit(0);
                break;

            // Si l'action n'est pas reconnue
            default:
                view.showErrorMessage("Action non reconnue: " + command);
                break;
        }
    }
}