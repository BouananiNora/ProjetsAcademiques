<?php
session_start();
include_once('../model/fonctions_BDD.php');

if (isset($_POST['login']) && isset($_POST['password'])) 
{
    $login = $_POST['login'];
    $password = $_POST['password'];

    if (!empty($login) && !empty($password)) 
    {
        // verif si login existe
        $userExists = checklogin($login);
        if ($userExists) 
        {
            //verifie si login et mdp sont correct
            if (verifConnexion($login, $password)) 
            {
                $data = get_data($login); //retourne les donnees 
                $_SESSION['iduser'] = $data['iduser'];
                echo json_encode(['code' => 200, 'login' => $data['login'], 'iduser' => $data['iduser']]);
            } 
            else 
            {
                http_response_code(401); // Unauthorized
                echo json_encode(['code' => 401, 'ERREUR' => 'Mot de passe incorrect']);
            }
        } 
        else 
        {
            http_response_code(404); // Not Found
            echo json_encode(['code' => 404, 'ERREUR' => 'Login inexistant']);
        }
    } 
    else 
    {
        http_response_code(400); // Bad Request
        echo json_encode(['code' => 400, 'ERREUR' => 'Veuillez saisir le login et le mot de passe']);
    }
    exit;
}