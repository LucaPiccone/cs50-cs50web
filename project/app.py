# flask --app app run           Regular mode 
# flask --app app --debug run   Debug mode 
import datetime
from db import get_db, db, db_insert, close_database
from flask import Flask, g, jsonify, redirect, render_template, request, session, url_for
from flask_mail import Mail, Message
from functions import login_required, admin_required, cad
from itsdangerous import URLSafeTimedSerializer, SignatureExpired
import os
import pytz
from werkzeug.security import generate_password_hash, check_password_hash
from werkzeug.utils import secure_filename


app = Flask(__name__)
mail = Mail(app)

s = URLSafeTimedSerializer('SECRET')

app.config['SECRET_KEY']            = 'SECRET'
app.config["MAIL_DEFAULT_SENDER"]   = os.getenv('MAIL_DEFAULT_SENDER')
app.config["MAIL_PASSWORD"]         = os.getenv('MAIL_PASSWORD')
app.config["MAIL_PORT"]             = 587
app.config["MAIL_SERVER"]           = "smtp.gmail.com"
app.config["MAIL_USE_TLS"]          = True
app.config["MAIL_USERNAME"]         = os.getenv('MAIL_USERNAME')
mail = Mail(app)



# --------------- MAIN --------------- #
@app.route('/')
def index():
    products = db('SELECT * FROM products')

    print(products)

    try:
        return render_template('index.html', products=products, name=session['user'].title())
    except:
        return render_template('index.html', products=products, name='Guest')


# --------------- SEARCH --------------- #
@app.route('/search', methods=["GET", "POST"])
def getdata():
    if request.method == "POST":
        search = request.form.get('?')
        
        print('-------------------', search, '----------')

        products = db('SELECT * FROM products WHERE LOWER(name) LIKE LOWER(%s) OR LOWER(brand) LIKE LOWER(%s)', [f'{search}%', f'{search}%'])
        
        if len(products) < 1:
            return render_template('index.html')
        
        try:
            return render_template('index.html', products=products, name=session['user'].title())
        except:
            return render_template('index.html', products=products, name='Guest')

    else:
        search = request.values.get('data')

        companies = db('SELECT DISTINCT brand FROM products WHERE UPPER(brand) LIKE UPPER(%s) ORDER BY brand', [f'{search}%'])
        items = db('SELECT DISTINCT name FROM products WHERE UPPER(name) LIKE UPPER(%s) ORDER BY name', [f'{search}%'])
        products = []
        # print(companies)
        # print(items)

        for company in companies:
            dict = {}
            dict['brand'] = company['brand']
            products.append(dict)

        for item in items:
            dict = {}
            dict['name'] = item['name']
            products.append(dict)

        if len(products) > 10:
            products = products[0:10]

        return jsonify({'data': render_template('search.html', products=products)})


# --------------- CART --------------- #
@app.route('/cart', methods=["GET", "POST"])
def cart():
    if request.method == "POST":
        quantity    = int(request.form.get('qty'))
        id          = int(request.form.get('id'))
        product_qty = int(request.form.get('originalqty'))

        print('=---------------', quantity)
        print('=---------------', id)
        print('=---------------', product_qty)

        if 'cart' not in session:
            session['cart'] = []
            
        cart = session['cart']

        if quantity == 0:
            for product in cart:
                if id == product['id']:
                    cart.remove({'id': id, 'qty': product_qty})

        for item in cart:
            if id == item['id']:
                item['qty'] = quantity

        print(cart)

        session['cart'] = cart
        
        products = []
        for item in cart:
            product = db('SELECT * FROM products WHERE id IN (%s)', [item['id']])
            dict = {}
            dict['name'] = product[0]['name']
            dict['price'] = product[0]['price']
            dict['image'] = product[0]['image']
            dict['id'] = product[0]['id']
            dict['qty'] = item['qty']
            products.append(dict)
        
        subtotal = 0
        tax = 0
        total = 0
        for item in products:
            subtotal += (float(item['price'] * int(item['qty'])) * 100)

        tax = round(round(subtotal * 0.13, 2) / 100, 2)
        subtotal = round(subtotal / 100, 2)
        total = subtotal + tax

        tax = cad(float(tax))
        subtotal = cad(float(subtotal))
        total = cad(float(total))

        session['cart'] = cart
        return redirect('/cart')

    elif request.method == "GET":
        if "cart" not in session:
            session["cart"] = [] 
            
        cart = session['cart']

        products = []
        subtotal = 0
        tax = 0
        total = 0
        for item in cart:
            product = db('SELECT * FROM products WHERE id IN (%s)', [item['id']])
            dict = {}
            dict['name'] = product[0]['name']
            dict['price'] = product[0]['price']
            dict['image'] = product[0]['image']
            dict['id'] = product[0]['id']
            dict['qty'] = item['qty']
            products.append(dict)

        for item in products:
            subtotal += (float(item['price']) * 100)

        subtotal = 0
        tax = 0
        total = 0
        for item in products:
            subtotal += (float(item['price'] * int(item['qty'])) * 100)

        tax = round(round(subtotal * 0.13, 2) / 100, 2)
        subtotal = round(subtotal / 100, 2)
        total = subtotal + tax

        tax = cad(float(tax))
        subtotal = cad(float(subtotal))
        total = cad(float(total))
        session['cart'] = cart

        return render_template('cart.html', products=products, total=total, tax=tax, subtotal=subtotal)


# --------------- PRODUCTS --------------- #
@app.route('/product/<id>', methods=["GET", "POST"])    
def product(id):
    if request.method == "POST":
        product_id = int(request.values.get('data').strip())
        product_qty = int(request.values.get('quantity').strip())

        print(product_id)
        print(product_qty)

        if "cart" not in session:
            session["cart"] = []
        
        cart = session["cart"]

        print('----------', cart)

        if not product_id or not product_qty:
            return '<p>Something went wrong</p>'
        
        cart_product = {}
        cart_product['id'] = product_id
        cart_product['qty'] = product_qty

        cart_check = 0
        for dict in cart:
            if str(cart_product['id']) in str(dict['id']):
                cart_check += 1 
                break
            
        if cart_check == 0:
            cart.append(cart_product)
        else:
            for item in cart:
                if item['id'] == cart_product['id']:
                    item['qty'] += cart_product['qty']
                    break

        session['cart'] = cart
        
        return redirect(f'/product/{id}')

    else:
        # View the product page
        product = db('SELECT * FROM products WHERE id = %s',[id] )
        print(id)
        return render_template('product.html', product=product)

        
# --------------- CHECKOUT --------------- #
@app.route('/checkout', methods=['GET', 'POST'])
@login_required
def checkout():
    if request.method == 'POST':
        if 'cart' not in session:
            session['cart'] = []

        cart = session['cart']

        print(len(cart))

        if len(cart) == 0:
            redirect('/cart')

        #
    else:
        # Render payment form 

        # insert into payment method 
        return render_template('checkout.html')

    


    return redirect('/cart')

# --------------- USER --------------- #

# ------ LOG IN ------ #
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        
        print(email)
        print(password)

        if not email or not password:
            return render_template('login.html', error="Empty form")

        users = db('SELECT * FROM users WHERE email = %s', [email])

        if len(users) != 1 or not check_password_hash(users[0]['password'], password):
            return render_template('login.html', error="Incorrect username or password.")

        session["user_id"] = users[0]['id']
        session["user"] = users[0]['fname']

        return redirect('/')

    else:
        if 'user' in session:
            print(session['user'])

        return render_template('login.html')


# ------ LOG OUT ------ #
@app.route('/logout')
def logout():
    if 'user' in session:
        session.pop('user',None)
    return redirect('/')


# ------ REGISTER USER ------ #
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == "POST":
        fname       = request.form.get('fname').strip().lower()
        lname       = request.form.get('lname').strip().lower()
        email       = request.form.get('email').strip().lower()
        password    = request.form.get('password')
        cpassword   = request.form.get('cpassword')
        date        = datetime.datetime.now(tz=pytz.timezone('US/Eastern'))
        checkbox    = int(request.form.get('checkbox'))

        print(checkbox)

        if fname == None or lname == None or email == None or password == None or cpassword == None or checkbox != 1 or password != cpassword or len(password) < 6:
            return render_template('register.html', error="Please complete the form.")
        
        users = db('SELECT email FROM users')

        for user in users:
            if email.lower() == user['email'].lower():
                return render_template('register.html', error="An account has already been made with that email.")


        # HASH PASSWORD 
        hashed = generate_password_hash(password)

        # INSERT ACOUNT INTO DATABASE 
        db_insert("users", "INSERT INTO users (fname, lname, email, password, date) VALUES(%s, %s, %s, %s, %s)", [fname, lname, email, hashed, date])

        # SEND A CONFIRMATION EMAIL
        token = s.dumps(email, salt=b'emailconfirmation')

        print(token)

        message = Message("Verify your lcpecommerce account.", recipients=[email], body=f"Please follow this link to verify your account http://127.0.0.1:5000/emailconfirmation/{token}")
        mail.send(message) 

        session["user"] = fname

        return redirect('/')

    else:
        return render_template('register.html')


# # ------ CONFIRM EMAIL ------ #
@app.route('/emailconfirmation/<token>')
def email_confirmation(token):
    # Age 1 hr
    try: 
        email = s.loads(token, salt=b'emailconfirmation', max_age=(60 * 60 * 60))
        print('everything works')
        print(email)
        db_insert("users", "UPDATE users SET confirmation_token = %s WHERE email = %s", [0, email])
    except SignatureExpired:
        return 'Signiture expired'
    return redirect('/login')


# ------ FORGOT PASSWORD ------ #
# @app.route('/forgotpassword', methods=["GET", "POST"])
# def forgotPassword():
#     if request.method == "POST":
#         return "POST"
#     else:
#         return "GET"


# --------------- ADMIN LOGIN --------------- #

# ------ ADMIN LOG IN  ------ #
# @app.route('/admin/login', methods=['GET', 'POST'])
# def admin_login():
#     if request.method == "POST":
#         return "POST"
#     else:
#         return "GET"


# ------ ADMIN C.R.U.D ------ #
# @app.route('/admin/products', methods=["GET", "POST"])
# def admin_products():
#     if request.method == "POST":
#         return "POST"
#     else:
#         return "GET"


# The ANSI C Programming Language - Brian w. kernighan and Dennis M.Ritchie
# HTML & css john duckett
# Javacript & Jquery - jon duckett
# https://www.youtube.com/playlist?list=PLzMcBGfZo4-n4vJJybUVV3Un_NFS5EOgX
# https://www.youtube.com/watch?v=_U_hJZ9uA2g
# https://flask.palletsprojects.com/en/1.1.x/
# Pretty Printed - Using flask-Mail to Send Email Confirmation Links - youtube 
#https://stackoverflow.com/questions/25564399/send-json-response-from-sqlite-queries-in-python
#https://stackoverflow.com/questions/41323679/how-to-send-data-to-flask-via-ajax
#https://www.youtube.com/watch?v=zJdQxS3ZpNI
#https://flask.palletsprojects.com/en/1.0.x/security/#security-cookie
#https://www.udemy.com/course/django-with-react-an-ecommerce-website 
