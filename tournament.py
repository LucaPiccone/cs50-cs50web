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
        # for every row in reader append to teams[] the row.
        for row in reader:
            teams.append(row);

        for dictionarys in teams:
            for keys in dictionarys:
                try:
                    dictionarys[keys] = int(dictionarys[keys])
                except:
                    dictionarys[keys] = dictionarys[keys]

        #print(f"RATINGS ARE INTS {teams[0]}")

    # Simulate tornament. Returns the name of the winning team.
    winner = simulate_tournament(teams)

    counts = {}
    for team in teams:
        counts[team['team']] = 0
        
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1
    
    # TODO: Simulate N tournaments and keep track of win counts
    #for i in range(N):
    #   winner = simulate_tournament(teams)
        
        
        
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
    number_of_teams = len(teams)

    copy_teams = teams

    while len(copy_teams) != 2:
        winners = copy_teams
        copy_teams = simulate_round(winners)

    winner = simulate_game(winners[0], winners[1])

    if winner == True:
        first_place = winners[0]
    else:
        first_place = winners[1]

    return first_place['team']


if __name__ == "__main__":
    main()
