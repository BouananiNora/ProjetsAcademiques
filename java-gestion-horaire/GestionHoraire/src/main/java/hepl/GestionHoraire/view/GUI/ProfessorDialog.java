package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.Professor;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Boîte de dialogue pour l'ajout ou la modification d'un professeur
 * Cette classe implémente un formulaire permettant à l'utilisateur
 * de créer un nouveau professeur avec nom et prénom
 */
public class ProfessorDialog extends JDialog
{
    //---------------VARIABLES---------------
    private JPanel mainPanel;           // Panel principal contenant tous les composants
    private JTextField lastNameField;   // Champ pour le nom du professeur
    private JTextField firstNameField;  // Champ pour le prénom du professeur
    private JButton okButton;           // Bouton de confirmation
    private JButton cancelButton;       // Bouton d'annulation
    private Professor professor;        // Objet professeur créé par la boîte de dialogue

    //---------------CONSTRUCTEUR---------------
    /**
     * Constructeur pour l'ajout d'un professeur
     * @param parent La fenêtre parente
     */
    public ProfessorDialog(JFrame parent)
    {
        super(parent,"Ajouter un professeur" , true);
        this.professor = null;

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
        lastNameField = new JTextField(15);
        firstNameField = new JTextField(15);
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
        formPanel.add(new JLabel("Nom:"));
        formPanel.add(lastNameField);
        formPanel.add(new JLabel("Prénom:"));
        formPanel.add(firstNameField);

        // Panel pour les boutons - utilise FlowLayout pour l'espacement
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
        // Gestionnaire pour le bouton OK - crée un objet Professor avec les valeurs saisies
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Récupérer les valeurs des champs
                String lastName = lastNameField.getText();
                String firstName = firstNameField.getText();

                // Vérifier que les champs ne sont pas vides
                if (lastName.equals("") || firstName.equals("")) {
                    JOptionPane.showMessageDialog(ProfessorDialog.this,
                            "Veuillez remplir tous les champs!",
                            "Erreur de saisie",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Créer le professeur avec un ID temporaire (sera défini correctement par le DAO)
                professor = new Professor(0, lastName, firstName); // ID sera défini par le DAO

                dispose();
            }
        });

        // Gestionnaire pour le bouton d'annulation - annule l'opération
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                professor = null;
                dispose();
            }
        });
    }

    //---------------ACCESSEUR---------------
    /**
     * Récupère le professeur créé
     * Cette méthode permet au code appelant de récupérer le résultat de la boîte de dialogue
     * @return Le professeur créé ou null si annulé
     */
    public Professor getProfessor() {
        return professor;
    }

    //---------------MÉTHODE DE TEST---------------
    /**
     * Méthode main de test pour la boîte de dialogue
     * Permet de tester la boîte de dialogue de manière isolée
     * @param args arguments de ligne de commande (non utilisés)
     */
    public static void main(String[] args) {

        // Test d'ajout d'un nouveau professeur
        ProfessorDialog dialog = new ProfessorDialog(null);
        dialog.setVisible(true);
        Professor professor = dialog.getProfessor();

        if (professor != null) {
            System.out.println("Professeur ajouté: " + professor.getlastName() + " " + professor.getfirstName());

        } else {
            System.out.println("Ajout annulé");
        }
    }
}