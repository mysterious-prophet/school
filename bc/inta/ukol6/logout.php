<?php // ukazka prace se session -- odhlaseni (logout.php)

session_start();

$_SESSION = array();       // smaže session proměnné
$cjm = session_name();     // jméno identifikátoru
if (isset($_COOKIE[$cjm])) // zneplatnění cookie
  setcookie($cjm, '', time()-42000, '/');
session_destroy();         // zrušení sezení
header('Location:  http://'.$_SERVER['SERVER_NAME'].dirname($_SERVER['PHP_SELF']).'/vzkazy.php'); // přesměrování na přihlaš. stránku
// tento skript nic negeneruje, jen presmeruje na login.php