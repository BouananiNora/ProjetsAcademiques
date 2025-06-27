package hepl.GestionHoraire.view.GUI;

import hepl.GestionHoraire.model.entity.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Dialogue permettant de planifier un cours
 * Ce dialogue utilise le pattern MVC où le modèle est représenté par les entités,
 * la vue par les composants Swing, et le contrôleur par les handlers d'événements
 */
public class CourseDialog extends JDialog
{
    //---------------------- VARIABLES ----------------------
    // Panels pour organiser les composants
    private JPanel mainPanel;
    private JPanel formPanel;
    private JPanel buttonPanel;

    // Champs de saisie pour les attributs du cours
    private JTextField titleField;        // Titre du cours
    private JComboBox<String> dayComboBox; // Jour de la semaine

    // Spinners pour gérer l'heure de début et la durée
    private JSpinner startHourSpinner;    // Heure de début (heures)
    private JSpinner startMinuteSpinner;  // Heure de début (minutes)
    private JSpinner durationHourSpinner; // Durée (heures)
    private JSpinner durationMinuteSpinner; // Durée (minutes)

    // Listes déroulantes pour les relations
    private JComboBox professorComboBox;  // Professeur assigné
    private JComboBox classroomComboBox;  // Local assigné
    private JList groupsList;             // Groupes participants
    private DefaultListModel groupsListModel; // Modèle pour la liste des groupes

    // Boutons d'action
    private JButton planButton;           // Bouton pour valider
    private JButton cancelButton;         // Bouton pour annuler

    // Variables pour stocker les données
    private Course result;                // Cours créé par la boîte de dialogue
    private List<Professor> professors;   // Liste des professeurs disponibles
    private List<Classroom> classrooms;   // Liste des locaux disponibles
    private List<Group> groups;           // Liste des groupes disponibles

    //---------------------- CONSTRUCTEUR ----------------------
    /**
     * Constructeur du dialogue de planification de cours
     * Initialise la boîte de dialogue avec les listes d'entités disponibles
     * @param parent Fenêtre parente
     * @param professors Liste des professeurs disponibles
     * @param classrooms Liste des salles disponibles
     * @param groups Liste des groupes disponibles
     */
    public CourseDialog(Frame parent, List<Professor> professors, List<Classroom> classrooms, List<Group> groups)
    {
        super(parent, "Planifier un cours", true);
        this.professors = professors;
        this.classrooms = classrooms;
        this.groups = groups;

        // Initialiser tous les panneaux ici
        mainPanel = new JPanel();
        formPanel = new JPanel();
        buttonPanel = new JPanel();

        initComponents();
        setupLayout();
        setupEventHandlers();
        loadData();

        pack();
        setLocationRelativeTo(parent);
    }

    //---------------------- MÉTHODES D'INITIALISATION ----------------------
    /**
     * Initialise les composants du dialogue
     * Cette méthode crée tous les widgets nécessaires pour le formulaire
     */
    private void initComponents()
    {
        titleField = new JTextField(20);

        String[] days = {
                Timing.MONDAY, Timing.TUESDAY, Timing.WEDNESDAY,
                Timing.THURSDAY, Timing.FRIDAY, Timing.SATURDAY, Timing.SUNDAY
        };
        dayComboBox = new JComboBox(days);

        // Spinners pour l'heure et la durée avec valeurs par défaut avec min, max et incrément
        startHourSpinner = new JSpinner(new SpinnerNumberModel(8, 0, 23, 1));
        startMinuteSpinner = new JSpinner(new SpinnerNumberModel(0, 0, 55, 5));
        durationHourSpinner = new JSpinner(new SpinnerNumberModel(1, 0, 10, 1));
        durationMinuteSpinner = new JSpinner(new SpinnerNumberModel(30, 0, 55, 5));

        // Création des listes déroulantes
        professorComboBox = new JComboBox();
        classroomComboBox = new JComboBox();

        // Création de la liste des groupes avec sélection multiple
        groupsListModel = new DefaultListModel();
        groupsList = new JList(groupsListModel);
        groupsList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);

        planButton = new JButton("Planifier");
        cancelButton = new JButton("Annuler");
    }

    /**
     * Configure la disposition des composants dans le dialogue
     * Utilise principalement BorderLayout et GridLayout pour organiser les éléments
     */
    private void setupLayout()
    {
        setLayout(new BorderLayout());

        // Panel principal avec GridLayout pour aligner les champs
        JPanel formPanel = new JPanel(new GridLayout(0, 2, 5, 5));

        formPanel.add(new JLabel("Jour :"));
        formPanel.add(dayComboBox);

        formPanel.add(new JLabel("Heure de début :"));
        createTimePanel(formPanel, startHourSpinner, startMinuteSpinner);

        formPanel.add(new JLabel("Durée :"));
        createTimePanel(formPanel, durationHourSpinner, durationMinuteSpinner);

        formPanel.add(new JLabel("Titre :"));
        formPanel.add(titleField);

        formPanel.add(new JLabel("Professeur :"));
        formPanel.add(professorComboBox);

        formPanel.add(new JLabel("Local :"));
        formPanel.add(classroomComboBox);

        formPanel.add(new JLabel("Groupes :"));
        JScrollPane groupScrollPane = new JScrollPane(groupsList);
        groupScrollPane.setSize(100, 60);
        formPanel.add(groupScrollPane);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(planButton);
        buttonPanel.add(cancelButton);

        add(formPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.SOUTH);
    }

    /**
     * Crée un panel pour la saisie de temps (heures et minutes)
     * Cette méthode factorize le code pour les panels de temps
     * @param formPanel Le panel parent
     * @param hourSpinner Le spinner pour les heures
     * @param minuteSpinner Le spinner pour les minutes
     */
    private void createTimePanel(JPanel formPanel, JSpinner hourSpinner, JSpinner minuteSpinner)
    {
        JPanel timePanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 0, 0));
        timePanel.add(hourSpinner);
        timePanel.add(new JLabel("h"));
        timePanel.add(minuteSpinner);
        timePanel.add(new JLabel("min"));
        formPanel.add(timePanel);
    }

    //---------------------- GESTIONNAIRES D'ÉVÉNEMENTS ----------------------
    /**
     * Configure les écouteurs d'événements pour les boutons
     * Implémente le pattern Observer pour réagir aux actions utilisateur
     */
    private void setupEventHandlers()
    {
        // Gestionnaire d'événements pour le bouton de planification
        planButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Récupération des valeurs du formulaire
                String title = titleField.getText();
                String day = (String) dayComboBox.getSelectedItem();

                int startHour = (Integer) startHourSpinner.getValue();
                int startMinute = (Integer) startMinuteSpinner.getValue();

                int durationHour = (Integer) durationHourSpinner.getValue();
                int durationMinute = (Integer) durationMinuteSpinner.getValue();

                int professorIndex = professorComboBox.getSelectedIndex();
                int classroomIndex = classroomComboBox.getSelectedIndex();

                //  parcourir la liste pour trouver tous les indices sélectionnés
                List<Integer> selectedIndicesList = new ArrayList<>();
                for (int i = 0; i < groupsList.getModel().getSize(); i++) {
                    if (groupsList.isSelectedIndex(i)) {
                        selectedIndicesList.add(i);
                    }
                }

                // Vérification que tous les champs nécessaires sont remplis
                if (title.equals("") || professorIndex == -1 || classroomIndex == -1 || selectedIndicesList.isEmpty()) {
                    JOptionPane.showMessageDialog(CourseDialog.this,
                            "Veuillez remplir tous les champs et sélectionner au moins un groupe!",
                            "Erreur de saisie",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Création des objets Time et Timing pour le cours
                Time start = new Time(startHour, startMinute);
                Time duration = new Time(durationHour, durationMinute);
                Timing timing = new Timing(day, start, duration);

                // Récupération des objets sélectionnés
                Professor selectedProfessor = professors.get(professorIndex);
                Classroom selectedClassroom = classrooms.get(classroomIndex);

                // Création de l'ensemble des IDs de groupes
                Set<Integer> groupIds = new HashSet<>();
                for (int i : selectedIndicesList) {
                    groupIds.add(groups.get(i).getId());
                }

                // Création du cours avec les données recueillies
                result = new Course(0, title, timing, selectedProfessor.getId(), selectedClassroom.getId(), groupIds);

                dispose();
            }
        });

        // Gestionnaire d'événements pour le bouton d'annulation
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                result = null;
                dispose();
            }
        });
    }

    //---------------------- CHARGEMENT DES DONNÉES ----------------------
    /**
     * Charge les données dans les composants
     * Remplit les combobox et la liste avec les données disponibles
     */
    private void loadData()
    {
        for (int i = 0; i < professors.size(); i++) {
            Professor professor = professors.get(i);
            professorComboBox.addItem(professor.getlastName() + " " + professor.getfirstName());
        }

        for (int i = 0; i < classrooms.size(); i++) {
            Classroom classroom = classrooms.get(i);
            classroomComboBox.addItem(classroom.getName());
        }

        for (int i = 0; i < groups.size(); i++) {
            Group group = groups.get(i);
            groupsListModel.addElement(group.getName());
        }
    }

    //---------------------- ACCESSEURS ----------------------
    /**
     * Retourne le cours créé
     * Cette méthode permet au code appelant de récupérer le résultat du dialogue
     * @return le cours créé ou null si annulé
     */
    public Course getResult() {
        return result;
    }

    //---------------------- MÉTHODE DE TEST ----------------------
    /**
     * Méthode main de test pour la boîte de dialogue
     * Permet de tester le dialogue indépendamment du reste de l'application
     * @param args arguments de ligne de commande (non utilisés)
     */
    public static void main(String[] args) {
        List<Professor> professors = new ArrayList<>();
        professors.add(new Professor(1, "Dupont", "Jean"));
        professors.add(new Professor(2, "Martin", "Sophie"));
        professors.add(new Professor(3, "Lambert", "Michel"));

        List<Classroom> classrooms = new ArrayList<>();
        classrooms.add(new Classroom(1, "S210", 30));
        classrooms.add(new Classroom(2, "L025", 60));
        classrooms.add(new Classroom(3, "A120", 120));

        List<Group> groups = new ArrayList<>();
        groups.add(new Group(1, "BAC1 Info"));
        groups.add(new Group(2, "BAC2 Info"));
        groups.add(new Group(3, "BAC3 Info"));
        groups.add(new Group(4, "BAC1 Elec"));

        CourseDialog dialog = new CourseDialog(null, professors, classrooms, groups);
        dialog.setVisible(true);
    }
}