<?php
session_start();

include("../model/fonctions_BDD.php");

if (!empty($_SESSION['iduser'])) 
{
    $userId = $_SESSION['iduser'];
    $data = recupererProgress4img($userId);

    if ($data !== null) 
    {
        echo json_encode(['status' => 'success', 'data' => $data]);
    } 
    else 
    {
        echo json_encode(['status' => 'error', 'message' => 'Aucune donnée disponible']);
    }
} 
else 
{
    echo json_encode(['status' => 'error', 'message' => 'Utilisateur non connecté']);
}
?>
