<?php
class anketa extends zaklad {

    public function __construct() {
        parent::__construct(); // připojení k DB
        session_start();
    }

	public function new_form(\Base $f3) {
		$this->test_logged(); // je někdo přihlášený? (pokud ne, přesměruje)
		$f3->set('pocet_odpo',array(1,2,3,4,5));
		$f3->set('subtitle','Nová anketa');
		$f3->set('content','anketa_nova.html');
	}
	
	public function new_check(\Base $f3) {
		$this->test_logged(); // je někdo přihlášený? (pokud ne, přesměruje) 
		// data: textot,odkdy,dokdy,odp[],barva[]
		$otazka = $f3->get('POST.textot'); // string; $otazka = isset($_POST['textot'])?$_POST['textot']:'';
		$datum_od = $f3->get('POST.odkdy'); // string
		$datum_do = $f3->get('POST.dokdy'); // string (nepovinný)
		$odpovedi = array(); // příprava
		$barvy = array(); // příprava
		$chyba = ''; // příprava
		if (mb_strlen($otazka)>255)
			$chyba .= 'Příliš dlouhý text otázky (povoleno max. 255 znaků).<br>';
		if (!preg_match('|^\d{4}-\d{1,2}-\d{1,2}$|',$datum_od))
			$chyba .= 'Chybný formát data začátku!<br>';
		if ($datum_do!=null && !preg_match('|^\d{4}-\d{1,2}-\d{1,2}$|',$datum_do))
			$chyba .= 'Chybný formát data konce!<br>';
        // kontrola, že $datum_do (pokud je vyplněno) > $datum_od
        $k = 1; // čítač odpovědí
        srand(); // inicializace generátoru náh. čísel
		foreach($f3->get('POST.odp') as $i=>$odpo) {
			if (mb_strlen($odpo)>255)
				$chyba .= 'Dlouhá ' . ($i+1) . '. odpověď!<br>';
            if (!empty($odpo)) {
                $odpovedi[$k] = $odpo;
                // barva z formuláře nebo náhodná barva
                $barva_pom = (isset($_POST['barva'][$i]) && preg_match('/^[0-9a-f]{6}$/i',$_POST['barva'][$i])) ? $_POST['barva'][$i] : sprintf('%02X%02X%02X', rand(0,255), rand(0,255), rand(0,255));
                if ($k==1)
                    $barvy[$k] = $barva_pom; // první barva
                else { // aby se barvy neopakovaly:
                    $kk = 1;
                    while (in_array($barva_pom,$barvy) && $kk<30) { // pojistka proti opakování barev u odpovědí
                        $barva_pom = sprintf('%02X%02X%02X', rand(0,255), rand(0,255), rand(0,255));
                        $kk++;
                    }
                    $barvy[$k] = $barva_pom;
                }
                $k++; // jdeme na další odpověď
            }
		}
        if (count($odpovedi)<2)
            $chyba .= 'Odpovědi musí být nejméně dvě!<br>';

        // uložíme data do DB:
        if (empty($chyba)) { // data z formuláře neobsahují chyby
            $v = $this->save($otazka,$datum_od,$datum_do,$odpovedi,$barvy);
            if ($v===FALSE) {
                $_SESSION['error'] = "Nastala chyba při ukládání dat do databáze! Kontaktujte administrátora serveru.";
                // vrátit zpět formulář s daty? Upravit anketa_nova.html, aby bralo data z PHP->$_POST
            }
            else
                $_SESSION['ok'] = "Anketa byla uložena do databáze s $v odpověďmi.";
            $f3->reroute('/');
        }
        else { // ve formuláři byly chyby
            $_SESSION['error'] = $chyba;
            $f3->reroute('/survey'); // znovu prázdný formulář s anketou
            // vrátit zpět formulář s daty? 
            // připravit VŠECHNA data pro šablonu $f3->set(proměnná,hodnota)
            // $f3->set('pocet_odpo',array(1,2,3,4,5));
		    // $f3->set('subtitle','Nová anketa (oprava)');
		    // $f3->set('content','anketa_nova.html');// Upravit anketa_nova.html, aby bralo data z PHP->$_POST
        }
	}

    public function vote_form(\Base $f3) { // formulář pro hlasování v anketě; routes.ini: GET /vote/@id_ankety
        $id_ankety = $f3->get('PARAMS.id_ankety');
        $row = $this->db->exec('SELECT textot, datum_od, datum_do, idodpo, textodpo FROM a_otazka JOIN a_odpoved ON idotazky=idot WHERE idot=?',array($id_ankety));
        if ($row===FALSE) { // nedalo se zeptat v DB
            $_SESSION['error'] = 'Nelze hlasovat (kontaktujte administrátora)!';
            $f3->reroute('/'); // přeroutujeme na hlavní stránku
        }
        if (count($row)<1) { // nemáme žádná data! Asi chybné ID ankety?
            $_SESSION['error'] = 'Na vybranou anketu NELZE hlasovat!';
            $f3->reroute('/'); // přeroutujeme na hlavní stránku
        }
        // zjistíme, zda je anketa aktuální:
        $aktualni = $this->is_actual($row[0]['datum_od'],$row[0]['datum_do']);
        // kontroly, zda lze hlasovat:
        if (!$aktualni && !isset($_SESSION['userID'])) { // anketa ještě nezačala anebo už skončila!
            $_SESSION['error'] = 'Ve vybrané anketě NELZE hlasovat!';
            $f3->reroute('/'); // přeroutujeme na hlavní stránku
        }
        $f3->set('anketni_otazka',$row[0]['textot']);
        $odpovedi = array(); // příprava pro VIEW (template)
        foreach ($row as $radek=>$zaznam)  // složíme si texty odpovědí s jejich IDéčky
            $odpovedi[$row[$radek]['idodpo']] = $row[$radek]['textodpo'];
        $f3->set('odpovedi',$odpovedi);
		$f3->set('subtitle','Hlasování');
		$f3->set('content','anketa_hlasuj.html');
    }

    public function vote_check(\Base $f3) { // obsluha hlasování; routes.ini: POST /vote/@id_ankety
        $id_ankety = $f3->get('PARAMS.id_ankety');
        $id_odpovedi = $f3->get('POST.odpoved');

        // kontrola, zda vůbec lze hlasovat (povoleno hlasovat mají přihlášení uživatelé)
        $v = $this->db->exec('SELECT datum_od, datum_do FROM a_otazka WHERE idot=?',$id_ankety);
        if ($v===FALSE || count($v)<1) { // povedlo se poslat dotaz? Bylo vráceno 0 řádků? Anketa není aktuální?
            $_SESSION['error'] = 'Nastala chyba při pokusu o hlasování. Vyberte si anketu a hlasujte znovu.';
            $f3->reroute('/'); // přeroutujeme na úvodní stránku
        }
        $aktualni = $this->is_actual($v[0]['datum_od'],$v[0]['datum_do']);
        if (!$aktualni && !isset($_SESSION['userID'])) { // anketa není aktuální a ani není přihlášený uživatel
            $_SESSION['error'] = 'V anketě nelze hlasovat. Vyberte si jinou.';
            $f3->reroute('/'); // přeroutujeme na úvodní stránku
        }

        $v = $this->db->exec('UPDATE a_odpoved SET pocet_hlasu = pocet_hlasu+1 WHERE idotazky=? AND idodpo=?',array($id_ankety,$id_odpovedi));
        if ($v===FALSE) { // nedalo se zeptat v DB
            $_SESSION['error'] = 'Váš hlas se bohužel nepodařilo uložit (kontaktujte administrátora)!';
            $f3->reroute("/vote/$id_ankety"); // přeroutujeme zpět na hlasovací formulář dané ankety
        }
        else {
            $_SESSION['ok'] = 'Váš hlas byl zaznamenán.';
            $f3->reroute("/graph/$id_ankety"); // přeroutujeme na graf
//            $f3->reroute('/');
        }
    }


    public function graph(\Base $f3) { // GET /graph/@id_ankety=anketa->graph
        $id_ankety = $f3->get('PARAMS.id_ankety');
        $row = $this->db->exec('SELECT textot, textodpo, pocet_hlasu, barva FROM a_otazka JOIN a_odpoved ON idotazky=idot WHERE idot=?',array($id_ankety));
        if ($row===FALSE) { // nedalo se zeptat v DB
            $_SESSION['error'] = 'Nelze zobrazit výsledky ankety (kontaktujte administrátora)!';
            $f3->reroute('/'); // přeroutujeme na hlavní stránku
        }
        if (count($row)<2) { // neexistující anketa!
            $_SESSION['error'] = 'Nelze zobrazit graf!';
            $f3->reroute('/'); // přeroutujeme na hlavní stránku
        }

        $odpovedi = array();
        foreach ($row as $zaznam)
            $odpovedi[] = array('odp'=>$zaznam['textodpo'], 'pocet'=>$zaznam['pocet_hlasu'], 'b'=>$zaznam['barva']);

        $f3->set('otazka',$row[0]['textot']);
        $f3->set('odpovedi',$odpovedi);
		$f3->set('subtitle','Graf');
		$f3->set('content','anketa_graf.html');
    // NUTNO DOPLNIT KÓD NA KRESLENÍ GRAFU
    }



    public function summary() { // vrací přehled anket: $vystup[$i]=array(idot,textot,aktualni,detaily)
        $vystup = array(); // příprava
        $row = $this->db->exec('SELECT idot, textot, datum_od, datum_do FROM a_otazka ORDER BY idot');
        if ($row!==FALSE) { // povedlo se poslat dotaz
            foreach($row as $zaznam) { // převedeme si data do pole $vystup
                $akt = $this->is_actual($zaznam['datum_od'],$zaznam['datum_do']);
                $detaily = "(platná od {$zaznam['datum_od']}";
                if (!empty($zaznam['datum_do']))
                    $detaily .= " do {$zaznam['datum_do']})";
                else
                    $detaily .= " bez omezení)";
                // připojujeme prvky do pole pro VIEW (template); kontroler: zaklad->home()
                $vystup[] = array('idot'=>$zaznam['idot'],'textot'=>$zaznam['textot'],'aktualni'=>$akt,'detaily'=>$detaily);
            }
        }
        return $vystup;
    }


    private function is_actual($odkdy, $dokdy) { // ze zadaných dnů zjistí, zda je anketa aktuální (= není minulá ani budoucí)
        $dnes = new DateTime(date('Y-m-d')); // dnešní datum (objekt) podle času na serveru
        $odkdy = new DateTime($odkdy); // vstup převedeme na objekt
        if (!is_null($dokdy))
            $dokdy = new DateTime($dokdy); // vstup převedeme na objekt
        if($odkdy > $dnes) // anketa je budoucí
            return FALSE;
        if (!empty($dokdy) && $dokdy < $dnes) // anketa je minulá
            return FALSE;
        return TRUE; // anketa je aktuální
    }

    private function save($otazka, $datum_od, $datum_do, $odpovedi, $barvy) { // uložení dat ankety (i s odpověďmi) do DB
        $this->db->begin(); // zahájení transakce
        $row = $this->db->exec("SELECT MAX(idot) AS lastId FROM a_otazka"); // jaké je nejvyšší použité IDotázky?
        if ($row === FALSE) {// dotaz se nepodařilo provést!
            $this->db->rollback(); // odvolat transakci
            return FALSE;
        }
        if (count($row)<1) // vrátí 0, pokud je tabulka prázdná (a 1 řádek, pokud tam už něco je)
            $idot = 1; // budeme vkládat PRVNÍ anketní otázku
        else
            $idot = $row[0]['lastId'] + 1; // nové ID anketní otázky
        $idu = $_SESSION['userID'];// $idu = $f3->get(SESSION.userID);
        $v = $this->db->exec('INSERT INTO a_otazka VALUES(?,?,?,?,?)',array($idot,$otazka,$datum_od,$datum_do,$idu));
        if ($v===FALSE) {
            $this->db->rollback(); // odvolat transakci
            return FALSE;
        }
        $k = 1; // indexace v DB pro odpovědi
        foreach($odpovedi as $i=>$text) {
            $v = $this->db->exec('INSERT INTO a_odpoved (idotazky,idodpo,textodpo,barva) VALUES(?,?,?,?)',array($idot,$k,$text,$barvy[$i])); // uložíme i-tou odpověď
            if ($v===FALSE && $k<2) { // nepovedlo se uložit $k-tou odpověď a $k<2 => problém
                $this->db->rollback(); // odvolat transakci
                return FALSE;
            }
            $k++;
        }
        $this->db->commit(); // potvrdit transakci => změny se uloží do DB
        return $k-1;
    }
}

