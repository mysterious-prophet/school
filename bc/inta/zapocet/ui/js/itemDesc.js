if (document.getElementsByClassName("prodDesc")) {
  var autos = document.getElementsByClassName("prodDesc");
  for (var i=0; i<autos.length; i++) {
    autos[i].addEventListener("mouseover", autoOver);
    autos[i].addEventListener("mouseout", autoOut);
  }
}

function autoOver() {
  this.style.height = this.scrollHeight + "px";
}

function autoOut() {
  this.style.height = "80px";
}