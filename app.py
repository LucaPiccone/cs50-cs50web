import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session['user_id']

    stocks_owned = db.execute('SELECT * FROM assets WHERE user_id = ?', user_id)

    cash_balance = {}
    cash_balance['symbol'] = 'CASH'
    cash_balance['total'] = db.execute('SELECT cash FROM users WHERE id = ?', user_id)[0]['cash']

    for stock_owned in stocks_owned:
        stock_owned['current_price'] = lookup(stock_owned['symbol'])['price']
        stock_owned['total'] = round(stock_owned['current_price'] * stock_owned['quantity'], 2)

    stocks_owned.append(cash_balance)

    bank = {}
    bank_balance = 0
    for stock_owned in stocks_owned:
        bank_balance += stock_owned['total']
        try:
            stock_owned['total'] = usd(stock_owned['total'])
            stock_owned['current_price'] = f"${stock_owned['current_price']}"
            stock_owned['total_cost'] = usd(stock_owned['total_cost'])
        except:
            continue

    bank['current_price'] = 'TOTAL'
    bank['total'] = usd(bank_balance)

    stocks_owned.append(bank)

    print(stocks_owned)

    return render_template('index.html', stocks=stocks_owned)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        date_time = str(datetime.datetime.now())

        symbol = request.form.get('symbol')
        try:
            shares = int(request.form.get('shares'))
            if shares < 1:
                return apology("Number of shares must be positive")
        except:
            return apology("Shares must be an integer")

        stock = lookup(symbol)

        if stock == None:
            return apology("Invalid Symbol")
        elif shares < 1:
            return apology("# of shares must be a positive integer")

        stock_price = stock['price']
        stock_name = stock['name']
        stock_symbol = stock['symbol']
        user_id = session['user_id']
        user_cash = db.execute('SELECT cash FROM users WHERE id = ?', user_id)
        transaction = 'BUY'

        if len(user_cash) != 1:
            return apology("An error has occured")

        user_cash = user_cash[0]['cash']

        # Calculate the total price
        final_price = stock_price * 100
        total_cost = round(shares * final_price) / 100
        cash_balance = user_cash - total_cost

        if user_cash < total_cost:
            return apology("Not enough funds")

        # add to current assets if available
        asset_symbol = ''
        try:
            asset = db.execute('SELECT * FROM assets WHERE user_id = ? AND symbol = ?', user_id, stock_symbol)
            asset_symbol += asset[0]['symbol']
            asset_quantity = asset[0]['quantity'] + shares
            asset_price = round((stock['price'] + asset[0]['price']) / 2, 2)
            asset_total_cost = round(asset[0]['total_cost'] + total_cost, 2)

        except:
            pass

        print(asset_symbol)
        # Insert the transaction into transactions table
        db.execute('INSERT INTO transactions (stock, symbol, price, quantity, total_cost, date_time, transactions, user_id) VALUES(?, ?, ?, ?, ?, ?, ?, ?)',
                   stock_name, stock_symbol, stock_price, shares, total_cost, date_time, transaction, user_id)

        if asset_symbol == stock_symbol:
            db.execute('UPDATE assets SET price = ?, quantity = ?, total_cost = ? WHERE user_id = ?',
                       asset_price, asset_quantity, asset_total_cost, user_id)
        else:
            db.execute('INSERT INTO assets (stock, symbol, price, quantity, total_cost, user_id) VALUES(?, ?, ?, ?, ?, ?)',
                       stock_name, stock_symbol, stock_price, shares, total_cost, user_id)

        db.execute('UPDATE users SET cash = ? WHERE id = ?', cash_balance, user_id)

        return redirect('/')

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
#    return apology("TODO")
    stocks = db.execute('SELECT * FROM transactions WHERE user_id = ? ORDER BY date_time', session['user_id'])

    return render_template('history.html', stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get('symbol')

        quote = lookup(symbol)

        if quote == None:
            return apology("Invalid Symbol")

        # print("-->", quote)

        return render_template('quoted.html', quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":
        existingUsers = db.execute("SELECT username FROM users")

        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        if not username or not password or not confirmation:
            return apology("Empty fields")

        elif password != confirmation:
            return apology("Passwords do not match")

        for user in existingUsers:
            if username in user['username']:
                return apology("Username is taken")

        pw_hash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, pw_hash)

        handleUser = db.execute("SELECT * FROM users WHERE username = ?", username)

        session["user_id"] = handleUser[0]["id"]

        return redirect('/')

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session['user_id']
    stocks_owned = db.execute('SELECT * FROM assets WHERE user_id = ?', user_id)

    if request.method == "POST":
        date_time = str(datetime.datetime.now())
        symbol = request.form.get('symbol')
        try:
            shares = int(request.form.get('shares'))
            if shares < 1:
                return apology("Invalid amount of shares")
        except:
            return apology("Invalid amount of shares")

        stocks_list = []
        for stock_owned in stocks_owned:
            if stock_owned['symbol'] == symbol:
                if shares > stock_owned['quantity']:
                    return apology('You don\'t own this amount of stock')
            stocks_list.append(stock_owned['symbol'])

        if symbol not in stocks_list:
            return apology('You do not own that stock')

        stock = lookup(symbol)

        stock_price = stock['price']
        stock_name = stock['name']
        stock_symbol = stock['symbol']
        user_id = session['user_id']
        user_cash = db.execute('SELECT cash FROM users WHERE id = ?', user_id)
        transaction = "SOLD"
        # update the user cash
        final_price = stock_price * 100
        total_cost = round(shares * final_price) / 100
        cash_balance = user_cash[0]['cash'] + total_cost

        # update the cost of assests
        asset = db.execute('SELECT * FROM assets WHERE user_id = ? AND symbol = ?', user_id, symbol)
        asset_price = round((stock['price'] + asset[0]['price']) / 2, 2)
        asset_quantity = asset[0]['quantity'] - shares
        asset_total_cost = round(asset[0]['total_cost'] - total_cost, 2)

        db.execute('INSERT INTO transactions (stock, symbol, price, quantity, total_cost, date_time, transactions, user_id) VALUES(?, ?, ?, ?, ?, ?, ?, ?)',
                   stock_name, stock_symbol, stock_price, shares, total_cost, date_time, transaction, user_id)

        if asset_quantity == 0:
            db.execute('DELETE FROM assets WHERE user_id = ? AND symbol = ?', user_id, symbol)
        else:
            db.execute('UPDATE assets SET price = ?, quantity = ?, total_cost = ? WHERE user_id = ? AND symbol = ?',
                       asset_price, asset_quantity, asset_total_cost, user_id, stock_symbol)

        db.execute('UPDATE users SET cash = ? WHERE id = ?', cash_balance, user_id)

        return redirect('/')

    else:
        return render_template('sell.html', stocks=stocks_owned)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


# import time
# https://docs.python.org/3/
# https://www.sqlite.org/index.html
# CS50