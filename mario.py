from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
    
width = height * 2 + 2

for y in range(height):
    for x in range(width):
        if x == height or x == height + 1:
            print(" ", end="")
        elif y + height + 2 < x:
            print("", end="")
        elif y + x < height - 1:
            print(" ", end="")
        else:
            print("#", end="")
    print()
        


