using MODEL;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;

namespace VIEW
{
    public partial class EmpruntWindow : Window, INotifyPropertyChanged
    {
        public Emprunt NouvelEmprunt { get; private set; }

        // Propriétés liées à l'interface
        public IEnumerable<Livre> Livres { get; set; }

        private Livre _livreSelectionne;
        public Livre LivreSelectionne
        {
            get { return _livreSelectionne; }
            set
            {
                _livreSelectionne = value;
                OnPropertyChanged(nameof(LivreSelectionne));
            }
        }

        private string _nomEmprunteur;
        public string NomEmprunteur
        {
            get { return _nomEmprunteur; }
            set
            {
                _nomEmprunteur = value;
                OnPropertyChanged(nameof(NomEmprunteur));
            }
        }

        private DateTime _dateEmprunt;
        public DateTime DateEmprunt
        {
            get { return _dateEmprunt; }
            set
            {
                _dateEmprunt = value;
                OnPropertyChanged(nameof(DateEmprunt));

                // Mettre à jour la date de retour prévue
                DateRetourPrevue = value.AddDays(_nombreJoursEmprunt);
            }
        }

        private DateTime _dateRetourPrevue;
        public DateTime DateRetourPrevue
        {
            get { return _dateRetourPrevue; }
            set
            {
                _dateRetourPrevue = value;
                OnPropertyChanged(nameof(DateRetourPrevue));
            }
        }

        // Indique si le livre peut être modifié
        public bool IsLivreModifiable { get; private set; }

        // Nombre de jours d'emprunt par défaut

        private int _nombreJoursEmprunt;


        /// <summary>
        /// Constructeur pour créer un emprunt avec un livre spécifique
        /// </summary>
        public EmpruntWindow(Livre livre, int nombreJoursEmprunt)
        {
            InitializeComponent();

            _nombreJoursEmprunt = nombreJoursEmprunt;

            // Initialiser les propriétés
            Livres = new List<Livre> { livre };
            LivreSelectionne = livre;
            IsLivreModifiable = false;

            InitialiserDonnees();
        }

        /// <summary>
        /// Constructeur pour créer un emprunt avec un choix de livres
        /// </summary>
        public EmpruntWindow(IEnumerable<Livre> livres, int nombreJoursEmprunt)
        {
            InitializeComponent();

            _nombreJoursEmprunt = nombreJoursEmprunt;

            // Initialiser les propriétés
            Livres = livres;
            IsLivreModifiable = true;

            InitialiserDonnees();
        }

        private void InitialiserDonnees()
        {
            NomEmprunteur = "";
            DateEmprunt = DateTime.Now;
            DateRetourPrevue = DateEmprunt.AddDays(_nombreJoursEmprunt);

            DataContext = this;
        }

        private void Annuler_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
            Close();
        }

        private void Enregistrer_Click(object sender, RoutedEventArgs e)
        {
            // Valider les entrées
            if (LivreSelectionne == null)
            {
                MessageBox.Show("Veuillez sélectionner un livre.", "Validation", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            if (NomEmprunteur == null || NomEmprunteur == "")
            {
                MessageBox.Show("Veuillez saisir le nom de l'emprunteur.", "Validation", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            if (DateRetourPrevue <= DateEmprunt)
            {
                MessageBox.Show("La date de retour prévue doit être postérieure à la date d'emprunt.", "Validation", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            // Créer le nouvel emprunt
            NouvelEmprunt = new Emprunt
            {
                Livre = LivreSelectionne,
                NomEmprunteur = NomEmprunteur,
                DateEmprunt = DateEmprunt,
                DateRetourPrevue = DateRetourPrevue,
                EstRetourne = false
            };

            DialogResult = true;
            Close();
        }

        #region INotifyPropertyChanged Implementation

        public event PropertyChangedEventHandler PropertyChanged;

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