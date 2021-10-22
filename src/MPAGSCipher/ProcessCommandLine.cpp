#include <string>
#include <vector>
#include <cctype>
#include <iostream>

#include "ProcessCommandLine.hpp"

bool processCommandLine(
    const std::vector<std::string>& args,
    bool& helpRequested,
    bool& versionRequested,
    std::string& inputFileName,
    std::string& outputFileName,
    int& toEncrypt,
    size_t& key)
{

    /*
    Parse the command line arguments, modifying the
    helpRequested, versionRequested and input/output
    filenames if applicable.

    const std::vector<std::string>& args: command line arguments (don't need to modify)
    bool& helpRequested: has the user asked for help
    bool& versionRequested: has the user asked about the version
    std::string& inputFileName: optional filename
    std::string& outputFileName: optional filename
    int& toEncrypt: -1 if not provided, 0 to decrpyt and 1 to encrypt
    int& key: key for cipher (number shift)

    return: Like the main() function, this function will
    return 0 upon success and 1 upon failure.
    failure occurs if the -i or -o or -k flags are the last arguments
    (so reading the filename fails) or if an unexpected
    argument is supplied.
    */

    const std::size_t nArgs{args.size()};
    //assume success in reading arguments by default
    bool failure{false};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                failure = true;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                //No point breaking the loop here because this only
                //happens for the last argument
                failure = true;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        } 
        else if (args[i] == "--encrypt" || args[i] == "-e") {
            //Make sure --decrypt has not already been specified
            if (toEncrypt==0)
            {
                std::cerr << "[error] --decrypt already specified\nYou can only specify --encrypt OR --decrypt" << std::endl;
                failure = true;
            }
            else
            {
                toEncrypt = 1;
            }
        }
        else if (args[i] == "--decrypt" || args[i] == "-d") {
            //Make sure --encrypt has not already been specified
            if (toEncrypt==1)
            {
                std::cerr << "[error] --encrypt already specified\nYou can only specify --encrypt OR --decrypt" << std::endl;
                failure = true;
            }
            else
            {
                toEncrypt = 0;
            }
        }
        else if (args[i] == "-k") {
            // Handle key option
            // Next element is key value unless "-k" is the last argument
            if (i == nArgs - 1) {
                std::cerr << "[error] -k requires a key value"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                //No point breaking the loop here because this only
                //happens for the last argument
                failure = true;
            } else {
                // Got key value, so assign temp to check value
                const int temp{std::stoi(args[i+1])};
                // Make sure key is 1-25
                if(temp >= 1 && temp <= 25)
                {
                    key = temp;
                }
                else
                {
                    std::cerr << "[error] key value must be in the range 0-25" << std::endl;
                    failure = true;
                    break;
                }
                ++i;
            }
        } 
        else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            failure = true;
            //Exit the loop early
            break;
        }
    }
    if(toEncrypt==-1)
    {
        std::cerr << "[error] you must specify whether to encrypt with --encrypt\nor decrypt with --decrypt" << std::endl;
        failure = true;
    }
    if(key==0)
    {
        std::cerr << "[error] you must specify a key with -k KEY" << std::endl;
        failure = true;
    }
    return failure;
}