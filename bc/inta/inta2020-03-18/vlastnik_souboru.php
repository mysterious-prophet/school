<?php // skript pro vytvoření souboru 'pokus.dat' v adresáři 'pocet' + výpis informací o tomto souboru (uživatel, skupina)

$jmeno = "./pocet/pokus.dat"; // vytvářený soubor (pomocí PHP)
if (!@file_exists($jmeno)) { // co když neexistuje soubor $jmeno?
  if ($fp = @fopen($jmeno,'w')) { // pokus o vytvoření souboru
    @fwrite($fp,'Soubor vytvořený pomocí PHP.'); // zapíšeme text
    fclose($fp); // soubor zavřeme
  }
  else
    $chyba = "Soubor <code>$jmeno</code> se nepodařilo vytvořit. Zkontrolujte, zda existuje adresář <code>./pocet</code> s právem zápisu pro 'ostatní'!";
}
// else ... když už soubor existuje, tak ho nebudeme vytvářet

if (!isset($chyba)) { // pokud nenastala chyba, tak zkusíme zjistit vlastníka souboru + skupinu
  // vlastník souboru (možná nepůjde zjistit!)
  $user = fileowner($jmeno); // číslo vlastníka
  if (function_exists('posix_getpwuid')) {
    $u = posix_getpwuid($user); // pole údajů o uživateli
    $username = $u['name']; // jméno uživatele
  }
  else
    $username = '<em>nelze zjistit</em>';
  // skupina (možná nepůjde zjistit!)
  $group = filegroup($jmeno); // číslo skupiny
  if (function_exists('posix_getgrgid')) {
    $g = posix_getgrgid($group);  // pole údajů o skupině
    $groupname = $g['name']; // jméno skupiny
  }
  else
    $groupname = '<em>nelze zjistit</em>';
}

// ------------- závěrečný výpis informací (HTML kód):
include './fce_html.php';
echo html_hlavicka('Informace o souboru');
if (isset($chyba)) // pokud se soubor nepodařilo vytvořit, tak existuje $chyba
  echo "<p>$chyba</p>";
else {
  echo "<p>Vlastníkem souboru <code>$jmeno</code> je $username ($user), skupina: $groupname ($group).</p>";
  echo "<p>Stejné údaje získáte z vlastností souboru <code>$jmeno</code> (v prohlížeči souborů)...</p>";
}
echo html_paticka();
