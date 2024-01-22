<?php // stranka generujici obrazek snehulaka na svuj vystup

header("Content-type: image/png"); // výstupem bude JENOM obrázek

$obr = imagecreate(250,400);
$b1 = imagecolorallocate($obr, 255, 255, 255); // pozadi bude bile
$b2 = imagecolorallocate($obr, 0, 0, 0); // cerna barva
$b3 = imagecolorallocate($obr, 0, 0, 51); // tmave modra barva
$b4 = imagecolorallocate($obr, 102, 51, 0); // hneda barva
$b5 = imagecolorallocate($obr, 255, 51, 0); // oranzova barva

imageellipse($obr, 125, 270, 100, 100, $b2); // "nohy"
imageellipse($obr, 125, 185, 70, 70, $b2); // "bricho"
imageellipse($obr, 125, 125, 50, 50, $b2); // "hlava"
imagearc($obr, 165, 163, 30, 30, 0, 120, $b2); // "prava ruka" - dolni oblouk
imagearc($obr, 165, 163, 30, 30, 180, 359, $b2); // "prava ruka" - horni oblouk
imagearc($obr, 85, 163, 30, 30, 57, 350, $b2); // "leva ruka"
imagefilledrectangle($obr, 112, 90, 138, 104, $b4); // hrnec
imagefilledellipse($obr, 115, 113, 5, 5, $b2); // leve oko
imagefilledellipse($obr, 135, 113, 5, 5, $b2); // prave oko
imagefilledpolygon($obr, array(125,120, 135,125, 125,125), 3, $b5); // mrkev
imagearc($obr, 125, 128, 25, 25, 10, 170, $b5); // pusa

imagepng($obr); // poslat na vystup skriptu
