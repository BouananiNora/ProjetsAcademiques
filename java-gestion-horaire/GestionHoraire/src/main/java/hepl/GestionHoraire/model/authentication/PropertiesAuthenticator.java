package hepl.GestionHoraire.model.authentication;

import java.io.*;
import java.util.Properties;
import java.util.Enumeration;


// Cette classe gère les utilisateurs et mots de passe à partir d'un fichier properties
// Elle étend la classe Authenticator abstraite et implémente ses méthodes
public class PropertiesAuthenticator extends Authenticator
{

    //-------------------VARIABLES-------------------
    private Properties properties;
    private final String propertiesFile;

    //-------------------CONSTRUCTEUR-------------------
    // Initialise l'authenticator avec un fichier de propriétés
    public PropertiesAuthenticator(String filename) {
        this.propertiesFile = filename;
        this.properties = new Properties();
        loadProperties();
    }

    //-------------------CHARGEMENT FICHIER-------------------
    // Charge les utilisateurs depuis le fichier properties
    // Crée des utilisateurs par défaut si le fichier n'existe pas
    private void loadProperties() {
        try {
            File file = new File(propertiesFile);
            if (file.exists()) {
                // Le fichier existe, on charge les données
                FileInputStream fis = new FileInputStream(file);
                properties.load(fis);
                fis.close();
            } else {
                // Le fichier n'existe pas, on crée des utilisateurs par défaut
                addUser("admin", "admin123");
                addUser("utilisateur1", "motdepasse1");
                addUser("Dupont", "passDupont");
                saveProperties();
            }
        } catch (IOException e) {
            System.out.println("Erreur lors du chargement du fichier properties : " + e.getMessage());
            e.printStackTrace();
        }
    }

    //-------------------SAUVEGARDE FICHIER-------------------
    // Sauvegarde les utilisateurs dans le fichier properties
    // Vérifie que le dossier existe, sinon le crée
    private void saveProperties() {
        try {
            // Vérifier si le répertoire data existe
            File dataDir = new File("data");
            if (!dataDir.exists()) {
                dataDir.mkdir();
            }

            // Créer le fichier properties
            File file = new File(propertiesFile);
            FileOutputStream fos = new FileOutputStream(file);

            // Parcourir et écrire les propriétés
            for (Enumeration e = properties.keys(); e.hasMoreElements();) {
                String username = (String) e.nextElement();
                String password = properties.getProperty(username);
                String line = username + "=" + password + "\n";
                fos.write(line.getBytes());
            }

            fos.close();
        } catch (IOException e) {
            System.out.println("Erreur lors de la sauvegarde du fichier properties : " + e.getMessage());
        }
    }

    //-------------------MÉTHODES AUTHENTIFICATION-------------------
    // Vérifie si un login existe déjà
    @Override
    protected boolean isLoginExists(String username) {
        return properties.containsKey(username);
    }

    // Récupère le mot de passe associé à un login
    @Override
    protected String getPassword(String username) {
        return properties.getProperty(username);
    }

    // Ajoute un nouvel utilisateur
    @Override
    public boolean addUser(String username, String password) {
        if (isLoginExists(username)) {
            return false;
        }
        properties.put(username, password);

        saveProperties();
        return true;
    }

}