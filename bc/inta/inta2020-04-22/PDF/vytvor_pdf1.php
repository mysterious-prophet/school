<?php // generování PDF souboru s obrázkem

require('tfpdf.php');

$pdf = new tFPDF('L','mm','A5'); // na šířku, mm, A5
$pdf->AddPage(); // nová stránka

// přidáme Unicode-font (UTF-8)
$pdf->AddFont('DejaVu','','DejaVuSerif.ttf',true);
$pdf->SetFont('DejaVu','',16);

// kreslení grafiky, vložení obrázku:
$pdf->SetDrawColor(255,0,0); // barva cary cervena
$pdf->SetFillColor(255,255,0); // barva vyplne zluta
$pdf->Rect(10,10,190,130,'DF'); // obdelnik skoro pres celou stranku
$pdf->Image('./logo_fpdf.gif',100,60); // obrazek slona

// výpis českého textu
$w = 7; // výška řádku
$pdf->Write($w, "Příliš žluťoučký kůň úpěl ďábelské ódy\n");
$pdf->Ln(10);

// výpis tabulky druhých mocnin:
$pdf->SetDrawColor(0,0,0); // barva cary cerna
$tabw = 10;
$tabw2 = 14;
$pdf->SetFont('DejaVu','',12);
$pdf->Write($w,"Tabulka druhých mocnin:\n");
$pdf->Cell($tabw,$w,'x',1,0,'R');
$pdf->Cell($tabw2,$w,'x^2',1,1,'R');
$pdf->SetFont('Arial','',14); // vybereme standardní font (kódování windows-1252)
for($i=0; $i<=10; $i++) // tabulka druhych mocnin
{ $pdf->Cell($tabw,$w,$i,1,0,'R');
  $pdf->Cell($tabw2,$w,$i*$i,1,1,'R');
}  

$pdf->Output(); // $pdf->Output('pokusne.pdf','I');
