# LCP E-Commerce
#### Video Demo:  <URL HERE>
#### Description:
    LCP E-Commerce is a website built for the purpose of buying and selling products online. The platform was built upon the Flask framework and implements languages such as Python, Javascript, HTML and CSS from the back-end to the front-end. The program includes a back-end server that communicates the applications and the database to the user interface.

    The back-end of the application is written in Python using the Flask micro web framework. It was designed for users to insert and retrieve information from the database securely and to display relevant information to the user interface. The application implements features such as: creating an account, email verification, logging in, and shopping for products. Specific libraries were included to make these function possible such as Flask-Mail, werkzeug and more.

    The application connects to a postgresql database using psycopg2. This method of connection was chosen because it closely resembles the implementation of sqlite. Another option was to connect the database using SQLAlchemy.

    The user interface is created with the help of HTML, CSS, Jinja, and Javascript. The HTML and CSS components make up the layout and design of the webpage, while Jinja retrieves information from the sever and Javascript applies features to allow for user interaction. The search component is a good example of a component of the webpage that implements all languages. The search bar implements AJAX requests asynchronously Javascript and XML. This feature sends requests to the server depending on the user input and returns data based on the results. The data is then shown to the user using without having to reload the webpage.