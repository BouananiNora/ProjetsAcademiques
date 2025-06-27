package hepl.GestionHoraire;

import hepl.GestionHoraire.controller.Controller;
import hepl.GestionHoraire.model.DataAccessLayer;
import hepl.GestionHoraire.model.dao.ScheduleDAO;
import hepl.GestionHoraire.view.GUI.MainFrame;
import hepl.GestionHoraire.view.ViewSchedule;

import com.formdev.flatlaf.FlatDarkLaf;
import javax.swing.UIManager;


/**
 * Classe principale qui initialise et démarre l'application de gestion d'horaires
 * Cette classe suit le point d'entrée classique d'une application Java
 */
public class Main {
    public static void main(String[] args) {
        try {
            // Mise en place du thème sombre pour l'application
            FlatDarkLaf.setup();
            UIManager.setLookAndFeel(new FlatDarkLaf());
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Créer le modèle (gestion des données)
        DataAccessLayer model = new ScheduleDAO();

        // Créer la vue (interface graphique)
        MainFrame view = new MainFrame();

        // Créer le contrôleur et connecter modèle et vue (pattern MVC)
        Controller controller = new Controller(model, (ViewSchedule) view);

        // Démarrer l'application
        controller.run();
    }
}
