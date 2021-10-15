#include <string>
#include <vector>
#include <cctype>
#include <iostream>

#include "RunCaesarCipher.hpp"

std::string runCaesarCipher(
    const std::string& inputText,
    const size_t key,
    const bool encrypt)
{
    std::string outputText {""};

    for(const char& letter : inputText)
    {
        int in_char{int(letter)};
        /*
        Would probably be better to use the alphabet vector suggested but
        thought this would be a bit more fun. Convert the charcter to ASCII
        which will be [65-90], so subtract 65 to make the range [0-25], then
        key shifts right (encrypt) if k>0 or left (decrypt) if k<0.
        Then mod 26 for the wrap-around, then add 65 back on to get back
        to the range [65-90] for A-Z in ASCII
        */
        //Have to convert size_t to int (which is fine as K should be
        //between 0-25 anyway).
        const int i_key{static_cast<int>(key)};
        int out_char{0};
        if(encrypt) out_char = (((in_char-65)+i_key)%26)+65;
        //Note, the weird extra operations for the neagtive
        //k case. This is because the C++ modulo operator interprets
        //e.g. -5%26=-5, rather than e.g. Python which instead does
        // -5%26=21...
        else out_char = ((((in_char-65)-i_key)%26+26)%26)+65;
        
        outputText += char(out_char);
    }
    return outputText;
}