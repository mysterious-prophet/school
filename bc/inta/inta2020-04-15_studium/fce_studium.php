<?php // pomocné funkce pro miniaplikaci STUDIUM

// konstanty pro grafický vzhled řazení:
define ('ordASC','<div class="sipka nahoru"></div>');
define ('sortASC','<div class="sipka nahoruT"></div>'); // aktuálně seřazeno vzest.
define ('ordDESC','<div class="sipka dolu"></div>'); 
define ('sortDESC','<div class="sipka doluT"></div>'); // aktuálně seřazeno sest.

function menu($nadpis,$skript)
{ // vypisuje menu a podle jména skriptu označí aktuálně vybranou položku

  include_once './db_cnf.php'; // kvůli tomu, zda je/není zapnutý mód ladění
  // vždy dostupné položky menu:
  $skripty = array('index.php'=>'Hlavní strana',
                   'novy_student.php' => 'Nový student',
                   'nova_skola.php' => 'Nová škola', 
                   'student_skola_zacni.php' => 'Nové studium',
                   // 'student_skola_konci.php' => 'Konec studia',
                   'vypis_studentu.php' => 'Výpis studentů',
                   'vypis_skol.php' => 'Výpis škol'); // povolené položky menu pro ostrý provoz
  // v módu ladění navíc může být volán také SQL_dotaz.php:
  if (defined('MOD_LADENI') && MOD_LADENI==1)
    $skripty['SQL_prikaz.php'] = 'Odeslání příkazu SQL'; 

  // kontrola vstupu:
  $skript = basename($skript); // jméno skriptu
  if (!isset($skripty[$skript])) // nejde o "povolený" skript!
    $skript = 'index.php'; // implicitně na hl. stranu aplikace                 
  $t = '<nav><ul id="menu">';
  foreach ($skripty as $s=>$jm)
  { if ($s==$skript)
      $styl = ' id="akt"';
    else
      $styl = ''; 
    $t .= "<li $styl><a href=\"./$s\">$jm</a></li>";
  } 
  $t .= '</ul></nav>';
  $t .= "<h1>$nadpis</h1>";

  return $t;
}

/*
function presmeruj($soubor) 
{
  $URL = $_SERVER['SERVER_NAME']  . dirname($_SERVER['PHP_SELF']) . '/'. $soubor;
  header("Location: http://$URL");
  exit; // konec skriptu
} */



function tabulka_zahlavi($nazvy,$skript,$o,$a)
{ // vrací pole, kde k názvům přidá odkaz na vzestupné/sestupné řazení záznamů z DB
  // volání: tabulka_zahlavi(array('Jméno','Příjmení','Datum narození'),"vypis_studentu.php",2,0));
  $zahlavi = $nazvy; // příprava
  $jmeno_skriptu = basename($skript); // jméno "hlavníhho" skriptu
  foreach ($nazvy as $k=>$nazev) {
    $odkazasc = "<a href=\"$jmeno_skriptu?o=$k&a=1\">".ordASC.'</a>'; // využití konstanty
    $odkazdesc = "<a href=\"$jmeno_skriptu?o=$k&a=0\">".ordDESC.'</a>'; // využití konstanty
    if ($k == $o) { // řadilo se dle tohoto sloupce?
      if ($a==1) // řadilo se vzest. dle tohoto sloupce
        $odkazasc = sortASC;
      elseif ($a==0) // řadilo se sestupně dle tohoto sloupce
        $odkazdesc = sortDESC;
    }
    $zahlavi[$k] .= " $odkazasc$odkazdesc"; // doplnění odkazů ke jménu sloupce
  }
  return $zahlavi;
}


function datum_preved($udaj,$format='cz')
{ // převádí datum $udaj (z formátu RRRR-MM-DD nebo DD.MM.RRRR)
  // do formátu nového: "cz" (DD. MM. RRRR) nebo "en" (RRRR-MM-DD)
  // !!! pokud vstupem není datum, funkce nechá $udaj nezměněn !!!

  switch ($format)
  { case 'cz': // chceme získat datum v "českém" formátu, předp., že je v anglickém
      if (preg_match('@^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})$@',$udaj,$d))
        $udaj = "$d[3]. $d[2]. $d[1]";
      break;
    case 'en':
      if (preg_match('@^([0-9]{1,2})\. *([0-9]{1,2})\. *([0-9]{4})$@',$udaj,$d))
        $udaj = "$d[3]-$d[2]-$d[1]";
      break;
    // default:
  }
  return $udaj;
}


function datum_zmena_pole(&$polozka_pole, $index)
{ // funkce, která změní položku pole obsahující "anglické datum" na "české datum"
  // bude to voláno v rámci array_walk()
	$polozka_pole = datum_preved($polozka_pole);
}

function datum_kontrola($den,$mesic,$rok,&$chyba)
{ // funkce pro kontrolu kalendářního data $udaj:
  // - dní v měsíci musí být správný počet
  // - přestupný únor <=> rok je dělitelný 4 nebo 400, ale ne 100

  $kontr_mesic31 = array(1,3,5,7,8,10,12); // měsíce s 31 dny 
  if (in_array($mesic,$kontr_mesic31) && ($den>31 || $den<1)) // měsíc nesmí mít nad 31 dní
  { $chyba = 'Zadaný den v měsíci neexistuje!';
    return 0;
  }
  $kontr_mesic = array(4,6,9,11); // měsíce s 30 dny 
  // "hrubá" kontrola: rok mezi 1930 až 2099, měsíc 1-12, den 1-31
  if (in_array($mesic,$kontr_mesic) && ($den>30 || $den<1)) // měsíc nesmí mít nad 30 dní
  { $chyba = 'Zadaný den v měsíci neexistuje!';
    return 0;
  }
  if ($mesic==2)
    if ($den>29 || $den<1) // nelze!
    { $chyba = 'Zadaný den v měsíci neexistuje!';
      return 0;
    }
    elseif ($den==29 && $rok%4>0 || ($rok%100==0 && $rok%400>0)) // přestupný únor: rok je děl. 4 nebo 400, ale ne 100
    { $chyba = "V roce $rok nebyl únor přestupný!";
      return 0;
    }
  return 1; // pokud fce neskončila, tak je vše OK
}


function vypis_tabulku($data, $vynechat=-1, $nazvy=array())
{ // $data ... tabulka (array of arrays), první řáděk je záhlaví (jména sloupců z DB), další řádky jsou data
  // $vynechat ... číslo (jednoho) sloupce, který bude ve výpisu vynechán (0,1,2,...). Pro $vynechat=-1 se nevynechá nic
  // $nazvy ... pole (array), které obsahuje záhlaví tabulky pro HTML (není vhodné zveřejňovat na webu názvy sloupců z DB)
  echo '<table>';
  foreach($data as $i=>$zaznam) {
    // převod EN na CZ u kalendářního data (je-li v poli obsaženo)
	array_walk($zaznam, 'datum_zmena_pole'); // změna formátu, pokud je ve tvaru YYYY-MM-DD
    // vynechání sloupce, kde je "id"
	if ($vynechat>=0) {
	  unset($zaznam[$vynechat]);
	}
	// výpis do tabulky:
    if ($i==0)
	  if (!empty($nazvy) && count($nazvy) == count($zaznam)) // nahradím DB názvy za ty vstupní
	    echo '<tr><th>'.implode('</th><th>',$nazvy).'</th></tr>'; // zahlavi podle 2. vstupu
	  else
        echo '<tr><th>'.implode('</th><th>',$zaznam).'</th></tr>'; // zahlavi
    else        
      echo '<tr><td>'.implode('</td><td>',$zaznam).'</td></tr>'; // zahlavi
  }     
  echo '</table><br><br>';
}
