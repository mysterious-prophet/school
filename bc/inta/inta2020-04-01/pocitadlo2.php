<?php // počítadlo přístupů blokující inkrementaci po dobu 25 minut

// nastavení a odeslání hlaviček HTTP:
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
// header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
// header("Pragma: no-cache");
header("Cache-Control: no-cache, must-revalidate");

// zjistíme existenci $_COOKIE['pocitan']
if (isset($_COOKIE['pocitan'])) // už tu klient byl?
  $zapis = 0; // uz nezapočítáme přístup  (ale nemáme uložen ten starý údaj o počtu přístupů! Nevadí, bude se to měnit podle obsahu souboru...)
else
{ $_COOKIE['pocitan']=1; // inicializujeme cookie
  setcookie('pocitan','1',time()+60*25,'/'); // odesle prohlizeci cookie
  // před jejím voláním skript NESMÍ generovat výstup! (nebo output_buffering)
  $zapis = 1; // připočteme jako nový přístup
}

// ---- generujeme WWW, ale "špagetově" (smícháno s logikou):
include './fce_html.php';
$titulek = 'Počítadlo (využívající COOKIE)';
echo html_hlavicka($titulek);
echo '<h1>Počítadlo přístupů</h1>';

$jmeno = "./pocet/pocet2.dat"; // využíváme soubor "pocet2.dat"
if (!file_exists($jmeno)) // zatím nebyly žádné přístupy
{ $kolik = 1; // flag $zapis nás tentokrát nezajímá
  @$fp = fopen($jmeno, "w"); // zkusíme vytvořit nový soubor
  if (!$fp) // nelze vytvořit
    die('<p>Nelze založit počítadlo.</p>' . html_paticka()); // konec
  flock($fp, LOCK_EX); // zamkneme soubor
  if (!@fwrite($fp, "1")) { // byl zapsán 1. přístup?
    flock($fp, LOCK_UN);
    die("<p>Byl jste $kolik. návštěvník, ale nemohu počítadlo aktualizovat!</p>" . html_paticka());
  }
  flock($fp, LOCK_UN); // odemknout soubor
  fclose($fp);
}
else // už existuje soubor "pocet1.dat"
{ // otevřeme soubor pro čtení i zápis
  @$fp = fopen($jmeno, "r+"); // zkusíme otevřít pro čtení a zápis
  if (!$fp) // nelze otevřít
    die('<p>Nelze zjistit počet přístupů.</p>' . html_paticka()); // konec
  flock($fp, LOCK_EX); // zamkneme soubor
  fscanf($fp,"%d",$kolik); // načteme cele číslo
  if ($zapis == 1)
  { $kolik++; // zvětším počet přístupů
    rewind($fp); // přesuneme ukazatel zpět na začátek souboru
    if (!@fwrite($fp, "$kolik ")) {// lze zapsat?
      flock($fp, LOCK_UN);
      die("<p>Byl jste $kolik. návštěvník, ale nemohu počítadlo aktualizovat!</p>" . html_paticka());
    }
  }
  flock($fp, LOCK_UN); // odemknout soubor
  fclose($fp);
}

// hodnota počítadla:
echo "<p>Jste $kolik. návštěvník.</p>";

echo html_paticka();
