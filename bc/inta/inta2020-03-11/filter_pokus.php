<?php

include './fce_html.php'; // funkce: html_hlavicka, html_paticka, html_escape

// připravíme proměnné pro sestavení WWW stránky:
$titulek = 'Rozšíření "filter"'; // titulek WWW stránky
$styl = 'ul {
    list-style-type: disc;
    -webkit-columns: 3;
    -moz-columns: 3;
    columns: 3;
    list-style-position: inside;
}
  body {
    background-color:#E7E7FF;
}
  .modra {
    color: #0000FF;
    font-style: normal;
}'; // CSS pro třísloupcový vzhled odrážkového seznamu, tj. <ul> + barva pozadí stránky světlemodrá + modré texty
$URL_skriptu = $_SERVER['REQUEST_SCHEME'] . '://' . $_SERVER['SERVER_NAME'] . '/' . $_SERVER['PHP_SELF']; // URL tohoto skriptu

// generujeme výstup v HTML:
echo html_hlavicka($titulek,'utf-8','',$styl); // začátek HTML, přidané styly
echo "<h1>$titulek</h1>"; // nadpis

// pokus s funkcí FILTER_LIST():
echo '<h4>Seznam filtrů:</h4>';
$pole = filter_list();
echo '<ul><li>' . implode('</li><li>',$pole) . '</li></ul>'; // vytiskne odrážkový seznam jmen filtrů, nastylovaný do 3 sloupců

// pokusy s funkcí FILTER_ID():
echo '<h4>ID filtru</h4>';
$jmeno="unsafe_raw";
$id=filter_id($jmeno);
echo "<p>Číslo (ID) filtru '$jmeno' " . ($id==FALSE ? "neexistuje!" : "je $id.") . '</p>';
$jmeno="muj_filtr";
$id=filter_id($jmeno);
echo "<p>Číslo (ID) filtru '$jmeno' " . ($id==FALSE ? "neexistuje!" : "je $id.") . '</p>';

// pokusy s funkcí FILTER_HAS_VAR():
echo '<h4>GET-data</h4>';
$_GET['test'] = 1; // pokud není součástí dotazu v URL proměnná 'test', tak není chápána jako "vstupní" => následující odpověď bude "NE"!
echo '<p>Existuje $_GET["test"]? <em class="modra">' . (filter_has_var(INPUT_GET, 'test') ? 'ANO' : 'NE') . '</em></p>';
echo '<p>Existuje $_POST["test"]? <em class="modra">' . (filter_has_var(INPUT_POST, 'test') ? 'ANO' : 'NE') . '</em></p>'; // POST-proměnná určitě skriptu nepřišla
echo '<p>Použijte odkaz: <a href="' . $URL_skriptu . '?promenna=&promenna2=pokus">tento skript s GETproměnnou</a> a všimněte si, jak se změní dolní řádek! (Podle URL. Můžete i doplnit proměnnou "test" do URL.)</p>';
echo '<p>Existuje $_GET["promenna"]? <em class="modra">' . (filter_has_var(INPUT_GET, 'promenna') ? 'ANO' : 'NE') . '</em></p>';

// pokus s funkcemi FILTER_INPUT() a FILTER_VAR():
echo '<h4>filter_input()</h4>';
$vzor = '?text=' . filter_var('pokusný text #10, kde zkoušíme, jak se zobrazí "3.14<9.1" v HTML. A jiné znaky: &\^$%', FILTER_SANITIZE_ENCODED); // escapujeme hodnotu pro URL
$vysledek = filter_input(INPUT_GET, 'text', FILTER_SANITIZE_SPECIAL_CHARS); // escapujeme vstupní proměnnou $_GET['text'] pro HTML
if ($vysledek===FALSE)
  echo '<p>$_GET["text"] nelze escapovat pro HTML! <a href="' . $URL_skriptu . $vzor . '">Použijte odkaz</a> pro korektní vstup.</p>';
elseif ($vysledek===NULL)
  echo '<p>$_GET["text"] není zadán. <a href="' . $URL_skriptu . $vzor . '">Použijte odkaz</a>, aby se výstup změnil.</p>';
else
  echo "<p>Byl zadán tento text: <em class='modra'>$vysledek</em> (porovnejte jej s URL).<br>K další změně můžete využít <a href=\"$URL_skriptu\">odkaz bez parametrů</a>.</p>";

echo html_paticka(); // konec HTML