<?php
if(empty($_SESSION))
{
    session_start();
}
session_unset();
session_destroy();
echo '<script>
    localStorage.clear();
    window.location.href = "../vue/login.html";
</script>';



?>