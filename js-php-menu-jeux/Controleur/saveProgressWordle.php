<?php
session_start();
include("../model/fonctions_BDD.php");

    if (!empty($_SESSION['iduser']) &&  isset($_POST['scoreActuel']) && isset($_POST['niveauActuel']) ) 
    {
        $userId = $_SESSION['iduser'];
        $level = $_POST['niveauActuel'];
        $points = $_POST['scoreActuel'];

        save_wordle_progress($userId, $points, $level);

        echo json_encode(['code' => 200,'status' => 'success', 'message' => 'Progression enregistrée']);
    } else {
        echo json_encode(['code' => 400,'status' => 'error', 'message' => 'Données manquantes ou utilisateur non connecté']);
    }

?>
