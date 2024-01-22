<?php 
include './fce_html.php'; // funkce pro generování HTML záhlaví apod.
echo html_hlavicka('barvy2v1');                                
echo "<h1>barvy2v1</h1>";

if (isset($_GET['jmb']))
	$barva = $_GET['jmb'];
	$vstupHTML = filter_input(INPUT_GET,'jmb',FILTER_SANITIZE_SPECIAL_CHARS); // pomocná proměnná pro výpis vstupu ($_GET['jmb']) do HTML 
	$informace = "<p>Zadaná vstupní barva: <strong>$vstupHTML</strong><br>Zobrazovaná barva: <strong>$barva</strong></p>"; // pomocný text 
	$tip = '<p>Tip: zkuste v URL změnit kód barvy např. na <strong>A81c9f</strong> (funguje) nebo na <strong>HOKEJ&lt;em&gt;</strong> (chyba, bude bílé pozadí).</p>'; // pomocný text 

	echo $informace, $tip; // výpis pomocných proměnných
	echo '<div style="background-color:#'.$barva.'; -webkit-columns: 6; -moz-columns: 6; columns: 6;">'; // obarveno pozadí, 6 sloupců
	for ($r=0x00; $r<=0xFF; $r+=0x33) // red = červená barva
		for ($g=0x00; $g<=0xFF; $g+=0x33) // green = zelená barva
			for ($b=0x00; $b<=0xFF; $b+=0x33) { // blue = modrá barva
				$barva_jm = sprintf('%02X%02X%02X',$r,$g,$b);
				echo '<p style="color:#'.$barva_jm.'">Text v barvě <strong>';
				echo $barva_jm.'</strong>.</p>';
			}
	echo '</div>';

else{ 	
	for ($r=0x00; $r<=0xFF; $r+=0x33) { // červená barva
		echo '<table>';
		for ($g=0x00; $g<=0xFF; $g+=0x33) { // zelená barva
			echo '<tr>';
			for ($b=0x00; $b<=0xFF; $b+=0x33) { // modrá barva
				$barva2 = sprintf('%02X%02X%02X',$r,$g,$b); 
				echo sprintf('<td style="background-color: #%s"></td>',$barva2); 
			}
			echo '</tr>';
		}
		echo '</table><br>';
	}
}

echo '</body></html>';
?>