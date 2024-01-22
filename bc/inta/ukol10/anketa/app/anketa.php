<?php
class anketa extends zaklad {

	public function new_form(\Base $f3) {
		$this->test_logged(); // je někdo přihlášený? (pokud ne, přesměruje)
		$f3->set('pocet_odpo',array(1,2,3,4,5));
		$f3->set('subtitle','Nová anketa');
		$f3->set('content','anketa_nova.html');
	}
	
	public function new_check(\Base $f3) {
		$this->test_logged(); // je někdo přihlášený? (pokud ne, přesměruje) 
		// data: textot,odkdy,dokdy,odp[],barva[]
		$otazka = $f3->get('POST.textot'); // string
		$datum_od = $f3->get('POST.odkdy'); // string
		$datum_do = $f3->get('POST.dokdy'); // string (nepovinný)
		$odpovedi = $f3->get('POST.odp'); // array
		$barvy = $f3->get('POST.barva'); // array
		$chyba = '';
		if (mb_strlen($otazka)>255)
			$chyba .= 'Příliš dlouhý text otázky (povoleno max. 255 znaků).<br>';
		if (!preg_match('|^\d{4}-\d{1,2}-\d{1,2}$|',$datum_od))
			$chyba .= 'Chybný formát data začátku!<br>';
		if ($datum_do!=null && !preg_match('|^\d{4}-\d{1,2}-\d{1,2}$|',$datum_do))
			$chyba .= 'Chybný formát data konce!<br>';
		foreach($odpovedi as $i=>$odpo) {
			if (mb_strlen($odpo)>255)
				$chyba .= 'Dlouhá odpoved!';
		}
		/* echo "Chyby: $chyba";
zpracování chyb -> CHYBA je => vrátit data do formuláře? reroute (NUTNÁ změna anketa_nova.html)
                   není CHYBA => uložit data do DB + reroute + session[ok]
       */

	}
}