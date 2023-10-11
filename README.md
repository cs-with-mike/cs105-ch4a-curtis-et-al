[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/a2fQs4QM)
# Lexer & Parser for the Tokki Language
Westmont College CS 105 Fall 2023
Chapter 4 Assignment A

## Author Information
- Curtis Barnhart, cbarnhart@westmont.edu
- Joshua Nielsen jnielsen@westmont.edu
- Meghan Nugent mnugent@westmont.edu

## Overview
This program is a lexer for the toy language tokki.
This program will take a tokki source code file and output a file "out.txt" containing the lexical contents of the tokki source code file.
Lexical symbols that this program will recognize include identifiers (composed of alphanumeric strings beginning with an alphabetical char),
integers, opening and closing parentheses, addition, subtraction, multiplication, division, and assignment operators.

## Design Notes
Our algorithm is implemented as one large finite state machine. This is really the only major design choice in this program.

## Lessons Learned
We learned a lot of C++ syntax (including the many ways that constructors can be written, haha).
One interesting thing that we were exposed to but didn't have a chance to fully understand was how templates work in C++.
Luckily, we didn't need to have a thorough understanding of them to complete the project.

Something we learned not related exactly to C++ was how to effectively set up one remote repository for people with multiple operating systems and IDEs.
On a similar note, some of us actually used different build systems, and it was very nice that our code and remote repository could be shared while allowing
for minor differences in our build systems and IDEs.

