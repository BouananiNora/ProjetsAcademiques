package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.*;
import hepl.GestionHoraire.controller.Controller;
import hepl.GestionHoraire.controller.ControllerActions;
import hepl.GestionHoraire.view.ViewSchedule;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.List;
import java.util.Map;
import java.util.HashMap;


/**
 * Fenêtre principale de l'application de gestion d'horaires de cours
 * Cette classe implémente l'interface ViewSchedule (pattern MVC)
 */
public class MainFrame extends JFrame implements ViewSchedule
{
    //region -------VARIABLES-------

    //---------------ATTRIBUTS PRINCIPAUX---------------
    // Le contrôleur qui gère les interactions avec le modèle (pattern MVC)
    private Controller controller;

    // État d'authentification
    private boolean isAuthenticated = false;
    private String currentUser = null;

    //---------------COMPOSANTS PANELS---------------
    // Panels principaux pour l'organisation de l'interface
    private JPanel mainPanel;
    private JPanel professorsPanel;
    private JPanel groupsPanel;
    private JPanel classroomsPanel;
    private JPanel planificationPanel;

    //---------------COMPOSANTS TABLES---------------
    // Tables pour afficher les données
    private JTable professorsTable;
    private JTable groupsTable;
    private JTable classroomsTable;
    private JTable coursesTable;

    //---------------MODÈLES DE DONNÉES---------------
    // Modèles pour les listes de données
    private DefaultListModel<Professor> professorsListModel;
    private DefaultListModel<Group> groupsListModel;
    private DefaultListModel<Classroom> classroomsListModel;

    //---------------CHAMPS DE SAISIE---------------
    // Champs pour l'ajout de professeurs
    private JTextField nomField;
    private JTextField prenomField;

    // Champs pour l'ajout de groupes
    private JTextField groupNameField;

    // Champs pour l'ajout de locaux
    private JTextField classroomNameField;
    private JTextField capacityField;

    //---------------BOUTONS---------------
    // Boutons pour les actions sur les entités
    private JButton addProfessorButton;
    private JButton deleteProfessorButton;
    private JButton addGroupButton;
    private JButton deleteGroupButton;
    private JButton addClassroomButton;
    private JButton deleteClassroomButton;
    private JButton planifyButton;
    private JButton deleteCourseButton;

    //---------------MENU---------------
    // Composants du menu principal
    private JMenuBar menuBar;
    private JMenu fileMenu;
    private JMenu sessionMenu;
    private JMenu importMenu;

    // Items de menu
    private JMenuItem saveMenuItem;
    private JMenuItem exitMenuItem;
    private JMenuItem loginMenuItem;
    private JMenuItem logoutMenuItem;
    private JMenuItem importProfessorsMenuItem;
    private JMenuItem importGroupsMenuItem;
    private JMenuItem importClassroomsMenuItem;

    //endregion

    //---------------CONSTRUCTEUR---------------
    /**
     * Constructeur de la fenêtre principale
     * Initialise tous les composants et configure l'interface
     */
    public MainFrame()
    {
        super("Gestion d'horaire de cours");

        initComponents();
        setupMenuBar();
        setupLayout();
        setupEventHandlers();

        // Configuration de la fenêtre
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    //---------------MÉTHODES D'INITIALISATION---------------
    /**
     * Initialisation des composants de l'interface
     * Cette méthode crée tous les composants nécessaires avant de les ajouter au layout
     */
    private void initComponents()
    {
        mainPanel = new JPanel(new BorderLayout());

        // Création des modèles de listes
        professorsListModel = new DefaultListModel<>();
        groupsListModel = new DefaultListModel<>();
        classroomsListModel = new DefaultListModel<>();

        // Initialisation des tables
        professorsTable = new JTable();
        groupsTable = new JTable();
        classroomsTable = new JTable();
        coursesTable = new JTable();

        // Initialisation des champs texte
        nomField = new JTextField(15);
        prenomField = new JTextField(15);
        groupNameField = new JTextField(15);
        classroomNameField = new JTextField(15);
        capacityField = new JTextField(5);

        // Initialisation des boutons avec leurs libellés
        addProfessorButton = new JButton("Ajouter");
        deleteProfessorButton = new JButton("Supprimer");
        addGroupButton = new JButton("Ajouter");
        deleteGroupButton = new JButton("Supprimer");
        addClassroomButton = new JButton("Ajouter");
        deleteClassroomButton = new JButton("Supprimer");
        planifyButton = new JButton("Planifier");
        deleteCourseButton = new JButton("Supprimer");
    }

    /**
     * Configuration de la barre de menu
     * Crée les menus et leurs items et configure leurs actions
     */
    private void setupMenuBar()
    {
        menuBar = new JMenuBar();

        // Menu Fichier
        fileMenu = new JMenu("Fichier");
        saveMenuItem = new JMenuItem("Enregistrer");
        exitMenuItem = new JMenuItem("Quitter");

        fileMenu.add(saveMenuItem);
        fileMenu.add(exitMenuItem);

        // Menu Session
        sessionMenu = new JMenu("Session");
        loginMenuItem = new JMenuItem("Login");
        logoutMenuItem = new JMenuItem("Logout");

        sessionMenu.add(loginMenuItem);
        sessionMenu.add(logoutMenuItem);

        // Menu Importer
        importMenu = new JMenu("Importer");
        importProfessorsMenuItem = new JMenuItem("Professeurs");
        importGroupsMenuItem = new JMenuItem("Groupes");
        importClassroomsMenuItem = new JMenuItem("Locaux");
        importMenu.add(importProfessorsMenuItem);
        importMenu.add(importGroupsMenuItem);
        importMenu.add(importClassroomsMenuItem);

        // Ajout des menus à la barre de menu
        menuBar.add(fileMenu);
        menuBar.add(sessionMenu);
        menuBar.add(importMenu);


        // Créer un espace flexible pour pousser le logo vers la droite
        JPanel spacerPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        menuBar.add(spacerPanel);

        // Ajout du logo - élément visuel pour représenter l'application
        try {
            // Chargement et redimensionnement de l'image du logo
            ImageIcon originalIcon = new ImageIcon(getClass().getResource("/images/hepl-icon.png"));
            Image originalImage = originalIcon.getImage();

            // Taille adaptée à la barre de menu
            int menuBarHeight = 20;
            int width = menuBarHeight; // Logo carré

            // Redimensionnement de l'image avec la méthode standard Java
            Image smallImage = originalImage.getScaledInstance(width, menuBarHeight, Image.SCALE_SMOOTH);
            ImageIcon logoIcon = new ImageIcon(smallImage);

            // Ajout du logo à la barre de menu
            JLabel logoLabel = new JLabel(logoIcon);
            JPanel logoPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 10, 0));
            logoPanel.add(logoLabel);
            menuBar.add(logoPanel);
        } catch (Exception e) {
            System.out.println("Logo non trouvé: " + e.getMessage());
        }

        // Définir la barre de menu pour cette JFrame
        setJMenuBar(menuBar);
    }

    /**
     * Configuration de la disposition des composants
     * Utilise un JTabbedPane pour organiser les différentes fonctionnalités
     */
    private void setupLayout()
    {
        // Création d'un panneau à onglets pour les différentes sections
        JTabbedPane tabbedPane = new JTabbedPane();

        // Onglet des Professeurs
        professorsPanel = createProfessorsPanel();
        tabbedPane.addTab("Professeurs", professorsPanel);

        // Onglet des Groupes
        groupsPanel = createGroupsPanel();
        tabbedPane.addTab("Groupes", groupsPanel);

        // Onglet des Locaux
        classroomsPanel = createClassroomsPanel();
        tabbedPane.addTab("Locaux", classroomsPanel);

        // Onglet de planification
        planificationPanel = createPlanificationPanel();
        tabbedPane.addTab("Planification", planificationPanel);

        // Ajout du panneau à onglets au panel principal
        mainPanel.add(tabbedPane, BorderLayout.CENTER);

        // Définir le panel principal comme contenu de la fenêtre
        setContentPane(mainPanel);
    }

    //region -------CREATEXPANEL-------

    /**
     * Création du panel pour la gestion des professeurs
     * Ce panel contient une table des professeurs et les boutons d'action
     */
    private JPanel createProfessorsPanel() {
        JPanel panel = new JPanel(new BorderLayout());

        // Table des professeurs avec défilement
        JScrollPane scrollPane = new JScrollPane(professorsTable);
        panel.add(scrollPane, BorderLayout.CENTER);

        // Panel pour les boutons d'action
        JPanel controlPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        controlPanel.add(addProfessorButton);
        controlPanel.add(deleteProfessorButton);
        panel.add(controlPanel, BorderLayout.SOUTH);

        return panel;
    }

    /**
     * Création du panel pour la gestion des groupes
     */
    private JPanel createGroupsPanel() {
        JPanel panel = new JPanel(new BorderLayout());

        JScrollPane scrollPane = new JScrollPane(groupsTable);
        panel.add(scrollPane, BorderLayout.CENTER);

        JPanel controlPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        controlPanel.add(addGroupButton);
        controlPanel.add(deleteGroupButton);
        panel.add(controlPanel, BorderLayout.SOUTH);

        return panel;
    }

    /**
     * Création du panel pour la gestion des locaux
     */
    private JPanel createClassroomsPanel() {
        JPanel panel = new JPanel(new BorderLayout());

        JScrollPane scrollPane = new JScrollPane(classroomsTable);
        panel.add(scrollPane, BorderLayout.CENTER);

        JPanel controlPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        controlPanel.add(addClassroomButton);
        controlPanel.add(deleteClassroomButton);
        panel.add(controlPanel, BorderLayout.SOUTH);

        return panel;
    }

    /**
     * Création du panel pour la planification des cours
     */
    private JPanel createPlanificationPanel() {
        JPanel panel = new JPanel(new BorderLayout());

        // Table des cours planifiés
        JScrollPane coursesScrollPane = new JScrollPane(coursesTable);
        panel.add(coursesScrollPane, BorderLayout.CENTER);

        // Boutons pour gérer les cours (planifier, supprimer)
        JPanel bottomPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        bottomPanel.add(planifyButton);
        bottomPanel.add(deleteCourseButton);
        panel.add(bottomPanel, BorderLayout.SOUTH);

        return panel;
    }

    //endregion

    /**
     * Configuration des gestionnaires d'événements
     * Cette méthode configure tous les listeners pour les boutons et menus
     * C'est ici que les actions de l'interface sont liées au contrôleur
     */
    private void setupEventHandlers()
    {
        // Gestionnaires pour le menu Session
        loginMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Demande au controller de gérer l'authentification
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.LOGIN));
            }
        });

        logoutMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.LOGOUT));
            }
        });

        // Gestionnaires pour le menu Fichier
        exitMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.EXIT));
            }
        });

        saveMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.SAVE));
            }
        });

        // Gestionnaires pour les boutons Professeurs
        addProfessorButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.ADD_PROFESSOR));
            }
        });

        deleteProfessorButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.DELETE_PROFESSOR));
            }
        });

        // Gestionnaires pour les boutons Groupes
        addGroupButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.ADD_GROUP));
            }
        });

        deleteGroupButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.DELETE_GROUP));
            }
        });

        // Gestionnaires pour les boutons Locaux
        addClassroomButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.ADD_CLASSROOM));
            }
        });

        deleteClassroomButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.DELETE_CLASSROOM));
            }
        });

        // Gestionnaires pour les boutons Planification
        planifyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.PLAN_COURSE));
            }
        });

        deleteCourseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ControllerActions.DELETE_COURSE));
            }
        });

        // Gestionnaires pour l'import CSV
        importProfessorsMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String filename = selectCSVFile();
                if (filename != null) {
                    // Format spécial "commande:paramètre" pour l'import
                    controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
                            ControllerActions.IMPORT_PROFESSORS + ":" + filename));
                }
            }
        });

        importGroupsMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String filename = selectCSVFile();
                if (filename != null) {
                    controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
                            ControllerActions.IMPORT_GROUPS + ":" + filename));
                }
            }
        });

        importClassroomsMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String filename = selectCSVFile();
                if (filename != null) {
                    controller.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
                            ControllerActions.IMPORT_CLASSROOMS + ":" + filename));
                }
            }
        });
    }

    /**
     * Active ou désactive les fonctionnalités selon l'état d'authentification
     * Cette méthode est utilisée après login/logout pour mettre à jour l'interface
     * @param enabled true pour activer, false pour désactiver
     */
    private void enableFeatures(boolean enabled) {
        // Active/désactive les boutons d'action
        addProfessorButton.setEnabled(enabled);
        deleteProfessorButton.setEnabled(enabled);
        addGroupButton.setEnabled(enabled);
        deleteGroupButton.setEnabled(enabled);
        addClassroomButton.setEnabled(enabled);
        deleteClassroomButton.setEnabled(enabled);
        planifyButton.setEnabled(enabled);
        deleteCourseButton.setEnabled(enabled);

        // Active/désactive les menus
        saveMenuItem.setEnabled(enabled);
        exitMenuItem.setEnabled(!enabled);
        importMenu.setEnabled(enabled);

        // Modifie l'état des items de menu pour la session
        loginMenuItem.setEnabled(!enabled); // Login uniquement si non connecté
        logoutMenuItem.setEnabled(enabled);  // Logout uniquement si connecté
    }

    /**
     * Affiche une boîte de dialogue pour sélectionner un fichier CSV
     * Utilisé lors de l'import de données
     * @return Le chemin du fichier sélectionné ou null si annulé
     */
    private String selectCSVFile() {
        JFileChooser fileChooser = new JFileChooser();

        // Filtre pour n'afficher que les fichiers CSV
        String[] extensions = {".csv"};
        fileChooser.setFileFilter(new FiltreFichiers(extensions, "Fichiers CSV"));

        int result = fileChooser.showOpenDialog(this);

        if (result == JFileChooser.APPROVE_OPTION) {
            return fileChooser.getSelectedFile().getAbsolutePath();
        }
        return null;
    }

    //---------------MÉTHODES DE L'INTERFACE ViewSchedule---------------
    /**
     * Définit le contrôleur pour cette vue (pattern MVC)
     * Cette méthode est appelée lors de l'initialisation de l'application
     */
    @Override
    public void setController(Controller controller) {
        this.controller = controller;
    }


    //region -------DISPLAY-------

    /**
     * Affiche la liste des professeurs dans la table
     * Cette méthode est appelée après chaque mise à jour des professeurs
     */
    @Override
    public void displayProfessors(List<Professor> professors) {
        // Crée un modèle de table avec les données des professeurs
        ProfessorTableModel model = new ProfessorTableModel(professors);
        professorsTable.setModel(model);

        // Met à jour le modèle de liste pour la planification
        professorsListModel = new DefaultListModel<>();
        for(int i = 0; i < professors.size(); i++) {
            professorsListModel.addElement(professors.get(i));
        }
    }

    /**
     * Affiche la liste des groupes dans la table
     */
    @Override
    public void displayGroups(List<Group> groups) {
        GroupTableModel model = new GroupTableModel(groups);
        groupsTable.setModel(model);

        groupsListModel= new DefaultListModel<>();
        for(int i = 0; i < groups.size(); i++) {
            groupsListModel.addElement(groups.get(i));
        }
    }

    /**
     * Affiche la liste des locaux dans la table
     */
    @Override
    public void displayClassrooms(List<Classroom> classrooms) {
        ClassroomTableModel model = new ClassroomTableModel(classrooms);
        classroomsTable.setModel(model);

        classroomsListModel= new DefaultListModel<>();
        for(int i = 0; i < classrooms.size(); i++) {
            classroomsListModel.addElement(classrooms.get(i));
        }
    }

    /**
     * Affiche la liste des cours dans la table
     * Méthode plus complexe car elle doit résoudre les références entre objets
     */
    @Override
    public void displayCourses(List<Course> courses) {
        // Crée le modèle de table pour les cours
        CourseTableModel model = new CourseTableModel(courses);
        coursesTable.setModel(model);

        // Prépare les maps pour résoudre les références entre objets
        // Un cours fait référence à des professeurs, locaux et groupes par ID
        Map<Integer, Professor> professorMap = new HashMap<>();
        Map<Integer, Classroom> classroomMap = new HashMap<>();
        Map<Integer, Group> groupMap = new HashMap<>();


        // Remplit les maps à partir des modèles de tables existants
        if (professorsTable.getModel() instanceof ProfessorTableModel) {
            ProfessorTableModel profModel = (ProfessorTableModel) professorsTable.getModel();
            for (int i = 0; i < profModel.getRowCount(); i++) {
                Professor prof = profModel.getProfessorAt(i);
                professorMap.put(prof.getId(), prof);
            }
        }

        if (classroomsTable.getModel() instanceof ClassroomTableModel) {
            ClassroomTableModel classModel = (ClassroomTableModel) classroomsTable.getModel();
            for (int i = 0; i < classModel.getRowCount(); i++) {
                Classroom classroom = classModel.getClassroomAt(i);
                classroomMap.put(classroom.getId(), classroom);
            }
        }

        if (groupsTable.getModel() instanceof GroupTableModel) {
            GroupTableModel groupModel = (GroupTableModel) groupsTable.getModel();
            for (int i = 0; i < groupModel.getRowCount(); i++) {
                Group group = groupModel.getGroupAt(i);
                groupMap.put(group.getId(), group);
            }
        }

        // Configure les références dans le modèle de table des cours
        model.setReferenceMaps(professorMap, classroomMap, groupMap);
    }

    //endregion

    //region -------PROMPT-------


    //region ---PROMPTFORNEW---

    /**
     * Affiche une boîte de dialogue pour ajouter un professeur
     * @return Le nouveau professeur créé ou null si annulé
     */
    @Override
    public Professor promptForNewProfessor() {
        ProfessorDialog dialog = new ProfessorDialog(this);
        dialog.setVisible(true);
        return dialog.getProfessor();
    }

    /**
     * Affiche une boîte de dialogue pour ajouter un groupe
     * @return Le nouveau groupe créé ou null si annulé
     */
    @Override
    public Group promptForNewGroup() {
        GroupDialog dialog = new GroupDialog(this);
        dialog.setVisible(true);
        return dialog.getGroup();
    }

    /**
     * Affiche une boîte de dialogue pour ajouter un local
     * @return Le nouveau local créé ou null si annulé
     */
    @Override
    public Classroom promptForNewClassroom() {
        ClassroomDialog dialog = new ClassroomDialog(this);
        dialog.setVisible(true);
        return dialog.getClassroom();
    }

    /**
     * Affiche une boîte de dialogue pour planifier un cours
     * @param professors Liste des professeurs disponibles
     * @param classrooms Liste des locaux disponibles
     * @param groups Liste des groupes disponibles
     * @return Le nouveau cours créé ou null si annulé
     */
    @Override
    public Course promptForNewCourse(List<Professor> professors, List<Classroom> classrooms, List<Group> groups) {
        CourseDialog dialog = new CourseDialog(this, professors, classrooms, groups);
        dialog.setVisible(true);
        return dialog.getResult();
    }

    //endregion PROMPTFORNEW


    //region ---PROMPTFORXID---

    /**
     * Récupère l'ID du professeur sélectionné dans la table
     * @return L'ID du professeur ou -1 si aucun sélectionné
     */
    @Override
    public int promptForProfessorId() {
        int row = professorsTable.getSelectedRow();
        if (row != -1) {
            return ((ProfessorTableModel) professorsTable.getModel()).getProfessorAt(row).getId();
        }
        showErrorMessage("Veuillez sélectionner un professeur!");
        return -1;
    }

    /**
     * Récupère l'ID du groupe sélectionné dans la table
     * @return L'ID du groupe ou -1 si aucun sélectionné
     */
    @Override
    public int promptForGroupId() {
        int row = groupsTable.getSelectedRow();
        if (row != -1) {
            return ((GroupTableModel) groupsTable.getModel()).getGroupAt(row).getId();
        }
        showErrorMessage("Veuillez sélectionner un groupe!");
        return -1;
    }

    /**
     * Récupère l'ID du local sélectionné dans la table
     * @return L'ID du local ou -1 si aucun sélectionné
     */
    @Override
    public int promptForClassroomId() {
        int row = classroomsTable.getSelectedRow();
        if (row != -1) {
            return ((ClassroomTableModel) classroomsTable.getModel()).getClassroomAt(row).getId();
        }
        showErrorMessage("Veuillez sélectionner un local!");
        return -1;
    }

    /**
     * Récupère l'ID du cours sélectionné dans la table
     * @return L'ID du cours ou -1 si aucun sélectionné
     */
    @Override
    public int promptForCourseId() {
        int row = coursesTable.getSelectedRow();
        if (row != -1) {
            return ((CourseTableModel) coursesTable.getModel()).getCourseAt(row).getCode();
        }
        showErrorMessage("Veuillez sélectionner un cours!");
        return -1;
    }

    //endregion PROMPTFORXID


    //endregion PROMPT


    /**
     * Affiche un message d'information à l'utilisateur
     * @param message Le message à afficher
     */
    @Override
    public void showMessage(String message) {
        JOptionPane.showMessageDialog(this, message, "Information", JOptionPane.INFORMATION_MESSAGE);
    }

    /**
     * Affiche un message d'erreur à l'utilisateur
     * @param message Le message d'erreur à afficher
     */
    @Override
    public void showErrorMessage(String message) {
        JOptionPane.showMessageDialog(this, message, "Erreur", JOptionPane.ERROR_MESSAGE);
    }

    /**
     * Affiche la boîte de dialogue de connexion
     * @return true si l'utilisateur s'est authentifié, false sinon
     */
    @Override
    public boolean showLoginDialog() {
        LoginDialog dialog = new LoginDialog(this);
        dialog.setVisible(true);

        if (dialog.isAuthenticated()) {
            isAuthenticated = true;
            currentUser = dialog.getAuthenticatedUser();
            enableFeatures(true);
            return true;
        }

        return false;
    }

    /**
     * Déconnecte l'utilisateur et désactive les fonctionnalités
     */
    @Override
    public void logout() {
        isAuthenticated = false;
        currentUser = null;
        enableFeatures(false);
        showMessage("Vous avez été déconnecté.");
    }

    /**
     * Démarre l'application en rendant la fenêtre visible
     */
    @Override
    public void run() {
        setVisible(true);
    }

    /**
     * Retourne le nom d'utilisateur authentifié
     * @return Le nom d'utilisateur ou null si non authentifié
     */
    @Override
    public String getAuthenticatedUser() {
        return currentUser;
    }

    //---------------MÉTHODE MAIN DE TEST---------------
    /**
     * Point d'entrée pour tester l'interface graphique indépendamment
     * Dans l'application complète, cette méthode n'est pas utilisée
     */
    public static void main(String[] args) {
        MainFrame frame = new MainFrame();
        frame.setVisible(true);
    }
}