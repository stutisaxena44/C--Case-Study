#include <iostream>
#include <string>
using namespace std;

// Check if all characters are digits
bool isAllDigits(string card) {
    for (int i = 0; i < card.length(); i++) {
        if (!isdigit(card[i])) {
            return false;
        }
    }
    return true;
}

// Luhn Algorithm - checks if card number is mathematically valid
bool luhnCheck(string card) {
    int sum = 0;
    bool doubleIt = false;

    // Start from the last digit and move left
    for (int i = card.length() - 1; i >= 0; i--) {
        int digit = card[i] - '0';

        if (doubleIt) {
            digit = digit * 2;
            if (digit > 9) {
                digit = digit - 9;
            }
        }

        sum = sum + digit;
        doubleIt = !doubleIt;
    }

    return (sum % 10 == 0);
}

// Identify card type
string getCardType(string card) {
    int len = card.length();
    string firstTwo = card.substr(0, 2);

    if (card[0] == '4' && (len == 13 || len == 16)) {
        return "Visa";
    }
    if ((firstTwo >= "51" && firstTwo <= "55") && len == 16) {
        return "MasterCard";
    }
    if ((firstTwo == "34" || firstTwo == "37") && len == 15) {
        return "American Express";
    }
    if (firstTwo == "60" && len == 16) {
        return "Discover";
    }

    return "Unknown";
}

// Validate and display result
void validateCard() {
    string card;
    cout << "\nEnter Credit Card Number: ";
    cin >> card;

    // Step 1: Check for non-numeric characters
    if (!isAllDigits(card)) {
        cout << "Card Number is Invalid! (Non-numeric characters found)" << endl;
        return;
    }

    // Step 2: Check length
    if (card.length() < 13 || card.length() > 16) {
        cout << "Card Number is Invalid! (Must be 13-16 digits)" << endl;
        return;
    }

    // Step 3: Check card type
    string type = getCardType(card);
    if (type == "Unknown") {
        cout << "Card Number is Invalid! (Unrecognized card format)" << endl;
        return;
    }

    // Step 4: Luhn check
    if (!luhnCheck(card)) {
        cout << "Card Number is Invalid! (Failed Luhn Check)" << endl;
        return;
    }

    // All checks passed
    cout << "Card Number is Valid!" << endl;
    cout << "Card Type  : " << type << endl;
}

int main() {
    int choice;

    do {
        // Menu
        cout << "\n==========================" << endl;
        cout << "  Credit Card Validation  " << endl;
        cout << "==========================" << endl;
        cout << "1. Validate Card" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            validateCard();
        } else if (choice == 2) {
            cout << "Goodbye!, thanks for choosing us as your card verifier!" << endl;
        } else {
            cout << "Invalid choice! Enter 1 or 2." << endl;
        }

    } while (choice != 2);

    return 0;
}