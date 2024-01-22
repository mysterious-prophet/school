function kontrola(form){
	var cislo1Var=form.elements.cislo1.value;
	var cislo2Var=form.elements.cislo2.value;
	
	if(isNaN(cislo1Var) || isNaN(cislo2Var) || cislo1Var =="" || cislo2Var=""){
		return false;
	}
	return true;
}