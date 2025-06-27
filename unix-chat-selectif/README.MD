# Mini Chat Unix (Projet C sous Linux)

## Description
Application en C sous Linux permettant à plusieurs utilisateurs de discuter entre eux via un système client/serveur. Chaque utilisateur peut se connecter, voir les autres connectés, et sélectionner avec qui échanger.

## Fonctionnalités
- Authentification des utilisateurs (login/mot de passe avec hashage).
- Création de nouveaux utilisateurs.
- Communication sélective entre utilisateurs connectés.
- Affichage d’une publicité en haut de l’interface (chargée dynamiquement).
- Consultation et modification des données personnelles (GSM, email).
- Interface d’administration pour :
  - Ajouter des publicités.
  - Créer de nouveaux comptes utilisateur.

## Architecture
- Application répartie : client / serveur.
- Base de données pour la gestion des utilisateurs.
- Fichier binaire pour les publicités.
- Fichier `protocole.h` partagé entre les programmes.

## Outils et langages
- Langage C
- Développement sous Linux (bash, makefiles…)
- Programmation réseau (sockets TCP)
- Base de données (PostgreSQL ou équivalent selon environnement)
- Fichiers binaires & sérialisation

---

*Projet réalisé dans le cadre du bachelier en informatique de gestion à HEPL.*
