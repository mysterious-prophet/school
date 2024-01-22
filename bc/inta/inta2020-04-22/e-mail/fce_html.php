<?php // funkce pro HTML kód "okolo" každého skriptu
/**
 * html_hlavicka - začátek HTML kódu stránky
 *
 * funkce doplní <!DOCTYPE>, částe <head> a otevírací <body>
 *
 * @param $tit - titulek stránky do <title></title>
 * @param string $zs - znaková sada (utf-8, windows-1250, iso-8859-2) pro <meta ...charset... (implicitně utf-8)
 * @param string $css_body - definice stylů CSS pro BODY = hodnota atributu STYLE pro značku BODY (implic. prázdná) 
 * @param array|string $css - pole, kde jsou URL souborů (string) s kaskádovými styly, které se "přilinkují" k HTML. Nebo řetězec (do tagu <style>).
 *
 * @return string - kód HTML
 */
function html_hlavicka($tit,$zs="utf-8",$css_body="",$css=array())
{
  // výstupem bude řetězec $html (kód HTML od <!DOCTYPE> do <body>):
  $html = "<!DOCTYPE html>\r\n"; // HTML 5, s odřádkováním na konci
  $html .= '<html lang="cs"><head>';
  // vyřešíme znakovou sadu WWW stránky:
  switch (strtolower($zs))
  { 
    case 'windows-1250':
    case 'iso-8859-2':
      $html .= "<meta http-equiv=\"content-type\" content=\"text/html;charset=$zs\">";
      break;
    case 'utf-8':
    default: 
      $html .= '<meta charset="UTF-8">';
  }
  // titulek WWW stránky:
  $html .= "<title>$tit</title>";
  // přidání externích CSS souborů:
  if (is_array($css))
    foreach($css as $soubor)
      $html .= "<link rel=\"stylesheet\" href=\"$soubor\" type=\"text/css\">";
  elseif (!empty($css))
    $html .= "<style>$css</style>";
  // konec záhlaví HTML:
  $html .= '</head>';
  // začátek těla dokumentu (s CSS?):
  if (empty($css_body))
    $html .= '<body>';
  else
    $html .= "<body style=\"$css_body\">";  
  
  return $html; // vracíme řetězec
}


/**
 * html_paticka - konec HTML kódu stránky
 *
 * funkce doplní </body></html>
 *
 * @return string - kód HTML
 */
function html_paticka()
{
  return '</body></html>'; 
}



/**
 * html_escape - výpis textu do WWW stránky
 *
 * funkce nahradí znaky >, <, & a " 
 *
 * @param $text - řetězec, ve kterém se nahrazuje
 *
 * @return string - řetězec po nahrazeních
 */
function html_escape($text)
{ // nahradí "rizikové" HTML znaky za entity

  if (function_exists('mb_ereg_replace')) // pro vícebajtová kódování
  { mb_regex_encoding('utf-8'); 
    $co = array('&', '<', '>', '"'); 
    $cim = array('&amp;', '&lt;', '&gt;', '&quot;'); 
    for ($i=0; $i<sizeof($co); $i++) 
      $text = mb_ereg_replace($co[$i], $cim[$i], $text); 
    return $text; 
  }
  else // (pro 1bajtová kódování)
  { $nahrady = array('&'=>'&amp;',
                   '<'=>'&lt;',
                   '>'=>'&gt;',
                   '"'=>'&quot;');
		   
    return strtr($text,$nahrady); // escapovaný řetězec pro HTML
  }              
}

/**
 * escape_url - výpis textu do URL
 *
 * funkce nahradí rizikové znaky správnou entitou (pro URL) 
 *
 * @param $text - řetězec, který bude escapován
 *
 * @return string - řetězec pro použití v URL
 */
function escape_url($text)
{ // nahradí "rizikové" URL znaky za "správné"
  $url_string = filter_var($text, FILTER_SANITIZE_ENCODED); // escapujeme hodnotu pro URL
  if ($url_string)
    return $url_string; // escapování proběhlo OK
  return ''; // nepodařilo se escapovat!
}
