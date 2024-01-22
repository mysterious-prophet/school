<?php // ukázka práce s objekty - vytvoření dvou tříd, jedné instance první třídy, spuštění metody + výpis všech tříd, které by se daly ve skriptu použít

class MojeTrida {
  // členské proměnné:
  public $a = "p_A";
  private $b = 'ahoj';
  // metody:
  public function __construct($h1,$h2) { // konstruktor
    $this->a = $h1; // bez kontrol spravnosti!!!
    $this->b = $h2; // bez kontrol spravnosti!!! 
  }
  public function vypis_a() {
    echo $this->a;
  }
  private function zmen_b($h) {
    $this->b = $h; // bez kontrol spravnosti!!!
  }
}

class MojeTrida2 {
  // členské proměnné:
  private $a;
  public $b = 'ahoj', $c = 7;
  // metody:
  public function __construct($v1, $v2='ahoj', $v3=7) {
    $this->a = $v1;
    $this->b = $v2; // implicitně 'ahoj'
    $this->c = $v3; // implicitně 7
  }
  public function secti() {
    $v = $this->a + $this->c;
    return $v;
  }
}

// --- výstup do HTML (kombinujeme objektový a procedurální kód):

include "./fce_html.php"; // soubor s funkcemi pro HTML zahlavi atd.
$t = 'Objekty v PHP';
echo html_hlavicka($t); // HTML zahlavi
echo "<h1>$t</h1>";

echo '<h2>Vytvoření objektu:</h2>';
$o1 = new MojeTrida('u','v');
if (method_exists($o1,'vypis_a')) {
  echo 'Výsledek volání metody "vypis_a():" ';
  $o1->vypis_a();
}
echo '<h3>Hodnoty veřejných vlastností objektu $o1:</h3>'; //  před změnou $b
echo implode('<br>',get_object_vars($o1)); // výpis vlastností objektu $o1
/* $o1->zmen_b('w'); // NELZE!!! Fatal error: Uncaught Error: Call to private method MojeTrida::zmen_b()
echo '<h3>Vlastnosti objektu po změně $b:</h3>';
implode('<br>',get_object_vars($o1)); // výpis vlastností objektu $o1
*/
$jmeno_tridy ='MojeTrida';
echo "<h3>Hodnoty veřejných vlastností třídy '$jmeno_tridy':</h3>";
echo implode('<br>',get_class_vars($jmeno_tridy)); // výpis vlastností třídy MojeTrida
echo "<h3>Veřejné metody třídy '$jmeno_tridy':</h3>";
echo implode('<br>',get_class_methods($jmeno_tridy)); // výpis metod třídy MojeTrida

echo '<h2>Seznam VŠECH tříd, které má skript k dispozici:</h2>';
echo implode('<br>',get_declared_classes()); // výpis všech tříd
/* // alternativní kód:
$jmenatrid = get_declared_classes();
foreach ($jmenatrid as $jmeno)
  echo "$jmeno<br>"; */

echo html_paticka();
