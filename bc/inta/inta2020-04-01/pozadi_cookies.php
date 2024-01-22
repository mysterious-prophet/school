<?php // stránka, jejíž pozadí je načítáno z COOKIE proměnné a lze je měnit pomocí formuláře 

// ------- pomocná funkce:

/* je_povolena_barva ... pomocná funkce využívající globální pole $barvicky */
function je_povolena_barva($barva)
{ // zkontroluje existenci barvy v poli (nemáme asociativní pole!)
  foreach ($GLOBALS['barvicky'] as $h)
    if ($barva == $h)
      return true; // OK, barva je v glob. poli $barvicky pritomna
  return false; 
}

// ------- logika skriptu:

$barvicky = array(
	'bílá' => '#FFFFFF',
	'červená' => '#FFCCCC',
	'zelená' => '#CCFFCC',
	'modrá' => '#CCCCFF',
	'fialová' => '#FFCCFF',
	'šedá' => '#CCCCCC',
	'žlutá' => '#FFFFCC',
	'oranžová' => '#FF6000'
); // globální pole


$chyba = ''; // pro ošetření chyb
// máme data z níže uvedeného formuláře?
if ($_SERVER['REQUEST_METHOD']=='POST') {
  if (isset($_POST['b']) && je_povolena_barva($_POST['b'])) {
    $barva = $_POST["b"];  // máme hodnotu barvy
    setcookie('pozadi',$barva, time()+3*60*60,'/'); // platí 3 hodiny
    // při znovuotevření stránky během 3 hodin se projeví: $_COOKIE['pozadi'] = $barva;
  }
  else // nekorektní data z formuláře!
    $chyba = 'Zneužití formuláře!';
}
else { // nemáme data z formuláře
  if (!isset($_COOKIE['pozadi'])) // máme alespoň data v cookie?
    $barva = "#ffffff"; // barvu nevíme ani z cookie, tak implicitně bílá barva
  else {
    $barva = urldecode($_COOKIE['pozadi']); // vezmeme hodnotu z cookie

    if (!je_povolena_barva($barva)) // problém - někdo se asi v té cookie "vrtal"
      $chyba = 'Zneužití cookie!';
  }             
}

// ------- generování WWW:

include './fce_html.php'; // funkce pro výpis záhlaví a zápatí HTML kódu

if ($chyba)
  die(html_hlavicka('CHYBA - cookies!').'<p style="color:red;font-weight:bold">'.$chyba.'</p>'.html_paticka()); // KONEC

echo html_hlavicka('Pokus - cookies','utf8',"background-color:$barva");
echo '<h1>Vítejte</h1><p>Toto je stránka, kde si můžete vybrat barvu pozadí:</p>';
// formulář pro výběr barvy pozadí:
echo '<form method="post"><select name="b" size="1">';
foreach ($barvicky as $barva_nazev => $barva_html)
  echo "<option value=\"$barva_html\" style=\"background-color:$barva_html\">$barva_nazev</option>";
echo '<input type="submit" value="OK"></form>';
echo html_paticka();
