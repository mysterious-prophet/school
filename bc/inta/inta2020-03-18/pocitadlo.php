<?php  // využíváme soubor 'pocet1.dat' v adresáři 'pocet', zamykáme jej
  // Problém: KAŽDÝ přístup se počítá, přestože jde o tentýž prohlížeč (zkuste znovunačíst/obnovit WWW stránku).

function konec($soubor, $text) { // pomocná fce pro odemčení souboru a jeho uzavření a konec skriptu
  flock($soubor, LOCK_UN); // odemknout soubor
  fclose($soubor);
  die($text . html_paticka());
}
// ----- skript:
include './fce_html.php';
$titul = 'Počítadlo přístupů';
echo html_hlavicka($titul,'utf8','','','background-color:#FFCC66');
echo "<h1>$titul</h1>";

$jmeno = "./pocet/pocet1.dat"; // jiný soubor pro počítadlo

if (!file_exists($jmeno)) // zatím nebyly žádné přístupy
{ $kolik = 1;
  @$fp = fopen($jmeno, "w"); // zkusíme vytvořit nový soubor
  if (!$fp) // nelze vytvořit
    die('<p>Nelze založit počítadlo.</p>' . html_paticka()); // konec
  @flock($fp, LOCK_EX); // zamkneme soubor
  if (!@fwrite($fp, "1")) // byl zapsán 1. přístup?
    konec($fp, "<p>Byl jste $kolik. návštěvník, ale nemohu počítadlo aktualizovat!</p>");
  fclose($fp);
}
else // už existuje soubor "pocet1.dat"
{ // otevřeme soubor pro čtení i zápis
  @$fp = fopen($jmeno, "r+"); // zkusíme otevřít pro čtení a zápis
  if (!$fp) // nelze otevřít
    die('<p>Nelze zjistit počet přístupů.</p>' . html_paticka()); // konec
  flock($fp, LOCK_EX); // zamkneme soubor
  fscanf($fp,"%d",$kolik); // načteme cele číslo
  $kolik++; // zvětším počet přístupů
  rewind($fp); // přesuneme ukazatel zpět na začátek souboru
  if (!@fwrite($fp, "$kolik ")) // lze zapsat?
    konec($fp, "<p>Byl jste $kolik. návštěvník, ale nemohu počítadlo aktualizovat!</p>");
  fclose($fp);
}
// hodnota počítadla ve všech případech:
echo "<p>Jste $kolik. návštěvník.</p>";

echo html_paticka();
