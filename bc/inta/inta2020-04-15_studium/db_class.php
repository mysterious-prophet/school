<?php // db_fce.php = třída pro práci s databází MySQL

include_once './db_cnf.php'; // načtení konstant potřebných pro připojení k serveru MySQL a pro ladění (v módu ladění se vypisují chyby od DBS, jinak "obecné" texty) + jméno LOG-souboru, kam se zapisují všechny prováděné činnosti

class TDatabase
{
// konstanty:
  const ZS = ZNAKOVA_SADA; // konstanta pro znakovou sadu
  const LOG = LOG_SOUBOR; // kam se ukládají záznamy o činnosti
  const MOD = MOD_LADENI; // ladíme nebo jde o ostrý provoz?

// členské proměnné:
  protected $db; // obsahuje ID spojení s DB
  private $hlaseni; // řetězec; obsahuje poslední chybové hlášení
  private $cinnost; // řetězec; obsahuje poslední prováděnou činnost (dotaz apod.)
  public $pocet_radku; // číslo; kolik řádků bylo ovlivněno posledním příkazem, resp. vráceno posl. dotazem


// metody:
  public function __construct($db=DB_NAME,$server=SERVER,$uzivatel=USER,$heslo=PASS)
  { /* konstruktor provede připojení k DBS, 
       výběr DB a nastavení znakové sady pro
       komunikaci s DBS. Všechny úspěšné
       i neúspěšné činnosti loguje do souboru
    */
    $this->cinnost = "připojení k DB"; // co děláme?
    $this->hlaseni = "OK"; // předpoklad úspěchu
    $this->db = new mysqli($server,$uzivatel,$heslo,$db); // připojení k MySQL s výběrem DB
    if ($this->db->connect_errno) {
    // nezdařilo se připojení!
      $this->hlaseni = (self::MOD==1) ? $this->db->connect_error : 'nelze se připojit k databázi!';
      $this->loguj(); // zapíše do LOG-souboru neúspěch
      $this->vypis_chybu(); // zajistí chybové hlášení a konec skriptu
    }
    $this->loguj(); // zapíše do LOG-souboru úspěšné připojení k DB

    $this->cinnost = "nastavení znakové sady ".self::ZS;
    $this->hlaseni = "OK"; // předpoklad
    if (!$this->db->set_charset(self::ZS)) { 
    // pokus nastavit znakovou sadu pro komunikaci s MySQL
      $this->hlaseni = (self::MOD==1) ? $this->db->error : 'nelze nastavit znakovou sadu!';
      /* $this->vypis_chybu(); // nejde o fatální chybu, nezveřejníme to uživatelům */
    }
    $this->loguj(); // zapíše do LOG-souboru (ne)úspěch nastavení znakové sady
    $this->pocet_radku = 0; // inicializace členské proměnné
  }

/*  public function __destruct()
  { // destruktor provede odpojení od databáze
      $this->cinnost = "odpojení od DB"; // odpojujeme se od DB
      $this->hlaseni = 'OK'; // předpoklad
      if (!@$this->$db->close()) {
      // problém s odpojením!
        $this->hlaseni = (self::MOD==1) ? $this->db->error : 'chyba při uzavření spojení s DBS!';
        // $this->vypis_chybu(); // nejde o fatální chybu
      }
      $this->loguj(); // zapíše do LOG-souboru (ne)úspěch o odpojení
  } */

  public function posli_pripr_dotaz($sql,$hodnoty,$pozadavek='')
  { // odešle do DB příkaz/dotaz, bezpečná pro data z formulářů
    // $sql ...  řetězec obsahující SQL příkaz, kde místo hodnot jsou otazníky, např.:
    //           SELECT * FROM student WHERE prijmeni=? ORDER BY jmeno
    //           INSERT INTO skola (nazev,mesto) VALUES(?,?)
    // $hodnoty ... pole, kde 1. prvek jsou datové typy a další prvky jsou data
    //              (datové typy: "i" integer, "d" double, "s" string, "b" BLOB)
    // $pozadavek ... řetězec specifikující akci, která se měla vykonat
    // návratová hodnota: dvourozměrné pole (prvek 0 = názvy sloupců vrácených SELECTem,
    //      další prvky = záznamy. Pokud nešlo o SELECT, vrátí prázdné pole)
    $this->hlaseni = "požadavek <em>$pozadavek</em> nelze zpracovat! Zopakujte akci později."; // jsme pesimisté
    $this->cinnost = "SQL prep.: $sql, ".implode('\|/',$hodnoty); // posíláme "předzpracovaný" SQL dotaz/příkaz
    // 1. krok - otazníky pro hodnoty ... mysqli_stmt mysqli::prepare ( string $query )
    @$prikaz = $this->db->prepare($sql); // vrací objekt
    // 2. krok - hodnoty místo otazníků ... bool mysqli_stmt::bind_param ( string $types , mixed &$var1 [, mixed &$... ] )
    $i = 0; // příprava
    foreach($hodnoty as $k=>$h) // potřebujeme ale jenom jen indexy
    { if ($i==0) // 1. vstup není reference
      $vstupy[$i++] = $hodnoty[$k]; // datové typy
    else
      $vstupy[$i++] = &$hodnoty[$k]; // další vstupy musí být reference
    }
    @call_user_func_array(array($prikaz, 'bind_param'), $vstupy); // zavoláme 'bind_param' se všemi vstupy
    // 3. krok - odeslání dotazu/příkazu do DB ... bool mysqli_stmt::execute ( void )
    if ($prikaz->execute() == FALSE)
      $this->hlaseni = (self::MOD==1) ? $this->db->error : $this->hlaseni;
    // 4. krok ... počet ovlivněných/vrácených řádků  + výsledek SELECTu
    $this->pocet_radku = 0;
    $tabulka = array(); // příprava výsledku
    if (strncasecmp("SELECT",$sql,6)==0) // šlo o dotaz nebo jiný příkaz?
    { @$prikaz->store_result(); // do bufferu (zabírá paměť, ale je to rychlejší)
      $this->pocet_radku = $prikaz->num_rows; // počet vrácených řádků
      if ($this->pocet_radku>0)
      { // 5. krok ... zpracování výsledku
        @$popis_dat = $prikaz->result_metadata(); // vrací objekt (lze z něj získat názvy sloupců výsledku)
        $sloupce_obj = $popis_dat->fetch_fields(); // vrací pole
        $sloupce = array();
        foreach ($sloupce_obj as $sl)
          $sloupce[] = $sl->name; // máme jména sloupců
        // bool mysqli_stmt::bind_result ( mixed &$var1 [, mixed &$... ] )
        @eval('$prikaz->bind_result($c_'.implode(',$c_',$sloupce).');'); // připraví výstupy: c_<sloupec1>, c_<sloupec2>, ...
        $tabulka[0] = $sloupce; // "záhlaví" tabulky obsahuje názvy sloupců
        $zaznam = 1;
        while(@$prikaz->fetch()) // vrací proměnné c_<sloupec1>, c_<sloupec2>, ...
        { foreach($sloupce as $sloupec1)
		  { $jmeno = "c_$sloupec1";
			$tabulka[$zaznam][] = $$jmeno; // postupně přiřazujeme hodnoty sloupců do "řádku" tabulky
		  }
          $zaznam++;
        }
      }
      $prikaz->free_result(); // zpracováno, buffer uvolníme
    }
    else // asi šlo o INSERT, UPDATE nebo DELETE (ale může to být i SHOW nebo CREATE...!)
      $this->pocet_radku = $prikaz->affected_rows;

    $prikaz->close(); // nebo ->reset()
    $this->loguj();
    return $tabulka; // vracíme výsledek
  }

  public function posli_prikaz_slepe($sql, $pozadavek='')
  { /* velmi jednoduchá metoda pro "slepé" odeslání příkazu SQL
       (nekontroluje ani neescapuje vstupní příkaz SQL!
        => NEPOUŽÍVAT pro data z formulářů!!!)
       Vstupy:
       $sql ... řetězec obsahující SQL příkaz/dotaz
         (pro odeslání do DB a pro mód ladění)
       $pozadavek ... řetězec popisující typ požadavku
         (např. "vložení dat") => výpis "uživatelské" chyby
       Výstup:
       pole s výsledkem (buď prázdné pole, nebo "tabulka" výsledků
         od SELECTu: řádek č. 0 obsahuje jména vrácených sloupců,
         další řádky pak obsahují data)
    */
    $this->cinnost = "SQL: $sql"; // posíláme SQL (dotaz/příkaz)

    // příprava -- co když nebudou data?
    $tabulka = array();
    $this->pocet_radku = 0;

    @$v = $this->db->query($sql); // pošleme dotaz
    if ($v === FALSE) {
    // nelze poslat dotaz
      $this->hlaseni = (self::MOD==1) ? $this->db->error : "požadavek <em>$pozadavek</em> nelze zpracovat! Zopakujte akci později.";
      $this->loguj(); // neúspěch, nastala nějaká chyba
      $this->vypis_chybu(); // konec skriptu
    }
    elseif ($v === TRUE) {
    // úspěch dotazu, který nevrací data
      $this->pocet_radku = $this->db->affected_rows; // počet ovlivněných řádků
      $this->hlaseni = 'OK'; // úspěch
      $this->loguj(); // záznam do LOG-souboru
    }
    else {
    // úspěch SELECTu, $v je objekt
      $this->pocet_radku = $v->num_rows; // obsahuje počet vrácených řádků
      $sloupce = $v->fetch_fields(); // chceme jména sloupců výsledku
      foreach ($sloupce as $jmeno)
        $tabulka[0][] = $jmeno->name; // máme pole jmen
      while($zaznam = $v->fetch_row()) // vrácená data
        $tabulka[] = $zaznam; // uložíme celý jeden záznam
      $this->hlaseni = 'OK'; // úspěch
      $this->loguj(); // záznam do LOG-souboru
    }
    return $tabulka;
  } 

    
  private function vypis_chybu() // výpis chyby na výstup skriptu + konec skriptu
  {
    die('<p style="background-color:#FFCCCC">Nastala chyba: ' . $this->hlaseni . '</p></body></html>');
  }


  private function loguj() 
  { // zápis záznamu o činnostech
    if (self::LOG=='')
      return; // v konfiguraci není nastaven soubor
    
    @$fp = fopen(self::LOG, 'a'); // přidáváme (logujeme) na konec souboru
    if ($fp) { // povedlo se otevřít LOG-soubor?
      flock($fp, LOCK_EX); // uzamkneme soubor
      // řádek se záznamem o činnosti (datum+čas, co se dělo, výsledek činnosti, IP adresa)
      @fwrite($fp, date("Y-m-d H:i:s").' '.$this->cinnost.'...'.$this->hlaseni.' ('.$_SERVER['REMOTE_ADDR'].")\n"); // zapíšeme obsah privátních členských proměnných
      flock($fp, LOCK_UN); // odemkneme
      fclose($fp);
    }
    elseif (self::MOD==1) {
    // do souboru nelze zapisovat, ale je nastaven mód ladění!
      $odst = '<p style="background-color:#FFCCCC">'; // odstavec podbarvený sv. červenou (lepší by byla třída CSS!)
      $odst .= 'Nelze zapisovat do LOG souboru: '; 
      if (!is_dir(dirname(self::LOG)))
        $odst .= 'neexistuje adresář pro LOG soubor!'; 
      elseif (!file_exists(self::LOG))
        $odst .= 'LOG soubor neexistuje!';
      echo $odst,'</p>'; // bez ukončení skriptu
    }
    // else // do souboru nelze zapisovat a není nastaven mód ladění => nic neděláme
  }

} // konec definice třídy TDatabase
