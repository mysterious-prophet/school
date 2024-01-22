function kontrola(form){
	var jmenoVar= form.elements.jmeno.value;
	var hesloVar=form.elements.heslo.value;
	var emailVar=form.elements.email.value;
	var souhlasVar=form.elements.souhlas.value;
	var datumVar=form.elements.datum.value;
	var napojeVar=form.elements.napoje.value;
	
	if(jmenoVar=="" || hesloVar=="" || emailVar==""){
		return false;
	}
	if(souhlasVar==false){
		return false;
	}
	window.alert(jmenoVar + " " + hesloVar + " " + emailVar + " " + datumVar + " " + napojeVar);
	return true;	
}