/*
 * @author Alex Bonamo
 * Class: COSC 4316 - Compiler Design
 * Professor: Dr. David Burris
 * Due Date: May 4th, 2022
 * Turned In: May 3rd, 2022
 */

#include "LexicalAnalyzer.cpp"
#include "SemanticAnalyzer.cpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main(){

    TableDrivenDFSA FSA; //Declare a FSA
	PushDownAutomaton PDA; //Declare a PDA

	string program = "";
	vector<token> tokenTable;
	vector<Quad> Quads;
	char ch;
	ifstream inputFile;
	ofstream QFile;
	//inputFile.open("P1.txt"); // Testcase #1
	//inputFile.open("P2.txt"); // Testcase #2

	// Reads our entire file to a string
	while(inputFile.get(ch)){

		program = program + ch;

	}
	//cout << program << endl;

	inputFile.close();
	tokenTable = FSA.stateChanger(program);
	
    QFile.open("Quads.txt");
	QFile << "Quads:" << endl; // Clears the previous contents
	QFile << "---------------" << endl; // Clears the previous contents
	QFile.close();

	Quads = PDA.findLine(tokenTable);

	return 0;
}