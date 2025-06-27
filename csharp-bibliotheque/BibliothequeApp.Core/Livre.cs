using System;
using System.ComponentModel;

namespace MODEL
{
    // Une énumération qui définit les différents genres de livres possibles
    public enum GenreLivre
    {
        Roman,              // Genre roman
        ScienceFiction,     // Genre science-fiction
        Policier,           // Genre policier
        Biographie,         // Genre biographie
        Histoire,           // Genre histoire
        Fantastique,        // Genre fantastique
        Jeunesse,           // Genre jeunesse
        Autre               // Autres genres
    }


    public class Livre : INotifyPropertyChanged, IEquatable<Livre>, IComparable<Livre>
    {

        #region Champs et Propriétés

        // Champ privé pour stocker l'ISBN du livre
        private string _isbn;

        // Propriété publique pour accéder et modifier l'ISBN
        public string ISBN
        {
            get { return _isbn; } // Retourne la valeur du champ privé
            set
            {
                if (_isbn != value) // Vérifie si la valeur a changé
                {
                    _isbn = value; // Assigne la nouvelle valeur au champ privé
                    OnPropertyChanged(nameof(ISBN)); // Notifie que la propriété a changé
                }
            }
        }

        // Champ privé pour stocker le titre du livre
        private string _titre;

        // Propriété publique pour accéder et modifier le titre
        public string Titre
        {
            get { return _titre; }
            set
            {
                if (_titre != value)
                {
                    _titre = value;
                    OnPropertyChanged(nameof(Titre));
                }
            }
        }

        // Champ privé pour stocker l'année de publication
        private int _annee;

        // Propriété publique pour accéder et modifier l'année
        public int Annee
        {
            get { return _annee; }
            set
            {
                if (_annee != value)
                {
                    _annee = value;
                    OnPropertyChanged(nameof(Annee));
                }
            }
        }

        // Champ privé pour stocker le nombre de pages
        private int _nombrePages;

        // Propriété publique pour accéder et modifier le nombre de pages
        public int NombrePages
        {
            get { return _nombrePages; }
            set
            {
                if (_nombrePages != value)
                {
                    _nombrePages = value;
                    OnPropertyChanged(nameof(NombrePages));
                }
            }
        }

        // Champ privé pour stocker le genre du livre
        private GenreLivre _genre;

        // Propriété publique pour accéder et modifier le genre
        public GenreLivre Genre
        {
            get { return _genre; }
            set
            {
                if (_genre != value)
                {
                    _genre = value;
                    OnPropertyChanged(nameof(Genre));
                }
            }
        }

        // Champ privé pour stocker le résumé du livre
        private string _resume;

        // Propriété publique pour accéder et modifier le résumé
        public string Resume
        {
            get { return _resume; }
            set
            {
                if (_resume != value)
                {
                    _resume = value;
                    OnPropertyChanged(nameof(Resume));
                }
            }
        }

        // Champ privé pour stocker le chemin de l'image de couverture
        private string _couverturePath;

        // Propriété publique pour accéder et modifier le chemin de l'image
        public string CouverturePath
        {
            get { return _couverturePath; }
            set
            {
                if (_couverturePath != value)
                {
                    _couverturePath = value;
                    OnPropertyChanged(nameof(CouverturePath));
                }
            }
        }

        // Champ privé pour stocker l'auteur du livre
        private Auteur _auteur;

        // Propriété publique pour accéder et modifier l'auteur
        public Auteur Auteur
        {
            get { return _auteur; }
            set
            {
                if (_auteur != value)
                {
                    _auteur = value;
                    OnPropertyChanged(nameof(Auteur));
                }
            }
        }

        // Propriété calculée (sans champ privé) qui combine le titre et l'auteur
        public string TitreComplet
        {
            get
            {
                string nomAuteur;
                if (Auteur != null)
                {
                    nomAuteur = Auteur.NomComplet;
                }
                else
                {
                    nomAuteur = "Auteur inconnu";
                }

                return Titre + " - " + nomAuteur;
            }
        }
        #endregion



        #region Constructeurs

        // Constructeur principal qui initialise toutes les propriétés du livre
        public Livre(string isbn, string titre, int annee, int nombrePages, GenreLivre genre, Auteur auteur, string resume = "", string couverturePath = "")
        {
            ISBN = isbn;                // Initialise l'ISBN
            Titre = titre;              // Initialise le titre
            Annee = annee;              // Initialise l'année de publication
            NombrePages = nombrePages;  // Initialise le nombre de pages
            Genre = genre;              // Initialise le genre
            Auteur = auteur;            // Initialise l'auteur
            Resume = resume;            // Initialise le résumé (paramètre optionnel)
            CouverturePath = couverturePath; // Initialise le chemin de la couverture (paramètre optionnel)
        }

        // Constructeur par défaut qui appelle le constructeur principal avec des valeurs par défaut
        public Livre() : this("", "Sans titre", DateTime.Now.Year, 0, GenreLivre.Autre, null)
        {
            // Ce constructeur ne fait rien de plus que d'appeler l'autre constructeur avec des valeurs par défaut
        }
        #endregion



        #region Méthodes

        // Méthode qui retourne une représentation textuelle du livre
        public override string ToString()
        {
            return TitreComplet; // Retourne le titre complet du livre
        }


        // Méthode pour comparer si ce livre est égal à un autre livre
        public bool Equals(Livre other)
        {
            if (other == null)
                return false;

            return ISBN == other.ISBN; // Deux livres sont égaux si leur ISBN est identique
        }


        // Méthode qui surcharge la méthode Equals de la classe Object
        public override bool Equals(object obj)
        {
            return Equals(obj as Livre); // Convertit l'objet en Livre et utilise la méthode Equals définie ci-dessus
        }


        // Méthode qui génère un code de hachage unique pour ce livre
        public override int GetHashCode()
        {
            return ISBN.GetHashCode(); // Utilise le code de hachage de l'ISBN
        }


        // Méthode pour comparer ce livre à un autre pour le tri
        public int CompareTo(Livre other)
        {
            if (other == null)
                return 1; // Si l'autre est null, ce livre est considéré comme "plus grand"

            return Titre.CompareTo(other.Titre); // Compare les livres par leur titre
        }
        #endregion



        #region Implémentation INotifyPropertyChanged

        // Événement qui est déclenché lorsqu'une propriété change
        public event PropertyChangedEventHandler PropertyChanged;

        // Méthode qui déclenche l'événement PropertyChanged
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