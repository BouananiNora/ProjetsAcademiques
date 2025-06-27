using Microsoft.Win32;
using System;

namespace VIEWMODEL
{
    // Cette classe gère les paramètres de configuration de l'application de bibliothèque
    // Elle utilise le registre Windows pour stocker et récupérer les paramètres de manière persistante
    public class BibliothequeParamManager
    {
        // Chemin dans le registre où stocker les paramètres
        private const string REG_PATH = @"SOFTWARE\BibliothequeApp";

        // Propriété pour le chemin du dossier
        private string _cheminDossierDonnees;
        public string CheminDossierDonnees
        {
            get
            {
                if (_cheminDossierDonnees == null || _cheminDossierDonnees == "")
                {
                    // Lire depuis le registre
                    RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(REG_PATH);
                    if (registryKey != null)
                    {
                        object valeur = registryKey.GetValue("CheminDossierDonnees");
                        if (valeur != null)
                        {
                            _cheminDossierDonnees = valeur.ToString();
                        }
                        else
                        {
                            _cheminDossierDonnees = @"C:\BibliothequeApp";
                        }
                        registryKey.Close();
                    }
                    else
                    {
                        _cheminDossierDonnees = @"C:\BibliothequeApp";
                    }
                }
                return _cheminDossierDonnees;
            }
            set
            {
                _cheminDossierDonnees = value;

                // Sauvegarder dans le registre
                RegistryKey registryKey = Registry.CurrentUser.CreateSubKey(REG_PATH);
                if (registryKey != null)
                {
                    registryKey.SetValue("CheminDossierDonnees", value);
                    registryKey.Close();
                }
            }
        }

        // Propriété pour le nombre de jours d'emprunt
        private int _nombreJoursEmprunt;
        public int NombreJoursEmprunt
        {
            get
            {
                if (_nombreJoursEmprunt == 0)
                {
                    // Lire depuis le registre
                    RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(REG_PATH);
                    if (registryKey != null)
                    {
                        object valeur = registryKey.GetValue("NombreJoursEmprunt");
                        if (valeur != null)
                        {
                            // Convertir la valeur en int en utilisant Int32.Parse
                            try
                            {
                                _nombreJoursEmprunt = Int32.Parse(valeur.ToString());
                            }
                            catch
                            {
                                _nombreJoursEmprunt = 14; // Valeur par défaut en cas d'erreur
                            }
                        }
                        else
                        {
                            _nombreJoursEmprunt = 14;
                        }
                        registryKey.Close();
                    }
                    else
                    {
                        _nombreJoursEmprunt = 14;
                    }
                }
                return _nombreJoursEmprunt;
            }
            set
            {
                _nombreJoursEmprunt = value;

                // Sauvegarder dans le registre
                RegistryKey registryKey = Registry.CurrentUser.CreateSubKey(REG_PATH);
                if (registryKey != null)
                {
                    registryKey.SetValue("NombreJoursEmprunt", value.ToString());
                    registryKey.Close();
                }
            }
        }

        // Méthode pour initialiser les paramètres
        public void ChargerParametres()
        {
            // Forcer la lecture des propriétés
            var temp1 = CheminDossierDonnees;
            var temp2 = NombreJoursEmprunt;
        }
    }
}