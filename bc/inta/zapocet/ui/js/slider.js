function getPrices() {
    let pricesNL = document.getElementsByClassName("price");
    let pricesStr = Array.from(pricesNL);
    let n = pricesStr.length;
    let pricesNum = [];
    for(i=0; i<n; i++){
        pricesNum.push(pricesStr[i].innerHTML);
    }
    pricesNum = pricesNum.map(Number);
    let maxPrice = Math.max.apply(Math, pricesNum) + 0.01;
    let minPrice = Math.min.apply(Math, pricesNum);
    let prices = [minPrice, maxPrice];
    return prices;
}


function getPlayers(){
    let playersMinNL = document.getElementsByClassName("playersMin");
    let playersMaxNL = document.getElementsByClassName("playersMax");

    let playersMinStr = Array.from(playersMinNL);
    let playersMaxStr = Array.from(playersMaxNL);

    let nMin = playersMinStr.length;
    let nMax = playersMaxStr.length;

    let playersMinNum = [];
    let playersMaxNum = [];

    for(i=0; i<nMin; i++){
        playersMinNum.push(playersMinStr[i].innerHTML);
    }
    for(j=0; j<nMax; j++){
        playersMaxNum.push(playersMaxStr[j].innerHTML);
    }

    playersMinNum = playersMinNum.map(Number);
    playersMaxNum = playersMaxNum.map(Number);

    let minPlayers = Math.min.apply(Math, playersMinNum);
    let maxPlayers = Math.max.apply(Math, playersMaxNum);
    let players = [minPlayers, maxPlayers];
    return players;
}

/*function inStock(product){

}

function inPriceRange(product){

}

function inPlayerRange(product){

}

function filterCheck(){
    let prices = $(".price").get();
    for(let i = 0; i < prices.length; i++) {
        if (inStock(prices[i]) && inPriceRange(prices[i]) && inPlayerRange(prices[i])) {
            prices[i].parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "inline-flex";
        } else {
            prices[i].parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "none";
        }
    }
}

$( "#sliderPrice" ).on( "slidechange", function( event, ui ) { filterCheck();} );*/

$(function(){
    $("#sliderPrice").slider({
        range: true,
        min: getPrices()[0],
        max: getPrices()[1],
        step: 0.01,
        values: [0, 1],
        slide: function( event, ui ) {
            $("#amountPrice").val(ui.values[ 0 ] + "€ – " + ui.values[ 1 ] + "€");
        },
        change: function(event, ui){
            let prices = $(".price").get();
            for (let i = 0; i < prices.length; i++){
                if (parseFloat(prices[i].innerHTML) < ui.values[0] || parseFloat(prices[i].innerHTML) > ui.values[1]){
                    prices[i].parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "none";
                }
                else if (parseFloat(prices[i].innerHTML) >= ui.values[0] && parseFloat(prices[i].innerHTML) <= ui.values[1]){
                    prices[i].parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "inline-flex";
                }
            }
        }
    });
//$("#sliderPrice").slider("option", "max", getPrices()[1]);
//$("#sliderPrice").slider("option", "min", getPrices()[0]);
    $("#sliderPrice").slider("option", "values", [getMaxPrice()[0], getMaxPrice()[1]]);

    $("#amountPrice").val($("#sliderPrice").slider("values", 0) + "€ – "
        + $("#sliderPrice").slider("values", 1 ) + "€");
});


$(function(){
    $("#sliderPlayers").slider({
        range: true,
        min: 0,
        max: 1,
        step: 1,
        values: [0, 1],
        slide: function( event, ui ) {
            $("#amountPlayers").val(ui.values[ 0 ] + " – " + ui.values[ 1 ]);
        },
        change: function (event, ui){
            let playersMin = $(".playersMin").get();
            let playersMax = $(".playersMax").get();
            if(playersMin.length == playersMax.length || playersMin.length > playersMax.length)
                var n = playersMin.length;
            else
                var n = playersMax.length;
            for(let i = 0; i < n; i++){
                if((parseInt(playersMin[i].innerHTML) < ui.values[0] || parseInt(playersMax[i].innerHTML) > ui.values[1]) || (parseInt(playersMin[i].innerHTML) > ui.values[1]) || (parseInt(playersMax[i].innerHTML) < ui.values[0])){
                    playersMin[i].parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "none";
                }
                else if(parseInt(playersMin[i].innerHTML) >= ui.values[0] && parseInt(playersMax[i].innerHTML) <= ui.values[1]){
                    playersMin[i].parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "inline-flex";
                }

            }
        }
    });
    $("#sliderPlayers").slider("option", "min", getPlayers()[0]);
    $("#sliderPlayers").slider("option", "max", getPlayers()[1]);
    $("#sliderPlayers").slider("option", "values", [getPlayers()[0], getPlayers()[1]]);

    $("#amountPlayers").val($("#sliderPlayers").slider("values", 0) +
        " – " + $("#sliderPlayers").slider("values", 1 ));
});


$("#stockCheck").click(function (){
    let inStock = $(".inStockAmount").get();
    if ($("#stockCheck").prop('checked') == true){
        for (let i = 0; i < inStock.length; i++){
            if (inStock[i].innerHTML == "0"){
                inStock[i].parentNode.parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "none";
            }
        }
    }

    if ($("#stockCheck").prop('checked') == false){
        for (let i = 0; i < inStock.length; i++) {
            if (inStock[i].innerHTML == "0" ) {
                inStock[i].parentNode.parentNode.parentNode.parentNode.parentNode.parentNode.style.display = "inline-flex";
            }
        }
    }
});
