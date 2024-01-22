<?php
include './fce_html.php'; // funkce pro generování HTML záhlaví apod.
$skript = 'slova_razeni.php'; // jméno tohoto skriptu (použijeme jej vícekrát)

echo html_hlavicka('Slova razeni');
if ($_SERVER['REQUEST_METHOD'] != 'POST') {
  echo '<h1>Slova - zadání nových</h1>';
  echo '<form action="'.$skript.'" method="post">';
  echo '<ol type="1">';
  for ($i=1; $i<=15; $i++)
	  echo '<li><input type="text" name="slova[]"></li>';
  echo '</ol>';
  echo '<input type="submit" value="Odeslat">';
  echo '</form>';
}
elseif (isset($_POST['slova']) && is_array($_POST['slova'])) { // metoda POST; máme správná data z formuláře?
  echo '<h1>Slova - zpracování</h1>';
  echo '<p>Zadal(a) jste:</p><ol type="1">';
  foreach($_POST['slova'] as $slovo) // lze zjednodušit: join + array_walk
    echo '<li>', html_escape($slovo), '</li>'; // echo '<li>', htmlentities($slovo), '</li>';  NEBO filter_input(...)
  echo '</ol>';
  //razeni
  $slova_seraz = sort($_POST['slova']);
  echo '<p>Serazena slova: </p><ol type="1">';
  foreach($slova_seraz as $slovo_seraz)
	echo '<li>', html_escape($slovo_seraz), '</li>';
  echo '</ol>';
  echo "<p>Vyplnit <a href=\"$skript\">formulář</a> znovu.</p>";
}
else {
  echo '<p>Nastala chyba při načítaní pole dat.</p>';
  echo "<p><a href=\"$skript\">Zadat data</a> korektně.</p>";
}
echo html_paticka();
?>