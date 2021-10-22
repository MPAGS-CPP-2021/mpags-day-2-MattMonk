# mpags-cipher
A simple command line tool for encrypting/decrypting text using classical ciphers

## Authors
Thomas Latham, Ben Morgan, Mark Slater, Matt Williams, Luke Kreczko

## Building `mpags-cipher`
Compilation of `mpags-cipher` requires a  C++11 compatible compiler
(GCC 8 or better, Clang 8 or better are recommended) on a UNIX operating
system and cmake version 3.2 or greater.
Windows platforms with Visual Studio 2015 or better are also expected to
work, but not tested.

To build from a clone of this repository, open a terminal window
and change directory into that holding this README. Then run:
```
$ cd build
$ cmake ../src
$ make
$ ./mpags-cipher
```

The user must specify whether they want to encrypt text or decrypt
using the flags --encrypt (or -e) or --decrpyt (or -d). A key must
also be specified which corresponds to the shift in the alphabet
for the Caesar Cipher -k <INT>.

If no input file is supplied, `mpags-cipher` will wait for user input
from the keyboard until RETURN followed by CTRL-D are pressed.
To ensure the input text can be used with the character sets known to
classical ciphers, it is transliterated using the following rules:

- Alphabetical characters are converted to uppercase
- Digits are translated to their English equivalent words (e.g. '0' -> "ZERO")
- All other characters (punctuation) are discarded

If an output file is specified, the encrypted (decrypted) text is written
to the output file, otherwise it will be written to stdout.

## Source code layout
```
.
├── build                        Empty directory to build and run the program in
├── src                          Contains the source files
 ├── CMakeLists.txt              CMake configuration file
 ├── MPAGSCipher                 Source files
  ├── ProcessCommandLine.cpp     File to process command line options
  ├── ProcessCommandLine.hpp     Header file to command line processing
  ├── RunCaesarCipher.cpp        File to implement the Caesar Cipher (encrypt/decrypt)
  ├── RunCaesarCipher.hpp        Header for Caesar Cipher
  ├── TransformChar.cpp          File to transliterate text for cipher application
  ├── TransfromChar.cpp          Header file for transliteration
├── LICENSE                      License file, in our case MIT
├── mpags-cipher.cpp             Main program C++ source file
└── README.md                    This file, describes the project
```

## Copying
`mpags-cipher` is licensed under the terms of the MIT License.
Please see the file [`LICENSE`](LICENSE) for full details.