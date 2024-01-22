<?php // přidání nové školy do DB (pokud jsou úspěšné kontroly!!!)

include "./fce_studium.php"; // např. přesměr., menu,...
include "./fce_html.php"; // html záhlaví,...
include "./db_class.php"; // vždy se připojujeme k DB!

function f_prirazeni($idstudenta, $idskoly, $den, $seznam_studentu, $seznam_skol, $den_konec='')
{ // vypisuje formulář pro přiřazení studenta ke škole
  // $idstudenta, $idskoly, $den ... údaje z formuláře (zpětný výpis)
  // $seznam_ = dvourozměrné pole předem získané z DB
   
  $t = '<form method="post">'; // formulář obsluhuje sám sebe
  // menu pro výběr studenta:
  $t .= 'Student (řazeno dle příjmení): <select name="st">';
  foreach($seznam_studentu as $i=>$s) // $s=pole (0=id,1=jmeno,2=prijmeni,3=datum nar.)
  { $s[3] = datum_preved($s[3],'cz'); // úprava data
    if ($idstudenta == $s[0]) // zpětný výpis: byl student vybrán?
      $vybr = " selected";
    else
      $vybr = "";
    if ($i>0) // názvy DB slouců nevypisujeme                                        
      $t .= "<option value=\"$s[0]\"$vybr>$s[2], $s[1] ($s[3])</option>";
  }
  $t .= '</select><br>';
  // menu pro výběr školy:
  $t .= 'Škola (řazeno dle názvu): <select name="sk">';
  foreach($seznam_skol as $i=>$s) // $s=pole (0=id,1-nazev,2=mesto)
  { if ($idskoly == $s[0]) // zpětný výpis: byla škola vybraná?
      $vybr = " selected";
    else
      $vybr = "";
    if ($i>0) // názvy DB slouců nevypisujeme
      $t .= "<option value=\"$s[0]\" $vybr>$s[1] ($s[2], $s[3])</option>";
  }
  $t .= '</select><br>';
  $t .= 'Studium od (DD. MM. RRRR): ';
  $t .= '<input type="text" name="od" value="'.html_escape($den).'" required><br>';
  $t .= 'Ukončení studia (DD. MM. RRRR): ';
  $t .= '<input type="text" name="do" value="'.html_escape($den_konec).'"><br>';
  $t .= '<input type="submit" value="Uložit">';
  $t .= '</form>';
  return $t;
}

$tit = 'STUDIUM - student zahajuje studium na škole';
echo html_hlavicka($tit,'','',array('studium.css'));
$nadpis = 'Přiřazení studenta ke škole';
echo menu($nadpis,__FILE__);

$s = new TDatabase(); // vždy potřebujeme seznam studentů a škol
$sezn_stud = $s->posli_prikaz_slepe('SELECT * FROM student ORDER BY prijmeni,jmeno','přehled studentů');
if ($s->pocet_radku < 1) // je výsledek prázdný?
  die('<p>Zatím nebyl vložen žádný student. '.
      'Pokračujte <a href="./novy_student.php">vložením studenta</a>.</p>'.
      html_paticka());

$sezn_skol = $s->posli_prikaz_slepe('SELECT * FROM skola ORDER BY nazev,mesto','přehled škol');
if ($s->pocet_radku < 1) // je výsledek prázdný?
  die('<p>Zatím nebyla vložena žádná škola. '.
      'Pokračujte <a href="./nova_skola.php">vložením školy</a>.</p>'.
      html_paticka());

// pokud skript neskončil:
if ($_SERVER['REQUEST_METHOD'] == 'POST') // máme data
{ $idst = (isset($_POST['st'])) ? $_POST['st'] : '';
  $idsk = (isset($_POST['sk'])) ? $_POST['sk'] : '';
  $datum = (isset($_POST['od'])) ? $_POST['od'] : '';
  $datum_konec = (isset($_POST['do'])) ? $_POST['do'] : '';

  $chyba = array();
  // kontroly vstupů:
  if (!preg_match('@^[1-9][0-9]*$@',$idst)) // idst musí být číslo
    $chyba[] = 'Nebyl vybrán student!';
  if (!preg_match('@^[1-9][0-9]*$@',$idsk)) // idsk musí být číslo
    $chyba[] = 'Nebyla vybrána škola!';

  $datum = datum_preved($datum,'en'); // datum začátku studia je povinné
  if (!preg_match('@^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})$@',$datum,$ddd))
    $chyba[] = 'Datum je vyplněno chybně!';
  elseif (!datum_kontrola((int)$ddd[3],(int)$ddd[2],(int)$ddd[1],$ch)) // kontrola kalendářního data (Není-li ošetřeno, tak v MySQL se objeví 0000-00-00!)
    $chyba[] = $ch;
  elseif ($ddd[1]>date("Y") || $ddd[1]<1990) // rok nejméně 1990 a max. letošní!
    $chyba[] = 'Datum je vyplněno chybně (rok musí být mezi 1990 a '.date('Y').')!';

  $datum_konec = datum_preved($datum_konec,'en');
  if (!empty($datum_konec))
  { if(!preg_match('@^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})$@',$datum_konec,$dddK))
      $chyba[] = 'Datum ukončení studia je vyplněno chybně!';
    elseif (!datum_kontrola((int)$dddK[3],(int)$dddK[2],(int)$dddK[1],$ch)) // kontrola kalendářního data (Není-li ošetřeno, tak v MySQL se objeví 0000-00-00!)
      $chyba[] = $ch;
    elseif (mktime(0,0,1,(int)$dddK[2],(int)$dddK[3],(int)$dddK[1]) > time()) // datum ukončení nesmí být budoucí a dřív než začátek studia + 40 dní
      $chyba[] = 'Datum ukončení studia nesmí být z budoucnosti!';
    elseif (mktime(23,23,59,(int)$dddK[2],(int)$dddK[3],(int)$dddK[1]) <= mktime(0,0,1,(int)$ddd[2],(int)$ddd[3],(int)$ddd[1])) // datum ukončení nesmí být dřív než začátek studia
      $chyba[] = 'Datum ukončení studia nesmí dřív než začátek studia!';
  }
  
  // další kontrola: student smí školu studovat jen jednou!
  $dotaz = 'SELECT od_kdy FROM studium WHERE kdo=? AND kde=?';  
  $data = array('ii', $idst, $idsk);
  $od_kdy = $s->posli_pripr_dotaz($dotaz, $data, 'kontrola studia');
  if ($s->pocet_radku==1) // už studuje!
  { $od_kdy = datum_preved($od_kdy[1][0],'cz');
    $chyba[] = "Student již na škole studuje (od $od_kdy)!";
  }

  // bylo vše OK nebo ne?
  if (!empty($chyba)) // co když pole s chybami není prázdné?
  { echo '<p class="chyba">'.implode('<br>',$chyba). '</p>';
    echo '<p>Opravte vstupní data:</p>';
    echo f_prirazeni($idst,$idsk,$_POST['od'],$sezn_stud,$sezn_skol,$_POST['do']); // uživatel vidí, co zadal
  }
  else
  { if (!empty($datum_konec)) {
      $dotaz = 'INSERT INTO studium VALUES(?, ?, ?, ?)';
      $data = array('iiss', $idst, $idsk, $datum, $datum_konec);
    }
    else {
      $dotaz = 'INSERT INTO studium (kdo,kde,od_kdy) VALUES(?, ?, ?)';
      $data = array('iis', $idst, $idsk, $datum);
    }
    $s->posli_pripr_dotaz($dotaz, $data, 'začátek studia');
    echo "<p class=\"uspech\">Studium bylo zahájeno.</p>";
    echo f_prirazeni(0,0,'',$sezn_stud,$sezn_skol); // vypíšeme "prázdný" formulář
  }
}
else // nemáme data z formuláře
  echo f_prirazeni(0,0,'',$sezn_stud,$sezn_skol); // vypíšeme "prázdný" formulář

echo html_paticka();
