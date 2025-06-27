package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.Classroom;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Boîte de dialogue pour l'ajout d'un local
 * Cette classe implémente un formulaire simple permettant à l'utilisateur
 * de créer un nouveau local avec un nom et une capacité
 */
public class ClassroomDialog extends JDialog
{

    //---------------VARIABLES---------------
    private JPanel mainPanel;           // Panel principal contenant tous les composants
    private JTextField nameField;       // Champ pour le nom du local
    private JSpinner capacitySpinner;   // Spinner pour la capacité du local
    private JButton okButton;           // Bouton de confirmation
    private JButton cancelButton;       // Bouton d'annulation
    private Classroom classroom;        // Objet local créé par la boîte de dialogue

    //---------------CONSTRUCTEUR---------------
    /**
     * Constructeur pour l'ajout d'un local
     * @param parent La fenêtre parente
     */
    public ClassroomDialog(JFrame parent) {
        super(parent, "Ajouter un local", true);
        this.classroom = null;

        // Initialisation des composants
        initComponents();

        // Configuration de la disposition
        setupLayout();

        // Ajout des gestionnaires d'événements
        setupEventHandlers();

        // Configuration de la boîte de dialogue
        setSize(350, 150);
        setLocationRelativeTo(parent);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setResizable(false);
    }

    //---------------MÉTHODES D'INITIALISATION---------------
    /**
     * Initialisation des composants de l'interface
     * Cette méthode crée tous les composants GUI nécessaires
     */
    private void initComponents() {
        mainPanel = new JPanel();
        nameField = new JTextField(15);
        capacitySpinner = new JSpinner(new SpinnerNumberModel(30, 1, 500, 1));
        okButton = new JButton("Ajouter");
        cancelButton = new JButton("Annuler");
    }

    /**
     * Configuration de la disposition des composants
     * Cette méthode utilise des layouts pour organiser les éléments dans la fenêtre
     */
    private void setupLayout() {
        mainPanel.setLayout(new BorderLayout(5, 5));

        // Panel pour les champs de formulaire - utilise GridLayout pour l'alignement
        JPanel formPanel = new JPanel(new GridLayout(2, 2, 5, 5));
        formPanel.add(new JLabel("Nom du local:"));
        formPanel.add(nameField);
        formPanel.add(new JLabel("Capacité:"));
        formPanel.add(capacitySpinner);

        // Panel pour les boutons — utilise FlowLayout pour l'espacement
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(okButton);
        buttonPanel.add(cancelButton);

        // Ajout des panels au panel principal
        mainPanel.add(formPanel, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        // Définir le panel principal comme contenu de la boîte de dialogue
        getContentPane().add(mainPanel, BorderLayout.CENTER);
    }

    //---------------GESTION DES ÉVÉNEMENTS---------------
    /**
     * Configuration des gestionnaires d'événements
     * Cette méthode implémente le pattern Observer pour réagir aux actions de l'utilisateur
     */
    private void setupEventHandlers()
    {
        // Gestionnaire pour le bouton OK - crée un objet Classroom avec les valeurs saisies
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Récupérer les valeurs des champs
                String name = nameField.getText();
                int capacity = (Integer) capacitySpinner.getValue();

                // Vérifier que les champs ne sont pas vides
                if (name.equals("")) {
                    JOptionPane.showMessageDialog(ClassroomDialog.this,
                            "Veuillez remplir tous les champs!",
                            "Erreur de saisie",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Créer le local
                classroom = new Classroom(0, name, capacity); // ID sera défini par le DAO


                dispose();
            }
        });

        // Gestionnaire pour le bouton d'annulation - annule l'opération
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                classroom = null;
                dispose();
            }
        });
    }

    //---------------ACCESSEUR---------------
    /**
     * Récupère le local créé
     * Cette méthode permet au code appelant de récupérer le résultat de la boîte de dialogue
     * @return Le local créé ou null si annulé
     */
    public Classroom getClassroom() {
        return classroom;
    }

    //---------------MÉTHODE DE TEST---------------
    /**
     * Méthode main de test pour la boîte de dialogue
     * Permet de tester la boîte de dialogue de manière isolée
     * @param args arguments de ligne de commande (non utilisés)
     */
    public static void main(String[] args) {
        ClassroomDialog dialog = new ClassroomDialog(null);
        dialog.setVisible(true);
        Classroom classroom = dialog.getClassroom();

        if (classroom != null) {
            System.out.println("Local ajouté: " + classroom.getName() + ", Capacité: " + classroom.getSeatingCapacity());
        } else {
            System.out.println("Ajout annulé");
        }
    }
}