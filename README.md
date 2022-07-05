# CompilerProject
**Intro**

This project was created as a semester project for my "COSC 4316 - Compiler Design" course, taught by Dr. David Burris.
I took this course during my final semester while attending Sam Houston State University back in the Spring of 2022.

**About the Project**

A lexical analyzer and semantic analyzer were written using table-driven problem solving techniques such as a Deterministic Finite State Automaton (DFSA) and a Push Down Automaton. 

Created from this project are a token table, symbol table, quads, and an assembly file which can be ran using Linux to successfully run the designated program.

The file titled "LexicalAnalyzer.cpp" was both a lexical analyzer and syntax analyzer. The lexical analyzer was written utilizing a Deterministic Finite State Automaton (DFSA) which constructs tokens by reading one character at a time. These characters would then be combined to form complete tokens during syntax analysis. The output from these processes would be a Token Table to a file designated "TokenTable.txt" and a Symbol Table to a file titled "SymbolTable.txt".

The file titled "SemanticAnalyzer.cpp" utilized a Push Down Automaton (PDA) which did precedence parsing, allowing for the creation of Quads, which was later converted into assembly. During the creation of Quads, a form of optimization was done to minimize how many temporary registers were used, as well as to reduce the amount of assembly processes necessary to run the code.  The quads would be output to a file called "Quads.txt", and once converted to assembly (.asm) would be printed to a file titled "Assembly.asm".


This compiler was based off of my understanding of Chomsky Type 3 grammars and could recognize very basic Java programs.
Some programming functionalities the compiler can recognize includes:
- Classes
- Variables
- Constants
- Arithmetic Operations
- Relational Operators
- If-Else Statements
- I/O Routines
- User Comments

**Extra Info**

The "P1" and "P2" text files were simply two test cases. Each test case has a corresponding token table, symbol table, and quads text file, along with an assembly file.
