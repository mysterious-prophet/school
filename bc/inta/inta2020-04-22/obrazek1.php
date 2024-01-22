<?php   // generování obrázku se soustøednými kru¾nicemi, odeslán do prohlí¾eèe
header("Content-Type: image/png");

$obr = imagecreate(200,200); // nové plátno 200x200 px
// pøidáme barvy:
$pozadi = imagecolorallocate($obr,255,255,255); // bílá
$zluta = imagecolorallocate($obr,204,204,0); // µlutá
$zelena = imagecolorallocate($obr,0,204,0); // zelená
$cervena = imagecolorallocate($obr,255,0,0); // èervená

imagefilledellipse($obr,100,100,160,160,$cervena); // nejvìt¹í kru¾nice
imagefilledellipse($obr,100,100,120,120,$zluta); // prostøední kru¾nice
imagefilledellipse($obr,100,100,80,80,$zelena); // nejmen¹í kru¾nice

imageline($obr,100,98,100,102,$cervena); // køí¾ek uprostøed
imageline($obr,98,100,102,100,$cervena); // køí¾ek uprostøed

imagestring($obr,4,0,0,"Tøi soustøedné kru¾nice:",$cervena); // text uprostøed

imagepng($obr); // odeslání prohlí¾eèi
imagedestroy($obr); // uvolnìní pamìti
