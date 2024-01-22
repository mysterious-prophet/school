<?php // index.php = úvodní stránka miniaplikace STUDIUM

include "./fce_studium.php"; // např. přesměr., menu,...
include "./fce_html.php"; // html záhlaví,...

$tit = 'STUDIUM - úvodní strana';
echo html_hlavicka($tit,'','',array('studium.css'));
$nadpis = 'Miniaplikace STUDIUM';
echo menu($nadpis,__FILE__);

echo '<p>Vítejte na stránkách miniaplikace STUDIUM, 
kde můžete vkládat nové studenty a nové školy,
přiřazovat studenta na školu, vypisovat přehled škol
nebo vypisovat přehled studentů.</p>';

echo html_paticka();
