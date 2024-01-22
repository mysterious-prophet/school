<?php /* skript realizující jednoduchý "vzkazovník" -- data ukládá do souboru,
  * vypisuje vždy formulář a pod něj vzkazy. Obsluhuje sám sebe -- dostává
  * POST-proměnné 'kdo' a 'co'
  * Problém: duplicita vzkazů při znovuodeslání formuláře (F5). Muselo by se
  * přesměrovávat (zatím neumíme -- až po TCP/IP). */

// pomocné funkce:
session_start();
ob_start();
function formular() // funkce, která vrací HTML kód formuláře
{
  $t = '<form method="post">'; // action ne => obsluhuje sám sebe
  $t .= 'Jméno a příjmení (přezdívka): <input type="text" name="kdo" size="40"><br>';
  $t .= 'Vzkaz:<br><textarea rows="5" cols="25" name="co"></textarea>';
  $t .= '<br><input type="submit" value="Odeslat">';
  $t .= '</form>';
  return $t;
}

function vypis_vzkazy($soubor) // vypíše vzkazy ze souboru
{ if (file_exists($soubor)) 
    @readfile($soubor); // výpis souboru na výstup
  else
    echo '<p>Zatím zde nejsou žádné příspěvky.</p>';
}

function zpracuj_vzkaz($kdo,$vzkaz,$soubor) // uloží nový vzkaz "HTML safe", doplní datum a čas
{ // příprava textu, který uložíme do souboru:
  if (function_exists('get_magic_quotes_gpc') && get_magic_quotes_gpc()) {
    $vzkaz = stripslashes($vzkaz); // pryč zbytečná lomítka
    $kdo = stripslashes($kdo);
  }
  // escapujeme data pro HTML:
  $vzkaz = html_escape($vzkaz);
  $kdo = html_escape($kdo);
  //$vzkaz = str_replace("\n",'<br>',$vzkaz); // HTML odřádkování pro Unix a MS Win
  // netřeba... $vzkaz = strip_tags($vzkaz); // vyházet HTML značky
  $vzkaz = nl2br($vzkaz,false); // HTML (ne XHTML) odřádkování pro všechny OS  
  $vzkaz = str_replace("\n",'',$vzkaz); // pryč souborové odřádkování
  $vzkaz = str_replace("\r",'',$vzkaz); // pryč souborové odřádkování
  $dnes = date('d. m. Y, H:i:s'); // dnešní datum a čas
  // vzkaz zpracovaný pro HTML:
  $nove = "<p><strong>$kdo</strong><br><small>$dnes</small><br>$vzkaz</p>";

  if (file_exists($soubor)) // načteme starý obsah (chceme přidat vzkaz na začátek souboru)
    $stare = "<hr>\r\n" . file_get_contents($soubor); //načteme vše do řetězce
  else // zatím nebyly žádné příspěvky (nebo soubor někdo smazal)
    $stare = '';

  @$f = fopen($soubor,'w'); // vytvoření prázdného nebo otevření stávajícího souboru pro zápis (a smazání obsahu)
  if ($f) { // OK, povedlo se
    @flock($f, LOCK_EX); // zamkneme soubor
    @fwrite($f,"$nove$stare"); // nejnovější vzkaz nahoře, pod ním staré
    @flock($f, LOCK_UN); // odemkneme soubor
    @fclose($f);
  }
  else // nepovedlo se otevřít
    die('Nelze zpracovat příspěvek!!!'.html_paticka());
}

// ------------------------------ samotný skript:
$s = "./vzkazy.dat"; // soubor pro vzkazy v adresáři 'pocet' (smí tam zapisovat PHP)
include './fce_html.php';
$titulek = 'Jednoduchý vzkazovník';
echo html_hlavicka($titulek);
echo "<h1>$titulek</h1>";

if ($_SERVER['REQUEST_METHOD']=='POST') { // přišel klient metodou POST? Tak asi máme data...
  $f_kdo = (isset($_POST['kdo']) ? $_POST['kdo'] : '');
  $f_co = (isset($_POST['co']) ? $_POST['co'] : '');
  $chyba = ''; // příprava
  if (empty($f_kdo))
    $chyba .= '<p style="color:red">Zadejte jméno/přezdívku!</p>';
  if (empty($f_co))
    $chyba .= '<p style="color:red">Zadejte text vzkazu!</p>';
  if (empty($chyba))
    zpracuj_vzkaz($f_kdo,$f_co,$s); // uložíme data
  else
    echo $chyba; // vypíšeme chybu
}

if (isset($_SESSION['prihlasen'])) {
	echo formular(); // prázdný formulář
	echo '<a href="./logout.php">logout</a>';
}
else{
    echo '<a href="./login.php">login</a>';
}

echo '<h2>Vzkazy:</h2>';
vypis_vzkazy($s); // pod formulářem vypíšeme všechny dosud zadané vzkazy (už v escapovaném HTML)
echo html_paticka();

ob_flush();
?>
