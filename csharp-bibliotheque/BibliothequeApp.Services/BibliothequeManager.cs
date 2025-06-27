using MODEL;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Windows;
using System.Windows.Shapes;
using System.Xml;
using System.Xml.Serialization;


namespace VIEWMODEL
{
    // Classe principale qui gère toutes les données et la logique métier de l'application
    // Fait partie de la couche VIEWMODEL dans l'architecture MVVM
    public class BibliothequeManager : INotifyPropertyChanged
    {
        #region Collections
        // Collections observables qui notifient automatiquement l'interface des changements
        public ObservableCollection<Auteur> Auteurs { get; private set; }
        public ObservableCollection<Livre> Livres { get; private set; }
        public ObservableCollection<Emprunt> Emprunts { get; private set; }
        #endregion

        #region Constructeur
        // Initialise les collections vides lors de la création d'une nouvelle instance
        public BibliothequeManager()
        {
            Auteurs = new ObservableCollection<Auteur>();
            Livres = new ObservableCollection<Livre>();
            Emprunts = new ObservableCollection<Emprunt>();
        }
        #endregion

        #region Fonctions Utilitaires
        // Vérifie si une chaîne est null, vide ou ne contient que des espaces
        private bool EstChaineVide(string texte)
        {
            if (texte == null)
                return true;

            if (texte.Length == 0)
                return true;

            // Vérifie si la chaîne ne contient que des espaces
            for (int i = 0; i < texte.Length; i++)
            {
                if (texte[i] != ' ')
                    return false;
            }

            return true;
        }

        // Trouve un auteur par son ID dans la collection
        private Auteur TrouverAuteurParId(int id)
        {
            foreach (var auteur in Auteurs)
            {
                if (auteur.Id == id)
                    return auteur;
            }
            return null;
        }

        // Trouve un livre par son ISBN dans la collection
        private Livre TrouverLivreParISBN(string isbn)
        {
            foreach (var livre in Livres)
            {
                if (livre.ISBN == isbn)
                    return livre;
            }
            return null;
        }

        // Trouve un emprunt par son ID dans la collection
        private Emprunt TrouverEmpruntParId(int id)
        {
            foreach (var emprunt in Emprunts)
            {
                if (emprunt.Id == id)
                    return emprunt;
            }
            return null;
        }

        // Génère un nouvel ID pour un auteur (max ID actuel + 1)
        private int GenererNouvelIdAuteur()
        {
            int maxId = 0;
            foreach (var auteur in Auteurs)
            {
                if (auteur.Id > maxId)
                    maxId = auteur.Id;
            }
            return maxId + 1;
        }

        // Génère un nouvel ID pour un emprunt (max ID actuel + 1)
        private int GenererNouvelIdEmprunt()
        {
            int maxId = 0;
            foreach (var emprunt in Emprunts)
            {
                if (emprunt.Id > maxId)
                    maxId = emprunt.Id;
            }
            return maxId + 1;
        }

        // Vérifie si un ID d'auteur existe déjà dans la collection
        private bool IdAuteurExisteDeja(int id)
        {
            foreach (var auteur in Auteurs)
            {
                if (auteur.Id == id)
                    return true;
            }
            return false;
        }

        // Vérifie si un ID d'emprunt existe déjà dans la collection
        private bool IdEmpruntExisteDeja(int id)
        {
            foreach (var emprunt in Emprunts)
            {
                if (emprunt.Id == id)
                    return true;
            }
            return false;
        }
        #endregion

        #region Gestion des Auteurs
        // Ajoute un nouvel auteur à la collection après validation
        public bool AjouterAuteur(Auteur auteur)
        {
            if (auteur == null)
                return false;

            // Si l'ID est 0, on génère un nouvel ID
            if (auteur.Id == 0)
            {
                if (Auteurs.Count == 0)
                {
                    auteur.Id = 1; // Premier auteur
                }
                else
                {
                    auteur.Id = GenererNouvelIdAuteur();
                }
            }
            else
            {
                // Vérifier si l'ID existe déjà
                if (IdAuteurExisteDeja(auteur.Id))
                {
                    // Si l'ID existe déjà, on refuse l'ajout
                    return false;
                }
            }

            Auteurs.Add(auteur);
            OnPropertyChanged(nameof(Auteurs));
            return true;
        }

        // Modifie un auteur existant dans la collection
        public bool ModifierAuteur(Auteur auteurModifie)
        {
            if (auteurModifie == null)
                return false;

            Auteur auteurExistant = TrouverAuteurParId(auteurModifie.Id);
            if (auteurExistant == null)
                return false;

            // Mise à jour des propriétés
            auteurExistant.Nom = auteurModifie.Nom;
            auteurExistant.Prenom = auteurModifie.Prenom;
            auteurExistant.DateNaissance = auteurModifie.DateNaissance;
            auteurExistant.Biographie = auteurModifie.Biographie;
            auteurExistant.PhotoPath = auteurModifie.PhotoPath;

            OnPropertyChanged(nameof(Auteurs));
            return true;
        }

        // Supprime un auteur s'il n'est pas référencé par des livres
        public bool SupprimerAuteur(int id)
        {
            Auteur auteur = TrouverAuteurParId(id);
            if (auteur == null)
                return false;

            // Vérifier si l'auteur est utilisé dans des livres
            bool auteurUtilise = false;
            foreach (var l in Livres)
            {
                // Vérifier si l'auteur n'est pas null et si son Id correspond
                if (l.Auteur != null)
                {
                    if (l.Auteur.Id == id)
                    {
                        auteurUtilise = true;
                        break;
                    }
                }
            }

            if (auteurUtilise)
                return false;

            Auteurs.Remove(auteur);
            OnPropertyChanged(nameof(Auteurs));
            return true;
        }
        #endregion

        #region Gestion des Livres
        // Ajoute un nouveau livre à la collection après validation
        public bool AjouterLivre(Livre livre)
        {
            if (livre == null || EstChaineVide(livre.ISBN))
                return false;

            // Vérifier si l'ISBN existe déjà
            if (TrouverLivreParISBN(livre.ISBN) != null)
                return false;

            Livres.Add(livre);
            OnPropertyChanged(nameof(Livres));
            return true;
        }

        // Modifie un livre existant dans la collection
        public bool ModifierLivre(Livre livreModifie)
        {
            if (livreModifie == null || EstChaineVide(livreModifie.ISBN))
                return false;

            Livre livreExistant = TrouverLivreParISBN(livreModifie.ISBN);
            if (livreExistant == null)
                return false;

            // Mise à jour des propriétés
            livreExistant.Titre = livreModifie.Titre;
            livreExistant.Annee = livreModifie.Annee;
            livreExistant.NombrePages = livreModifie.NombrePages;
            livreExistant.Genre = livreModifie.Genre;
            livreExistant.Resume = livreModifie.Resume;
            livreExistant.CouverturePath = livreModifie.CouverturePath;
            livreExistant.Auteur = livreModifie.Auteur;

            OnPropertyChanged(nameof(Livres));
            return true;
        }

        // Supprime un livre s'il n'est pas référencé dans des emprunts
        public bool SupprimerLivre(string isbn)
        {
            Livre livre = TrouverLivreParISBN(isbn);
            if (livre == null)
                return false;

            // Vérifier si le livre est utilisé dans des emprunts
            bool livreUtiliseDansEmprunts = false;
            foreach (var e in Emprunts)
            {
                if (e.Livre != null)
                {
                    if (e.Livre.ISBN == isbn)
                    {
                        livreUtiliseDansEmprunts = true;
                        break;
                    }
                }
            }

            if (livreUtiliseDansEmprunts)
                return false;

            Livres.Remove(livre);
            OnPropertyChanged(nameof(Livres));
            return true;
        }
        #endregion

        #region Gestion des Emprunts
        // Ajoute un nouvel emprunt à la collection après validation
        public bool AjouterEmprunt(Emprunt emprunt)
        {
            if (emprunt == null)
                return false;

            // Si l'ID est 0, on génère un nouvel ID
            if (emprunt.Id == 0)
            {
                if (Emprunts.Count == 0)
                {
                    emprunt.Id = 1; // Premier emprunt
                }
                else
                {
                    emprunt.Id = GenererNouvelIdEmprunt();
                }
            }
            else
            {
                // Vérifier si l'ID existe déjà
                if (IdEmpruntExisteDeja(emprunt.Id))
                {
                    // Si l'ID existe déjà, on refuse l'ajout
                    return false;
                }
            }

            Emprunts.Add(emprunt);
            OnPropertyChanged(nameof(Emprunts));
            return true;
        }

        // Modifie un emprunt existant dans la collection
        public bool ModifierEmprunt(Emprunt empruntModifie)
        {
            if (empruntModifie == null)
                return false;

            Emprunt empruntExistant = TrouverEmpruntParId(empruntModifie.Id);
            if (empruntExistant == null)
                return false;

            // Mise à jour des propriétés
            empruntExistant.Livre = empruntModifie.Livre;
            empruntExistant.NomEmprunteur = empruntModifie.NomEmprunteur;
            empruntExistant.DateEmprunt = empruntModifie.DateEmprunt;
            empruntExistant.DateRetourPrevue = empruntModifie.DateRetourPrevue;
            empruntExistant.EstRetourne = empruntModifie.EstRetourne;

            OnPropertyChanged(nameof(Emprunts));
            return true;
        }

       
        // Marque un emprunt comme retourné (change l'état EstRetourne)
        public bool RetournerLivre(int empruntId)
        {
            Emprunt emprunt = TrouverEmpruntParId(empruntId);
            if (emprunt == null || emprunt.EstRetourne)
                return false;

            emprunt.EstRetourne = true;
            OnPropertyChanged(nameof(Emprunts));
            return true;
        }
        #endregion

        #region Sauvegarde/Chargement JSON
        // Sauvegarde toutes les données dans un fichier JSON
        public bool SauvegarderDonnees(string cheminFichier)
        {
            try
            {
                // Préparation des données à sauvegarder
                var donnees = new DonneesBibliotheque
                {
                    Auteurs = Auteurs.ToList(),
                    Livres = Livres.ToList(),
                    Emprunts = Emprunts.ToList()
                };

                // Sérialisation JSON avec indentation
                var options = new JsonSerializerOptions { WriteIndented = true };
                string jsonString = JsonSerializer.Serialize(donnees, options);

                // Écriture du fichier
                File.WriteAllText(cheminFichier, jsonString);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        // Charge toutes les données depuis un fichier JSON
        public bool ChargerDonnees(string cheminFichier)
        {
            try
            {
                if (!File.Exists(cheminFichier))
                    return false;

                // Lecture et désérialisation du fichier JSON
                string jsonString = File.ReadAllText(cheminFichier);
                var donnees = JsonSerializer.Deserialize<DonneesBibliotheque>(jsonString);

                // Vider les collections existantes
                Auteurs.Clear();
                Livres.Clear();
                Emprunts.Clear();

                // Ajouter les auteurs
                foreach (var auteur in donnees.Auteurs)
                    Auteurs.Add(auteur);

                // Ajouter les livres en rétablissant les références aux auteurs
                foreach (var livre in donnees.Livres)
                {
                    // Récupérer la référence correcte de l'auteur
                    if (livre.Auteur != null)
                    {
                        Auteur auteurRef = TrouverAuteurParId(livre.Auteur.Id);
                        livre.Auteur = auteurRef;
                    }
                    Livres.Add(livre);
                }

                // Ajouter les emprunts en rétablissant les références aux livres
                foreach (var emprunt in donnees.Emprunts)
                {
                    // Récupérer la référence correcte du livre
                    if (emprunt.Livre != null)
                    {
                        Livre livreRef = TrouverLivreParISBN(emprunt.Livre.ISBN);
                        emprunt.Livre = livreRef;
                    }
                    Emprunts.Add(emprunt);
                }

                // Notifier les changements
                OnPropertyChanged(nameof(Auteurs));
                OnPropertyChanged(nameof(Livres));
                OnPropertyChanged(nameof(Emprunts));

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
        #endregion

        #region Import/Export XML
        // Exporte un auteur au format XML
        public bool ExporterAuteurXML(Auteur auteur, string cheminFichier)
        {
            StreamWriter writer = null;
            try
            {
                // Créer un sérialiseur XML pour le type Auteur
                XmlSerializer serializer = new XmlSerializer(typeof(Auteur));

                // Créer un StreamWriter pour écrire dans le fichier
                writer = new StreamWriter(cheminFichier);

                // Sérialiser l'objet auteur dans le fichier
                serializer.Serialize(writer, auteur);

                // Fermer le writer explicitement
                writer.Close();
                writer = null;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
            finally
            {
                // S'assurer que le writer est fermé même en cas d'exception
                if (writer != null)
                {
                    writer.Close();
                }
            }
        }

        // Importe des auteurs depuis un fichier XML
        public bool ImporterAuteursXML(string cheminFichier)
        {
            try
            {
                // Vérifier si le fichier existe
                if (!File.Exists(cheminFichier))
                    return false;

                // Utiliser XmlSerializer pour les auteurs
                XmlSerializer serializer = new XmlSerializer(typeof(Auteur[]));

                // Ouvrir le fichier avec StreamReader
                StreamReader reader = new StreamReader(cheminFichier);

                // Désérialiser le fichier XML
                Auteur[] auteursImportes = (Auteur[])serializer.Deserialize(reader);
                reader.Close();

                // Ajouter les auteurs
                bool success = false;
                for (int i = 0; i < auteursImportes.Length; i++)
                {
                    Auteur auteur = auteursImportes[i];

                    // Générer un nouvel ID
                    auteur.Id = GenererNouvelIdAuteur();

                    // Ajouter l'auteur
                    if (AjouterAuteur(auteur))
                        success = true;
                }

                return success;
            }
            catch
            {
                return false;
            }
        }

        // Importe des livres depuis un fichier XML
        public bool ImporterLivresXML(string cheminFichier)
        {
            try
            {
                // Vérifier si le fichier existe
                if (!File.Exists(cheminFichier))
                    return false;

                // Utiliser XmlSerializer pour les livres
                XmlSerializer serializer = new XmlSerializer(typeof(Livre[]));

                // Ouvrir le fichier avec StreamReader
                StreamReader reader = new StreamReader(cheminFichier);

                // Désérialiser le fichier XML
                Livre[] livresImportes = (Livre[])serializer.Deserialize(reader);
                reader.Close();

                // Ajouter les livres
                bool success = false;
                for (int i = 0; i < livresImportes.Length; i++)
                {
                    Livre livre = livresImportes[i];

                    // Trouver l'auteur correspondant
                    if (livre.Auteur != null)
                    {
                        Auteur auteurExistant = null;
                        foreach (var a in Auteurs)
                        {
                            if (a.Nom == livre.Auteur.Nom && a.Prenom == livre.Auteur.Prenom)
                            {
                                auteurExistant = a;
                                break;
                            }
                        }

                        livre.Auteur = auteurExistant;
                    }

                    // Ajouter le livre
                    if (AjouterLivre(livre))
                        success = true;
                }

                return success;
            }
            catch
            {
                return false;
            }
        }

        // Exporte un livre au format XML
        public bool ExporterLivreXML(Livre livre, string cheminFichier)
        {
            StreamWriter writer = null;
            try
            {
                // Créer un sérialiseur XML pour le type Livre
                XmlSerializer serializer = new XmlSerializer(typeof(Livre));

                // Créer un StreamWriter pour écrire dans le fichier
                writer = new StreamWriter(cheminFichier);

                // Sérialiser l'objet livre dans le fichier
                serializer.Serialize(writer, livre);

                // Fermer le writer explicitement
                writer.Close();
                writer = null;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
            finally
            {
                // S'assurer que le writer est fermé même en cas d'exception
                if (writer != null)
                {
                    writer.Close();
                }
            }
        }
        #endregion

        #region INotifyPropertyChanged Implementation
        // Événement qui notifie que les propriétés ont changé
        public event PropertyChangedEventHandler PropertyChanged;

        // Méthode qui déclenche l'événement de notification
        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        #endregion
    }

    // Classe auxiliaire pour sérialiser/désérialiser les données
    public class DonneesBibliotheque
    {
        public List<Auteur> Auteurs { get; set; }
        public List<Livre> Livres { get; set; }
        public List<Emprunt> Emprunts { get; set; }
    }
}