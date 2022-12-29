document.addEventListener('DOMContentLoaded', function () {

    let addtocart = document.querySelector('.addtoCartBtn')
    addtocart.addEventListener('click', function() {
        let product_id = addtocart.value
        let product_qty = document.querySelector('#productQty').value
        console.log(product_id)
        console.log(product_qty)
        ajax = new XMLHttpRequest();
        ajax.open('POST', '/product/' + product_id, true)
        ajax.onload = function() {
            if (ajax.readyState == 4 && ajax.status == 200)
            {
                response = JSON.parse(ajax.response.trim())
                console.log(response)
                document.querySelector('#addtoCartBanner').innerHTML = response.data
            }
        }
        let sendData = new FormData();
        sendData.append('data', product_id)
        sendData.append('quantity', product_qty)
        ajax.send(sendData)
    })

})