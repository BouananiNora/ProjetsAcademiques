package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.authentication.Authenticator;
import hepl.GestionHoraire.model.authentication.PropertiesAuthenticator;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Boîte de dialogue pour l'authentification des utilisateurs
 * Cette classe gère le formulaire de connexion à l'application
 */
public class LoginDialog extends JDialog
{
    //---------------VARIABLES---------------
    // Composants graphiques pour l'interface
    private JPanel mainPanel;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JButton cancelButton;
    private JButton registerButton;

    // Variables pour stocker l'état d'authentification
    private boolean authenticated = false;
    private String authenticatedUser = null;

    // Système d'authentification
    private Authenticator authenticator;

    //---------------CONSTRUCTEUR---------------
    /**
     * Constructeur de la boîte de dialogue de login
     * Initialise la boîte de dialogue et tous ses composants
     * @param parent La fenêtre parente
     */
    public LoginDialog(JFrame parent) {
        super(parent, "Authentification", true);

        // Création d'un authenticator qui utilise un fichier properties
        authenticator = new PropertiesAuthenticator("data/users.properties");

        initComponents();
        setupLayout();
        setupEventHandlers();

        // Configuration de la boîte de dialogue
        setSize(300, 150);
        setLocationRelativeTo(parent);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setResizable(false);
    }

    //---------------INITIALISATION COMPOSANTS---------------
    /**
     * Initialise tous les composants de l'interface
     */
    private void initComponents() {
        mainPanel = new JPanel();
        usernameField = new JTextField(15);
        passwordField = new JPasswordField(15);
        loginButton = new JButton("Connexion");
        cancelButton = new JButton("Annuler");
        registerButton = new JButton("Inscription");
    }

    //---------------CONFIGURATION LAYOUT---------------
    /**
     * Configuration de la disposition des composants
     */
    private void setupLayout()
    {
        // Utilisation de BorderLayout pour organiser les composants
        mainPanel.setLayout(new BorderLayout(5, 5));

        // Panel pour les champs de formulaire avec GridLayout (2 colonnes)
        JPanel formPanel = new JPanel(new GridLayout(2, 2, 5, 5));
        formPanel.add(new JLabel("Login:"));
        formPanel.add(usernameField);
        formPanel.add(new JLabel("Mot de passe:"));
        formPanel.add(passwordField);

        // Panel pour les boutons avec FlowLayout (alignés à droite)
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(loginButton);
        buttonPanel.add(registerButton);
        buttonPanel.add(cancelButton);

        mainPanel.add(formPanel, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        // Ajout du panel principal à la boîte de dialogue
        getContentPane().add(mainPanel, BorderLayout.CENTER);
    }

    //---------------GESTION DES ÉVÉNEMENTS---------------
    /**
     * Configuration des gestionnaires d'événements
     * Cette méthode implémente le pattern Observer pour réagir aux actions de l'utilisateur
     */
    private void setupEventHandlers() {
        // Gestionnaire pour le bouton de connexion
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                authenticate();
            }
        });

        // Gestionnaire pour le bouton d'annulation
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                authenticated = false;
                authenticatedUser = null;
                dispose();
            }
        });

        // Gestionnaire pour le bouton d'inscription
        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Ouvre la boîte de dialogue d'inscription
                RegisterDialog registerDialog = new RegisterDialog((JFrame) getParent(), authenticator);
                registerDialog.setVisible(true);
                usernameField.setText("");
            }
        });
    }

    //---------------AUTHENTIFICATION---------------
    /**
     * Tente d'authentifier l'utilisateur avec les identifiants saisis
     * Cette méthode vérifie les données saisies puis utilise l'authenticator
     */
    private void authenticate() {
        // Récupération des valeurs saisies
        String username = usernameField.getText();
        String password = new String(passwordField.getPassword());

        // Vérification que les champs ne sont pas vides
        if (username.equals("") || password.equals("")) {
            JOptionPane.showMessageDialog(this,
                    "Veuillez saisir un login et un mot de passe.",
                    "Champs vides",
                    JOptionPane.WARNING_MESSAGE);
            return;
        }

        // Vérification des identifiants via l'authenticator
        if (authenticator.authenticate(username, password)) {
            // Si authentification réussie, stocke les informations et ferme la boîte
            authenticated = true;
            authenticatedUser = username;
            dispose();
        } else {
            // Si échec, affiche un message d'erreur et réinitialise le mot de passe
            JOptionPane.showMessageDialog(this,
                    "Login ou mot de passe incorrect.",
                    "Échec de l'authentification",
                    JOptionPane.ERROR_MESSAGE);
            passwordField.setText("");
        }
    }

    //---------------GETTERS---------------
    /**
     * Indique si l'utilisateur a été authentifié
     * @return true si l'utilisateur est authentifié, false sinon
     */
    public boolean isAuthenticated() {
        return authenticated;
    }

    /**
     * Récupère le nom d'utilisateur authentifié
     * @return Le nom d'utilisateur ou null si pas authentifié
     */
    public String getAuthenticatedUser() {
        return authenticatedUser;
    }

    //---------------MÉTHODE DE TEST---------------
    /**
     * Méthode main de test pour la boîte de dialogue
     * Permet de tester la boîte de dialogue de manière isolée
     * @param args arguments de ligne de commande (non utilisés)
     */
    public static void main(String[] args) {
        LoginDialog dialog = new LoginDialog(null);
        dialog.setVisible(true);

        if (dialog.isAuthenticated()) {
            System.out.println("Authentification réussie !");
            System.out.println("Utilisateur: " + dialog.getAuthenticatedUser());
        } else {
            System.out.println("Authentification annulée ou échouée");
        }

        System.out.println("\nLogins valides pour les tests:");
        System.out.println("- utilisateur1 / motdepasse1");
        System.out.println("- admin / admin123");
        System.out.println("- Dupont / passDupont");
    }
}