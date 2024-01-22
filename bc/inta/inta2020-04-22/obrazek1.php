<?php   // generov�n� obr�zku se soust�edn�mi kru�nicemi, odesl�n do prohl�e�e
header("Content-Type: image/png");

$obr = imagecreate(200,200); // nov� pl�tno 200x200 px
// p�id�me barvy:
$pozadi = imagecolorallocate($obr,255,255,255); // b�l�
$zluta = imagecolorallocate($obr,204,204,0); // �lut�
$zelena = imagecolorallocate($obr,0,204,0); // zelen�
$cervena = imagecolorallocate($obr,255,0,0); // �erven�

imagefilledellipse($obr,100,100,160,160,$cervena); // nejv�t�� kru�nice
imagefilledellipse($obr,100,100,120,120,$zluta); // prost�edn� kru�nice
imagefilledellipse($obr,100,100,80,80,$zelena); // nejmen�� kru�nice

imageline($obr,100,98,100,102,$cervena); // k��ek uprost�ed
imageline($obr,98,100,102,100,$cervena); // k��ek uprost�ed

imagestring($obr,4,0,0,"T�i soust�edn� kru�nice:",$cervena); // text uprost�ed

imagepng($obr); // odesl�n� prohl�e�i
imagedestroy($obr); // uvoln�n� pam�ti
