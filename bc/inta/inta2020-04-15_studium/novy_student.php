<?php // přidání nového studenta do DB (pokud jsou úspěšné kontroly!!!)

include "./fce_studium.php"; // např. přesměr., menu,...
include "./fce_html.php"; // html záhlaví,...

function f_student($jm='', $prijm='', $dn='')
{
  $jm = html_escape($jm);
  $prijm = html_escape($prijm);
  $dn = html_escape($dn);

  $t = '<form method="post">'; // obsluhuje sám sebe
  $t .= '<label>Jméno: <input type="text" name="jmeno" maxlength="35" size="20" value="'.$jm.'" required></label> <em>2-35 písmen, povinné</em>';
  $t .= '<br><label>Příjmení: <input type="text" name="prijmeni" maxlength="50" value="'.$prijm.'" required></label> <em>2-50 písmen, povinné</em><br>';
  $t .= '<label>Datum narození: <input type="date" name="datum" maxlength="12" size="13" value="'.$dn.'" required></label> <em>formát: DD. MM. RRRR, min. 16 let staré, povinné</em>';
  $t .= '<br><input type="submit" value="Uložit">';
  $t .= '</form>';
  return $t;
}
       
// samotny skript:
$tit = 'STUDIUM - nový student';
echo html_hlavicka($tit,'','',array('studium.css'));
$nadpis = 'Přidání nového studenta';
echo menu($nadpis,__FILE__);

if ($_SERVER['REQUEST_METHOD'] == 'POST') // máme data
{  
  // přejmenujeme si vstupy z formuláře + odstraníme mezery (pokud vstupy nejsou, nastavíme prázdné):
  $jmeno = (isset($_POST['jmeno'])) ? trim($_POST['jmeno']) : '';
  $prijmeni = (isset($_POST['prijmeni'])) ? trim($_POST['prijmeni']) : '';
  $datum = (isset($_POST['datum'])) ? trim($_POST['datum']) : '';
    
  $chyba = array(); // příprava
  $pov_znaky = 'a-zA-ZáéěíóúůýčďňřšťžÁÉĚÍÓÚŮÝČĎŇŘŠŤŽ'; // příprava - povolené znaky pro jméno
  if (!preg_match("@^([$pov_znaky]+([ -]?[$pov_znaky]+)?){2,35}$@", $jmeno))
    $chyba[] = 'Jméno je vyplněno chybně!';
  if (!preg_match("@^([$pov_znaky]+( ?-? ?[$pov_znaky]+)?){2,50}$@", $prijmeni))
    $chyba[] = 'Příjmení je vyplněno chybně!';
  $datum = datum_preved($datum,'en'); // pro kontrolu a případné uložení do DB použijeme angl. formát
  if (!preg_match("@^(19[3-9][0-9]|20[0-2][0-9])-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01])$@", $datum, $ddd))
    $chyba[] = 'Datum je vyplněno chybně!';
  elseif (!datum_kontrola((int)$ddd[3],(int)$ddd[2],(int)$ddd[1],$ch)) // kontrola kalendářního data (Není-li ošetřeno, tak v MySQL se objeví 0000-00-00!)
    $chyba[] = $ch;
  elseif (time()-mktime(23,59,59,$ddd[2],$ddd[3],$ddd[1])<16*(365.25*24*60*60)) // je člověk nejméně 16 let starý? (mladší lidi na VŠ nepustíme)
    $chyba[] = 'Nelze vložit - student musí být starší 16 let! Zkontrolujte datum narození.';

  // bylo vše OK nebo ne?
  if (!empty($chyba)) // co když pole s chybami není prázdné?
  { echo '<p class="chyba">'.implode('<br>',$chyba). '</p>';
    echo '<p>Opravte data:</p>';
    echo f_student($_POST['jmeno'], $_POST['prijmeni'], $_POST['datum']); // uživatel vidí, co zadal
  }
  else
  {
    include "./db_class.php";
    $s = new TDatabase();
    $dotaz = 'INSERT INTO student VALUES(NULL, ?, ?, ?)';
    $data = array('sss', $jmeno, $prijmeni, $datum);
    $s->posli_pripr_dotaz($dotaz, $data, 'vložení nového studenta');
    if ($s->pocet_radku == 1)
      echo '<p class="uspech">Student <em>'. html_escape($jmeno). ' ' .html_escape($prijmeni).'</em> byl úspěšně přidán.</p>';
    else // nikdy by to sem nemělo dojít
      echo '<p class="chyba">Student <em>'. html_escape($jmeno). ' ' .html_escape($prijmeni).'</em> bohužel nebyl přidán.</p>';
    echo f_student(); // vypíšeme znovu prázdný formulář
  }
}
else
  echo f_student(); // nejsou data - vypíšeme prázdný formulář
echo html_paticka();
