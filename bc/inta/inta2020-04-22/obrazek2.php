<?php // obrazek s n�kolika �tvary a textem vzat�m z URL ... GET['t']

if (isset($_GET['t'])) // m�me data?
  $text = $_GET['t'];
else
  $text = "Ahoj lidi!";

$text = urldecode($text); // p�evod dat na p�vodn� tvar
// d�le by bylo dobr� text p�ev�st na znakovou sadu ISO Latin2, ale Z JAK� sady???

$obr = imagecreate(400,300); // nov� pl�tno
// barvy:
$b1 = imagecolorallocate($obr,204,152,255); // pozad� (fialov�)
$b2 = imagecolorallocate($obr,0,0,255); // modr�
$b3 = imagecolorallocate($obr,0,0,51); // tm. modr�
$b4 = imagecolorallocate($obr,255,0,0); // �erven�
$b5 = imagecolorallocate($obr,255,204,0); // �lut�

imageline($obr,400,0,0,300,$b4);
$styl1 = array($b5,$b5,$b5,$b5,$b1,$b1,$b1); // styl: p�eru�. ��ra
imagesetstyle($obr,$styl1);
imageline($obr,400,20,20,300,IMG_COLOR_STYLED); // p�eru�. ��ra

imagestring($obr, 3, 0, 0, $text, $b3); // text z URL

imagefilledarc($obr, 350,250, 80,80, 25,155, $b3, IMG_ARC_PIE);

imagefilledpolygon($obr, array(20,20, 80,80, 80,20, 20,80),4,$b5);

header("Content-Type: image/png");
imagepng($obr);
imagedestroy($obr);
