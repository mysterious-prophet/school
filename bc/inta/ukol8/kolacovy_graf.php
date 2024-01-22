<?php
header("Content-type: image/png");

$data = array("jan"=>29,"feb"=>15,"mar"=>31,"apr"=>25, "may"=>19, "jun"=>11, "jul"=>24); //pole vstupu
$graf = imagecreate(600, 600); //vytvoreni obrazku
$bp = imagecolorallocate($graf, 255, 255, 255); //barva pozadi bila
$bl = imagecolorallocate($graf, 0, 0, 0); //barva legendy cerna
$cx = imagesx($graf)/2; //sirka a vyska kolacoveho grafu
$cy = imagesy($graf)/2;
$sirkaGrafu = $cx-50;
$soucet = 0; //soucet hodnot vstupu
$start = 0; //zacatek a konec uhlu kazde casti grafu
$konec = 0;
$x = imagesx($graf)-75; //x-ova souradnice legendy
$y = 20; //y-ova souradnice legendy
foreach($data as $zaznam => $hodnota){
	$soucet += $hodnota;
}

$uhly = $data;
foreach($uhly as $zaznam => $uhel){
	$uhel = ($uhel/$soucet)*359; 
	$konec += $uhel;
	$b = imagecolorallocate($graf, rand(0,255), rand(0,255), rand(0,255)); //barvy vyseci nahodne
	imagefilledarc($graf, $cx, $cy, $sirkaGrafu, $sirkaGrafu, $start, $konec, $b, IMG_ARC_PIE);
	imagestring($graf, 2, $x, $y, $zaznam, $bl); 
	imagefilledrectangle($graf, $x-30, $y, $x-10, $y+20, $b);
	$start += $uhel;	
	$y += 25;
}	

imagepng($graf);
