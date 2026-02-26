#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0));

    // Character set: numbers + full alphabet
    string charset = "0123456789abcdefghijklmnopqrstuvwxyz";
    int length = 6;   // 10+ characters for final challenge

    // Generate random password
    string passcode = "";
    for (int i = 0; i < length; i++) {
        passcode += charset[rand() % charset.size()];
    }

    cout << "Password generated. Try to crack it!" << endl;
    cout << passcode << endl; // show for testing

    // Start timer
    auto start = high_resolution_clock::now();

    int attempts = 0;
    string guess(length, charset[0]);  // start at "0000000000"

    while (true) {
        attempts++;

        if (guess == passcode) {
            break;
        }

        // Increment guess like a base-N number
        int position = length - 1;

        while (position >= 0) {
            int index = charset.find(guess[position]);

            if (index + 1 < charset.size()) {
                guess[position] = charset[index + 1];
                break;
            } else {
                guess[position] = charset[0];
                position--;
            }
        }

        if (position < 0) {
            break;
        }
    }

    // Stop timer
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "Password found: " << guess << endl;
    cout << "Attempts: " << attempts << endl;
    cout << "Password cracked in: " << duration.count() << " nanoseconds!" << endl;

    return 0;
}