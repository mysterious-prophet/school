<?php

if(isset($_POST)){
	if(is_numeric($_POST['c1']) && is_numeric($_POST['c2'])){
		switch($_POST['operace']){
			case 'scitani':
				$result=$_POST['c1']+$_POST['c2'];
				break;
			case 'odcitani':
				$result=$_POST['c1']-$_POST['c2'];
				break;
			case 'nasobeni':
				$result=$_POST['c1']*$_POST['c2'];
				break;
			case 'deleni':
				$result=$_POST['c1']/$_POST['c2'];
				break;
			default:
				unset($_POST);
				generateCalculator();
				echo 'Chybna operace.';
			break;
		}
	echo $result;
	saveToXML($result);
	}
	elseif($_POST['c1']=='' || $_POST['c2']==''){
		unset($_POST);
		generateCalculator();
		
	}
	else{
		unset($_POST);
		generateCalculator();
		echo '<br><br>Neplatne cislice.';
	}
}
else{
	generateCalculator();
}

function generateCalculator(){
	echo' <html lang="cs"><head>
      <meta charset="utf-8">
      <title>Primitivní kalkulačka</title>
    </head>
    <body>
    <h1>Primitivní kalkulačka</h1>
    <form method="post" action="kalkulacka.php">
    <input type="text" name="c1" size="4" maxlength="4"value="'.$_POST['c1'].'">
    <select name="operace">
    <option value="scitani">+</option>
    <option value="odcitani">-</option>
    <option value="nasobeni">*</option>
    <option value="deleni">/</option>
    </select>
    <input type="text" name="c2" size="4" maxlength="4" value="'.$_POST['c2'].'">
    <input type="submit" value="=">
    </body>
    </html>';
}

function saveToXML($result){
    if (!file_exists('./pocet')) {
		mkdir('./pocet', 0755, true);
    }
    $myFile = fopen("./pocet/kalkulacka.dat", "a") or die("Nepodarilo se otevrit soubor.");
    if(!filesize("./pocet/kalkulacka.dat")) {
        fwrite($myFile, '<kalkulacka>');
    }
    else{
        $lines = file('./pocet/kalkulacka.dat'); 
        $last = sizeof($lines) - 1 ;
        unset($lines[$last]);
        $fp = fopen('./pocet/kalkulacka.dat', 'w');
        fwrite($fp, implode('', $lines));
        fclose($fp);
    }
	
	$myXML="<priklad>
<datumcas>".date("Y/m/d") . "_".date("h:i:sa")."</datumcas>
<cisloA>".$_POST['c1'] . "</cisloA>
<operace>". $_POST['operace'] . "</operace>
<cisloB>".$_POST['c2'] ." </cisloB>
<vysledek>". $result."</vysledek> 
</priklad>
";

	fwrite($myFile, $myXML);
	fwrite($myFile, '</kalkulacka>');
	fclose($myFile);
}

?>