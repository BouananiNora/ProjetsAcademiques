$('#Form').submit((e) => {
    e.preventDefault();

    let loginInput = $('#Form input[name=login]');
    let passwordInput = $('#Form input[name=password]');
    let confirmationInput = $('#Form input[name=confirmation]');
    let messageBox = $('#message-box');

    loginInput.removeClass('error');
    passwordInput.removeClass('error');
    confirmationInput.removeClass('error');

    let errors = checkForm(loginInput.val(), passwordInput.val(), confirmationInput.val());

    // reinitialise les messages d'erreur
    messageBox.html('');
    
    if (errors.length > 0) 
    {
        errors.forEach((error) => 
        {
            switch (error) 
            {
                case 'InvalidLogin':
                    showLabelError(loginInput, 'Login doit contenir entre 8 et 30 caractères !');
                    break;
                case 'InvalidStringLogin':
                    showLabelError(loginInput, 'Login doit contenir des lettres, des chiffres et des symboles (# ! _ -)');
                    break;
                case 'InvalidPassword':
                    showLabelError(passwordInput, 'Mot de passe doit contenir entre 8 et 50 caractères !');
                    break;
                case 'NotSamePassword':
                    showLabelError(confirmationInput, 'Les mots de passe sont différents !');
                    break;
            }
        });

    } 
    else 
    {
        $.ajax(
        {
            url: "../Controleur/signup.php",

            type: 'POST',

            data: 
            {
                'login': loginInput.val(),
                'password': passwordInput.val()
            },

            success: (data) => {
                console.log("Inscription réussie:", data);
                window.location.href = "../vue/login.html";
            },

            error: (jqXHR) => {
                console.log("Erreur lors de l'inscription", jqXHR);
                let response = jqXHR.responseJSON;
                if (response && response.code === 400) 
                {
                    messageBox.html('Login existant');
                }
            }
        });
    }
});

// verifie les erreurs
function checkForm(login, password, confirmation) 
{
    let errors = [];

    if (!login || login.length < 8 || login.length > 30) 
    {
        errors.push('InvalidLogin');
    } 
    else if (!/^(?=.*[A-Za-z])(?=.*[0-9])(?=.*[\#\!\_\-])[^\s]{8,30}$/.test(login)) 
    {
        errors.push('InvalidStringLogin');
    }

    if (!password || password.length < 8 || password.length > 50) {
        errors.push('InvalidPassword');
    }

    if (password !== confirmation || !confirmation) {
        errors.push('NotSamePassword');
    }

    return errors;
}

// affiche messages d'erreur
function showLabelError(input, message) 
{
    input.addClass('error');
    let messageBox = $('#message-box');
    messageBox.append('<p class="error">' + message + '</p>').show();
}
