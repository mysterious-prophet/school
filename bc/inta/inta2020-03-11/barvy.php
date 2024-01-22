<?php
include './fce_html.php';

$titulek = 'Bezpečné barvy';
$css = 'td {font-family: monospace}
a {text-decoration: none; color: black}'; // CSS pro <td> a <a> (odkazy nepodtržené a černé) 
echo html_hlavicka($titulek,'utf-8','',$css);
echo "<h1>$titulek</h1>";

for ($r=0x00; $r<=0xFF; $r+=0x33) { // červená barva
  echo '<table>';
  for ($g=0x00; $g<=0xFF; $g+=0x33) { // zelená barva
    echo '<tr>';
    for ($b=0x00; $b<=0xFF; $b+=0x33) { // modrá barva
      $barva = sprintf('%02X%02X%02X',$r,$g,$b); // jméno barvy (šestice znaků), např. 00FF66 (nikoli 0FF66)
      $url = "barvy_pozadi.php?jmb=$barva"; // URL skriptu, který zobrazí barvy na zadaném pozadí, dostane $_GET['jmb']
      echo sprintf('<td style="background-color: #%s"><a href="%s">%s</a></td>',$barva,$url,$barva); // barevná buňka s textem barvy jako odkaz jinam
    }
    echo '</tr>';
  }
  echo '</table><br>';
}
  
echo html_paticka();