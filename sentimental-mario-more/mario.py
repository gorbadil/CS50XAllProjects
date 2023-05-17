# TODO

def mario():

    n = True
    h = "#"
    s = " "
    while (n):
        height = input("Height: ")
        try:
            height = int(height)
        except:
            height = input("Height: ")

        if height < 9 and height > 0:
            n = False

    for i in range(1, height + 1):
        # print(f"{s * (height - i)}{i * h}  {i * h}{s * (height - i)}")
        print(f"{s * (height - i)}{i * h}  {i * h}")


mario()
