<?php

include './db_class.php';
include './fce_html.php';

echo html_hlavicka('Vytvoření DB tabulek');
$objektDB = new TDatabase(); // při chybě skript končí

$DB_tabulky = $objektDB->posli_prikaz_slepe('SHOW TABLES'); // 1. řádek je záhlaví, pak jsou jména tabulek

$hezci_tabulky = array();
foreach ($DB_tabulky as $i=>$zaznam) {
  if ($i==0) // záhlaví vynecháme!
    continue;
  $hezci_tabulky[] = $DB_tabulky[$i][0]; // jméno existující tabulky v DB
}

// v poli "hezci_tabulky" by měly být 3 jména, pokud už jsou tabulky v DB vytvořeny
if (count($hezci_tabulky)<3) { // nemáme tam všechny tabulky!
  $soubor = './DB/studium_tabulky.sql';
  if (file_exists($soubor)) {
    $obsah = file_get_contents($soubor); // načtu soubor do řetězce
    $prikazy = explode(';',$obsah);
  }
  else
    die('Při instalaci nastala chyba.'.html_paticka());

  $k = 1; // budeme počítat zpracované příkazy
  foreach ($prikazy as $sql) {
    $sql = trim($sql);
    if (empty($sql))
      continue; // prázdný (poslední) příkaz neprovádíme
    $shodne = '';
    @preg_match('/^CREATE +TABLE +([^ (]+)/iu',$sql,$shodne); // jméno vytvářené tabulky
    if (!in_array($shodne[1],$hezci_tabulky)) { // co když už tu tabulku máme v DB?
      $objektDB->posli_prikaz_slepe($sql,"Vytvoření $k. tabulky.");
      echo "<p>Byla vytvořena $k. tabulka.</p>";
      $k++;
    } // else ... tiše mlčíme
  }
}

echo '<p>Instalace tabulek je hotová.</p>';
echo html_paticka();
