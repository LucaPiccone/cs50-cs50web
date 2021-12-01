from cs50 import get_float 
from math import floor


def main():
    # Ask users for a positive amount of change owed to them.
    while True:
        owed = get_float("Change owed: ")
        if owed > 0:
            break
    
    # initialize counters
    change = 0.00
    coins = 0
    
    # Quarters
    while True:
        change += 0.25 
        coins += 1
        change = round(change, 3)
        if change > owed:
            change -= 0.25
            coins -= 1
            break
        elif change == owed:
            break
    
    # Dimes
    while True:
        change += 0.10
        coins += 1
        change = round(change, 3)
        if change > owed:
            change -= 0.10
            coins -= 1
            break
        elif change == owed:
            break
        
    # Nickels
    while True:
        change += 0.05
        coins += 1
        change = round(change, 3)
        if change > owed:
            change -= 0.05
            coins -= 1
            break
        elif change == owed:
            break
        
    # 1 cent 
    while True:
        change += 0.01
        coins += 1
        change = round(change, 3)
        if change > owed:
            change -= 0.01
            coins -= 1
            break
        elif change == owed:
            break
    
    #print(owed)
    #print(change)
    print(coins)


main()