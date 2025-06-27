using MODEL;
using VIEWMODEL;
using Microsoft.Win32;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace VIEW
{
    // Classe principale de l'interface utilisateur qui gère l'interaction avec l'utilisateur
    // Implémente INotifyPropertyChanged pour notifier les changements de propriétés liées à l'interface
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        // Gestionnaires principaux pour les données et les paramètres
        private BibliothequeManager _bibliothequeManager;
        private BibliothequeParamManager _paramManager;

        // Propriété pour le nom de la bibliothèque
        private string _nomBibliotheque = "Ma Bibliothèque";
        public string NomBibliotheque
        {
            get { return _nomBibliotheque; }
            set
            {
                if (_nomBibliotheque != value)
                {
                    _nomBibliotheque = value;
                    OnPropertyChanged(nameof(NomBibliotheque));
                }
            }
        }

        #region Collections
        // Collections liées à l'interface utilisateur
        public ObservableCollection<Auteur> Auteurs
        {
            get
            {
                return _bibliothequeManager.Auteurs;
            }
        }

        public ObservableCollection<Livre> Livres
        {
            get
            {
                return _bibliothequeManager.Livres;
            }
        }
        public ObservableCollection<Emprunt> Emprunts
        {
            get
            {
                if (_bibliothequeManager == null)
                {
                    return new ObservableCollection<Emprunt>();
                }
                else
                {
                    return _bibliothequeManager.Emprunts;
                }
            }
        }

        // Collection filtrée des emprunts pour l'affichage
        private ObservableCollection<Emprunt> _empruntsFiltres;
        public ObservableCollection<Emprunt> EmpruntsFiltres
        {
            get { return _empruntsFiltres; }
            set
            {
                _empruntsFiltres = value;
                OnPropertyChanged(nameof(EmpruntsFiltres));
            }
        }

        #endregion

        #region Sélections actuelles dans l'interface
        private Auteur _auteurSelectionne;
        public Auteur AuteurSelectionne
        {
            get { return _auteurSelectionne; }
            set
            {
                _auteurSelectionne = value;
                OnPropertyChanged(nameof(AuteurSelectionne));
                OnPropertyChanged(nameof(IsAuteurSelectionne));
            }
        }

        private Livre _livreSelectionne;
        public Livre LivreSelectionne
        {
            get { return _livreSelectionne; }
            set
            {
                _livreSelectionne = value;
                OnPropertyChanged(nameof(LivreSelectionne));
                OnPropertyChanged(nameof(IsLivreSelectionne));
                OnPropertyChanged(nameof(IsLivreExistant));
            }
        }
        #endregion

        #region Propriétés calculées pour l'état de l'interface
        public bool IsAuteurSelectionne
        {
            get
            {
                return AuteurSelectionne != null;
            }
        }

        public bool IsLivreSelectionne
        {
            get
            {
                return LivreSelectionne != null;
            }
        }

        public bool IsLivreExistant
        {
            get
            {
                // Vérifier si LivreSelectionne n'est pas null
                if (LivreSelectionne == null)
                {
                    return false;
                }

                // Vérifier si l'ISBN n'est pas null ou vide
                if (LivreSelectionne.ISBN == null || LivreSelectionne.ISBN == "")
                {
                    return false;
                }

                // Vérifier si un livre avec le même ISBN existe déjà dans la collection
                bool livreExiste = false;
                foreach (Livre livre in Livres)
                {
                    if (livre.ISBN == LivreSelectionne.ISBN)
                    {
                        livreExiste = true;
                        break;
                    }
                }

                return livreExiste;
            }
        }

        #endregion

        // Propriétés statistiques
        public int NombreLivres
        {
            get
            {
                return Livres.Count;
            }
        }

        public int NombreEmpruntsEnCours
        {
            get
            {
                int compteur = 0;

                foreach (Emprunt emprunt in Emprunts)
                {
                    if (!emprunt.EstRetourne)
                    {
                        compteur++;
                    }
                }

                return compteur;
            }
        }

        // Constructeur de la fenêtre principale
        public MainWindow()
        {
            InitializeComponent();

            _bibliothequeManager = new BibliothequeManager();
            _paramManager = new BibliothequeParamManager();
            _paramManager.ChargerParametres();

            // Initialiser la collection des emprunts filtrés
            EmpruntsFiltres = new ObservableCollection<Emprunt>();

            // Définir le DataContext
            DataContext = this;

            // Charger les données
            ChargerDonnees();

            // S'abonner aux événements de changement de collection
            _bibliothequeManager.PropertyChanged += BibliothequeManager_PropertyChanged;
        }

        // Gestionnaire d'événements pour les changements dans BibliothequeManager
        private void BibliothequeManager_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            // Mettre à jour les propriétés calculées
            OnPropertyChanged(nameof(NombreLivres));
            OnPropertyChanged(nameof(NombreEmpruntsEnCours));

            // Mettre à jour les emprunts filtrés
            if (e.PropertyName == nameof(Emprunts))
            {
                FiltrerEmprunts();
            }
        }

        // Charge les données initiales ou crée des exemples
        private void ChargerDonnees()
        {
            // Vérifier si le fichier existe
            string cheminFichier = _paramManager.CheminDossierDonnees + "\\" + "bibliotheque.json";
            if (File.Exists(cheminFichier))
            {
                _bibliothequeManager.ChargerDonnees(cheminFichier);
                MessageBox.Show("Données chargées avec succès.");

            }
            else
            {
                // Créer des données fictives pour l'exemple
                CreerDonneesExemple();
            }

            // Mettre à jour les emprunts filtrés
            FiltrerEmprunts();
        }

        // Crée des données d'exemple pour une bibliothèque vide
        private void CreerDonneesExemple()
        {
            // Exemple d'auteurs
            var auteur1 = new Auteur(1, "Hugo", "Victor", new DateTime(1802, 2, 26), "Victor Hugo est un poète, dramaturge et romancier français.");
            var auteur2 = new Auteur(2, "Rowling", "J.K.", new DateTime(1965, 7, 31), "J.K. Rowling est une romancière britannique, auteure de la saga Harry Potter.");

            _bibliothequeManager.AjouterAuteur(auteur1);
            _bibliothequeManager.AjouterAuteur(auteur2);

            // Exemple de livres
            var livre1 = new Livre("9782253096337", "Les Misérables", 1862, 1500, GenreLivre.Roman, auteur1, "Un des plus grands romans de la littérature française.");
            var livre2 = new Livre("9782070643028", "Harry Potter à l'école des sorciers", 1997, 320, GenreLivre.Fantastique, auteur2, "Premier tome de la saga Harry Potter.");

            _bibliothequeManager.AjouterLivre(livre1);
            _bibliothequeManager.AjouterLivre(livre2);

            // Exemple d'emprunts
            var emprunt1 = new Emprunt(1, livre1, "Jean Dupont", DateTime.Now.AddDays(-20), DateTime.Now.AddDays(-5));
            var emprunt2 = new Emprunt(2, livre2, "Marie Martin", DateTime.Now.AddDays(-5), DateTime.Now.AddDays(9));

            _bibliothequeManager.AjouterEmprunt(emprunt1);
            _bibliothequeManager.AjouterEmprunt(emprunt2);
        }

        // Filtre les emprunts selon le critère sélectionné
        private void FiltrerEmprunts()
        {
            // S'assurer que EmpruntsFiltres n'est jamais null
            if (EmpruntsFiltres == null)
                EmpruntsFiltres = new ObservableCollection<Emprunt>();

            EmpruntsFiltres.Clear();

            // Récupérer l'index du filtre sélectionné
            int filtreIndex;
            if (FiltreEmpruntsComboBox != null && FiltreEmpruntsComboBox.SelectedIndex != null)
            {
                filtreIndex = FiltreEmpruntsComboBox.SelectedIndex;
            }
            else
            {
                filtreIndex = 0;
            }

            IEnumerable<Emprunt> empruntsFiltrés;

            if (filtreIndex == 1)
            {
                // Emprunts en cours
                empruntsFiltrés = new List<Emprunt>();
                foreach (Emprunt e in Emprunts)
                {
                    if (!e.EstRetourne)
                    {
                        ((List<Emprunt>)empruntsFiltrés).Add(e);
                    }
                }
            }
            else if (filtreIndex == 2)
            {
                // Emprunts en retard
                empruntsFiltrés = new List<Emprunt>();
                foreach (Emprunt e in Emprunts)
                {
                    if (e.EstEnRetard)
                    {
                        ((List<Emprunt>)empruntsFiltrés).Add(e);
                    }
                }
            }
            else if (filtreIndex == 3)
            {
                // Emprunts retournés
                empruntsFiltrés = new List<Emprunt>();
                foreach (Emprunt e in Emprunts)
                {
                    if (e.EstRetourne)
                    {
                        ((List<Emprunt>)empruntsFiltrés).Add(e);
                    }
                }
            }
            else
            {
                // Tous les emprunts
                empruntsFiltrés = Emprunts;
            }

            foreach (var emprunt in empruntsFiltrés)
            {
                EmpruntsFiltres.Add(emprunt);
            }
        }

        #region Événements du menu

        // Crée une nouvelle bibliothèque
        private void NouveauMenuItem_Click(object sender, RoutedEventArgs e)
        {
            // Demander confirmation
            if (MessageBox.Show("Voulez-vous créer une nouvelle bibliothèque ? Toutes les données non sauvegardées seront perdues.",
                "Confirmation", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            {
                // Réinitialiser les sélections avant de créer une nouvelle bibliothèque
                AuteurSelectionne = null;
                LivreSelectionne = null;

                // Créer une nouvelle bibliothèque
                _bibliothequeManager = new BibliothequeManager();
                _bibliothequeManager.PropertyChanged += BibliothequeManager_PropertyChanged;

                // Réinitialiser les emprunts filtrés
                EmpruntsFiltres.Clear();

                // Mettre à jour le DataContext
                DataContext = null;
                DataContext = this;

                // Mettre à jour les propriétés calculées
                OnPropertyChanged(nameof(NombreLivres));
                OnPropertyChanged(nameof(NombreEmpruntsEnCours));
                OnPropertyChanged(nameof(Auteurs));
                OnPropertyChanged(nameof(Livres));
                OnPropertyChanged(nameof(Emprunts));

                MessageBox.Show("Nouvelle bibliothèque créée.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
            }
        }

        // Charge une bibliothèque existante
        private void ChargerMenuItem_Click(object sender, RoutedEventArgs e)
        {
            // Construire le chemin vers le sous-dossier BIBLIOTHEQUES
            string cheminBase = _paramManager.CheminDossierDonnees;
            string cheminDossierBibliotheques = cheminBase + "\\BIBLIOTHEQUES";


            var openFileDialog = new OpenFileDialog
            {
                Filter = "Fichiers JSON (*.json)|*.json",
                InitialDirectory = cheminDossierBibliotheques // Pointer directement vers le sous-dossier BIBLIOTHEQUES
            };

            if (openFileDialog.ShowDialog() == true)
            {
                if (_bibliothequeManager.ChargerDonnees(openFileDialog.FileName))
                {
                    // Mettre à jour le nom de la bibliothèque
                    string nomFichier = openFileDialog.FileName.Substring(openFileDialog.FileName.LastIndexOf('\\') + 1);
                    nomFichier = nomFichier.Substring(0, nomFichier.LastIndexOf('.'));
                    NomBibliotheque = nomFichier;

                    MessageBox.Show("Données chargées avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors du chargement des données.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Sauvegarde la bibliothèque actuelle
        private void SauvegarderMenuItem_Click(object sender, RoutedEventArgs e)
        {
            // Créer le chemin du dossier BIBLIOTHEQUES
            string cheminBase = _paramManager.CheminDossierDonnees;
            string cheminDossier = cheminBase + "\\BIBLIOTHEQUES";

            // Générer un nom de fichier avec la date et l'heure actuelles pour éviter les écrasements
            string dateHeure = DateTime.Now.ToString("yyyyMMdd_HHmmss");
            string nomFichier = "bibliotheque_" + dateHeure + ".json";
            string cheminComplet = cheminDossier + "\\" + nomFichier;

            // Informer l'utilisateur du chemin de sauvegarde
            MessageBox.Show("La bibliothèque sera sauvegardée dans :\n" + cheminComplet,
                           "Information", MessageBoxButton.OK, MessageBoxImage.Information);

            // Sauvegarder les données
            if (_bibliothequeManager.SauvegarderDonnees(cheminComplet))
            {
                MessageBox.Show("Données sauvegardées avec succès dans le fichier :\n" + cheminComplet,
                               "Succès", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else
            {
                MessageBox.Show("Erreur lors de la sauvegarde des données.",
                               "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        // Affiche la fenêtre des paramètres
        private void ParametresMenuItem_Click(object sender, RoutedEventArgs e)
        {
            // Afficher la fenêtre de paramètres
            var parametresWindow = new ParametresWindow(_paramManager);
            parametresWindow.Owner = this;
            parametresWindow.ShowDialog();
        }

        // Quitte l'application
        private void QuitterMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        // Ajoute un nouvel auteur
        private void AjouterAuteurMenuItem_Click(object sender, RoutedEventArgs e)
        {
            AuteurSelectionne = new Auteur();
        }

        // Importe un ou plusieurs auteurs depuis un fichier XML
        private void ImporterAuteurMenuItem_Click(object sender, RoutedEventArgs e)
        {
            // Calculer le chemin du dossier d'importation des auteurs
            string cheminBase = _paramManager.CheminDossierDonnees;
            string cheminDossier = cheminBase + "\\IMPORT\\AUTEURS";

            // Créer la boîte de dialogue avec le bon dossier initial
            var openFileDialog = new OpenFileDialog
            {
                Filter = "Fichiers XML (*.xml)|*.xml",
                InitialDirectory = cheminDossier
            };

            if (openFileDialog.ShowDialog() == true)
            {
                if (_bibliothequeManager.ImporterAuteursXML(openFileDialog.FileName))
                {
                    MessageBox.Show("Auteur(s) importé(s) avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors de l'importation du/des auteur(s).", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Importe un ou plusieurs livres depuis un fichier XML
        private void ImporterLivreMenuItem_Click(object sender, RoutedEventArgs e)
        {
            // Calculer le chemin du dossier d'importation des livres
            string cheminBase = _paramManager.CheminDossierDonnees;
            string cheminDossier = cheminBase + "\\IMPORT\\LIVRES";

            // Créer la boîte de dialogue avec le bon dossier initial
            var openFileDialog = new OpenFileDialog
            {
                Filter = "Fichiers XML (*.xml)|*.xml",
                InitialDirectory = cheminDossier
            };

            if (openFileDialog.ShowDialog() == true)
            {
                if (_bibliothequeManager.ImporterLivresXML(openFileDialog.FileName))
                {
                    MessageBox.Show("Livre(s) importé(s) avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors de l'importation du/des livre(s).", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Ajoute un nouveau livre
        private void AjouterLivreMenuItem_Click(object sender, RoutedEventArgs e)
        {
            LivreSelectionne = new Livre();
        }

        // Affiche la fenêtre d'emprunt pour créer un nouvel emprunt
        private void EnregistrerEmpruntMenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (Livres.Count == 0)
            {
                MessageBox.Show("Aucun livre disponible pour créer un emprunt.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            var empruntWindow = new EmpruntWindow(Livres, _paramManager.NombreJoursEmprunt);
            empruntWindow.Owner = this;

            if (empruntWindow.ShowDialog() == true && empruntWindow.NouvelEmprunt != null)
            {
                if (_bibliothequeManager.AjouterEmprunt(empruntWindow.NouvelEmprunt))
                {
                    MessageBox.Show("Emprunt enregistré avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors de l'enregistrement de l'emprunt.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        #endregion

        #region Événements des contrôles

        // Gère le changement de sélection dans la DataGrid des auteurs
        private void AuteursDataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (AuteursDataGrid.SelectedItem is Auteur auteur)
            {
                AuteurSelectionne = auteur;
            }
        }

        // Gère le changement de sélection dans la DataGrid des livres
        private void LivresDataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (LivresDataGrid.SelectedItem is Livre livre)
            {
                LivreSelectionne = livre;
            }
        }

        // Gère le changement de filtre des emprunts
        private void FiltreEmpruntsComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            FiltrerEmprunts();
        }

        // Permet de choisir une photo pour un auteur
        private void ChoisirPhotoAuteur_Click(object sender, RoutedEventArgs e)
        {
            if (AuteurSelectionne == null) return;

            // Utiliser le dossier d'images pour les auteurs
            string cheminDossier = _paramManager.CheminDossierDonnees + "\\IMAGES\\AUTEURS";

            var openFileDialog = new OpenFileDialog
            {
                Filter = "Images (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp",
                InitialDirectory = cheminDossier
            };

            if (openFileDialog.ShowDialog() == true)
            {
                AuteurSelectionne.PhotoPath = openFileDialog.FileName;
            }
        }

        // Permet de choisir une couverture pour un livre
        private void ChoisirCouvertureLivre_Click(object sender, RoutedEventArgs e)
        {
            if (LivreSelectionne == null) return;

            // Utiliser le dossier d'images pour les livres
            string cheminDossier = _paramManager.CheminDossierDonnees + "\\IMAGES\\LIVRES";

            var openFileDialog = new OpenFileDialog
            {
                Filter = "Images (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp",
                InitialDirectory = cheminDossier
            };

            if (openFileDialog.ShowDialog() == true)
            {
                LivreSelectionne.CouverturePath = openFileDialog.FileName;
            }
        }

        // Supprime un auteur
        private void SupprimerAuteur_Click(object sender, RoutedEventArgs e)
        {
            if (AuteurSelectionne == null) return;

            if (MessageBox.Show($"Voulez-vous vraiment supprimer l'auteur {AuteurSelectionne.NomComplet} ?",
                "Confirmation", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            {
                if (_bibliothequeManager.SupprimerAuteur(AuteurSelectionne.Id))
                {
                    AuteurSelectionne = null;
                    MessageBox.Show("Auteur supprimé avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Impossible de supprimer cet auteur car il est référencé par un ou plusieurs livres.",
                        "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Enregistre les modifications d'un auteur
        private void EnregistrerAuteur_Click(object sender, RoutedEventArgs e)
        {
            if (AuteurSelectionne == null) return;

            // Vérifier si l'auteur existe déjà
            bool auteurExiste = false;
            foreach (Auteur auteur in Auteurs)
            {
                if (auteur == AuteurSelectionne) // ou auteur.Id == AuteurSelectionne.Id si vous préférez comparer par ID
                {
                    auteurExiste = true;
                    break;
                }
            }

            if (auteurExiste)
            {
                // Modification
                _bibliothequeManager.ModifierAuteur(AuteurSelectionne);
                MessageBox.Show("Auteur modifié avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else
            {
                // Ajout
                if (_bibliothequeManager.AjouterAuteur(AuteurSelectionne))
                {
                    MessageBox.Show("Auteur ajouté avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors de l'ajout de l'auteur.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Exporte un auteur au format XML
        private void ExporterAuteurXML_Click(object sender, RoutedEventArgs e)
        {
            if (AuteurSelectionne == null) return;

            // Utiliser le dossier de base depuis paramManager et créer le chemin complet
            string cheminBase = _paramManager.CheminDossierDonnees;
            string cheminDossier = cheminBase + "\\EXPORT\\AUTEURS";
            string nomFichierParDefaut = "auteur_" + AuteurSelectionne.Id + ".xml";
            string cheminComplet = cheminDossier + "\\" + nomFichierParDefaut;

            // Informer l'utilisateur sur l'emplacement du fichier
            MessageBox.Show("Le fichier sera exporté à l'emplacement suivant: \n" + cheminComplet,
                           "Information", MessageBoxButton.OK, MessageBoxImage.Information);

            // Exporter directement
            if (_bibliothequeManager.ExporterAuteurXML(AuteurSelectionne, cheminComplet))
            {
                MessageBox.Show("Auteur exporté avec succès dans le fichier:\n" + cheminComplet,
                                "Succès", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else
            {
                MessageBox.Show("Erreur lors de l'exportation de l'auteur.",
                               "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        // Supprime un livre
        private void SupprimerLivre_Click(object sender, RoutedEventArgs e)
        {
            if (LivreSelectionne == null) return;

            if (MessageBox.Show($"Voulez-vous vraiment supprimer le livre {LivreSelectionne.Titre} ?",
                "Confirmation", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            {
                if (_bibliothequeManager.SupprimerLivre(LivreSelectionne.ISBN))
                {
                    LivreSelectionne = null;
                    MessageBox.Show("Livre supprimé avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Impossible de supprimer ce livre car il est référencé par un ou plusieurs emprunts.",
                        "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Enregistre les modifications d'un livre
        private void EnregistrerLivre_Click(object sender, RoutedEventArgs e)
        {
            if (LivreSelectionne == null) return;

            // Vérifier que les champs obligatoires sont remplis
            if (LivreSelectionne.ISBN == null || LivreSelectionne.ISBN == "" || LivreSelectionne.Titre == null || LivreSelectionne.Titre == "")
            {
                MessageBox.Show("Veuillez remplir tous les champs obligatoires (ISBN, Titre).",
                    "Validation", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            // Vérifier si le livre existe déjà
            if (IsLivreExistant)
            {
                // Modification
                _bibliothequeManager.ModifierLivre(LivreSelectionne);
                MessageBox.Show("Livre modifié avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else
            {
                // Ajout
                if (_bibliothequeManager.AjouterLivre(LivreSelectionne))
                {
                    MessageBox.Show("Livre ajouté avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors de l'ajout du livre.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Exporte un livre au format XML
        private void ExporterLivreXML_Click(object sender, RoutedEventArgs e)
        {
            if (LivreSelectionne == null) return;

            // Utiliser le dossier de base depuis paramManager et créer le chemin complet
            string cheminBase = _paramManager.CheminDossierDonnees;
            string cheminDossier = cheminBase + "\\EXPORT\\LIVRES";
            string nomFichierParDefaut = "livre_" + LivreSelectionne.ISBN + ".xml";
            string cheminComplet = cheminDossier + "\\" + nomFichierParDefaut;

            // Informer l'utilisateur sur l'emplacement du fichier
            MessageBox.Show("Le fichier sera exporté à l'emplacement suivant: \n" + cheminComplet,
                           "Information", MessageBoxButton.OK, MessageBoxImage.Information);

            // S'assurer que le dossier existe
            if (!Directory.Exists(cheminDossier))
            {
                Directory.CreateDirectory(cheminDossier);
            }

            // Exporter directement
            if (_bibliothequeManager.ExporterLivreXML(LivreSelectionne, cheminComplet))
            {
                MessageBox.Show("Livre exporté avec succès dans le fichier:\n" + cheminComplet,
                                "Succès", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            else
            {
                MessageBox.Show("Erreur lors de l'exportation du livre.",
                               "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        // Enregistre un emprunt pour le livre sélectionné
        private void EnregistrerEmprunt_Click(object sender, RoutedEventArgs e)
        {
            if (LivreSelectionne == null) return;

            var empruntWindow = new EmpruntWindow(LivreSelectionne, _paramManager.NombreJoursEmprunt);
            empruntWindow.Owner = this;

            if (empruntWindow.ShowDialog() == true && empruntWindow.NouvelEmprunt != null)
            {
                if (_bibliothequeManager.AjouterEmprunt(empruntWindow.NouvelEmprunt))
                {
                    MessageBox.Show("Emprunt enregistré avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors de l'enregistrement de l'emprunt.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        // Marque un livre comme retourné
        private void RetournerLivre_Click(object sender, RoutedEventArgs e)
        {
            if (sender is Button button && button.Tag is int empruntId)
            {
                if (_bibliothequeManager.RetournerLivre(empruntId))
                {
                    MessageBox.Show("Livre retourné avec succès.", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show("Erreur lors du retour du livre.", "Erreur", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        #endregion

        #region INotifyPropertyChanged Implementation

        // Implémentation de l'interface INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        // Méthode pour notifier les changements de propriétés
        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}