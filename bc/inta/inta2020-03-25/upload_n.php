<?php /* obsluha uploadu více souborů - u každého souboru:
     *  1) kontrola, zda se upload povedl;
     *  2) výpis informací o souboru;
     *  3) uložení souboru typu PNG, JPG a GIF do adresáře 'upload'.
     *     (počet souborů můžeme posílat v URL přes GET proměnnou 'N', od 1 do 20)
     */

// // kdyby bylo potřeba sledovat chyby:
//error_reporting(E_ALL);
//ini_set('display_errors',1);

// ------------- pomocná funkce pro výpis formuláře
function formik($n=5) // implicitně 5 souborů
{
  $t = '<form method="post" enctype="multipart/form-data">';
  for ($i=1; $i<=$n; $i++) // pro každý soubor jedno políčko
    $t .= '<label>Zadej '.$i.'. soubor: <input type="file" name="soub[]"></label><br>';
  $t .= '<input type="submit" value="Pošli!">';
  $t .= '</form>';
  return $t;
}

// ------------- samotný skript:
include './fce_html.php';
include './fce_upload.php';

$t = 'Upload více souborů';
echo html_hlavicka($t);

// zjistíme počet souborů z metody GET (jméno proměnné: N)
if (isset($_GET['N'])) {
  $N = (int)$_GET['N'];  // přetypování na INT, kdyby někdo zadat např. text
  if ($N<=0 || $N>20) // dovolíme jen 1 až 20 souborů ... !!! direktiva max_file_uploads
    $N = 5; // implicitní hodnota, když v URL je špatné číslo
}
else
  $N = 5; // implicitní hodnota, když v URL není uvedena proměnná N

// dále vypíšeme formulář nebo postupně uložíme všechny zadané soubory:
if (!isset($_FILES['soub'])) { // nejsou data
  $text = "<h1>$t</h1>";
  echo formik($N); // vypíšeme formulář
}
else { // data máme
  $text = "<h1>$t - výsledky:</h1>";
  foreach($_FILES['soub']['tmp_name'] as $i=>$h) {
    $ch = $_FILES['soub']['error'][$i]; // chyba přenosu?
    //$jmeno = $_FILES['soub']['tmp_name'][$i]; // soubor na serveru  => máme proměnnou $h
    $velikost_kB = round($_FILES['soub']['size'][$i]/1024); // velikost v kB
    $jmeno_puv = $_FILES['soub']['name'][$i]; // původní jméno
    $typ = function_exists('mime_content_type') ? mime_content_type($h) : $_FILES['soub']['type'][$i]; // MIME typ

    // testy + pokus o uložení do adresáře 'upload'
    $text .= '<h2>Informace o '.($i+1).'. souboru:</h2>';// pro oznámení, co se stalo (k textu budeme připojovat další info)
    if (empty($h)) // uživatel soubor nezadal (INPUT pole bylo prázdné)
      $text .= "<p>Soubor nebyl zadán!</p>";
    elseif ($ch != 0) // chyba při přenosu
      $text .= "<p>Soubor <em>$jmeno_puv</em> se nepodařilo přenést na server!</p>" . $chyby_uploadu[$ch];
    else { // u všech souborů vypíšeme informace o každém
      $text .= "<p>Původní název: <em>$jmeno_puv</em><br>Dočasný název: $h<br>";
      $text .= "Velikost: $velikost_kB kB<br>MIME typ: $typ</p>";
      // obrázky uložíme na server
      if ($typ=='image/png' || $typ=='image/gif' || $typ=='image/jpeg' || $typ=='image/pjpeg') { // obrázky zkusíme uložit
        $cil = "./upload/$jmeno_puv";
        // existuje už ten cílový soubor?
        $prepis = (file_exists($cil)) ? '(přepsal ten původní!)' : 'na server';
        if (@move_uploaded_file($h, $cil))
          $text .= "<p style=\"color:#009900\">Soubor <em>$jmeno_puv</em> byl uložen $prepis.</p>";
        else
          $text .= "<p>Soubor <em>$jmeno_puv</em> NEBYL uložen!!!</p>";
      }
    }
  }
  echo "<p>$text</p>"; // vypíšeme kompletní info o průběhu zpracování
  echo '<a href="upload_n.php?N='.$N.'">Chci uploadovat další!</a>';
}
echo html_paticka();
