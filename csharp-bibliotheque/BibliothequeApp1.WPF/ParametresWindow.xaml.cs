using VIEWMODEL;
using System.Windows;
using System.Windows.Forms;

namespace VIEW
{
    public partial class ParametresWindow : Window
    {
        private BibliothequeParamManager _paramManager;

        // Copie des paramètres pour l'édition
        public string CheminDossierDonnees { get; set; }
        public int NombreJoursEmprunt { get; set; }

        public ParametresWindow(BibliothequeParamManager paramManager)
        {
            InitializeComponent();

            _paramManager = paramManager;

            // Initialiser les copies
            CheminDossierDonnees = _paramManager.CheminDossierDonnees;
            NombreJoursEmprunt = _paramManager.NombreJoursEmprunt;

            DataContext = this;
        }

        private void ChoisirDossier_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new FolderBrowserDialog
            {
                Description = "Sélectionnez le dossier de données",
                ShowNewFolderButton = true,
                SelectedPath = CheminDossierDonnees
            };

            
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                CheminDossierDonnees = dialog.SelectedPath;

                // Forcer le rafraîchissement de la liaison de données
                DataContext = null;
                DataContext = this;
            }
        }

        private void Annuler_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
            Close();
        }

        private void Enregistrer_Click(object sender, RoutedEventArgs e)
        {
            // Valider les entrées
            if (CheminDossierDonnees == null || CheminDossierDonnees == "")
            {
                System.Windows.MessageBox.Show("Le chemin du dossier de données ne peut pas être vide.",
                    "Validation", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            if (NombreJoursEmprunt <= 0)
            {
                System.Windows.MessageBox.Show("La durée d'emprunt doit être supérieure à 0.",
                    "Validation", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            // Enregistrer les paramètres
            _paramManager.CheminDossierDonnees = CheminDossierDonnees;
            _paramManager.NombreJoursEmprunt = NombreJoursEmprunt;

            DialogResult = true;
            Close();
        }
    }
}