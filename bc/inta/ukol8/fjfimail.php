<?php
// konstanty (konfigurace):
define('ODES_EMAIL','pokorm20@fjfi.cvut.cz'); // e-mail odesílatele (změňte druhý vstup)!
define('ODES_NAME','Matej Pokorny'); // jméno odesílatele (a příjemce) -- změňte druhý vstup!
define('KOMU','');// e-mailpříjemce (změňte druhý vstup)!
define('AUTH_NAME','pokorm20'); // username ČVUT/FJFI (změňte druhý vstup)!
define('AUTH_PWD','tohleNenimojeHeslo420'); // heslo do e-mailu FJFI (heslo do sítě FJFI) -- změňte druhý vstup!

include './fce_html.php';

if($_SERVER['REQUEST_METHOD'] != 'POST') {
echo html_hlavicka('Posílání e-mailu');
	echo '<form action="" method="post" enctype="multipart/form-data">';
	echo '<p>Odesilatel: <input type="email" name="od" value="pokorm20@fjfi.cvut.cz"></p>';
	echo '<p>Prijemce: <input type="email" name="komu" value="@"></p>';
	echo '<p>Predmet: <input type="text" size="30" name="predmet"></p>';
	echo '<p><textarea name="dopis" cols="50" rows="5" wrap="yes"></textarea></p>';
	echo '<input type="hidden" name="MAX_FILE_SIZE" value="102400" />';
	echo '<p><input type="file" name="priloha" accept="text/plain"></p>';
	echo '<input type="submit" value="Poslat">';
	echo '</form>';
}
else{
// e-mail:
date_default_timezone_set('Europe/Prague'); // SMTP potřebuje správny čas

require './PHPMailerAutoload.php';

$mail = new PHPMailer(); // instance třídy
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

$mail->SetFrom($_POST["od"], $_POST["od"]); // jméno a příjmení se použije pro odesílatele
$mail->AddReplyTo($_POST["komu"], $_POST["komu"]); // jméno a příjmení se použije stejné i pro příjemce
$mail->AddAddress($_POST["komu"], $_POST["komu"]);
$mail->Subject = $_POST["predmet"];
$obsah = $_POST["dopis"]; // obsah e-mailu ze souboru
$mail->msgHTML($obsah, dirname(__FILE__)); // obsah e-mailu ze souboru na serveru PHP
$mail->AltBody = strip_tags($obsah);
if((isset($_FILES["priloha"]))){
	$mail->AddAttachment($_FILES['priloha']['tmp_name'], $_FILES['priloha']['name']);      // attachment
}
else{
	echo '<p>Email odeslan bez prilohy. Jako priloha jsou povoleny pouze textove soubory do velikosti 100 kB.';
}

// sestavení webové stránky:

if(!$mail->Send()) {
  echo '<p style="background-color:#FFCCCC">Mailer Error: ' . $mail->ErrorInfo . '</p>';
} else {
  echo '<p style="background-color:#CCFFCC">E-mail byl odeslán.</p>';
}
}

echo html_paticka();
