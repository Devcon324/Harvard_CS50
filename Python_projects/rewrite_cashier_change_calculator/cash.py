from cs50 import get_float


def main():
    # calls funciton to get user input for positive float of change
    change = get_change()
    # find the total cents and cast as int
    c = int(change * 100)
    # each casted in formula calculates quarters, dimes, nickles pennies, respectively
    # concept is to take the remainder of the preceeding larger coins
    # example: num_nickles = remainder after dimes of the remainder after quarters divided by 5 cents
    # each casted int can be viewed as (# of quarters) + (# of dimes) + (# of nickes) + (# of pennies)
    coin = int(c / 25) + int((c % 25) / 10) + int(((c % 25) % 10) / 5) + int((((c % 25) % 20) % 5) / 1)
    print(f"Total Coin = {int(coin)}")

# If the user fails to provide a non-negative value,
# your program should re-prompt the user for a valid amount again and again until the user complies.


def get_change():
    while True:
        # will keep trying to get input
        change_owed = get_float("Change owed?: ")
        if change_owed > 0:
            break
    return change_owed


if __name__ == "__main__":
    main()