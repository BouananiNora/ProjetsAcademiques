
<?php
session_start();
include_once('../model/fonctions_BDD.php');


$wordleHighScores = getWordleHighScores();


header('Content-Type: application/json');


echo json_encode($wordleHighScores);
?>
