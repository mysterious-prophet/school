<?php
// konstanty (konfigurace):
define('ODES_EMAIL','dana.majerova@fjfi.cvut.cz'); // e-mail odesílatele (změňte druhý vstup)!
define('ODES_NAME','Dana Majerova'); // jméno odesílatele (a příjemce) -- změňte druhý vstup!
define('KOMU','dana.majerova@atlas.cz');// e-mailpříjemce (změňte druhý vstup)!
define('AUTH_NAME','majerdan'); // username ČVUT/FJFI (změňte druhý vstup)!
define('AUTH_PWD','***skolniHeslo***'); // heslo do e-mailu FJFI (heslo do sítě FJFI) -- změňte druhý vstup!

// e-mail:
date_default_timezone_set('Europe/Prague'); // SMTP potřebuje správny čas

require './PHPMailerAutoload.php';

$mail             = new PHPMailer(); // instance třídy
//$mail->Encoding  //!!!
$mail->IsSMTP(); // chci používat SMTP
$mail->SMTPDebug  = 0; // SMTP debug information: 0=off, 1=client, 2=client+server, 3=client+server+connect.info
$mail->Debugoutput = 'html'; // debug-výpis v HTML
$mail->Host       = "smtp.fjfi.cvut.cz";  // SMTP-server = FJFI
$mail->Port       = 587; // port SMTP, vyžaduje TLS
$mail->SMTPSecure = "tls"; // druh zabezpečeného připojení
$mail->SMTPAuth   = true; // povolená SMTP autentifikace
$mail->Username   = AUTH_NAME;  // viz konstanty nahoře
$mail->Password   = AUTH_PWD; // viz konstanty nahoře

$mail->SetFrom(ODES_EMAIL, ODES_NAME); // jméno a příjmení se použije pro odesílatele
$mail->AddReplyTo(KOMU, ODES_NAME); // jméno a příjmení se použije stejné i pro příjemce
$mail->AddAddress(KOMU, ODES_NAME);
$mail->Subject = "PHPMailer - test pres FJFI";
$obsah = file_get_contents('phpmailer.html'); // obsah e-mailu ze souboru
$mail->msgHTML($obsah, dirname(__FILE__)); // obsah e-mailu ze souboru na serveru PHP
$mail->AltBody = strip_tags($obsah);
$mail->AddAttachment("phpmailer.png");      // attachment
$mail->AddAttachment("phpmailer_mini.png"); // attachment

// sestavení webové stránky:
include './fce_html.php';

echo html_hlavicka('Posílání e-mailu');
if(!$mail->Send()) {
  echo '<p style="background-color:#FFCCCC">Mailer Error: ' . $mail->ErrorInfo . '</p>';
} else {
  echo '<p style="background-color:#CCFFCC">E-mail byl odeslán.</p>';
}
echo html_paticka();
