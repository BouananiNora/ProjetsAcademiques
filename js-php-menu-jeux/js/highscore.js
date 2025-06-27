function loadWordleHighScores() {
    $.ajax({
        url: "../Controleur/wordle_highscores.php",
        type: "GET",
        dataType: "json",
        success: function(highScores) {
            console.log("Données HighScores Wordle:", highScores); 
            
            if (Array.isArray(highScores) && highScores.length > 0) {
                var table = $("#wordleTable");
                highScores.forEach(function(score) {
                    var row = $("<tr>");
                    $("<td>").text(score.user).appendTo(row);
                    $("<td>").text(score.level).appendTo(row);
                    $("<td>").text(score.score).appendTo(row);
                    row.appendTo(table);
                });
            } else {
                console.error("Les données HighScores Wordle ne sont pas au format attendu ou sont vides.");
            }
        },
        error: function(xhr, status, error) {
            console.error("Erreur lors du chargement des HighScores Wordle: " + error);
        }
    });
}


function load4imgHighScores() {
    $.ajax({
        url: "../Controleur/4img_highscores.php",
        type: "GET",
        dataType: "json",
        success: function(highScores) {
            var table = $("#4imgTable");
            highScores.forEach(function(score) {
                var row = $("<tr>");
                $("<td>").text(score.user).appendTo(row);
                $("<td>").text(score.theme).appendTo(row);
                $("<td>").text(score.score).appendTo(row);
                row.appendTo(table);
            });
        },
        error: function(xhr, status, error) {
            console.error("Erreur lors du chargement des HighScores 4 Images 1 Mot: " + error);
        }
    });
}

window.onload = function() 
{
    loadWordleHighScores();
    load4imgHighScores();                       
}
