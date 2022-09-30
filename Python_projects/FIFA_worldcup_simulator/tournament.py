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

    teams = []

    # Read teams into memory from file
    filename = sys.argv[1]
    with open(filename) as file:
        reader = csv.DictReader(file)
        # team is a struct
        # in each team... change the rating to an int
        for team in reader:
            team["rating"] = int(team["rating"])
            teams.append(team)  # adds the team as a whole (team:rating)

    counts = {}
    
    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:        # winner already in counts
            counts[winner] += 1
        else:
            counts[winner] = 1      # first time winner

    # will associate team names with the number of times that team won a simulated tournament
    # teams : how many times won tournament

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
    while len(teams) > 1:
        teams = simulate_round(teams)
    return teams[0]["team"]
# teams has 14 memebers
# run simulate_round,  there will be 7 memebers
# update teams to be the list of winners
# take winners and re-simulate_round
# repeat until onyl 1 final winner

# access the one only team, returning the name of team


if __name__ == "__main__":
    main()
