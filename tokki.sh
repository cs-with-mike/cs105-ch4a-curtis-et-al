#!/bin/bash
# Authors:
#  - Curtis Barnhart, cbarnhart@westmont.edu
#  - Meghan Nugent, mnugent@westmont.edu
#  - Joshua Nielsen, jnielsen@westmont.edu

# Run any commands necessary to set up your language's runtime environment here.
# If the runtime is expected to be present on Ubuntu by default, then do nothing.
echo "Setting up runtime ..."

# I'm checking Python interpreter's version here just as a placeholder.
python3 --version # TODO: YOUR RUNTIME SETUP HERE.

echo "BEGIN TOKKI BUILD--------------------------------------------------------------------------------"
cmake -S . -O RELEASE_BUILD
cd RELEASE_BUILD
make
cd ..
echo "END TOKKI BUILD----------------------------------------------------------------------------------"

echo "BEGIN PRINTING FILE------------------------------------------------------------------------------"
cat $1
echo "END PRINTING FILE--------------------------------------------------------------------------------"


# Run your Tokki lexer, passing in the first command line argument directly to the lexer.
# Any output to STDOUT should be directed to a text output file titled "out.txt."
echo "BEGIN RUN TOKKI----------------------------------------------------------------------------------"
./RELEASE_BUILD/tokki $1 > out.txt
echo "END RUN TOKKI------------------------------------------------------------------------------------"

echo "BEGIN PRINT RESULTS------------------------------------------------------------------------------"
cat out.txt
echo "END PRINT RESULTS--------------------------------------------------------------------------------"


# As an example, I have provided how I would run my tokki.pyc.
# python3 tokki.pyc $1 > out.txt # TODO: REPLACE THIS WITH YOUR OWN COMMAND.

