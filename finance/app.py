import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    user_result = db.execute(
        f"SELECT SUM(share) AS share, symbol, SUM(spend) AS spend FROM shares WHERE username = {user_id} GROUP BY symbol")
    # print(user_result)
    # print(round(float(user_result[0]["spend"]), 2))
    for i in user_result:
        i["spend"] = round(float(i["spend"]), 2)
    for i in user_result:
        current_rate = lookup(i["symbol"])
        current_rate = current_rate["price"]
        i["current"] = round(current_rate * i["share"], 2)
    gain = 0
    total = 0
    for i in user_result:
        gain += i["current"] - i["spend"]
        total += i["current"]
    gain = round(gain)
    total = round(total)
    cash = db.execute(f"SELECT cash FROM users WHERE id = {user_id}")
    return render_template("index.html", user_result=user_result, gain=gain, total=total, cash=usd(cash[0]["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("shares")
        try:
            share = int(share)
        except:
            return apology("Please Enter Symbol And Shares Correctly!", 400)
        if symbol == "" or share == "" or share <= 0:
            return apology("Please Enter Symbol And Shares Correctly!", 400)
        result = lookup(symbol)
        if not result:
            return apology("Enter A Valid Symbol Of Stock!", 400)
        user_id = session["user_id"]
        symbol = result["symbol"]
        price = round(result["price"], 2)
        spend = price * share
        share_req = db.execute(f"SELECT cash FROM users WHERE id = {user_id}")
        if price <= share_req[0]["cash"]:
            db.execute("INSERT INTO shares (username, share, spend, symbol) VALUES(?, ?, ?, ?)", user_id, share, spend, symbol)
            new_value = share_req[0]["cash"] - spend
            db.execute(f"UPDATE users SET cash = {new_value} WHERE id = {user_id}")
            return redirect("/")
        else:
            return apology("You Need More Cash To Add This Share", 400)
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    user_history = db.execute(f"SELECT * FROM shares WHERE username = {user_id}")
    print(user_history)
    return render_template("history.html", history=user_history)


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
        symbol = request.form.get("symbol")
        result = lookup(symbol)
        if not symbol:
            return apology("Symbol Error!", 400)
        elif not result:
            return apology("Symbol Error!", 400)
        return render_template("quoted.html", name=result["name"], price=round(result["price"], 2), symbol=result["symbol"])
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        users = db.execute("SELECT username FROM users")
        print(users)
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if username == "" or password == "" or confirmation == "":
            return apology("Please Fill The Form!", 400)
        for i in users:
            if i["username"] == username:
                return apology("username already taken!", 400)
        if confirmation != password:
            return apology("password deasn't match!", 400)
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    selling = db.execute(
        f"SELECT username, SUM(share) as share, SUM(spend) as spend, symbol FROM shares WHERE username = {user_id} GROUP BY symbol")
    options = []
    for i in selling:
        options.append(i["symbol"])
    if request.method == "POST":
        sell_share = request.form.get("shares")
        selected_share = request.form.get("symbol")
        try:
            sell_share = int(sell_share)
        except:
            return apology("Integer!", 400)
        if not selected_share in options:
            return apology("Search Options!", 400)
        if sell_share <= 0:
            return apology("sellshace <= 0!", 400)
        total_share = 0
        print(selling)
        for i in selling:
            if i["symbol"] == selected_share:
                total_share += i["share"]
        if sell_share > total_share:
            return apology("sell_share > i_share or selecte-share == i-symbol!", 400)
        result = lookup(selected_share)
        price = round(result["price"], 2)
        spend = price * sell_share * (-1)
        cash = db.execute(f"SELECT cash FROM users WHERE id = {user_id}")
        sell_share *= (-1)
        db.execute("INSERT INTO shares (username, share, spend, symbol) VALUES(?, ?, ?, ?)",
                   user_id, sell_share, spend, selected_share)
        cash_update = cash[0]['cash'] - spend
        db.execute(f"UPDATE users SET cash = {cash_update} WHERE id = {user_id} ")
        return redirect("/")
    return render_template("sell.html", options=options)
