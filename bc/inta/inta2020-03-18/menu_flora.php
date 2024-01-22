<?php // skript fungující jako šablona HTML stránky s vkládaným obsahem
  // používá proměnnou $_GET['m'] ... číslo položky menu

$pole = array(1=> array('Úvodní stránka', 'm_uvod.html', 'úvod'),
                 array('Cibuloviny', 'm_cib.html', 'cibuloviny'),
                 // array('Keře','m_kere.html', 'keře'),
                 array('Lekníny', 'm_lekniny.html','lekníny'),
                 array('Stromy','m_stromy.html', 'stromy')
); // vícerozměrné pole pro popis stránek: index=>[nadpis stránky, vkládaný soubor, titulek]
                        
// víme, co zobrazit?
if (!isset($_GET['m']))
  $i = 1; // nikdo zatím nevybral obsah, tak zobrazíme úvod
else
  $i = $_GET['m'];
// poznámka: v PHP7 lze místo IFu využít nový operátor: $i = $_GET['m'] ?? 1;

if (!isset($pole[$i])) // kontrola vstupu -- je to platná položka menu?
  $i = 1; // neplatná položka menu => zobrazíme úvod (uživateli nevynadáme)

// připravíme si proměnné pro WWW:
$adresar = './m_flora'; // adresář pro soubory, jejichž obsah bude vkládán do stránek
$styly = array("$adresar/menu_flora.css"); // odkud bereme kaskádové styly
$titulek = "Web o rostlinách - " . $pole[$i][2]; // připravíme titulek stránky z $pole
$nadpis = "<h1>{$pole[$i][0]}</h1>"; // nadpis stránky
$jmeno_soub = $adresar . '/' . $pole[$i][1]; // odkud bude zobrazovaný obsah (cesta k souboru)
$obsah_menu = ''; // příprava
$odkaz = ''; // pomocná proměnná
foreach ($pole as $h => $prvek) // chceme indexy i prvky
{ if ($h == $i) // aktuální položka? => bude tučný s fialovým písmem (CSS)
    $odkaz = "<a href=\"menu_flora.php?m=$h\"><strong id=\"actual\">{$prvek[0]}</strong></a>"; //vložení prvku pole dovnitř řetězce: {}
  else // $h není aktuálně zobrazeno => bude to odkaz
    $odkaz = "<a href=\"menu_flora.php?m=$h\">{$prvek[0]}</a>";
  $obsah_menu .= "<div class=\"box\">$odkaz</div>"; // připojujeme ke starému textu nový text
}


// ----- vygenerujeme HTML stránku:
include'./fce_html.php';

echo html_hlavicka($titulek, 'utf8','',$styly); // přilinkujeme CSS soubor
echo '<div id="obsah">';
echo $nadpis;
echo '<a class="schovane" href="#menu">Přejít na menu.</a>'; // odkaz skrytý pomocí CSS, ale čtečky ho "uvidí"
if (!file_exists($jmeno_soub)) // co když soubor neex.?
  echo "<p>Informace momentálně nejsou dostupné.</p>";
else
  @readfile($jmeno_soub); // obsah souboru vložit dovnitř této stránky (stačilo by jen INCLUDE)
echo '</div>';

// vygenerujeme menu s využitím CSS (je poslední, ale nastylováno tak, aby se zobrazilo vlevo nahoře):
echo '<nav id="menu">';
echo $obsah_menu;
echo '</nav>';  // konec menu

echo html_paticka();
