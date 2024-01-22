<?php
require './tfpdf.php';

$pdf = new tFPDF();
$pdf->AddPage();
$pdf->AddFont('DejaVu','','DejaVuSerif.ttf',true);
$pdf->SetFont('DejaVu','',16);
$pdf->Cell(60,10,'Žluťoučké kuřátko přeleze z buňky ven.'); // tato buňka je moc krátká!

$pdf->SetFillColor(255,0,0); // barva výplně
$pdf->Cell(100,10,'Červený trpaslík',0,1,'C',true);
$pdf->SetDrawColor(0,0,0); // barva čáry/rámečku
$pdf->Ln(5); // prázdný řádek
$pdf->SetFillColor(153,201,255); // jiná barva výplně
$pdf->Cell(60,10,'Modrá ježibaba',1,1,'C',true); // buňka stejné šířky jako "Kuřátko", ale sem se text vejde
$pdf->Ln(5); // prázdný řádek

$pdf->SetDrawColor(255,0,255); // jiná barva čáry
$pdf->Rect(80,40,20,10,'F'); // obdélník
$pdf->Line(80,40,100,50); // úhlopříčka v obdélníku (zleva doprava)

// vložení obrázku:
$pdf->Image('logo_fpdf.gif');
$pdf->Output();
