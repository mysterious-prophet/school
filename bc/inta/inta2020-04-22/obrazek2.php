<?php // obrazek s nмkolika ъtvary a textem vzatэm z URL ... GET['t']

if (isset($_GET['t'])) // mбme data?
  $text = $_GET['t'];
else
  $text = "Ahoj lidi!";

$text = urldecode($text); // pшevod dat na pщvodnн tvar
// dбle by bylo dobrй text pшevйst na znakovou sadu ISO Latin2, ale Z JAKЙ sady???

$obr = imagecreate(400,300); // novй plбtno
// barvy:
$b1 = imagecolorallocate($obr,204,152,255); // pozadн (fialovб)
$b2 = imagecolorallocate($obr,0,0,255); // modrб
$b3 = imagecolorallocate($obr,0,0,51); // tm. modrб
$b4 = imagecolorallocate($obr,255,0,0); // иervenб
$b5 = imagecolorallocate($obr,255,204,0); // ћlutб

imageline($obr,400,0,0,300,$b4);
$styl1 = array($b5,$b5,$b5,$b5,$b1,$b1,$b1); // styl: pшeruљ. ибra
imagesetstyle($obr,$styl1);
imageline($obr,400,20,20,300,IMG_COLOR_STYLED); // pшeruљ. ибra

imagestring($obr, 3, 0, 0, $text, $b3); // text z URL

imagefilledarc($obr, 350,250, 80,80, 25,155, $b3, IMG_ARC_PIE);

imagefilledpolygon($obr, array(20,20, 80,80, 80,20, 20,80),4,$b5);

header("Content-Type: image/png");
imagepng($obr);
imagedestroy($obr);
