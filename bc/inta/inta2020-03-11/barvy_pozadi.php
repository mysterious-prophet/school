<?php /* výpis bezpečných barev na zvoleném pozadí (posláno metodou GET protokolu HTTP).
         Skript do stává proměnnou 'jmb' poslanou metodou GET => KONTROLY!!! */

// ověření vstupu skriptu + nastavení implicitní hodnoty, pokud je chybný vstup
if (isset($_GET['jmb'])) // máme barvu? Lze též využít filter_has_var()
	$barva = $_GET['jmb']; // "přejmenujeme" proměnnou (kratší název)
else // nemáme barvu => bílé pozadí
	$barva = 'FFFFFF'; // implicitně bílá barva
if (!preg_match('/^[0-9a-f]{6}$/i',$barva)) // regulární výraz: obsahuje barva šestici hexadecimálních čísel?
  $barva = 'FFFFFF'; // barva nemá 6 znaků => nastavíme barvu na bílou
// else // barva má správný formát, ponecháme hodnotu ze vstupu (řádek 6)
// konec kontrol => měli bychom mít korektní HEXA kód barvy

include './fce_html.php'; // funkce pro HTML záhlaví a zápatí
// pomocné proměnné (pro HTML):
$tit = 'Barva '.$barva;
$vstupHTML = filter_input(INPUT_GET,'jmb',FILTER_SANITIZE_SPECIAL_CHARS); // pomocná proměnná pro výpis vstupu ($_GET['jmb']) do HTML 
$informace = "<p>Zadaná vstupní barva: <strong>$vstupHTML</strong><br>Zobrazovaná barva: <strong>$barva</strong></p>"; // pomocný text 
$odkaz = '<p><a href="barvy.php" title="tabulka bezpečných barev">Přehled bezpečných barev</a> (tabulka).</p>'; // pomocná proměnná (odkaz)
$tip = '<p>Tip: zkuste v URL změnit kód barvy např. na <strong>A81c9f</strong> (funguje) nebo na <strong>HOKEJ&lt;em&gt;</strong> (chyba, bude bílé pozadí).</p>'; // pomocný text 

// generování HTML:
echo html_hlavicka($tit);                                   
echo "<h1>$tit</h1>";
echo $informace, $tip, $odkaz; // výpis pomocných proměnných
echo '<div style="background-color:#'.$barva.'; -webkit-columns: 6; -moz-columns: 6; columns: 6;">'; // obarveno pozadí, 6 sloupců
for ($r=0x00; $r<=0xFF; $r+=0x33) // red = červená barva
	for ($g=0x00; $g<=0xFF; $g+=0x33) // green = zelená barva
		for ($b=0x00; $b<=0xFF; $b+=0x33) { // blue = modrá barva
			$barva_jm = sprintf('%02X%02X%02X',$r,$g,$b);
			echo '<p style="color:#'.$barva_jm.'">Text v barvě <strong>';
			echo $barva_jm.'</strong>.</p>';
		}
echo '</div>';
echo $odkaz; // odkaz ještě jednou
echo html_paticka();
?>