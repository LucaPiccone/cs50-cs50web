document.addEventListener('DOMContentLoaded', function () {

    // ---------------- CONFIRM REGISTER FORM ---------------- //
    form = document.querySelector('#registerform')
    checkbox = document.querySelector('#termsandconditions')
    names = document.querySelector('#name')
    password = document.querySelector('#floatingPassword')
    cpassword = document.querySelector('#floatingCPassword')

    form.addEventListener('submit', function (event) {
        if (checkbox.checked === false)
        {
            alert("Please accept the terms and conditions");
            event.preventDefault()
            return false;
        }
        else if (password.value !== cpassword.value) 
        {
            alert("Password do not match")
            event.preventDefault()
            return false; 
        }
        return true;
    })
})