<?php /* skript provádí náhrady v souboru odeslaném na server; skript obsluhuje sám sebe
       * skript dostává POST proměnné 'co', 'cim', 'reg' a využívá pole $_FILES pro soubor 's'
       * soubor musí být textový (přesněji: MIME typ 'text/plain') a do 60000 B
       */

// // pro účely zobrazení chyb v PHP (kdyby server hlásil chybu HTTP 500, odkomentujte):
//error_reporting(E_ALL);
//ini_set('display_errors','on');

function formular() // pomocná fce -- vypisuje (prázdný) formulář pro upload souboru
{
  $t = '<form method="post" enctype="multipart/form-data">'; // action netřeba
  $t .= '<label>Hledaný text: <input type="text" name="co" required></label><br>';
  $t .= '<label>Čím se nahradí: <input type="text" name="cim" required></label><br>';
  $t .= 'Používám regulární výraz (PCRE):';
    $t .= '<label><input type="radio" name="reg" value="1"> ano</label>';
    $t .= '<label><input type="radio" name="reg" value="0" checked> ne</label>';
    $t .= '<br>';
  $t .= '<input type="hidden" name="MAX_FILE_SIZE" value="60000">'; // pro omezení velikosti v prohlížeči
  $t .= '<label>Zadej <em>textový</em> soubor do 60 kB: <input type="file" name="s"></label><br>';
  $t .= '<input type="submit" value="Zpracovat">';
  $t .= '</form>';
  return $t;
}
              
// ------------ samotný skript:
include './fce_html.php';
include './fce_upload.php';

// globální proměnné skriptu:
$tit = 'Náhrady v souboru odeslaném na server';
$odkaz = '<p><a href="'.basename($_SERVER['SCRIPT_NAME']).'">ZPRACOVAT DALŠÍ SOUBOR</a></p>';

// generování výstupu v HTML:
echo html_hlavicka($tit,'utf8','background-color:#FFFF66');
echo "<h1>$tit</h1>"; // nadpis

if (!isset($_FILES['s']) || empty($_FILES['s']['tmp_name'])) // opět netřeba testovat $_SERVER['REQUEST_METHOD']
  die (formular() . html_paticka()); // není k dispozici soubor, KONEC

// máme soubor, inf. o něm uložíme do proměnných:
$soubor = $_FILES['s']['tmp_name']; // jméno dočasného souboru na serveru
$delka = $_FILES['s']['size']; // velikost uploadovaného souboru
$typ = function_exists('mime_content_type') ? mime_content_type($soubor) : $_FILES['s']['type']; // MIME typ upload. souboru
$chyba = $_FILES['s']['error']; // chyba při uploadu?

// otestujeme, zda je soubor do 60000 B a je textový (MIME typ 'text/plain'):
if ($chyba != 0) // nastala chyba během uploadu?
  die ('<p>Soubor se nepodařilo nahrát na server! ({$chyby_uploadu[$chyba]})</p>' . $odkaz . html_paticka());
if($delka > 60000) // je to soubor do velikosti cca 60 kB?
  die("<p>Soubor je moc velký ($delka B)! Povolená velikost: 60000 B.</p>" . $odkaz . html_paticka());
if(strncmp($typ,"text/",5)!=0) // je to textový soubor?
  die("<p>Soubor není textový (má typ: $typ)!</p>" . $odkaz . html_paticka());

// soubor zpracujeme:
$str = @file_get_contents($soubor); // načteme jeho obsah do proměnné $str
if ($str == FALSE)
  die('<p>Nelze otevřít dočasný soubor!</p>' . $odkaz . html_paticka()); // KONEC

if (isset($_POST['co']))
  $f_co = $_POST['co'];
else
  die('<p>Není zadáno, co se má nahradit!</p>' . $odkaz . html_paticka()); // KONEC
if (isset($_POST['cim']))
  $f_cim = $_POST['cim'];
else
  die('<p>Není zadáno, čím se má nahradit!</p>' . $odkaz . html_paticka()); // KONEC
if (isset($_POST['reg']))
  $f_reg = $_POST['reg'];
else
  $f_reg = '0'; // implicitně se nepoužívají regulární výrazy

if (function_exists('get_magic_quotes_gpc') && get_magic_quotes_gpc())
{ $f_co = stripslashes($f_co);   // odstranit zbytečná zpětná lomítka
  $f_cim = stripslashes($f_cim); // -"-
}

$kolik = 0; // příprava
if ($f_reg=='1') // použ. reg. výraz
  $str2 = preg_replace($f_co,$f_cim,$str,-1,$kolik); // může vypsat Warning!!!
else { // nepoužívat reg. výrazy
  if (function_exists('mb_ereg_replace_callback')) {
    //$kolik = NULL; // nelze zjistit(?)  
    $f_co = preg_quote($f_co);
    $str2 = mb_ereg_replace_callback($f_co,
			function ($a) {global $kolik, $f_cim; $kolik++; return $f_cim;},
			$str);
  }
  else
    $str2 = str_replace($f_co,$f_cim,$str,$kolik); // pro jistotu PŮVODNÍ data. Ale nebude správně fungovat pro UTF-8!
}  
$str2 = html_escape($str2); // kdyby v TXT souboru byly HTML značky

echo '<div style= "display:table;width:100%;table-layout:fixed;">';
echo "<div style='display: table-cell;width: 50%;'><h3>Soubor po $kolik náhradách:</h3></div>";
echo "<div style='display: table-cell;width: 50%;'><h3>Soubor před náhradami:</h3></div>";
echo '</div>';
/*if ($f_reg=='1') // zvýraznění nahrazeného textu - asi nelze nějak jednoduše... :-(
  $f_cim = preg_replace('/\$\d{1,2}|[\b]{1,2}\d{1,2}/','',$f_cim); // vynechání $1 nebo \\1 nebo \1
if (function_exists('mb_ereg_replace'))
    $str2 = mb_ereg_replace($f_cim,"<em style=\"color:red\">$f_cim</em>",$str2);
  else
    $str2 = str_replace($f_cim,"<em style=\"color:red\">$f_cim</em>",$str2); // $cim zvýrazníme
*/
echo '<div style="background-color:#FFFFFF;display: table-cell;width: 50%; padding: 10px;">'.nl2br($str2).'</div>'; // místo konců řádků je <br>;  
echo '<div style="background-color:#CCFFCC;display: table-cell;width: 50%; padding: 10px;">',nl2br(html_escape($str)),'</div>';
echo '</div>';

echo $odkaz;
echo html_paticka();
