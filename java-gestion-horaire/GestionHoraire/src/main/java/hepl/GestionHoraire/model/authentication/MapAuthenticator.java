package hepl.GestionHoraire.model.authentication;

import java.util.HashMap;
import java.util.Map;


/**
 * Implémentation de l'Authenticator qui utilise une Map pour stocker les utilisateurs et mots de passe
 * Cette classe permet de gérer l'authentification des utilisateurs dans l'application
 */
public class MapAuthenticator extends Authenticator
{
    //----------------------- ATTRIBUTS -----------------------//

    // Utilisation d'une HashMap pour stocker les paires username/password
    // private final -> une fois initialisée, cette référence ne changera pas
    // HashMap -> implémentation de Map avec accès rapide en O(1)
    final private Map<String, String> mapData = new HashMap<>();

    //----------------------- CONSTRUCTEUR -----------------------//

    /**
     * Constructeur par défaut qui initialise les utilisateurs du système
     * Crée 3 comptes utilisateurs prédéfinis pour les tests
     */
    public MapAuthenticator() {
        mapData.put("utilisateur1", "motdepasse1");
        mapData.put("admin", "admin123");
        mapData.put("Dupont", "passDupont");
    }

    //----------------------- GESTION DES UTILISATEURS -----------------------//

    /**
     * Vérifie si un nom d'utilisateur existe déjà
     */
    @Override
    protected boolean isLoginExists(String username) {
        return mapData.containsKey(username);
    }

    /**
     * Ajoute un nouvel utilisateur au système
     */
    public boolean addUser(String username, String password) {
        if (isLoginExists(username)) {
            return false;
        }
        mapData.put(username, password);
        return true; // L'ajout a réussi
    }

    //----------------------- GESTION DES MOTS DE PASSE -----------------------//

    /**
     * Récupère le mot de passe d'un utilisateur
     */
    @Override
    protected String getPassword(String username) {
        return mapData.get(username);
    }

    /**
     * Vérifie si un mot de passe est correct pour un utilisateur donné
     * Cette méthode est utilisée lors de l'authentification
     */
    public boolean checkPassword(String username, String passwordToCheck) {
        String stored = getPassword(username);
        return stored != null && stored.equals(passwordToCheck);
    }


}
