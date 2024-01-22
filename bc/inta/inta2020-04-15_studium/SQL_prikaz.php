<?php // umožní poslat libovolný příkaz SQL do databáze (mini-PhpMyAdmin)

function formular($sql)
{ // pomocná funkce pro vytvoření formuláře
  $t = '<form method="post"">';
  $t .= '<textarea name="sql" rows="10" cols="40">';
  $t .= html_escape($sql);
  $t .= '</textarea><br>';
  $t .= '<input type="submit" value="Odeslat příkaz SQL">';
  $t .= '</form>';
  return $t;
}

// samotný skript:
include_once './db_cnf.php';
include_once './fce_html.php';
include_once './fce_studium.php';  // funkce "presmeruj"

if (!defined('MOD_LADENI') || MOD_LADENI!=1) {
  presmeruj('index.php'); // pouze v módu ladění lze provádět libovolný příkaz SQL!
}
// else {}   // "else" netřeba, přesměrováním skript skončil

$tit = 'STUDIUM - libovolný příkaz SQL';
echo html_hlavicka($tit,'','',array('studium.css'));
$nadpis = 'Odeslání libovolného příkazu do DB';
echo menu($nadpis,__FILE__);

if (isset($_POST['sql']) && !empty($_POST['sql'])) {
// máme data z formuláře
  $sql = $_POST['sql'];
  include './db_class.php';
  $s = new TDatabase();
  $vysl = $s->posli_prikaz_slepe($sql,'mód ladění - libovolný příkaz');
  if (strncasecmp($sql,'SELECT',6)==0 || strncasecmp($sql,'SHOW',4)==0) { // byl to SELECT nebo SHOW?
    echo '<p>Počet záznamů: '.$s->pocet_radku .'</p>';
    if ($s->pocet_radku>0) // vypíšeme výsledek
      vypis_tabulku($vysl);
  }
  else // nebyl to SELECT, ale jiný příkaz
    echo '<p>Počet ovlivněných řádků: '.$s->pocet_radku .'</p>';
}
else // nemáme data z formuláře
  $sql = '';



echo formular($sql); // vžda vypíšeme formulář (s pův. daty nebo prázdný)
echo html_paticka();                                                     
