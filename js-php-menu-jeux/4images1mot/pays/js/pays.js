//Objet contenant les mots mystères pour chaque niveau du jeu.
var motParNiveau = {
    1: "MAROC",
    2: "AUTRICHE",
    3: "CANADA",
    4: "EGYPTE",
    5: "MADAGASCAR",
    6: "NORVEGE"
};

var totalNiveau = 6;
var niveauActuel = 1; 
var reponseTemporaire = motParNiveau[niveauActuel];  //variable stockant le mot mystère pour le niveau actuel

var nbIndices = 2;

/**
 * la variable options est un objet pour stocker les options (lettres) sélectionnées par le joueur
 * La boucle est utilisée pour initialiser les 18 premieres lettres de l'objet options à true
 */
var options = {}; //initialisé comme un objet vide
for (var i = 0; i < 18; i++) { 
    options[i] = true;  //cette initialisation à true signifie que les lettres (options) sont dispo au début du jeu
}

var espaces = {};  
var lettres = {};  
var freq = {};
var tempfreq = {};



/**
 * @function main
 * @description Initialise le jeu pour le niveau actuel,
 * Configure les options de lettres, les espaces pour le mot à deviner, et les images d'indices.
 */
function main() {
    
    startTimer();
    var alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    var reponse = motParNiveau[niveauActuel];  //il récupere le mot à partir de l'objet motParNiveau
    for (var i = 0; i < 26; ++i) {
        freq[alphabets[i]] = 0;  //freq est utilisé pr savoir cmb de fois chaque lettre doit apparaitre ds le mot mystere
        tempfreq[alphabets[i]] = 0; //tempfreq est utilisé pr suivre cmb de fois chaque lettre a été ajt par le joueur
    }
    //la boucle parcourt chaque lettre du mot a deviner et incremente la valeur correspondante dans freq
    for (var i = 0; i < reponse.length; ++i) {  
        freq[reponse[i]] += 1;
    }
    ajouterImages(niveauActuel);
    ajouterEspaces(niveauActuel);
    ajouterOptions(niveauActuel);
    // Appliquer la couleur transparente aux "_" au début du jeu
    var espaceElement = document.getElementsByClassName("espace");
    for (var i = 0; i < espaceElement.length; i++) {
        if (espaceElement[i].innerHTML === "_") {
            espaceElement[i].style.color = "transparent";
        }
    }
    
}

/* POUR LES POINTS */

var debutTemps;

/**
 * @function startTimer
 * @description Démarre le chronomètre en enregistrant l'heure actuelle dans la variable `debutTemps`.
*/
function startTimer() {
    debutTemps = new Date();
}

var points = 0; // Variable pour stocker les points gagnés
sessionStorage.setItem("points", points);  //enregistre les points initial (0) dans sessionStorage

/**
 * @function addPoints
 * @description Ajoute des points au total, met à jour le sessionStorage et met à jour l'affichage des points.
 * @param {number} amount - Le nombre de points à ajouter.
 */
function addPoints(amount) {
    points += amount;
    sessionStorage.setItem("pointssss", points);
    document.getElementById("points").innerText = "Points: " + points;
}

/**
 * @function calculatePoints
 * @description Calcule les points en fonction du temps écoulé.
 * @param {number} differenceTemps - Le temps écoulé en secondes.
 * @returns {number} - Le nombre de points attribués.
*/
function calculatePoints(differenceTemps) {
    if (differenceTemps >= 1 && differenceTemps <= 5) {
        return 200;
    } else if (differenceTemps <= 10) {
        return 150;
    } else if (differenceTemps <= 20) {
        return 100;
    } else {
        return 20;
    }
}

/**
 * @function stopTimer
 * @description Arrête le chronomètre, vérifie si le mot saisi est correct, et attribue des points en fonction du temps écoulé.
 */
function stopTimer() {
    var finTemps = new Date();
    var differenceTemps = (finTemps - debutTemps) / 1000; // Calcul le tps écoulé en secondes

    // Vérifier si le mot saisi est correct
    var estCorrect = checkifcorrect(niveauActuel);

    // Si le mot est correct, calculer les points en fonction du temps écoulé
    if (estCorrect) {
        var pointsGagnes = calculatePoints(differenceTemps);

        //alert("Vous avez gagné " + pointsGagnes + " points !");  
        
        addPoints(pointsGagnes);  //ajout des pts gagnés au total des pts du jeu
    } 
    document.getElementById("points").innerText = "Points: " + points; //maj l'affichage des points dans l'interface utilisateur
}


/*COMPTER LES NIVEAUX */

/**
 * @function afficherMotComplet
 * @description Affiche le mot complet en remplaçant les espaces par les lettres correctes et ajoute un effet d'illumination.
 */
function afficherMotComplet() {
    var espaces = document.getElementsByClassName("espace"); //recupere tous les elements avc la classe espace 
    var reponse = motParNiveau[niveauActuel];
    for (var i = 0; i < reponse.length; i++) {
        espaces[i].innerHTML = reponse[i];  //pour chaque espace on remplace la lettre correcte
        espaces[i].classList.add("found"); //ajout d'une class css found pour l'effet d'illumination
    }
}

// Tableau pour stocker le nombre de points gagnés à chaque niveau
var pointsParNiveau = [];

/**
 * @function passerNiveauSuivant
 * @description Arrête le chronomètre, vérifie si le mot saisi est correct, calcule et attribue les points, affiche le mot complet, puis passe au niveau suivant.
 */
function passerNiveauSuivant() {
    // Arrêter le chronomètre lorsque le joueur termine le niveau
    stopTimer();
    if (checkifcorrect(niveauActuel)) { //si le mot saisi est correct
        var finTemps = new Date();
        var differenceTemps = (finTemps - debutTemps) / 1000; // Calculer le temps écoulé en secondes

        // Calculer les points en fonction du temps écoulé
        var points = calculatePoints(differenceTemps);

        // Ajouter les points gagnés au tableau des points par niveau
        pointsParNiveau[niveauActuel] = points;
        console.log("vérif points du niveau actuel: " + points);

        // Calculer le total des points jusqu'au niveau actuel
        var totalPoints = 0;
        for (var i = 1; i <= niveauActuel; i++) {

            console.log("points du niveau actuel: " + pointsParNiveau[niveauActuel]);
            if (pointsParNiveau[i] !== undefined) { //verifie si des points ont été enregistrés pour le niveau "i"
                totalPoints += pointsParNiveau[i];
            }
        }

        // Afficher les points dans votre interface utilisateur
        document.getElementById("points").innerText = "Points: " + totalPoints;


        // Ajout d'une pause de 2 secondes pour afficher le mot complet avant de passer au niveau suivant
        setTimeout(function() { //pause
            afficherMotComplet(); //le mot est complet
            setTimeout(function() {  //encore petite pause
                if (niveauActuel < totalNiveau) {
                    niveauActuel++;
                    reponseTemporaire = motParNiveau[niveauActuel];

                    options = {};
                    for (var i = 0; i < 18; i++) {
                        options[i] = true;
                    }

                    espaces = {};
                    lettres = {};

                    nbIndices = 2;
                    main();
                    console.log("reponseTemporaire : " + reponseTemporaire);
                } else {
                    // Tous les niveaux ont été terminés
                    console.log("total des points: " + totalPoints);
                    // Sauvegarder la progression après avoir terminé tous les niveaux
                    saveProgress4img("pays", totalPoints);
                    window.location.href = "../final/congrats.html?points=" + totalPoints;
                    
                }
            }, 2000); // Temps de pause de 2 secondes avant de passer au niveau suivant 2000 milisecondes = 2sec
        }, 200); // Petit délai avant d'afficher le mot complet


    } else {
        marquerIncorrect();
    }

    
}

/**
 * @function getsubmission
 * @description Obtient la soumission du joueur en concaténant le contenu de tous les espaces dans le jeu.
 * @returns {string} La soumission du joueur sous forme de chaîne de caractères.
 */
function getsubmission() {
    var x = "";
    var espaces = document.getElementsByClassName("espace");
    for (var i = 0; i < espaces.length; i++) {
        x += espaces[i].innerHTML;
    }
    return x;
}


/**
 * @function checkifcorrect
 * @description Vérifie si la soumission du joueur correspond au mot mystère pour un niveau donné.
 * @param {number} level - Le niveau pour lequel vérifier la soumission.
 * @returns {boolean} True si la soumission est correcte, sinon False.
 */
function checkifcorrect(level) {
    var submission = getsubmission();
    return submission === motParNiveau[level];
}


/**
 * @function ajouterImages
 * @description Ajoute les images pour un niveau
 * @param {number} level - Le niveau pour lequel ajouter les images 
 */
function ajouterImages(level) {
    var divPetitesImages = document.getElementById("smallimages");
    divPetitesImages.innerHTML = "";
    
    var cheminDossImage = "./img/level" + level + "/";
    for (var i = 1; i <= 4; ++i) {
        var cheminAccesImage = cheminDossImage + i + ".jpg";
        var img = document.createElement("img");
        img.src = cheminAccesImage;  //definit la source de l'image
        img.className = "hintimage";  //ajoute la classe hintimage pour le css 
        //img.setAttribute("onclick", "viewfullimage(this)");
        divPetitesImages.appendChild(img);
        if (i === 2) { //si la 2eme image est ajoutee, on met balse <br> pour mettre a la ligne
            divPetitesImages.appendChild(document.createElement("br"));
        }
    }
}


/**
 * @function ajouterEspaces
 * @description Ajoute les espaces pour les lettres à deviner pour un niveau donné à la section des espaces.
 * @param {number} level - Le niveau pour lequel ajouter les espaces pour les lettres.
 * exemple : pour le mot canada y aura 6 espaces 
 */
function ajouterEspaces(level) {
    var divEspaces = document.getElementById("blanks");  //recupere l'element html blanks
    divEspaces.innerHTML = "";  //on vide le contenu de cette div pour eviter des doublons
    var reponse = motParNiveau[level];
    for (var i = 0; i < reponse.length; ++i) {  //pr chaque lettre, creation d'un element span pour representer l'espace
        var span = document.createElement("span"); // cree un élément span pour chaque espace
        span.className = "espace"; // ajout de la classe "espace" pour le style css
        span.innerHTML = "_";  //initialisation du contenu de l'espace avec le caractere '_'
        span.setAttribute("onclick", "deselect(" + i + ")"); // si on clique sur l'espace c'est pour deselctionner la lettre
        divEspaces.appendChild(span);
        espaces[i] = null;
    }
    
	// Vérifie si une image d'indice existe déjà dans le HTML avant d'en créer une nouvelle
    //var existingHintImage = document.getElementById("hintImage");
    //if (!existingHintImage) {
        var hintImage = document.createElement("img");
        hintImage.id = "hintImage"; // Ajoutez un ID à l'image pour pouvoir la référencer plus tard
        hintImage.src = "./img/indice.png";
        hintImage.setAttribute("onclick", "hint(" + level + ")");
        hintImage.style.cursor = "pointer";
        divEspaces.appendChild(hintImage);
    //}
}

/**
 * @function ajouterOptions
 * @description Ajoute les options de lettres pour un niveau donné à la section des lettres.
 * @param {number} level - Le niveau pour lequel ajouter les options de lettres.
 */
function ajouterOptions(level) {
    var s = creationMotNivMelange(level);
    for (var i = 0; i < 18; ++i) {
        lettres[i] = s[i];
    }
    var lettersDiv = document.getElementById("letters");
    lettersDiv.innerHTML = "";  //on vide cet element
    for (var i = 0; i < 9; ++i) {
        var span = document.createElement("span");
        span.className = "letter";
        span.innerHTML = s[i];
        span.setAttribute("onclick", "addletter('" + s[i] + "', " + i + ")");
        lettersDiv.appendChild(span);
    }
    lettersDiv.appendChild(document.createElement("br"));
    for (var i = 9; i < 18; ++i) {
        var span = document.createElement("span");
        span.className = "letter";
        span.innerHTML = s[i];
        span.setAttribute("onclick", "addletter('" + s[i] + "', " + i + ")");
        lettersDiv.appendChild(span);
    }
}

/**
 * @method shuffle
 * @memberof String
 * @description Méthode pour mélanger les caractères d'une chaîne de caractères pour les options de lettres.on va utiliser ca dans creationMotNivMelange
 * @returns {string} La chaîne de caractères mélangée.
 * this = la chaine de caractere sur laquelle on va appeler shuffle 
 * split = casse la chaine en un tableau de lettre ex : 'canada devient ["c","a","n","d","a"]
 */
String.prototype.shuffle = function() {
    var tab = this.split(""); 
    var longueurTab = tab.length, t, i;
    while (longueurTab) { //tt que la long du tab n'est pas = a 0
        i = Math.random() * longueurTab-- | 0;
        //echange de la lettre choisie au hasard avec la lettre a la pos actl ds le tableau:
        t = tab[longueurTab], tab[longueurTab] = tab[i], tab[i] = t; 
    }
    return tab.join(""); //on renvoie la nouvelle chaine melangéé
}


/**
 * @function creationMotNivMelange
 * @description Crée une chaîne de caractères contenant le mot-solution mélangé avec d'autres lettres 
 * aléatoires pour remplir les 18 cases disponibles.
 * @param {number} level - Le niveau pour lequel créer la chaîne de caractères mélangée.
 * @returns {string} La chaîne de caractères mélangée.
 */
function creationMotNivMelange(level) {
    var reponse = motParNiveau[level];
    var nbLettresA_Ajt = 18 - reponse.length;
    var s = reponse;
    var alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    var lettresNonPresentesDansMot = "";
    for (var i = 0; i < alphabets.length; ++i) {
        if (reponse.indexOf(alphabets[i]) == -1)
            lettresNonPresentesDansMot += alphabets[i];
    }
    lettresNonPresentesDansMot = lettresNonPresentesDansMot.shuffle();
    for (var i = 0; i < nbLettresA_Ajt; ++i)
        s += lettresNonPresentesDansMot[i];
    s = s.shuffle();
    return s;
}


/**
 * @function updateRepTemporaire
 * @description Met à jour la réponse temporaire "reponseTemporaire" en fct des lettres saisies par le joueur.
 * cette fonction sert a savoir quelles lettre doivent encore etre devinees pour pouvoir gerer les indices
 * s = chaine pour stocker les lettres incorrectes
 */
function updateRepTemporaire() {
    var reponse = motParNiveau[niveauActuel];
    var s = "";
    var espaces = document.getElementsByClassName("espace");
    for (var i = 0; i < espaces.length; i++) {
        var esp = espaces[i].innerHTML;
        if (esp === "_" || esp != reponse[i]) { //si y a pas de lettre donc "_" ou la lettre ne corresp pas a la lettre correcte du mot
            s += reponse[i];
        }
    }
    reponseTemporaire = s;
}

/*La fonction toutRempli vérifie si tous les espaces de lettres sont remplis dans le jeu*/
/**
 * @function toutRempli
 * @description Vérifie si tous les espaces sont remplis.
 * @returns {boolean} true si tous les espaces sont remplis, sinon false.
 */
function toutRempli() {
    var estVide = false;
    var espaces = document.getElementsByClassName("espace");
    for (var i = 0; i < espaces.length; i++) {
        if (espaces[i].innerHTML == "_")
            estVide = true;
    }
    return !estVide;
}

/**
 * @function trouverPremierEspaceVide
 * @description Trouve le premier espace vide et renvoie son élément ainsi que son index.
 * @returns {Array} Un tableau contenant l'élément de l'espace vide et son index(position).
 */
function trouverPremierEspaceVide() {
    var elementARetourner;
    var index;
    var espaces = document.getElementsByClassName("espace");
    for (var i = 0; i < espaces.length; i++) {
        if (espaces[i].innerHTML == "_") {
            index = i;
            elementARetourner = espaces[i];
            break;
        }
    }
    return [elementARetourner, index];
}

/**
 * @function addletter
 * @description Ajoute une lettre à un espace vide
 * @param {string} lettreA_Ajt - La lettre à ajouter
 * @param {number} index - La position de la lettre parmi les options disponibles
 */
function addletter(lettreA_Ajt, index) {
    if (options[index] == false) {  //si les options de lettres sont false ca veut dire quelles sont pas dispo
        return;
    } else {  //si dispo
        var ffv = trouverPremierEspaceVide();  
        var element = ffv[0];
        var elindex = ffv[1];

        // Réinitialiser la couleur du texte de la lettre à blanc
        element.style.color = "white";
        element.innerHTML = lettreA_Ajt;
        options[index] = false; // marque la lettre a false = plus dispo

        var lettreElements = document.getElementsByClassName("letter");
        lettreElements[index].removeAttribute("onclick"); //empeche un clic sur la lettre
        lettreElements[index].style.cursor = "not-allowed"; //pareil
        lettreElements[index].style.background = "#706f6f";//couleur grise pour dire quelle a ete utilisee

        espaces[elindex] = index;  //garde une trace de la position (index) de la lettre utilisee pour l'espace specifiq
        updateRepTemporaire();  //maj de la rep temp
        tempfreq[lettreA_Ajt] += 1;  //incremente le cmpt de cette lettre pr suivre cmb de fois elle a ete ajt

        if (toutRempli())
            passerNiveauSuivant();
    }
}

/**
 * @function deselect
 * @description Désélectionne une lettre dans un espace.
 * @param {number} elindex - L'index de l'espace à désélectionner.
 */
function deselect(elindex) {
    if (document.getElementsByClassName("espace")[elindex].innerHTML == "_") {
        return; //si l'espace qu'on "appuie" est deja vide, on sort de la fct pcq y a rien a deselect
    }

    var lettreASupp = document.getElementsByClassName("espace")[elindex].innerHTML;
    tempfreq[lettreASupp] -= 1;
    document.getElementsByClassName("espace")[elindex].innerHTML = "_"; //on remplace le contenu de l'espace par "_"
    var index = espaces[elindex];  //on recup la position de la lettre
    options[index] = true;  //rendre dispo

    var letterElements = document.getElementsByClassName("letter");
    letterElements[index].setAttribute("onclick", "addletter('" + lettres[index] + "', " + index + ")");
    letterElements[index].style.cursor = "pointer";
    letterElements[index].style.background = "white";
    document.getElementsByClassName("espace")[elindex].style.color = "transparent";
    

    letterElements[index].style.color = "black"; 
    // Vérifier si la lettre était incorrecte
    if (document.getElementsByClassName("espace")[elindex].classList.contains("incorrect")) {
        document.getElementsByClassName("espace")[elindex].style.color = "transparent"; // Réinitialiser la couleur dans les espaces
        document.getElementsByClassName("espace")[elindex].classList.remove("incorrect"); // Retirer la classe d'erreur "incorrect"
    }    
    updateRepTemporaire();
}

/**
 * @function marquerIncorrect
 * @description Marque les espaces en ajoutant la classe "incorrect" 
 */
function marquerIncorrect() {
    var espaceElement = document.getElementsByClassName("espace");
    for (var i = 0; i < espaceElement.length; i++) {
        if (espaceElement[i].innerHTML != "_") {
            espaceElement[i].classList.add("incorrect");
        }    
    }
}

/**
 * @function trouverLettre
 * @description Trouve l'index d'une lettre dans les options disponibles. on va l'utiliser pour les indices
 * @param {string} letter - La lettre à rechercher.
 * @returns {number} L'index de la lettre dans les options disponibles.
 */
function trouverLettre(letter) {
    var lettreElements = document.getElementsByClassName("letter");  //on recup tous les elements des lettres dispo
    for (var i = 0; i < lettreElements.length; i++) {
        if (lettreElements[i].innerHTML === letter) {
            return i;
        }
    }
}

/**
 * @function getLettreAleatoire
 * @description Obtient une lettre aléatoire de la réponse temporaire.
 * @returns {Array} Un tableau contenant la lettre aléatoire et sa position dans la réponse.
 * exemple : reponseTemporaire = "APP", motParniveau[nivActu]="APPLE"
 */
function getLettreAleatoire() {
    var position = Math.floor(Math.random() * reponseTemporaire.length); //genere une position aleatoire dans reponsetemp, si math.random retorune 0.5 : 0.5*3=1.5, mathfloor arrondit a 1, position=1
    var lettre = reponseTemporaire.charAt(position); //lettre = "P"
    reponseTemporaire = reponseTemporaire.substr(0, position) + reponseTemporaire.substr(position + 1, reponseTemporaire.length); // reponseTemp = "AP"
    
    var pos;
    var reponse = motParNiveau[niveauActuel]; //reponse="APPLE"
    for (var i = 0; i < reponse.length; ++i) {
        if (reponse[i] == lettre && document.getElementsByClassName("espace")[i].innerHTML != lettre) { //La boucle recherche "P" dans "APPLE" et vérifie si l'espace correspondant n'est pas déjà rempli
            pos = i; //la premiere occurence de "P" est a l'index 1 (le 2eme caractere)
            break;
        }
    }
    return [lettre, pos]; //return ["P",1]
}

/**
 * @function ajouterIndice
 * @description Ajoute un indice à un espace vide.
 * @param {string} lettreA_Ajt - La lettre à ajouter comme indice.
 * @param {number} index - L'index de la lettre à ajouter.
 * @param {number} position - La position de l'espace dans la réponse.
 */
function ajouterIndice(lettreA_Ajt, index, position) {
    var reponse = motParNiveau[niveauActuel];
    if (tempfreq[lettreA_Ajt] == freq[lettreA_Ajt]) { //si on a deja placé cette lettre autant de fois quelle apparait ds le mot
        var premierePos; //var pour stock la 1ere position ou la lettre est trouvee ds les espaces
        for (var i = 0; i < reponse.length; ++i) {
            if (document.getElementsByClassName("espace")[i].innerHTML == lettreA_Ajt) {
                premierePos = i;
                break;
            }
        }

        deselect(premierePos);
        tempfreq[lettreA_Ajt] -= 1;
    }

    var element = document.getElementsByClassName("espace")[position];
    var elindex = position;

    if (element.innerHTML != "_")
        deselect(position);

    element.innerHTML = lettreA_Ajt;
    options[index] = false;
    var letterElements = document.getElementsByClassName("letter");
    letterElements[index].removeAttribute("onclick");
    letterElements[index].style.cursor = "not-allowed";
    letterElements[index].style.background = "#89cf08";
    espaces[elindex] = index;
    element.removeAttribute("onclick");
    element.style.cursor = "not-allowed";
    tempfreq[lettreA_Ajt] += 1;
    if (toutRempli())
        passerNiveauSuivant();
    // Réinitialiser la couleur du texte de la lettre à blanc
    element.style.color = "white";
    // Ajouter une couleur d'illumination à l'arrière-plan
    element.style.background = "linear-gradient(70deg, blue, pink)";
}

/**
 * @function hint
 * @description Donne un indice au joueur.
 */
function hint() {
    if (nbIndices <= 0) { 
        return;
    }
    var gla = getLettreAleatoire(); //on appelle getLettreAleatoire qui renvoie une lettre aleat de la reptemp et sa position. gla = tableau
    var letter = gla[0];
    var position = gla[1];
    var index = trouverLettre(letter);  //on appelle trouverLettre pour trouver l'index de la lettre aleat 
    nbIndices--;
    ajouterIndice(letter, index, position);

}

// appels de fcts : recuperation de la progression et lancement de la fct main
recupererProgress4img();
main();
