<?php
session_start();

include_once('../model/fonctions_BDD.php');

if (isset($_POST['login']) && isset($_POST['password'])) 
{
    $login = $_POST['login'];
    $password = $_POST['password'];

    if (verifConnexion($login, $password)) 
    {
        echo json_encode(array('code' => 200, 'message' => 'Inscription réussie !'));
    } 
    else 
    {
        inscriptionBDD($login, $password);
        echo json_encode(array('code' => 200, 'message' => 'Inscription réussie !'));
    }
} 
else
{
    http_response_code(400); 
    echo json_encode(array('ERREUR' => 'Données de connexion manquantes', 'code' => 400));
}

exit;
?>
