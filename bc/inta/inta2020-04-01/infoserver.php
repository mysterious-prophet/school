<?php // výpis superblobálního pole $_SERVER

$t = 'Informace o serveru';
$css = '
table {border-collapse: collapse;}
td {border: 1px solid black;}
tr:nth-child(odd) {background-color: #CCE7FF;}
tr:nth-child(even) {background-color: #80CCFF;}
'; // styly pro tabulku

include "./fce_html.php"; // soubor s funkcemi pro HTML zahlavi atd.


// -- generování WWW:
echo html_hlavicka($t,'utf8','',$css); // HTML zahlavi
echo "<h1>$t</h1>";

echo '<table>'; // výpis do tabulky (CSS v záhlaví)
foreach ($_SERVER as $vlastnost => $hodnota)
  echo "<tr><td>$vlastnost</td><td>" . html_escape($hodnota) . "</td>";
echo '</table>';

echo html_paticka();
