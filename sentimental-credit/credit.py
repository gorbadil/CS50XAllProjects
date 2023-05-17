# TODO

def credit():
    is_card = False
    card = input("Number: ")
    card = list(card)
    multi = 0
    for i in range(len(card) - 2, -1, -2):
        top = int(card[i]) * 2
        if top >= 10:
            top1 = top % 10
            top2 = round((top - 4) / 10)
            multi += top1 + top2
            # print(f"{top1}")
            # print(f"{top2}")
        else:
            multi += top
        #     print(f"{top}")
        # print(f"{multi}")
    for i in range(len(card) - 1, -1, -2):
        multi += int(card[i])
        # print(f"{card[i]}")
        # print(f"{multi}")

    # print(f"{multi}")
    if multi % 10 == 0:
        is_card = True
    else:
        print("INVALID")

    if is_card:
        if len(card) == 15 and card[0] == "3":
            if card[1] == "4" or card[1] == "7":
                print("AMEX")
            else:
                print("INVALID")
        elif len(card) == 16 and card[0] == "5":
            if card[1] < "6" and card[1] > "0":
                print("MASTERCARD")
            else:
                print("INVALID")
        elif len(card) == 13 or len(card) == 16:
            if card[0] == "4":
                print("VISA")
            else:
                print("INVALID")
        else:
            print("INVALID")


credit()

