package hepl.GestionHoraire.model.authentication;

/**
 * Classe abstraite qui gère l'authentification des utilisateurs
 */
public abstract class Authenticator {

    //-------------- MÉTHODES --------------//

    /**
     * Vérifie si l'utilisateur peut se connecter avec ces identifiants
     */
    public boolean authenticate(String username, String password)
    {
        // Cette condition vérifie d'abord si l'utilisateur existe
        if (isLoginExists(username)) {
            String storedPassword = getPassword(username);

            //verifie que le mot de passe n'est pas null et qu'il correspond exactement à celui fourni
            return storedPassword != null && storedPassword.equals(password);
        }

        // Si l'utilisateur n'existe pas, on retourne false directement
        return false;
    }

    /**
     * Vérifie si un login existe dans le système
     */
    protected abstract boolean isLoginExists(String username);

    /**
     * Récupère le mot de passe d'un utilisateur
     */
    protected abstract String getPassword(String username);

    /**
     * Ajoute un nouvel utilisateur
     * Ajouté pour permettre l'inscription de nouveaux utilisateurs
     */
    public abstract boolean addUser(String username, String password);
}