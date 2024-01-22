<?php // ukazka prace se session (prihlaseny uzivatel uvidi menu, jinak jen info)
session_start();

include './fce_html.php';

if (isset($_SESSION['prihlasen'])) // je prihlasen?
{
  $tit = "Ukázka session - menu pro přihlášené";
  $obsah = '<p>Vítejte! Jste přihlášen(a) jako: '.$_SESSION['prihlasen'].'!</p>';
  $obsah .= '<p>Vyberte si z menu:..... nebo se <a href="logout.php">odhlašte</a>.</p>';
}
else // neni prihlasen!
{ $tit = "Ukázka session - pokus o přístup do menu bez přihlášení";
  $obsah = '<p>Nejste přihlášen! <a href="login.php">Přihlaste se.</a></p>';
}
echo html_hlavicka($tit, 'utf8', '', '', 'background-color: #99FF99');
echo "<h1>$tit</h1>";
echo $obsah;
echo html_paticka();

