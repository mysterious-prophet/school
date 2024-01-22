$("#alphabet").click(function () {
    //let order = document.getElementById("order");
    //let methodType = order.options[order.selectedIndex].value; //0-3
    let sortByName = function (a, b) {
        return a.id.toLowerCase().localeCompare(b.id.toLowerCase());
    }
    let products = $(".products > .product").get();
    products.sort(sortByName);
    for (let i = 0; i < products.length; i++) {
        products[i].parentNode.appendChild(products[i]);
    }
});