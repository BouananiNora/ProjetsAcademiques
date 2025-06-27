
function saveProgress4img(theme,totalPoints)
{
    //demarre une requete ajax a l'aide de jquery
    $.ajax({  
        url: '../../Controleur/saveProgress4img.php',

        type: 'POST', //la requete http sera de type post, cad quelle enverra des données au serveur
        
        data:   //les données a envoyer au serveur sont specifiées ici :
        {
            "totalPoints": totalPoints,
            "theme": theme
        },
        
        success: (data) => {  //cette fct est executée si la requete est reussie, data = données renvoyées par le serveur
            let response = JSON.parse(data); //les données renvoyées par le serveur sont analysées en json et stockees ds la var 'response'
            if (response.code === 200) 
                console.log('Réponse du serveur (save):', response);
        },

        error: (jqXHR, status, erreur) => { //si la requete echoue.  
            console.error('Erreur lors de la sauvegarde :', erreur);
            console.error('Statut de la requête :', status);
            console.error('Réponse du serveur :', jqXHR.responseText);
        }
    });
}


function recupererProgress4img()  
{

    $.ajax(
    {
        url: '../../Controleur/recupererData4img.php',

        type: 'GET', //la requete http sera de type get, cad quelle recuperera des données du serveur

        dataType: 'json',

        success: function(response) 
        {
            console.log('Réponse du serveur (recup):', response);
            if (response.status === 'success' && response.data.length > 0) 
            {
                const data = response.data.data[0];
                const theme = data.theme;
                const totalPoints = data.points;
            } 
            else 
            {
                console.error('Erreur lors de la récupération des données: ', response.message);
            }
        },
        error: function(xhr, status, error) 
        {
            console.error('Erreur lors de la communication avec le serveur:', error);
        }
    });
}
