<?php // přidání nové školy do DB (pokud jsou úspěšné kontroly!!!)

include "./fce_studium.php"; // např. přesměr., menu,...
include "./fce_html.php"; // html záhlaví,...

function f_skola($nazev='', $zkr = '', $mesto='')
{
  $nazev = html_escape($nazev);
  $zkr = html_escape($zkr);
  $mesto = html_escape($mesto);

  $t = '<form method="post">'; // obsluhuje sám sebe
  $t .= '<label>Název školy: <input type="text" name="nazev" maxlength="50" size="31" value="'.$nazev.'"></label> <em>min. 3 znaky, povinné pole</em>';
  $t .= '<br><label>Zkratka: <input type="text" name="zkr" maxlength="10" value="'.$zkr.'"></label> <em>min. 2 znaky, povinné pole</em><br>';
  $t .= '<br><label>Město (hl. sídlo školy): <input type="text" name="mesto" maxlength="35" value="'.
     $mesto.'"></label> <em>min. 2 znaky, povinné pole</em><br>';
  $t .= '<input type="submit" value="Uložit">';
  $t .= '</form>';
  return $t;
}

// samotny skript:
$tit = 'STUDIUM - nová škola';
echo html_hlavicka($tit,'','',array('studium.css'));
$nadpis = 'Přidání nové školy';
echo menu($nadpis,__FILE__);

if ($_SERVER['REQUEST_METHOD'] == 'POST') // máme data
{
  // přejmenujeme si vstupy z formuláře + odstraníme mezery (pokud vstupy nejsou, nastavíme prázdné):
  $nazev = (isset($_POST['nazev'])) ? trim($_POST['nazev']) : '';
  $zkr = (isset($_POST['zkr'])) ? trim($_POST['zkr']) : '';
  $mesto = (isset($_POST['mesto'])) ? trim($_POST['mesto']) : '';
    
  $chyba = array(); // příprava
  $pov_znaky = 'a-zA-ZáéěíóúůýčďňřšťžÁÉĚÍÓÚŮÝČĎŇŘŠŤŽôÔľĽ'; // příprava - povolené znaky pro jméno
  if (!preg_match("@^[$pov_znaky]{3,}([ -]?[$pov_znaky]+)*$@u", $nazev)) // !preg_match("@^[$pov_znaky -]{3,50}$@u", $nazev)) // ||
    $chyba[] = 'Název školy je vyplněn chybně!';
  if (!preg_match("@^([$pov_znaky]+([ -]?[$pov_znaky]+)?){2,10}$@u", $zkr))
    $chyba[] = 'Zkratka školy je vyplněna chybně!';
  if (!preg_match("@^([$pov_znaky]+( ?-? ?[0-9$pov_znaky]+)?){2,50}$@u", $mesto))
    $chyba[] = 'Město je vyplněno chybně!';

  // bylo vše OK nebo ne?
  if (!empty($chyba))
  { echo '<p class="chyba">'.implode('<br>',$chyba). '</p>';
    echo '<p>Opravte data:</p>';
    echo f_skola($nazev, $zkr, $mesto); // uživatel vidí, co zadal
  }
  else
  {
    include "./db_class.php";
    $s = new TDatabase();
    $dotaz = 'INSERT INTO skola VALUES(NULL, ?, ?, ?)';
    $data = array('sss', $nazev, $zkr, $mesto);
    $s->posli_pripr_dotaz($dotaz, $data, 'vložení nové školy');
    if ($s->pocet_radku == 1)
      echo "<p class=\"uspech\">Škola <em>$nazev</em> byla úspěšně přidána.</p>";
    else
      echo "<p class=\"chyba\">Škola <em>$nazev</em> bohužel nebyla přidána (pravděpodobně zkratka školy již existuje).</p>";
    echo f_skola(); // vypíšeme znovu prázdný formulář
  }
}
else
  echo f_skola(); // nejsou data - vypíšeme prázdný formulář
echo html_paticka();
