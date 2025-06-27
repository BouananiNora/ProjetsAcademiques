package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.Group;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Boîte de dialogue pour l'ajout ou la modification d'un groupe
 * Cette classe implémente un formulaire simple permettant à l'utilisateur
 * de créer un nouveau groupe avec un nom
 */
public class GroupDialog extends JDialog
{
    //---------------VARIABLES---------------
    private JPanel mainPanel;           // Panel principal contenant tous les composants
    private JTextField nameField;       // Champ pour le nom du groupe
    private JButton okButton;           // Bouton de confirmation
    private JButton cancelButton;       // Bouton d'annulation
    private Group group;                // Objet groupe créé par la boîte de dialogue


    //---------------CONSTRUCTEUR---------------
    /**
     * Constructeur pour l'ajout d'un groupe
     * @param parent La fenêtre parente
     */
    public GroupDialog(JFrame parent)
    {
        super(parent,"Ajouter un groupe" , true);
        this.group = null;

        // Initialisation des composants
        initComponents();

        // Configuration de la disposition
        setupLayout();

        // Ajout des gestionnaires d'événements
        setupEventHandlers();


        // Configuration de la boîte de dialogue
        setSize(300, 120);
        setLocationRelativeTo(parent);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setResizable(false);
    }

    //---------------MÉTHODES D'INITIALISATION---------------
    /**
     * Initialisation des composants de l'interface
     * Cette méthode crée tous les composants GUI nécessaires
     */
    private void initComponents()
    {
        mainPanel = new JPanel();
        nameField = new JTextField(15);
        okButton = new JButton("Ajouter");
        cancelButton = new JButton("Annuler");
    }

    /**
     * Configuration de la disposition des composants
     * Cette méthode utilise des layouts pour organiser les éléments dans la fenêtre
     */
    private void setupLayout()
    {
        mainPanel.setLayout(new BorderLayout(5, 5));

        // Panel pour les champs de formulaire - utilise GridLayout pour l'alignement
        JPanel formPanel = new JPanel(new GridLayout(1, 2, 5, 5));
        formPanel.add(new JLabel("Nom du groupe:"));
        formPanel.add(nameField);

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
        // Gestionnaire pour le bouton OK - crée un objet Group avec le nom saisi
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Récupérer les valeurs des champs
                String name = nameField.getText();

                // Vérifier que les champs ne sont pas vides
                if (name.equals("")) {
                    JOptionPane.showMessageDialog(GroupDialog.this,
                            "Veuillez remplir le nom du groupe!",
                            "Erreur de saisie",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Créer le groupe
                group = new Group(0, name); // ID sera défini par le DAO

                dispose();
            }
        });

        // Gestionnaire pour le bouton d'annulation - annule l'opération
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                group = null;
                dispose();
            }
        });
    }

    //---------------ACCESSEUR---------------
    /**
     * Récupère le groupe créé
     * Cette méthode permet au code appelant de récupérer le résultat de la boîte de dialogue
     * @return Le groupe créé ou null si annulé
     */
    public Group getGroup()
    {
        return group;
    }

    //---------------MÉTHODE DE TEST---------------
    /**
     * Méthode main de test pour la boîte de dialogue
     * Permet de tester la boîte de dialogue de manière isolée
     * @param args arguments de ligne de commande (non utilisés)
     */
    public static void main(String[] args)
    {

        // Test d'ajout d'un nouveau groupe
        GroupDialog dialog = new GroupDialog(null);
        dialog.setVisible(true);
        Group group = dialog.getGroup();

        if (group != null) {
            System.out.println("Groupe ajouté: " + group.getName());
        } else {
            System.out.println("Ajout annulé");
        }
    }
}
