<?php // pomocné pole pro chyby vzniklé při uploadu souboru na server (nejsou tu tedy funkce)

// pole s českými oznámeními chyb
$chyby_uploadu = array( //UPLOAD_ERR_OK => "OK"
  UPLOAD_ERR_INI_SIZE => "soubor překročil hodnotu direktivy 'upload_max_filesize'",
  UPLOAD_ERR_FORM_SIZE => "soubor překročil hodnotu MAX_FILE_SIZE zadanou ve formuláři",
  UPLOAD_ERR_PARTIAL => "soubor je uploadován jen částečně",
  UPLOAD_ERR_NO_FILE => "nebyl uploadován soubor",
  UPLOAD_ERR_NO_TMP_DIR => "chybí dočasná složka pro upload",
  UPLOAD_ERR_CANT_WRITE => "nelze zapisovat na disk",
  UPLOAD_ERR_EXTENSION => "upload souboru byl zastaven nějakým rozšířením PHP"
);


/*
nebo:

$chyby_uploadu = array(1=>'Soubor překročil velikost direktivy "upload_max_filesize".',
	2=>'Soubor překročil velikost MAX_FILE_SIZE definovanou v HTML formuláři.',
	3=>'Soubor byl na server přenesen jen částečně.',
	4=>'Nebyl uploadován žádný soubor.',
	6=>'Chybí adresář pro dočasné soubory.',
	7=>'Chyba zápisu souboru na disk.',
	8=>'Upload souboru byl zastaven.'
);
*/