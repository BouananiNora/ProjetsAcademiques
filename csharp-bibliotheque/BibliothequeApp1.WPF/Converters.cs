using MODEL;
using System;
using System.Globalization;
using System.IO;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace VIEW
{
    // Convertisseur pour afficher l'image à partir d'un chemin
    public class ImagePathConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // Convertir la valeur en chaîne et vérifier si elle est valide
            string path = value as string;
            if (path == null || path == "" || !File.Exists(path))
                return null;

            // Essayer de créer une image à partir du chemin
            try
            {
                // Version simplifiée en un seul appel
                return new BitmapImage(new Uri(path));
            }
            catch
            {
                // En cas d'erreur, ne pas afficher d'image
                return null;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    // Convertisseur pour afficher le statut d'un emprunt
    public class StatutEmpruntColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // Traitement uniquement pour les objets Emprunt
            if (value is Emprunt emprunt)
            {
                if (emprunt.EstRetourne)
                    return new SolidColorBrush(Colors.Green); // Vert pour retourné
                else if (emprunt.EstEnRetard)
                    return new SolidColorBrush(Colors.Red);   // Rouge pour en retard
                else
                    return new SolidColorBrush(Colors.Blue);  // Bleu pour emprunté
            }

            // Valeur par défaut si ce n'est pas un Emprunt
            return new SolidColorBrush(Colors.Black);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
    
    // Convertisseur pour formater les dates
    public class DateConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is DateTime date)
            {
                string format = parameter as string;
                if (format == null)
                {
                    format = "dd/MM/yyyy";
                }
                return date.ToString(format);
            }
            return string.Empty;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string strValue = value as string;
            if (DateTime.TryParse(strValue, out DateTime result))
                return result;

            return DateTime.Today;
        }
    }


    // Convertisseur pour la visibilité basée sur une condition booléenne
    public class BoolToVisibilityConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            bool bValue = false;
            if (value is bool)
                bValue = (bool)value;

            // Si parameter est "inverse", on inverse la logique
            bool inverse = parameter != null && parameter.ToString().ToLower() == "inverse";
            bValue = inverse ? !bValue : bValue;

            return bValue ? Visibility.Visible : Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is Visibility visibility)
            {
                bool inverse = parameter != null && parameter.ToString().ToLower() == "inverse";
                bool result = visibility == Visibility.Visible;
                return inverse ? !result : result;
            }
            return false;
        }
    }
}