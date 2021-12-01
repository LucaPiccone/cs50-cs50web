# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    with open(sys.argv[1], "r") as inputFile:
        reader = csv.DictReader(inputFile)

        teams = []
        # TODO: Read teams into memory from file
        # for every row in reader append to teams[] the row. Basically, go into the file and append every row to the list of teams.
        for row in reader:
            teams.append(row)

        # For every dictionary in the list of dictionaries
        for dictionarys in teams:
            # for every key in the dictionary
            for keys in dictionarys:
                # if dictionary[0], dictionary[1] can be converted to an int, convert it
                try:
                    dictionarys[keys] = int(dictionarys[keys])
                # Else leave it the same
                except:
                    dictionarys[keys] = dictionarys[keys]

        #print(f"RATINGS ARE INTS {teams[0]}")

    # Simulate tornament. Returns the name of the winning team.
    winner = simulate_tournament(teams)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts

    # For every dictionary in the list of dictionaries (teams)
    for team in teams:
        # counts (key) = the team in the dictionary,
        # counts (value) = 0
        counts[team['team']] = 0

    # For 0 - 999 simulate tournament and add 1 to count for the winner key.
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # Count the number of teams
    number_of_teams = len(teams)

    # Create a copy of the list of teams and ratings
    copy_teams = teams
    winners = {}
    
    # simulate round until two finalist remain
    while len(copy_teams) != 2:
        winners = copy_teams
        copy_teams = simulate_round(winners)

    # simulate the game of the two finalist
    if number_of_teams == 2:
        winners[0] = copy_teams[0]
        winners[1] = copy_teams[1]
        
    winner = simulate_game(winners[0], winners[1])

    # if true first team one else second team one
    if winner == True:
        first_place = winners[0]
    else:
        first_place = winners[1]

    # return the name of the first place team.
    return first_place['team']


if __name__ == "__main__":
    main()
