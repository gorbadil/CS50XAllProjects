# TODO

a = 0.25
b = 0.10
c = 0.05
d = 0.01

def cash():
    money = input("Change owed: ")
    try:
        money = float(money)
    except:
        money = input("Change owed: ")

    while (money > 0):
        ak = round(money / a)
        money -= a
    while (money > 0):
        bk = round(money / b)
        money -= b
    while (money > 0):
        ck = round(money / c)
        money -= c
    while (money > 0):
        dk = round(money / d)
        money -= d
    try:
        print(f"{ak + bk + ck + dk}")
    except:
        print("0")




cash()
