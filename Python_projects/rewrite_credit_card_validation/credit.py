from cs50 import get_int

def main():

    card = get_card()
    oddEven = 0
    currentDigit = 0
    sum1 = 0
    sum2 = 0
    cardMem = card
    while (card > 0):
        currentDigit = card % 10
        # if we land on digit place 0, 2, 4, 6...
        if oddEven % 2 == 0:
            sum1 = sum1 + currentDigit
        # if we land on a digit at location 1, 3, 4, 5...
        if oddEven % 2 != 0:
            sum2 = sum2 + ((currentDigit * 2) / 10) + ((currentDigit * 2) % 10)
        #chop the card down 1 digit from the right
        card = card / 10
        # move onto the next odd or even number && count how many digits
        oddEven += 1


    luhn        = (sum1 + sum2) % 10       # final calculation of luhns algorithm
    AMEXTest    = cardMem / pow(10, 13)   # check first two digits of AMEX
    MCTest      = cardMem / pow(10, 14)   # check first two digits of AMEX
    VISATest13  = cardMem / pow(10, 12)   # check first digit of AMEX with length 13
    VISATest16  = cardMem / pow(10, 15)   # check first digit of AMEX with length 16
    if luhn == 0:
        # AMEX
        if (AMEXTest == 34 or AMEXTest == 37) and oddEven == 15:
            print("AMEX\n")
        # MASTERCARD
        elif (MCTest >= 51 and MCTest <= 55) and oddEven == 16:
            print("MASTERCARD\n")
        # VISA
        elif (VISATest13 == 4 and oddEven == 13) or (VISATest16 == 4 and oddEven == 16):
            print("VISA\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")




def get_card():
    while True:
        # will keep trying to get input
        card = get_int("Number?: ")
        if card > 0:
            break
    return card


if __name__ == "__main__":
    main()