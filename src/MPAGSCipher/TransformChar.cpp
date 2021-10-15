#include <cctype>
#include <string>


// Our project headers
#include "TransformChar.hpp"

std::string transformChar(const char in_char) {
    /*
    Change all characters to upper case, numbers to words
    and disregard any non-alphanumeric characters.
    Note, could instead return in each branch/case
    e.g. return dynamic_cast<std::string>(std::toupper(in_char))
    but I prefer to have one clear return statement at the bottom.
    If the character should not be added, string returned is blank
    and so is not added to the final string in the loop.

    const char in_char: the character to process

    return: Return the processed charcter as a string (empty if
    the character should not be added).
    */
    std::string toReturn{""};
    // Uppercase alphabetic characters
    if (std::isalpha(in_char)) {
        toReturn += std::toupper(in_char);
    }
    else {
        // Transliterate digits to English words
        switch (in_char) {
            case '0':
                toReturn += "ZERO";
                break;
            case '1':
                toReturn += "ONE";
                break;
            case '2':
                toReturn += "TWO";
                break;
            case '3':
                toReturn += "THREE";
                break;
            case '4':
                toReturn += "FOUR";
                break;
            case '5':
                toReturn += "FIVE";
                break;
            case '6':
                toReturn += "SIX";
                break;
            case '7':
                toReturn += "SEVEN";
                break;
            case '8':
                toReturn += "EIGHT";
                break;
            case '9':
                toReturn += "NINE";
                break;
        }
    }
        // If the character isn't alphabetic or numeric, DONT add it
    return toReturn;
}