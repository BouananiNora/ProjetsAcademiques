$('#Form').submit((e) => {
    e.preventDefault();

    //selectionne elem input et msg-box
    let loginInput = $('#Form input[name=login]');
    let passwordInput = $('#Form input[name=password]');
    let messageBox = $('#message-box');

    // reinitialise les classes d'erreurs
    loginInput.removeClass('error');
    passwordInput.removeClass('error');

    //on obtinet les val des input
    let login = loginInput.val();
    let password = passwordInput.val();

    if (login !== '' && password !== '') 
    {
        $.ajax(
        {
            url: '../Controleur/login.php',

            type: 'POST',

            data: 
            {
                'login': login,
                'password': password
            },

            success: (data) => {
                let response = JSON.parse(data);
                if (response.code === 200) {
                    console.log('Connexion réussie');
                    window.location.href = '../vue/index.html';  //redirect vers index.html si la connexion est reussie
                } else {
                    messageBox.html(`<p class='error'>Erreur de connexion : ${response.ERREUR}</p>`).show();
                }
            },

            error: (jqXHR) => {
                try {
                    let response = JSON.parse(jqXHR.responseText); //txt reponse http
                    messageBox.html(`<p class='error'>Erreur de connexion : ${response.ERREUR}</p>`).show();

                    if (response.ERREUR.includes('mot de passe')) {
                        passwordInput.addClass('error');
                    } else if (response.ERREUR.includes('Login')) {
                        loginInput.addClass('error');
                    }
                } catch (e) {
                    console.log('Erreur réseau:', jqXHR.statusText);
                    messageBox.html(`<p class='error'>Erreur de connexion : ${jqXHR.statusText}</p>`).show();
                }
            }
        });
    } 
    else 
    {
        messageBox.html('<p class="error">Veuillez entrer toutes les valeurs !</p>').show();
        if (login === '') loginInput.addClass('error');
        if (password === '') passwordInput.addClass('error');
    }
});
