<?php // ukázka použití session

session_start(); // chceme využít mechanismus SESSION

include "./fce_html.php"; // soubor s funkcemi pro HTML záhlaví atd.
$t = 'Stránka 1 - session';
echo html_hlavicka($t); // HTML záhlaví
echo "<h1>$t</h1>";

if (!isset($_SESSION['barva'])) { // nemáme session proměnnou
  echo "<p>Nastavuji proměnnou BARVA...</p>";
  $_SESSION['barva'] = '#FF0000'; //červená
}
echo "<p style=\"color:{$_SESSION['barva']}\">Barva textu je: {$_SESSION['barva']}</p>";

echo '<p><a href="s2.php">Chci zobrazit další stránku.</a></p>';
echo html_paticka();
