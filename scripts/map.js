/* Geolocation */
document.addEventListener('DOMContentLoaded', function() {
    navigator.geolocation.getCurrentPosition(function(position) {
    let latitude = position.coords.latitude;
    let longitude = position.coords.longitude;
    document.querySelector('#searchLocation').value = (latitude + ", " + longitude);
    });

    if (!localStorage.getItem('style'))
        localStorage.setItem('style', 'styles.css')

    stylesheet.href = localStorage.getItem('style')

    document.querySelector('.btn-dark').addEventListener('click', () => {
        let style = localStorage.getItem('style')
        style = 'stylesDark.css'
        stylesheet.href = style
        localStorage.setItem('style', style)
    })

    document.querySelector('.btn-light').addEventListener('click', () => {
        let style = localStorage.getItem('style')
        style = 'styles.css'
        stylesheet.href = style
        localStorage.setItem('style', style)
    })

});