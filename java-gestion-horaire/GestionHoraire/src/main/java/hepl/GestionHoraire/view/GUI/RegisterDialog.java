package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.authentication.Authenticator;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Boîte de dialogue pour l'inscription de nouveaux utilisateurs
 */
public class RegisterDialog extends JDialog
{
    //----------------------- VARIABLES -----------------------
    private JPanel mainPanel;                 // Panel principal contenant tout
    private JTextField usernameField;         // Champ pour le login
    private JPasswordField passwordField;     // Champ pour mot de passe (masqué)
    private JPasswordField confirmPasswordField; // Champ pour confirmer mot de passe
    private JButton registerButton;           // Bouton pour valider inscription
    private JButton cancelButton;             // Bouton pour annuler l'inscription
    private Authenticator authenticator;

    //----------------------- CONSTRUCTEUR -----------------------
    /**
     * Constructeur de la boîte de dialogue d'inscription
     * Comme RegisterDialog extends JDialog, on doit appeler le constructeur parent
     * On utilise true pour modal pour bloquer l'interface principale
     */
    public RegisterDialog(JFrame parent, Authenticator authenticator)
    {
        super(parent, "Inscription", true);
        this.authenticator = authenticator;

        // Appel des méthodes pour initialiser et configurer l'interface
        initComponents();
        setupLayout();
        setupEventHandlers();

        // Configuration de la boîte de dialogue
        setSize(350, 200);
        setLocationRelativeTo(parent); // Centre la boîte par rapport à son parent
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setResizable(false);
    }

    //----------------------- INITIALISATION COMPOSANTS -----------------------
    /**
     * Cette méthode crée tous les composants Swing nécessaires
     * Mais ne les dispose pas encore dans la fenêtre (fait dans setupLayout)
     */
    private void initComponents()
    {
        mainPanel = new JPanel();
        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        confirmPasswordField = new JPasswordField(15);
        registerButton = new JButton("S'inscrire");
        cancelButton = new JButton("Annuler");
    }

    //----------------------- CONFIGURATION LAYOUT -----------------------
    /**
     * Met en place la disposition des composants en utilisant des layouts
     * On utilise une combinaison de BorderLayout, GridLayout et FlowLayout
     * GridLayout pour aligner proprement les labels et champs (3 lignes, 2 colonnes)
     */
    private void setupLayout()
    {
        mainPanel.setLayout(new BorderLayout(5, 5));

        // Panel pour les champs de formulaire - en grille pour l'alignement
        JPanel formPanel = new JPanel(new GridLayout(3, 2, 5, 5));
        formPanel.add(new JLabel("Login:"));
        formPanel.add(usernameField);
        formPanel.add(new JLabel("Mot de passe:"));
        formPanel.add(passwordField);
        formPanel.add(new JLabel("Confirmer mot de passe:"));
        formPanel.add(confirmPasswordField);

        // Panel pour les boutons - avec FlowLayout pour l'espacement
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(registerButton);
        buttonPanel.add(cancelButton);

        // Ajout des panels au panel principal
        mainPanel.add(formPanel, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        // Définir le panel principal comme contenu de la boîte de dialogue
        getContentPane().add(mainPanel, BorderLayout.CENTER);
    }

    //----------------------- GESTION DES ÉVÉNEMENTS -----------------------
    /**
     * Configure les écouteurs d'événements (pattern Observer)
     * Cette méthode utilise des classes anonymes implémentant ActionListener
     * pour réagir aux clics sur les boutons
     */
    private void setupEventHandlers() {
        // Gestionnaire pour le bouton d'inscription
        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                register();
            }
        });

        // Gestionnaire pour le bouton d'annulation - ferme simplement la boîte
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });
    }

    //----------------------- LOGIQUE D'INSCRIPTION -----------------------
    /**
     * Cette méthode réalise la logique d'inscription
     * Elle vérifie que:
     * 1. Tous les champs sont remplis
     * 2. Les deux mots de passe correspondent
     * 3. Le nom d'utilisateur n'existe pas déjà
     */
    private void register() {
        // Récupération des valeurs des champs
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());
        String confirmPassword = new String(confirmPasswordField.getPassword());

        // Vérification que tous les champs sont remplis
        if (username.equals("") || password.equals("") || confirmPassword.equals("")) {
            JOptionPane.showMessageDialog(this,
                    "Veuillez remplir tous les champs.",
                    "Champs vides",
                    JOptionPane.WARNING_MESSAGE);
            return; // Sort de la méthode si champs vides
        }

        // Vérification que les mots de passe correspondent
        if (!password.equals(confirmPassword)) {
            JOptionPane.showMessageDialog(this,
                    "Les mots de passe ne correspondent pas.",
                    "Erreur de mot de passe",
                    JOptionPane.ERROR_MESSAGE);
            passwordField.setText("");        // Vide les champs de mot de passe
            confirmPasswordField.setText("");
            return;
        }

        // Tentative d'ajout de l'utilisateur via l'authenticator
        if (authenticator.addUser(username, password))
        {
            JOptionPane.showMessageDialog(this,
                    "Inscription réussie ! Vous pouvez maintenant vous connecter.",
                    "Inscription réussie",
                    JOptionPane.INFORMATION_MESSAGE);
            dispose();
        } else {
            // Si l'ajout échoue (login déjà pris)
            JOptionPane.showMessageDialog(this,
                    "Ce nom d'utilisateur existe déjà.",
                    "Erreur d'inscription",
                    JOptionPane.ERROR_MESSAGE);
            usernameField.setText("");
        }
    }
}