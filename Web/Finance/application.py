import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

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
    # Get userid
    userid = session["user_id"]

    # Get portfolio data
    portfolio = db.execute("SELECT * FROM portfolio WHERE user_id=:id", id=userid)

    # Get total costs of stocks owned
    total = 0
    for row in portfolio:
        # Get current stock price
        stock = lookup(row["symbol"])
        shares = row["shares"]
        row["total"] = shares * stock["price"]
        row["price"] = stock["price"]
        total += row["total"]

    # Get user's balance
    userdb = db.execute("SELECT * FROM users Where id=:id", id=userid)
    balance = 0
    for row in userdb:
        balance = round(row["cash"], 2)

    # Get total for both stocks owned and user's balance
    newtotal = total + balance

    return render_template("index.html", portfolio=portfolio, balance=balance, newtotal=newtotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        userid = session["user_id"]
        symbol = request.form["symbolx"]
        share = int(request.form["sharex"])

        # Get stock information
        stock = lookup(symbol)
        stockname = stock["name"]
        stocksymbol = stock["symbol"]
        price = stock['price']

        # Ensure symbol input is not blank
        if not symbol:
            return apology("invalid symbol")

        # Ensure symbol is valid
        elif stock is None:
            return apology("invalid symbol")

        # Ensure share input is a positive integer
        elif share < 1:
            return apology("invalid number")


        else:

            # Get user's money
            userdb = db.execute(f"SELECT id, cash FROM users WHERE id='{userid}'")
            for row in userdb:
                cash = row['cash']

            # Total share bought
            total = share * price

            # Ensure user have enough cash to purchase shares
            if cash < total:
                return apology("not enough cash! sorry.")

            else:
                # Substract cash and update databse of balance
                balance = cash - total
                db.execute("UPDATE users SET cash=:balance WHERE id=:id", balance=balance, id=userid)

                # Record transaction into history
                db.execute("INSERT INTO history (user_id, symbol, name, price, shares, total) VALUES (:id, :symbol, :name, :price, :share, :total)",
                id=userid, symbol=stocksymbol, name=stockname, price=price, share=share, total=total)

                # Portfolio
                symboldb = db.execute("SELECT symbol FROM portfolio WHERE symbol=:symbol AND user_id=:id", symbol=stocksymbol, id=userid)
                if not symboldb:
                    # If none, insert into porfolio
                    db.execute("INSERT INTO portfolio (user_id, symbol, name, price, shares, total) VALUES (:id, :symbol, :name, :price, :shares, :total)",
                    id=userid, symbol=stocksymbol, name=stockname, price=price, shares=share, total=total)
                    return redirect("/buy")


                else:
                    oldsymbol=''
                    for row in symboldb:
                        oldsymbol = row["symbol"]
                    sharesdb = db.execute("SELECT shares FROM portfolio WHERE symbol=:symbol AND user_id=:id", symbol=stocksymbol, id=userid)
                    oldshares = ''
                    for row in sharesdb:
                        oldshares = row["shares"]
                    totaldb = db.execute("SELECT total FROM portfolio WHERE symbol=:symbol AND user_id=:id", symbol=stocksymbol, id=userid)
                    oldtotal = ''
                    for row in totaldb:
                        oldtotal = row["total"]

                    # Update portfolio database
                    for row in symboldb:
                        if stocksymbol == oldsymbol:
                            newshares = oldshares + share
                            newtotal = oldtotal + total
                            db.execute("UPDATE portfolio SET price=:price, shares=:shares, total=:total WHERE symbol=:symbol AND user_id=:id", price=price, shares=newshares, total=newtotal, symbol=oldsymbol, id=userid)
                            return redirect("/buy")



    else:
        # GET, load buy.html
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userid = session["user_id"]
    historydb = db.execute("SELECT symbol, shares, price, total, time FROM history WHERE user_id=:id", id=userid)
    for row in historydb:
        if row["total"] < 0:
            negative = row["shares"] * -1
            row["shares"] = negative
        else:
            None

    return render_template("history.html", historydb=historydb)


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
    if request.method == "POST":
        # Lookup for stock information
        stock = lookup(request.form["symbol"])

        # If symbol input field is left blank
        if not request.form["symbol"]:
            return apology("please provide stock symbol", 403)

        # If symbol provided is invalid
        if stock == None:
            return apology("symbol is invalid or none", 403)

        # Return the results of stock information into another html with the provided information
        else:
            return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])

    else:
        # GET, load quote
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        name = request.form["username"]
        dictdb = db.execute(f"SELECT username FROM users WHERE username='{name}'")
        usernameindb = ""
        for row in dictdb:
            usernameindb = row['username']

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure the password match
        elif request.form["confirmpassword"] != request.form["password"]:
            return apology("passsword does not match", 403)

        # Ensure username is not taken
        elif name == usernameindb:
            return apology("name is taken", 403)

        # Insert into database
        else:
            hashpw = generate_password_hash(request.form.get("confirmpassword"))
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashpw)", username=name, hashpw=hashpw)
            return redirect("/")

    else:
        # GET, load register page
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Get session ID
        userid = session["user_id"]

        # Get input data
        insymbol = request.form.get("symbol")
        inshares = int(request.form.get("shares"))

        # Lookup latest insymbol data
        stock = lookup(insymbol)

        # Ensure user selected a symbol
        if not insymbol:
            return apology("please select a symbol", 404)

        # Ensure user input amount of shares to be sold
        if not inshares:
            return apology("please provide shares to be sold", 404)

        # Ensure user input a positive integer for shares
        if inshares < 1:
            return apology("please provide a valid share amount", 404)

        # Ensure user have that amount of stock in database to be sold
        sharesdb = db.execute("SELECT shares FROM portfolio WHERE user_id=:id AND symbol=:symbol", id=userid, symbol=insymbol)
        sharesowned = 0
        for row in sharesdb:
            sharesowned += row["shares"]
        if inshares > sharesowned:
            return apology("not enough shares owned", 404)

        # The transaction process for selling shares
        # Update users cash
        cashdb = db.execute("SELECT cash FROM users WHERE id=:id", id=userid)
        cashowned = 0
        for row in cashdb:
            cashowned += row["cash"]
        soldshares = inshares * stock["price"]
        newcash = cashowned + soldshares
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=newcash, id=userid)

        # Update history
        negative = soldshares * -1
        db.execute("INSERT INTO history (user_id, symbol, name, price, shares, total) VALUES (:id, :symbol, :name, :price, :share, :total)",
        id=userid, symbol=insymbol, name=stock["name"], price=stock["price"], share=inshares, total=negative)

        # Update portfolio
        newshares = sharesowned - inshares
        db.execute("UPDATE portfolio SET shares=:shares WHERE user_id=:id", shares=newshares, id=userid)

        # Transaction succesful
        return redirect("/")


    else:
        # GET request.method
        # Get session ID
        userid = session["user_id"]

        # Get info from portfolio
        symboldb = db.execute("SELECT symbol FROM portfolio WHERE user_id=:id", id=userid)
        return render_template("sell.html", symboldb=symboldb)


@app.route("/changepw", methods=["GET", "POST"])
def changepassword():
    if request.method == "POST":

        # Get input from user
        username = request.form.get("username")
        oldpassword = request.form.get("password")
        newpassword = request.form.get("newpassword")

        # Ensure username is not blank
        if not username:
            return apology("please input username")

        # Ensure oldpassword is not blank
        if not oldpassword:
            return apology("please input old password")

        # Ensure newpassword is not blank
        if not newpassword:
            return apology("please input new password")

        # Get user's info from database
        userdb = db.execute("SELECT * FROM users WHERE username=:username", username=username)

        # Confirm username
        for row in userdb:
            if username != row["username"]:
                return apology("invalid username and/or password", 403)

        # Confirm old password
        for row in userdb:
            if not check_password_hash(row["hash"], oldpassword):
                return apology("invalid username and/or password", 403)
            else:
                # Change password
                hashnew = generate_password_hash(newpassword)
                db.execute("UPDATE users SET hash=:hash WHERE username=:username", hash=hashnew, username=username)

                # Successful
                return redirect("/")

    else:
        return render_template("changepw.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
