<?php // výpis škol; smí dostat: o={1,2} (číslo sloupce v DB: o+1), a={1,0} (ASC, DESC)

include "./fce_studium.php"; // např. přesměr., menu,...
include "./fce_html.php"; // html záhlaví,...

$tit = 'STUDIUM - výpis škol';
echo html_hlavicka($tit,'','',array('studium.css'));
$nadpis = 'Výpis seznamu škol';
echo menu($nadpis,__FILE__);

// ošetříme vstupy z URL:
if (isset($_GET['o'])) // máme kritérium řazení
  $o = $_GET['o'];
else
  $o = 2; // implic. řadíme dle názvu školy
if ($o!=1 && $o!=2 && $o!=3) // nepovolený vstup!
  $o = 2; // implic. řadíme dle názvu školy

if (isset($_GET['a'])) // jak řadit (vzest., sest.)
  $a = $_GET['a'];
else
  $a = 1; // implic. řadíme vzestupně
if ($a!=0 && $a!=1)
  $a = 1; // implic. řadíme vzestupně

// výpis dat z DB
$razeni = array(1=>'nazev','zkratka','mesto');
$ord = array('DESC','ASC'); // indexy: 0,1
$serad = $razeni[$o];
$jak = $ord[$a];

include "./db_class.php";
$s = new TDatabase();
$tab = $s->posli_prikaz_slepe("SELECT * FROM skola ORDER BY $serad $jak");
if ($s->pocet_radku < 1) // je výsledek prázdný?
  echo '<p>Zatím nebyla vložena žádná škola. 
        Pokračujte <a href="./nova_skola.php">vložením školy</a>.</p>';
else // máme řádky => ve výsledku přepíšeme názvy sloupců a vynecháme ID
{ echo '<p>Počet škol: '.$s->pocet_radku.'.</p>';
  vypis_tabulku($tab,0,tabulka_zahlavi(array(1=>'Název','Zkratka','Sídlo'),__FILE__,$o,$a));
  // ^-- použijeme funkci z "fce_studium.php", z výpisu odstraňujeme 'idst' (sloupec 0)
  
}
echo html_paticka();
