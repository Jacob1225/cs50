import os, sys

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, has_number, has_uppercase

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

    # Query the database to get the user's cash remaining
    row = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

    cash = row[0]["cash"]

    # Query the database to retrieve transaction information
    rows = db.execute("SELECT symbol, name, sum(shares) as total_shares FROM transactions WHERE user_id= :user_id GROUP BY symbol HAVING total_shares > 0",
                       user_id=session["user_id"])

    # Create a dictionary to store the information to be passed on to index.html
    stock_info = {}
    total = cash
    # Loop over the rows data to store it into the stock_info
    for stock in rows:
        stock_info[stock["symbol"]] = lookup(stock["symbol"])
        total += stock["total_shares"] * stock_info[stock["symbol"]]["price"]


    return render_template("index.html", stocks=stock_info, rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Retrieve the information about the stock
        quote = lookup(request.form.get("symbol"))

        # Verfiy if symbol is valid
        if quote == None:
            return apology("Symbol is invalid")

        # Ensure a postive number of shares was provided
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("Number of shares must be a positive integer", 403)

        # If user wants to buy 0 shares
        if shares == 0:
            return apology("Must purchase at least 1 share", 403)

        # Query database for the current user making a purchase
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # Find how much cash user has left
        cash = rows[0]["cash"]

        # Find price per share
        price_per_share = quote["price"]

        # Find total price of transaction
        price = shares * price_per_share

        # Determine if user has enough cash to complete transaction
        if cash < price:
            return apology("Not enough funds available", 403)

        # If enough cash make the transaction go through
        #Update the users cash in the users table
        cash_remaining = cash - price
        db.execute("UPDATE users SET cash = :cash_remaining WHERE id = :user_id", cash_remaining=cash_remaining, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, name) VALUES (:user_id, :symbol, :price, :shares, :name)",
                    user_id=session["user_id"],
                    symbol=request.form.get("symbol"),
                    price=price_per_share,
                    shares=shares,
                    name=quote["name"])

        # Notify user that they have successfully bought shares
        flash("Bought!")

        # Redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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

    # If the user is posting to the search form
    if request.method == "POST":

        # If no symbol is provided
        if not request.form.get("symbol"):
            return apology("Must provide a symbol", 403)

        quote = lookup(request.form.get("symbol"))

        # If the symbol is invalid
        if quote == None:
            return apology("Symbol is invalid", 403)

        name = quote["name"]
        symbol = quote["symbol"]
        price = usd(quote["price"])
        return render_template("quoted.html", name=name, symbol=symbol, price=price)

    # If the user wants to get to the quote page
    elif request.method == "GET":
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User submits registration form
    if request.method == "POST":

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        password = request.form.get("password")

        # if the user wants to register with a username that is taken
        if len(rows) == 1:
            return apology("Username is already taken", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords did not match", 403)

        # Ensure password is at least 8 characters long, has at least 1 uppercase, at least 1 number
        elif len(password) < 8 or not has_number(password) or not has_uppercase(password):
            return apology("Password must be at least 8 characters long with at least 1 number and 1 uppercase letter", 403)

        #Hash the password and insert it into the db
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        user = db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)", username=username, hash=hash)

        # Remember user
        session["user_id"] = user

        flash("Registered")

        # Redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User submits selling form
    if request.method == "POST":

        # Find current sale price of a share
        quote = lookup(request.form.get("symbol"))

        # Verify if symbol is valid
        if quote == "None":
            return apology("Invalid symbol", 403)

         # Query the database to see if user has enough shares
        shares = db.execute("SELECT sum(shares) as total_shares FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
                            user_id=session["user_id"], symbol=request.form.get("symbol"))

        stocks = int(request.form.get("shares"))
        if shares[0]["total_shares"] < stocks:
            return apology("Not enough shares to sell", 403)

        # Price per share
        price_per_share = quote["price"]

        # Find total value of sale
        value = price_per_share * stocks

        # Update the cash column for the user
        db.execute("UPDATE users SET cash = cash + :value WHERE id = :user_id", value=value, user_id=session["user_id"])

        # Insert the sale transactions in the transactions table
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, name) VALUES (:user_id, :symbol, :price, :shares, :name)",
                    user_id=session["user_id"],
                    symbol=request.form.get("symbol"),
                    price=price_per_share,
                    shares=(-1 * stocks),
                    name=quote["name"])

        # Redirect the user to the homepage
        return redirect("/")


    # User reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT symbol, sum(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0", user_id=session["user_id"])
        return render_template("sell.html", symbols=symbols)

@app.route("/add", methods=["GET", "POST"])
@login_required
def add_funds():
    """Allows users to add funds to their account"""

    # User submits add funds form
    if request.method == "POST":

        try:
            amount = float(request.form.get("amount"))

        except:
            return apology("Amount must be a number", 403)

        # Update cash column of users table in db
        db.execute("UPDATE users SET cash = cash + :amount WHERE id = :user_id", amount=amount, user_id=session["user_id"])

        # Notify user that funds were successfully added
        flash("Funds successfully added!")

        # redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("add.html")

@app.route("/change", methods=["GET", "POST"])
@login_required
def change_password():
    """Allow user to change their password"""
    # User submits change password form
    if request.method == "POST":

        # Ensure both password and confirmation match
        password = request.form.get("password")

        if password != request.form.get("confirmation"):
            return apology("Passwords do not match", 403)

        # Ensure password is at least 8 characters long, has at least 1 uppercase, at least 1 number
        elif len(request.form.get("password")) < 8 or not has_number(password) or not has_uppercase(password):
            return apology("Password must be at least 8 characters long with at least 1 number and 1 uppercase letter")

        # Hash new password and update the database
        hash = generate_password_hash(password)
        db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", hash=hash, user_id=session["user_id"])

        # Notify the user that the password has been successfully changed
        flash("Password successfully changed!")

        # Redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
