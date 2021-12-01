from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
    
width = height * 2 + 2

for y in range(height):
    for x in range(width):
        # Middle: print spaces 
        if x == height or x == height + 1:
            print(" ", end="")
        # Right side: height + 2 (brings us to right side) - 
        # If x is greater than y + height + 2 print nothing 
        elif y + height + 2 < x:
            print("", end="")
        # Left side: print spaces 
        elif y + x < height - 1:
            print(" ", end="")
        else:
            print("#", end="")
    print()