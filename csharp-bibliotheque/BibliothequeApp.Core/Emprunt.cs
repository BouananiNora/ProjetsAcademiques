using System;
using System.ComponentModel;

namespace MODEL
{
    public class Emprunt : INotifyPropertyChanged, IEquatable<Emprunt>, IComparable<Emprunt>
    {

        #region Champs et Propriétés

        // Identifiant unique de l'emprunt
        private int _id;

        public int Id
        {
            get { return _id; } // Renvoie la valeur de l'identifiant
            set
            {
                if (_id != value) // Vérifie si la valeur a changé
                {
                    _id = value; // Stocke la nouvelle valeur
                    OnPropertyChanged(nameof(Id)); // Notifie que la propriété a changé
                }
            }
        }

        // Référence au livre emprunté
        private Livre _livre;

        public Livre Livre
        {
            get { return _livre; } // Renvoie le livre emprunté
            set
            {
                if (_livre != value) // Vérifie si la valeur a changé
                {
                    _livre = value; // Stocke la nouvelle valeur
                    OnPropertyChanged(nameof(Livre)); // Notifie que la propriété a changé
                }
            }
        }

        // Nom de la personne qui emprunte le livre
        private string _nomEmprunteur;

        public string NomEmprunteur
        {
            get { return _nomEmprunteur; } // Renvoie le nom de l'emprunteur
            set
            {
                if (_nomEmprunteur != value) // Vérifie si la valeur a changé
                {
                    _nomEmprunteur = value; // Stocke la nouvelle valeur
                    OnPropertyChanged(nameof(NomEmprunteur)); // Notifie que la propriété a changé
                }
            }
        }

        // Date à laquelle le livre a été emprunté
        private DateTime _dateEmprunt;

        public DateTime DateEmprunt
        {
            get { return _dateEmprunt; } // Renvoie la date d'emprunt
            set
            {
                if (_dateEmprunt != value) // Vérifie si la valeur a changé
                {
                    _dateEmprunt = value; // Stocke la nouvelle valeur
                    OnPropertyChanged(nameof(DateEmprunt)); // Notifie que la propriété a changé
                    OnPropertyChanged(nameof(JoursEcoulés)); // Notifie que le nombre de jours écoulés a aussi changé
                    OnPropertyChanged(nameof(EstEnRetard)); // Notifie que le statut de retard a peut-être changé
                }
            }
        }

        // Date à laquelle le livre devrait être retourné
        private DateTime _dateRetourPrevue;

        public DateTime DateRetourPrevue
        {
            get { return _dateRetourPrevue; } // Renvoie la date de retour prévue
            set
            {
                if (_dateRetourPrevue != value) // Vérifie si la valeur a changé
                {
                    _dateRetourPrevue = value; // Stocke la nouvelle valeur
                    OnPropertyChanged(nameof(DateRetourPrevue)); // Notifie que la propriété a changé
                    OnPropertyChanged(nameof(EstEnRetard)); // Notifie que le statut de retard a peut-être changé
                }
            }
        }

        // Indique si le livre a été retourné ou non
        private bool _estRetourne;

        public bool EstRetourne
        {
            get { return _estRetourne; } // Renvoie si le livre est retourné ou non
            set
            {
                if (_estRetourne != value) // Vérifie si la valeur a changé
                {
                    _estRetourne = value; // Stocke la nouvelle valeur
                    OnPropertyChanged(nameof(EstRetourne)); // Notifie que la propriété a changé
                    OnPropertyChanged(nameof(Statut)); // Notifie que le statut a changé
                }
            }
        }

        // Propriété calculée qui indique combien de jours se sont écoulés depuis l'emprunt
        public int JoursEcoulés
        {
            get
            {
                return (DateTime.Now - DateEmprunt).Days; // Calcule la différence en jours entre aujourd'hui et la date d'emprunt
            }
        }

        // Propriété calculée qui indique si l'emprunt est en retard
        public bool EstEnRetard
        {
            get
            {
                return !EstRetourne && DateTime.Now > DateRetourPrevue; // Un emprunt est en retard s'il n'est pas retourné et que la date actuelle dépasse la date de retour prévue
            }
        }

        // Propriété calculée qui retourne le statut de l'emprunt sous forme de texte
        public string Statut
        {
            get
            {
                if (EstRetourne)
                    return "Retourné";
                else if (EstEnRetard)
                    return "En retard";
                else
                    return "Emprunté";
            }
        }
        #endregion



        #region Constructeurs

        // Constructeur qui initialise toutes les propriétés de l'emprunt
        public Emprunt(int id, Livre livre, string nomEmprunteur, DateTime dateEmprunt, DateTime dateRetourPrevue, bool estRetourne = false)
        {
            Id = id; // Définit l'identifiant
            Livre = livre; // Définit le livre emprunté
            NomEmprunteur = nomEmprunteur; // Définit le nom de l'emprunteur
            DateEmprunt = dateEmprunt; // Définit la date d'emprunt
            DateRetourPrevue = dateRetourPrevue; // Définit la date de retour prévue
            EstRetourne = estRetourne; // Définit si le livre est retourné (par défaut: non)
        }

        // Constructeur sans paramètres qui crée un emprunt par défaut
        public Emprunt() : this(0, null, "", DateTime.Now, DateTime.Now.AddDays(14))
        {
            // Appelle le constructeur principal avec des valeurs par défaut
            // ID = 0, livre = null, emprunteur = chaîne vide, date d'emprunt = maintenant, retour prévu dans 14 jours
        }
        #endregion



        #region Méthodes

        // Méthode qui crée une représentation textuelle de l'emprunt
        public override string ToString()
        {
            string titreLivre;
            if (Livre != null)
            {
                titreLivre = Livre.Titre;
            }
            else
            {
                titreLivre = "Livre inconnu";
            }

            return "Emprunt #" + Id + " - " + titreLivre + " par " + NomEmprunteur + " (" + Statut + ")";
            // Exemple: "Emprunt #1 - Les Misérables par Jean Dupont (Emprunté)"
        }


        // Méthode qui vérifie si cet emprunt est égal à un autre emprunt
        public bool Equals(Emprunt other)
        {
            if (other == null)
                return false;

            return Id == other.Id; // Deux emprunts sont égaux s'ils ont le même identifiant
        }


        // Méthode qui vérifie si cet emprunt est égal à un objet quelconque
        public override bool Equals(object obj)
        {
            return Equals(obj as Emprunt); // Convertit l'objet en Emprunt et utilise la méthode précédente
        }


        // Méthode qui génère un code de hachage pour cet emprunt
        public override int GetHashCode()
        {
            return Id.GetHashCode(); // Utilise l'identifiant pour générer le code de hachage
        }


        // Méthode qui compare cet emprunt à un autre pour le tri
        public int CompareTo(Emprunt other)
        {
            if (other == null)
                return 1; // Cet emprunt est considéré comme "plus grand" qu'un emprunt null

            // Trier d'abord par statut (non retournés en premier)
            if (EstRetourne != other.EstRetourne)
                return EstRetourne ? 1 : -1;

            // Puis par date d'emprunt (plus récents en premier)
            return other.DateEmprunt.CompareTo(DateEmprunt);
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
            // Notifie les écouteurs que la propriété nommée a changé
        }
        #endregion
    }
}