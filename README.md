# LCP E-Commerce
#### Video Demo:  <https://youtu.be/9oG2qTIWTRI>
#### Description:

    LCP E-Commerce is a website built for the purpose of buying and selling products online. The platform was built upon the Flask framework and implements languages such as Python, Javascript, HTML and CSS from the back-end to the front-end. The program includes a back-end server that communicates the applications and the database to the user interface.

    The back-end of the application is written in Python using the Flask micro web framework. It was designed for users to insert and retrieve information from the database securely and to display relevant information to the user interface. The application implements features such as: creating an account, email verification, logging in, and shopping for products. Specific libraries were included to make these function possible such as Flask-Mail, werkzeug and more.

    The application connects to a postgresql database using psycopg2. This method of connection was chosen because it closely resembles the implementation of sqlite. Another option was to connect the database using SQLAlchemy.

    The user interface is created with the help of HTML, CSS, Jinja, and Javascript and JQuery. The HTML and CSS components make up the layout and design of the webpage, while Jinja retrieves information from the sever and Javascript applies features to allow for user interaction. The search component and the add to cart button were created using AJAX requests asynchronously Javascript and XML. JQuery was a library involved to help make AJAX requested.

### Features:

    The application is created using various different components. Some of my favourite features of the website include, the database connection, the cart and the login confirmation and the search bar.

    The Database Connection file names db.py initiates the connection to the database on a local server and includes functions the application can use to connect to the database. The first function is db(query, args)'s purpose is to query the database. The db_insert(table, query, args)'s purpose is to insert into the database. the @app.teardown_appcontext closes the database connection one the app has stopped running.

    The Cart was the hardest feature to implement according to my vision. The main struggle was trying to change the quantities of each item because of the input type and submitting the quantity. I wanted uses to be able to enter a quantity through the number pad and use the arrows provided by the component. Each change in quantity needed to send the specific products id back to the server to have the price readjusted according.

    The Login Confirmation was fun to create although gmail no longer allows for unsafe apps so I had to begin to use an outlook account. After connecting to flask mail, I had to create a token specific to each users email address. Once the token is generated is sent to the user in the form of a url to their email address. After clicking the link the users 'confirmed' column in the database changes to 0 from 1;

    The Search Bar uses AJAX requests to take the users input and query the database. The script is constantly waiting for input from the user to query the database and return information to the front end without having to reload the page. The query looks through the products table where the brand or the name begins with the inputted letters.


    ### REFERENCES:
        # CS50
        # https://flask.palletsprojects.com/en/2.2.x/
        # The ANSI C Programming Language - Brian w. kernighan and Dennis M.Ritchie
        # HTML & css john duckett
        # Javacript & Jquery - jon duckett
        # https://www.youtube.com/playlist?list=PLzMcBGfZo4-n4vJJybUVV3Un_NFS5EOgX
        # https://www.youtube.com/watch?v=_U_hJZ9uA2g
        # https://flask.palletsprojects.com/en/1.1.x/
        # Pretty Printed - Using flask-Mail to Send Email Confirmation Links - youtube
        # https://stackoverflow.com/questions/25564399/send-json-response-from-sqlite-queries-in-python
        # https://stackoverflow.com/questions/41323679/how-to-send-data-to-flask-via-ajax
        # https://www.youtube.com/watch?v=zJdQxS3ZpNI
        # https://flask.palletsprojects.com/en/1.0.x/security/#security-cookie
        # https://www.udemy.com/course/django-with-react-an-ecommerce-website
        # https://stackoverflow.com/questions/21158033/query-from-postgresql-using-python-as-dictionary
        # https://www.postgresql.org/files/developer/concurrency.pdf