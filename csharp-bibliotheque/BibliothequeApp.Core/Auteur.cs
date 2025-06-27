using System;
using System.ComponentModel;

namespace MODEL
{
    // Cette classe représente un auteur de livre avec ses informations personnelles
    // Elle implémente des interfaces pour la notification, la comparaison et l'égalité
    public class Auteur : INotifyPropertyChanged, IEquatable<Auteur>, IComparable<Auteur>
    {
        #region Champs et Propriétés

        // Champ privé pour l'ID de l'auteur
        private int _id;

        // Propriété publique avec notification de changement
        public int Id
        {
            get { return _id; }
            set
            {
                if (_id != value)
                {
                    _id = value;
                    OnPropertyChanged(nameof(Id));
                }
            }
        }

        // Champ privé pour le nom de l'auteur
        private string _nom;

        // Propriété publique qui notifie aussi NomComplet quand le nom change
        public string Nom
        {
            get { return _nom; }
            set
            {
                if (_nom != value)
                {
                    _nom = value;
                    OnPropertyChanged(nameof(Nom));
                    OnPropertyChanged(nameof(NomComplet));
                }
            }
        }

        // Champ privé pour le prénom de l'auteur
        private string _prenom;

        // Propriété publique qui notifie aussi NomComplet quand le prénom change
        public string Prenom
        {
            get { return _prenom; }
            set
            {
                if (_prenom != value)
                {
                    _prenom = value;
                    OnPropertyChanged(nameof(Prenom));
                    OnPropertyChanged(nameof(NomComplet));
                }
            }
        }

        // Champ privé pour la date de naissance
        private DateTime _dateNaissance;

        // Propriété publique qui notifie aussi l'âge quand la date change
        public DateTime DateNaissance
        {
            get { return _dateNaissance; }
            set
            {
                if (_dateNaissance != value)
                {
                    _dateNaissance = value;
                    OnPropertyChanged(nameof(DateNaissance));
                    //OnPropertyChanged(nameof(Age));
                }
            }
        }

        // Champ privé pour la biographie
        private string _biographie;

        // Propriété publique pour la biographie
        public string Biographie
        {
            get { return _biographie; }
            set
            {
                if (_biographie != value)
                {
                    _biographie = value;
                    OnPropertyChanged(nameof(Biographie));
                }
            }
        }

        // Champ privé pour le chemin de la photo
        private string _photoPath;

        // Propriété publique pour le chemin de la photo
        public string PhotoPath
        {
            get { return _photoPath; }
            set
            {
                if (_photoPath != value)
                {
                    _photoPath = value;
                    OnPropertyChanged(nameof(PhotoPath));
                }
            }
        }

        // Propriété calculée qui renvoie l'âge actuel basé sur la date de naissance
        //public int Age
        //{
        //    get { return CalculateAge(DateNaissance); }
        //}

        // Propriété calculée qui combine prénom et nom
        public string NomComplet
        {
            get { return $"{Prenom} {Nom}"; }
        }
        #endregion



        #region Constructeurs

        // Constructeur principal qui initialise toutes les propriétés
        public Auteur(int id, string nom, string prenom, DateTime dateNaissance, string biographie = "", string photoPath = "")
        {
            Id = id;
            Nom = nom;
            Prenom = prenom;
            DateNaissance = dateNaissance;
            Biographie = biographie;
            PhotoPath = photoPath;
        }

        // Constructeur par défaut qui appelle le constructeur principal avec des valeurs par défaut
        public Auteur() : this(0, "Inconnu", "Inconnu", new DateTime(1900, 1, 1))
        {
        }
        #endregion



        #region Méthodes

        // Méthode qui calcule l'âge exact en tenant compte des mois et jours
        //private int CalculateAge(DateTime birthDate)
        //{
        //    var today = DateTime.Today;
        //    var age = today.Year - birthDate.Year;

        //    // Si l'anniversaire n'est pas encore passé cette année, on réduit l'âge de 1
        //    if (today.Month < birthDate.Month || (today.Month == birthDate.Month && today.Day < birthDate.Day))
        //        age--;

        //    return age;
        //}


        // Surcharge de ToString pour afficher le nom complet
        public override string ToString()
        {
            return NomComplet;
        }


        // Implémentation de IEquatable - deux auteurs sont égaux s'ils ont le même ID
        public bool Equals(Auteur other)
        {
            if (other == null)
                return false;

            return Id == other.Id;
        }


        // Surcharge de Equals pour tous types d'objets
        public override bool Equals(object obj)
        {
            return Equals(obj as Auteur);
        }


        // GetHashCode doit être cohérent avec Equals (basé sur même propriété)
        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }


        // Implémentation de IComparable - tri par nom puis prénom
        public int CompareTo(Auteur other)
        {
            if (other == null)
                return 1;

            int result = Nom.CompareTo(other.Nom);
            if (result == 0)
                result = Prenom.CompareTo(other.Prenom);

            return result;
        }
        #endregion



        #region Implémentation INotifyPropertyChanged

        // Événement qui sera déclenché quand une propriété change
        public event PropertyChangedEventHandler PropertyChanged;

        // Méthode pour notifier que la valeur d'une propriété a changé
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