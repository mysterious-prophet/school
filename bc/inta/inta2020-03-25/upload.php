<?php /* obsluha uploadu jednoho souboru:
 *     1) kontrola, zda se upload povedl;
 *     2) výpis info o souboru;
 *     3) je-li soubor textový (tj. text/plain nebo text/html), výpis jeho obsahu
 *        (dočasný soubor na serveru nezůstane);
 *     4) je-li soubor obrázek (gif, png, jpg), uložíme jej na serveru do složky
 *        'upload' a zobrazíme
 *        !!! adresář 'upload' musí existovat a mít právo zápisu pro skript !!!
 *
 * Skript obsluhuje sám sebe a dostává soubor 's' (v superglob. poli $_FILES)
 */

function formular()  // pomocná fce pro výpis formuláře:
{
  $text = '<form method="post" enctype="multipart/form-data">'; // případně i action="upload.php"
  $text .= 'Vyber soubor: <input type="file" name="s"><br>';
  $text .= '<input type="submit" value="Odešli">';
  $text .= '</form>';
  return $text;
}

// ----------------- samotný skript:

include './fce_html.php';
include './fce_upload.php'; // => pole $chyby_uploadu
$t = 'Upload souboru';
echo html_hlavicka($t);
echo "<h1>$t</h1>";

if (!isset($_FILES['s']) || empty($_FILES['s']['tmp_name'])) // nemáme soubor; netřeba kontrolovat $_SERVER['REQUEST_METHOD']
  die(formular() . html_paticka()); // nejsou data => jen prázdný HTML-formulář (a ukončíme skript)

$ch = $_FILES['s']['error'];
if ($ch != 0)  // nastala chyba při uploadu? => konec 
  die('<p>Soubor se nepodařilo přenést na server (chyba <em>'.$chyby_uploadu[$ch].'</em>)!</p>' . formular() . html_paticka());

// příprava "krátkých názvů"
$jmeno = $_FILES["s"]["name"];
$temp = $_FILES['s']['tmp_name'];
$velikost = $_FILES["s"]["size"];
$typP = $_FILES["s"]["type"]; // MIME typ podle prohlížeče
$typM = ''; // příprava
if (function_exists('mime_content_type')) {
  $typM = mime_content_type($temp); // zjištění skutečného MIME typu dleobsahu souboru (ne podle koncovky, jak to dělá prohlížeč)
  $typ = $typM;
}
else
  $typ = $typP;

// výpis info o souboru:
echo "<h2>Informace o souboru:</h2><p>Původní název: $jmeno<br>";
echo "Dočasný název: $temp<br>Velikost: $velikost B<br>MIME typ: $typM (a podle prohlížeče: $typP)</p>";

// je soubor textový?
if (!empty($typ) && ($typ=="text/plain" || $typ=="text/html"))
{
  $s = @file_get_contents($temp); // obsah souboru do řetězce
  echo '<pre style="background-color:#CCFFCC">'.html_escape($s).'</pre>'; // strukturovaný výpis včetně HTML značek
}
// je to obrázek povoleného typu?
if (!empty($typ) && ($typ=="image/jpeg" || $typ=="image/pjpeg" || $typ=="image/gif" || $typ=="image/png"))
  if (@move_uploaded_file($temp, "./upload/".basename($jmeno)))
  { echo '<p>Obrázek byl uložen a vypadá takto:</p>';
    echo "<img src=\"./upload/$jmeno\" alt=\"obrázek\">"; // vložíme do stránky obrázek (bez udání rozměrů!)
  }
  else
    echo '<p>Obrázek se nepodařilo uložit! Kontaktujte správce serveru.</p>';

$jmeno_skriptu = basename($_SERVER['SCRIPT_NAME']);// jméno tohoto skriptu (z URL)
echo "<p><a href=\"$jmeno_skriptu\">Poslat další soubor.</a></p>"; // odkaz na formulář
echo html_paticka();
