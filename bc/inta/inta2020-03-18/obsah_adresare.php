<?php // výpis obsahu aktuálního adresáře (= ten, kde je na serveru uložen tento skript)
$css = 'table { border-collapse: collapse; }
table, th, td { border: 1px solid black; }'; // CSS pro rámečky v tabulce

include './fce_html.php';
echo html_hlavicka('Obsah adresáře','utf-8','',$css);

$dir = dirname($_SERVER['SCRIPT_FILENAME']);  // aktuální adresář tohoto skriptu (ne URL adresa, ale adresa v souborovém systému)
echo "<h1>Výpis obsahu adresáře <code>$dir</code></h1>";
if(is_dir($dir)) { // je to adresář? (Měl by být.)
  if ($pole = @scandir($dir)) { // pokus o otevření adresáře
    echo '<table>'; // tabulkový výpis položek
    echo '<tr><th>Jméno</td><td>Typ</td></tr>';
    foreach($pole as $s)
      if ($s != "." && $s != "..") { // vynecháme adresáře . a ..
        if (is_dir($dir.'/'.$s)) // je to (pod)adresář?
          echo "<tr><td><strong>$s</strong></td>"; // podadresáře vypíšeme tučně
        else
          echo "<tr><td>$s</td>"; // ostatní položky (tj. soubory, linky apod.) obyčejně
        echo "<td>" . filetype($dir .'/'. $s) ."</td></tr>"; // typ souboru v OS
      }
    echo '</table>';
  }
  else
    echo "Adresář nelze číst!";
}

echo html_paticka();
