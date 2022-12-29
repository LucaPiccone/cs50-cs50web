document.addEventListener('DOMContentLoaded', () => {
    // ---------------- Search JS ---------------- //
    document.querySelector('#searchInput').addEventListener('keyup', function(event) {     
        search = document.querySelector('#searchInput').value
        $.ajax({
            url: '/search',
            data: {'data': search},
            type: 'GET',
            success: function(response) {
                document.querySelector('#searchSuggestions').innerHTML = response.data
                if (search === "") {
                    document.querySelector('#searchSuggestions').innerHTML = ""
                }
            },
            error: function(error) {
                console.log(error);
            }
        });
    })


    // ---------------- SITE JS ---------------- //
    form = document.querySelectorAll('form')
    password = document.querySelectorAll('.password')
    
    $(form).on('keypress', function (event) {
        var regex = new RegExp("^[a-zA-Z0-9!#-&(-/@=_\r ]+$");
        var key = String.fromCharCode(!event.charCode ? event.which : event.charCode);
        if (!regex.test(key)) {
           event.preventDefault();
           return false;
        }
    });

    $('.password').on('keypress', function (event) {
        var regex = new RegExp("^[a-zA-Z0-9!#-&(-/@=_\r ]+$");
        var key = String.fromCharCode(!event.charCode ? event.which : event.charCode);
        if (!regex.test(key)) {
           alert('That special character is not allowed')
           event.preventDefault();
           return false;
        }
    });


    // ---------------- PRODUCT JS ---------------- //
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


    // ---------------- CART JS ---------------- //
    // $('.itemQty').on('keypress focusout', () => {
    //   document.querySelector('.handleQty').submit()
    // })    


    // ---------------- REGISTER JS ---------------- //

    // let registerform = document.querySelector('#registerform')
    // registerform.addEventListener('submit', (e) => {
    //     let checkbox = document.querySelector('#termsandconditions')
    //     let password = document.querySelector('#floatingPassword')
    //     let cpassword = document.querySelector('#floatingCPassword')
    //     if (!checkbox.checked)
    //     {
    //         e.preventDefault()
    //         document.querySelector('#error').innerHTML = 'Please check the box'
    //     }
    //     else if (password !== cpassword)
    //     {
    //         e.preventDefault()
    //         document.querySelector('#error').innerHTML = 'Passwords do not match'
    //     }
    //     else {
    //         registerform.submit()
    //     }
    // })
    
})