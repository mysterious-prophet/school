<?php // použití session

session_start(); // chceme využít mechanismus SESSION

include "./fce_html.php"; // soubor s funkcemi pro HTML záhlaví atd.
$t = 'Stránka 2 - session';
echo html_hlavicka($t); // HTML záhlaví
echo "<h1>$t</h1>";

if (!isset($_SESSION['barva'])) // máme už nastavenou nějakou barvu?
  echo "<p>Barva textu je černá, zatím nebyl použit skript <a href=\"s1.php\">s1.php</a>.</p>";
else
  echo "<p style=\"color:{$_SESSION['barva']}\">Barva textu je: {$_SESSION['barva']}</p>"; // máme nastaveno od s1.php

$_SESSION['barva'] = '#0000FF'; // změna barvy na modrou
echo "<p style=\"color:{$_SESSION['barva']}\">Tímto skriptem nastavená barva textu je: {$_SESSION['barva']}</p>";

echo '<p><a href="s1.php">Chci zobrazit předchozí stránku.</a></p>';
echo html_paticka();
