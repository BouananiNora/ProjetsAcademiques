<?php
session_start();
include("../model/fonctions_BDD.php");

if (!empty($_SESSION['iduser']) && isset($_POST['theme']) && isset($_POST['totalPoints'])) 
{
    $userId = $_SESSION['iduser'];
    $theme = $_POST['theme'];
    $points = $_POST['totalPoints'];

    saveProgress4img($userId, $theme, $points);  

    echo json_encode(['code' => 200,'status' => 'success', 'message' => 'Progression enregistrée']);
} else {
    echo json_encode(['code' => 400,'status' => 'error', 'message' => 'Données manquantes ou utilisateur non connecté']);
}

?>

