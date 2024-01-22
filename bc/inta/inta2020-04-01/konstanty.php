<?php // ukázka práce s konstantami

// definice 2 uživatelských konstant:
define('MOJE_KONSTANTA','ahoj');
define('CISLO',12);
// globální proměnná skriptu:
$t = 'Konstanty';

include "./fce_html.php"; // soubor s funkcemi pro HTML zahlavi atd.


// -- generování WWW:
echo html_hlavicka($t); // HTML zahlavi
echo "<h1>$t</h1>";
echo "<p>Výpis konstanty MOJE_KONSTANTA: " . MOJE_KONSTANTA . "</p>"; // všimněte si rozdílu: název konstanty uvnitř/mimo uvozovky

echo '<h2 id="konst">Přehled konstant, které skript vidí:</h2>';
echo '<pre>'; // pro hezčí výpis (konce řádků by byly zobrazeny jako mezera!)
print_r(get_defined_constants()); // print_r(get_defined_constants(true));
echo '</pre>';

echo html_paticka();
