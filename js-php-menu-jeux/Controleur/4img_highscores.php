<?php
session_start();
include_once('../model/fonctions_BDD.php');

$QuatreimgHighScores = get4imgHighScores();

header('Content-Type: application/json');

echo json_encode($QuatreimgHighScores);
?>
