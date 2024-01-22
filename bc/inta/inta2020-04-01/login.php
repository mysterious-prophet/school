<?php // ukazka prace se session (prihlaseni uzivatele)

// spravne prihlasovaci udaje (pozdeji je budeme cist z databaze)
$jmeno = 'admin';
$heslo = '12358'; // heslo "natvrdo" a nezasifrovane!!!

session_start(); // budeme vyuzivat session

function formular($jm='')
{ $t = '<form method="post">';
  $t .= 'Jméno: <input type="text" name="jmeno" value="' . htmlspecialchars($jm) . '"><br>';
  $t .= 'Heslo: <input type="password" name="heslo"><br>';
  $t .= '<input type="hidden" name="odesl" value="1"><input type="submit" value="OK">';
  $t .= '</form>';
  return $t;
}

function zacatek_stranky($tit)
{
  echo html_hlavicka($tit, 'utf8', '', '', 'background-color: #99FF99');
  echo "<h1>$tit</h1>";
}


include './fce_html.php';
$tit = "Ukázka session - přihlášení";

if (isset($_POST['odesl']))
{ 
  $d_jmeno = isset($_POST['jmeno']) ? $_POST['jmeno'] : '';
  $d_heslo = isset($_POST['heslo']) ? $_POST['heslo'] : '';
  
  if (function_exists('get_magic_quotes_gpc') && get_magic_quotes_gpc())
  { $d_jmeno = stripslashes($d_jmeno);
    $d_heslo = stripslashes($d_heslo);
  }
  // máme data z formuláře:
  if ($d_jmeno==$jmeno && $d_heslo==$heslo) // OK, správné údaje
  { //session_name('male_menu'); // nové jméno pro cookie
    session_regenerate_id();
    $_SESSION['prihlasen']=$d_jmeno;
    // přesměrování (je-li přihlášení úspěšné, tato stránka NIC NEVYPISUJE, jen přesměruje)
    header('Location: http://'.$_SERVER['SERVER_NAME'].dirname($_SERVER['PHP_SELF']).'/menu.php');
    exit; // konec skriptu
  }
  else // uzivatel nezadal správné udaje!
  { zacatek_stranky($tit);
    echo '<p style="background-color:#ff0000">Jméno nebo heslo nejsou správné!</p>'.formular($d_jmeno);
    echo html_paticka();
  }
}
else // uzivatel nevyplnil formular
{ zacatek_stranky($tit);
  echo formular();
  echo html_paticka();
}
