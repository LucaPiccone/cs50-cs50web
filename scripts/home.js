function listen() {
    /* Greeting function */
    if (!localStorage.getItem('username')) {
        localStorage.setItem('username', 'Welcome !')
    }
    else if (localStorage.getItem('username') !== 'Welcome !') {
        document.querySelector('#name').style.display = "none"
        document.querySelector('#submitName').style.display = "none"
    }
    document.querySelector('#greetFriend').innerHTML = localStorage.getItem('username')

    document.querySelector('#greet').addEventListener('submit', () => {
        let username = localStorage.getItem('username')
        let name = document.querySelector('#name').value;
        username = ('Welcome ' + name + '!')

        document.querySelector('#greetFriend').innerHTML = (username);
        localStorage.setItem('username', username)

        document.querySelector('#name').style.display = "none"
        document.querySelector('#submitName').style.display = "none"
    })
}

document.addEventListener('DOMContentLoaded', listen);