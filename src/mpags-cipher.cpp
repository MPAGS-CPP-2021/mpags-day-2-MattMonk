#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    //Instead of a bool for encrypt/decrypt also have -1
    //option for not specified
    int toEncrypt{-1};
    size_t key{0};

    const bool failure{processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, toEncrypt, key)};

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>] [--encrypt] [--decrypt] [-k KEY]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  --encrypt        Program will encrypt the text with\n"
            << "                   Caesar Cipher\n\n"
            << "  --decrypt        Program will decrypt the text with\n"
            << "                   Casear Cipher\n\n"
            << "  -k KEY           Key for the Caesar cipher (number of\n"
            << "                   steps\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    bool b_toEncrypt{false};
    if(toEncrypt!=-1)
    {
        b_toEncrypt = toEncrypt;
    }

    //Check to see if an error occured and
    //if so, return with failure (1).
    if (failure) {
        std::cout << "An error occured, exiting program" << std::endl;
        return 1;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;
    bool ok_to_read{true};
    bool ok_to_write{true};

    // Read in user input from file if filename was supplied
    if (!inputFile.empty()) {
        std::ifstream in_file{inputFile};
        ok_to_read = in_file.good();
        if(ok_to_read)
        {
            while (in_file >> inputChar) {
                inputText += transformChar(inputChar);
            }
            in_file.close();
        }
        else {
            std::cerr << "There was a problem reading the input file.\nUse the command line instead:" << std::endl;
        }
    }
    //If no filename was supplied or there was a problem reading the file,
    //then use std::cin to read input
    if (inputFile.empty() || !ok_to_read) {
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    

    // Print out the encrypted/decrypted text

    const std::string outputText{runCaesarCipher(inputText, key, b_toEncrypt)};
    if (!outputFile.empty()) {
        std::ofstream out_file{outputFile};
        ok_to_write = out_file.good();
        if (ok_to_write) {
            out_file << outputText << std::endl;
            out_file.close();
        }
        else {
            std::cerr << "There was a problem opening the file.\nUsing the command line instead:" << std::endl;
        }
    }
    //If no filename was supplied or there was a problem opening the file,
    //then use std::cout to output instead
    if(outputFile.empty() || !ok_to_write) {
        std::cout << outputText << std::endl;
    }
    
    //std::cout << "Encrypt? " << toEncrypt << " and key: " << key << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}