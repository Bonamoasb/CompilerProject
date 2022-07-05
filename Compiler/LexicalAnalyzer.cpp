#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void stateChanger();
int findColumn(char);
string isReservedWord(string);

typedef int Boolean;

class token{
public:
	string name;
	string classification;
};

class symbol{
public:
	string token;
	string classification;
	string value = "";
	string address;
	string segment;
};

class TableDrivenDFSA{
private:
	int stateTable[28][17]; //rows => states, cols => response to question.

public:
	TableDrivenDFSA(){
		stateTable[0][0] = 0;   stateTable[0][1] = 1;   stateTable[0][2] = 3;   stateTable[0][3] = 5;   stateTable[0][4] = 6;   stateTable[0][5] = 10;  stateTable[0][6] = 13;  stateTable[0][7] = 16;  stateTable[0][8] = 19;  stateTable[0][9] = 20;  stateTable[0][10] = 21;  stateTable[0][11] = 22;  stateTable[0][12] = 23; stateTable[0][13] = 24;   stateTable[0][14] = 25;  stateTable[0][15] = 26;  stateTable[0][16] = 27;
		stateTable[1][0] = 2;   stateTable[1][1] = 1;   stateTable[1][2] = 2;   stateTable[1][3] = 2;   stateTable[1][4] = 2;   stateTable[1][5] = 2;   stateTable[1][6] = 2;   stateTable[1][7] = 2;   stateTable[1][8] = 2;   stateTable[1][9] = 2;   stateTable[1][10] = 2;   stateTable[1][11] = 2;   stateTable[1][12] = 2;   stateTable[1][13] = 2;   stateTable[1][14] = 2;   stateTable[1][15] = 2;   stateTable[1][16] = 2;
		stateTable[2][0] = 0;   stateTable[2][1] = 0;   stateTable[2][2] = 0;   stateTable[2][3] = 0;   stateTable[2][4] = 0;   stateTable[2][5] = 0;   stateTable[2][6] = 0;   stateTable[2][7] = 0;   stateTable[2][8] = 0;   stateTable[2][9] = 0;   stateTable[2][10] = 0;   stateTable[2][11] = 0;   stateTable[2][12] = 0;   stateTable[2][13] = 0;   stateTable[2][14] = 0;   stateTable[2][15] = 0;   stateTable[2][16] = 0;
		stateTable[3][0] = 4;   stateTable[3][1] = 3;   stateTable[3][2] = 3;   stateTable[3][3] = 4;   stateTable[3][4] = 4;   stateTable[3][5] = 4;   stateTable[3][6] = 4;   stateTable[3][7] = 4;   stateTable[3][8] = 4;   stateTable[3][9] = 4;   stateTable[3][10] = 4;   stateTable[3][11] = 4;   stateTable[3][12] = 4;   stateTable[3][13] = 4;   stateTable[3][14] = 4;   stateTable[3][15] = 4;   stateTable[3][16] = 4;
		stateTable[4][0] = 0;   stateTable[4][1] = 0;   stateTable[4][2] = 0;   stateTable[4][3] = 0;   stateTable[4][4] = 0;   stateTable[4][5] = 0;   stateTable[4][6] = 0;   stateTable[4][7] = 0;   stateTable[4][8] = 0;   stateTable[4][9] = 0;   stateTable[4][10] = 0;   stateTable[4][11] = 0;   stateTable[4][12] = 0;   stateTable[4][13] = 0;   stateTable[4][14] = 0;   stateTable[4][15] = 0;   stateTable[4][16] = 0;
        stateTable[5][0] = 0;   stateTable[5][1] = 0;   stateTable[5][2] = 0;   stateTable[5][3] = 0;   stateTable[5][4] = 0;   stateTable[5][5] = 0;   stateTable[5][6] = 0;   stateTable[5][7] = 0;   stateTable[5][8] = 0;   stateTable[5][9] = 0;   stateTable[5][10] = 0;   stateTable[5][11] = 0;   stateTable[5][12] = 0;   stateTable[5][13] = 0;   stateTable[5][14] = 0;   stateTable[5][15] = 0;   stateTable[5][16] = 0;
        stateTable[6][0] = 7;   stateTable[6][1] = 7;   stateTable[6][2] = 7;   stateTable[6][3] = 8;   stateTable[6][4] = 7;   stateTable[6][5] = 7;   stateTable[6][6] = 7;   stateTable[6][7] = 7;   stateTable[6][8] = 7;   stateTable[6][9] = 7;   stateTable[6][10] = 7;   stateTable[6][11] = 7;   stateTable[6][12] = 7;   stateTable[6][13] = 7;   stateTable[6][14] = 7;   stateTable[6][15] = 7;   stateTable[6][16] = 7;
        stateTable[7][0] = 0;   stateTable[7][1] = 0;   stateTable[7][2] = 0;   stateTable[7][3] = 0;   stateTable[7][4] = 0;   stateTable[7][5] = 0;   stateTable[7][6] = 0;   stateTable[7][7] = 0;   stateTable[7][8] = 0;   stateTable[7][9] = 0;   stateTable[7][10] = 0;   stateTable[7][11] = 0;   stateTable[7][12] = 0;   stateTable[7][13] = 0;   stateTable[7][14] = 0;   stateTable[7][15] = 0;   stateTable[7][16] = 0;
        stateTable[8][0] = 8;   stateTable[8][1] = 8;   stateTable[8][2] = 8;   stateTable[8][3] = 9;   stateTable[8][4] = 8;   stateTable[8][5] = 8;   stateTable[8][6] = 8;   stateTable[8][7] = 8;   stateTable[8][8] = 8;   stateTable[8][9] = 8;   stateTable[8][10] = 8;   stateTable[8][11] = 8;   stateTable[8][12] = 8;   stateTable[8][13] = 8;   stateTable[8][14] = 8;   stateTable[8][15] = 8;   stateTable[8][16] = 8;
        stateTable[9][0] = 8;   stateTable[9][1] = 8;   stateTable[9][2] = 8;   stateTable[9][3] = 9;   stateTable[9][4] = 0;   stateTable[9][5] = 8;   stateTable[9][6] = 8;   stateTable[9][7] = 8;   stateTable[9][8] = 8;   stateTable[9][9] = 8;   stateTable[9][10] = 8;   stateTable[9][11] = 8;   stateTable[9][12] = 8;   stateTable[9][13] = 8;   stateTable[9][14] = 8;   stateTable[9][15] = 8;   stateTable[9][16] = 8;
        stateTable[10][0] = 11; stateTable[10][1] = 11; stateTable[10][2] = 11; stateTable[10][3] = 11; stateTable[10][4] = 11; stateTable[10][5] = 12; stateTable[10][6] = 11; stateTable[10][7] = 11; stateTable[10][8] = 11; stateTable[10][9] = 11; stateTable[10][10] = 11; stateTable[10][11] = 11; stateTable[10][12] = 11; stateTable[10][13] = 11; stateTable[10][14] = 11; stateTable[10][15] = 11; stateTable[10][16] = 11;
		stateTable[11][0] = 0;  stateTable[11][1] = 0;  stateTable[11][2] = 0;  stateTable[11][3] = 0;  stateTable[11][4] = 0;  stateTable[11][5] = 0;  stateTable[11][6] = 0;  stateTable[11][7] = 0;  stateTable[11][8] = 0;  stateTable[11][9] = 0;  stateTable[11][10] = 0;  stateTable[11][11] = 0;  stateTable[11][12] = 0;  stateTable[11][13] = 0;  stateTable[11][14] = 0;  stateTable[11][15] = 0;  stateTable[11][16] = 0;
        stateTable[12][0] = 0;  stateTable[12][1] = 0;  stateTable[12][2] = 0;  stateTable[12][3] = 0;  stateTable[12][4] = 0;  stateTable[12][5] = 0;  stateTable[12][6] = 0;  stateTable[12][7] = 0;  stateTable[12][8] = 0;  stateTable[12][9] = 0;  stateTable[12][10] = 0;  stateTable[12][11] = 0;  stateTable[12][12] = 0;  stateTable[12][13] = 0;  stateTable[12][14] = 0;  stateTable[12][15] = 0;  stateTable[12][16] = 0;
        stateTable[13][0] = 14; stateTable[13][1] = 14; stateTable[13][2] = 14; stateTable[13][3] = 14; stateTable[13][4] = 14; stateTable[13][5] = 15; stateTable[13][6] = 14; stateTable[13][7] = 14; stateTable[13][8] = 14; stateTable[13][9] = 14; stateTable[13][10] = 14; stateTable[13][11] = 14; stateTable[13][12] = 14; stateTable[13][13] = 14; stateTable[13][14] = 14; stateTable[13][15] = 14; stateTable[13][16] = 14;
		stateTable[14][0] = 0;  stateTable[14][1] = 0;  stateTable[14][2] = 0;  stateTable[14][3] = 0;  stateTable[14][4] = 0;  stateTable[14][5] = 0;  stateTable[14][6] = 0;  stateTable[14][7] = 0;  stateTable[14][8] = 0;  stateTable[14][9] = 0;  stateTable[14][10] = 0;  stateTable[14][11] = 0;  stateTable[14][12] = 0;  stateTable[14][13] = 0;  stateTable[14][14] = 0;  stateTable[14][15] = 0;  stateTable[14][16] = 0;
        stateTable[15][0] = 0;  stateTable[15][1] = 0;  stateTable[15][2] = 0;  stateTable[15][3] = 0;  stateTable[15][4] = 0;  stateTable[15][5] = 0;  stateTable[15][6] = 0;  stateTable[15][7] = 0;  stateTable[15][8] = 0;  stateTable[15][9] = 0;  stateTable[15][10] = 0;  stateTable[15][11] = 0;  stateTable[15][12] = 0;  stateTable[15][13] = 0;  stateTable[15][14] = 0;  stateTable[15][15] = 0;  stateTable[15][16] = 0;
        stateTable[16][0] = 17; stateTable[16][1] = 17; stateTable[16][2] = 17; stateTable[16][3] = 17; stateTable[16][4] = 17; stateTable[16][5] = 18; stateTable[16][6] = 17; stateTable[16][7] = 17; stateTable[16][8] = 17; stateTable[16][9] = 17; stateTable[16][10] = 17; stateTable[16][11] = 17; stateTable[16][12] = 17; stateTable[16][13] = 17; stateTable[16][14] = 17; stateTable[16][15] = 17; stateTable[16][16] = 17;
        stateTable[17][0] = 0;  stateTable[17][1] = 0;  stateTable[17][2] = 0;  stateTable[17][3] = 0;  stateTable[17][4] = 0;  stateTable[17][5] = 0;  stateTable[17][6] = 0;  stateTable[17][7] = 0;  stateTable[17][8] = 0;  stateTable[17][9] = 0;  stateTable[17][10] = 0;  stateTable[17][11] = 0;  stateTable[17][12] = 0;  stateTable[17][13] = 0;  stateTable[17][14] = 0;  stateTable[17][15] = 0;  stateTable[17][16] = 0;
        stateTable[18][0] = 0;  stateTable[18][1] = 0;  stateTable[18][2] = 0;  stateTable[18][3] = 0;  stateTable[18][4] = 0;  stateTable[18][5] = 0;  stateTable[18][6] = 0;  stateTable[18][7] = 0;  stateTable[18][8] = 0;  stateTable[18][9] = 0;  stateTable[18][10] = 0;  stateTable[18][11] = 0;  stateTable[18][12] = 0;  stateTable[18][13] = 0;  stateTable[18][14] = 0;  stateTable[18][15] = 0;  stateTable[18][16] = 0;
        stateTable[19][0] = 0;  stateTable[19][1] = 0;  stateTable[19][2] = 0;  stateTable[19][3] = 0;  stateTable[19][4] = 0;  stateTable[19][5] = 0;  stateTable[19][6] = 0;  stateTable[19][7] = 0;  stateTable[19][8] = 0;  stateTable[19][9] = 0;  stateTable[19][10] = 0;  stateTable[19][11] = 0;  stateTable[19][12] = 0;  stateTable[19][13] = 0;  stateTable[19][14] = 0;  stateTable[19][15] = 0;  stateTable[19][16] = 0;
        stateTable[20][0] = 0;  stateTable[20][1] = 0;  stateTable[20][2] = 0;  stateTable[20][3] = 0;  stateTable[20][4] = 0;  stateTable[20][5] = 0;  stateTable[20][6] = 0;  stateTable[20][7] = 0;  stateTable[20][8] = 0;  stateTable[20][9] = 0;  stateTable[20][10] = 0;  stateTable[20][11] = 0;  stateTable[20][12] = 0;  stateTable[20][13] = 0;  stateTable[20][14] = 0;  stateTable[20][15] = 0;  stateTable[20][16] = 0;
        stateTable[21][0] = 0;  stateTable[21][1] = 0;  stateTable[21][2] = 0;  stateTable[21][3] = 0;  stateTable[21][4] = 0;  stateTable[21][5] = 0;  stateTable[21][6] = 0;  stateTable[21][7] = 0;  stateTable[21][8] = 0;  stateTable[21][9] = 0;  stateTable[21][10] = 0;  stateTable[21][11] = 0;  stateTable[21][12] = 0;  stateTable[21][13] = 0;  stateTable[21][14] = 0;  stateTable[21][15] = 0;  stateTable[21][16] = 0;
        stateTable[22][0] = 0;  stateTable[22][1] = 0;  stateTable[22][2] = 0;  stateTable[22][3] = 0;  stateTable[22][4] = 0;  stateTable[22][5] = 0;  stateTable[22][6] = 0;  stateTable[22][7] = 0;  stateTable[22][8] = 0;  stateTable[22][9] = 0;  stateTable[22][10] = 0;  stateTable[22][11] = 0;  stateTable[22][12] = 0;  stateTable[22][13] = 0;  stateTable[22][14] = 0;  stateTable[22][15] = 0;  stateTable[22][16] = 0;
        stateTable[23][0] = 0;  stateTable[23][1] = 0;  stateTable[23][2] = 0;  stateTable[23][3] = 0;  stateTable[23][4] = 0;  stateTable[23][5] = 0;  stateTable[23][6] = 0;  stateTable[23][7] = 0;  stateTable[23][8] = 0;  stateTable[23][9] = 0;  stateTable[23][10] = 0;  stateTable[23][11] = 0;  stateTable[23][12] = 0;  stateTable[23][13] = 0;  stateTable[23][14] = 0;  stateTable[23][15] = 0;  stateTable[23][16] = 0;
        stateTable[24][0] = 0;  stateTable[24][1] = 0;  stateTable[24][2] = 0;  stateTable[24][3] = 0;  stateTable[24][4] = 0;  stateTable[24][5] = 0;  stateTable[24][6] = 0;  stateTable[24][7] = 0;  stateTable[24][8] = 0;  stateTable[24][9] = 0;  stateTable[24][10] = 0;  stateTable[24][11] = 0;  stateTable[24][12] = 0;  stateTable[24][13] = 0;  stateTable[24][14] = 0;  stateTable[24][15] = 0;  stateTable[24][16] = 0;
        stateTable[25][0] = 0;  stateTable[25][1] = 0;  stateTable[25][2] = 0;  stateTable[25][3] = 0;  stateTable[25][4] = 0;  stateTable[25][5] = 0;  stateTable[25][6] = 0;  stateTable[25][7] = 0;  stateTable[25][8] = 0;  stateTable[25][9] = 0;  stateTable[25][10] = 0;  stateTable[25][11] = 0;  stateTable[25][12] = 0;  stateTable[25][13] = 0;  stateTable[25][14] = 0;  stateTable[25][15] = 0;  stateTable[25][16] = 0;
        stateTable[26][0] = 0;  stateTable[26][1] = 0;  stateTable[26][2] = 0;  stateTable[26][3] = 0;  stateTable[26][4] = 0;  stateTable[26][5] = 0;  stateTable[26][6] = 0;  stateTable[26][7] = 0;  stateTable[26][8] = 0;  stateTable[26][9] = 0;  stateTable[26][10] = 0;  stateTable[26][11] = 0;  stateTable[26][12] = 0;  stateTable[26][13] = 0;  stateTable[26][14] = 0;  stateTable[26][15] = 0;  stateTable[26][16] = 0;
        stateTable[27][0] = 0;  stateTable[27][1] = 0;  stateTable[27][2] = 0;  stateTable[27][3] = 0;  stateTable[27][4] = 0;  stateTable[27][5] = 0;  stateTable[27][6] = 0;  stateTable[27][7] = 0;  stateTable[27][8] = 0;  stateTable[27][9] = 0;  stateTable[27][10] = 0;  stateTable[27][11] = 0;  stateTable[27][12] = 0;  stateTable[27][13] = 0;  stateTable[27][14] = 0;  stateTable[27][15] = 0;  stateTable[27][16] = 0;
	}

	// Determines which reserved word our current token is
	string ReservedWord(string currentToken){

		if(currentToken == "CLASS"){
			return "$CLASS";
		}
		else if(currentToken == "IF"){
			return "$IF";
		}
		else if(currentToken == "THEN"){
			return "$THEN";
		}
		else if(currentToken == "ELSE"){
			return "$ELSE";
		}
		else if(currentToken == "WHILE"){
			return "$WHILE";
		}
		else if(currentToken == "DO"){
			return "$DO";
		}
		else if(currentToken == "CONST"){
			return "$CONST";
		}
		else if(currentToken == "VAR"){
			return "<var>";
		}
		else if(currentToken == "GET"){
			return "GET";
		}
		else if(currentToken == "PUT"){
			return "PUT";
		}
		else{
			return "<var>";
		}
	}

	void beginningAssemblyGeneration(){
		ofstream asmFile;
		asmFile.open("Assembly.asm");

        // Prints the first part of .asm file
        asmFile << "sys_exit equ 1" << endl;
        asmFile << "sys_read equ 3" << endl;
        asmFile << "sys_write equ 4" << endl;
        asmFile << "stdin equ 0" << endl;
        asmFile << "stdout equ 1" << endl;
        asmFile << "stderr equ 3" << endl;
        asmFile << "" << endl;
		asmFile.close();
  	}

	void assemblyData(vector<symbol> symbolTable){
		ofstream asmFile;
		asmFile.open("Assembly.asm", ios::app);
        asmFile << "section .data ;used to declare constants" << endl;
		asmFile << "" << endl;
		asmFile << "\tuserMsg db 'Enter an integer(less than 32,765): '" << endl;
		asmFile << "\tlenUserMsg equ $-userMsg" << endl;
		asmFile << "\tdisplayMsg db 'You entered: '" << endl;
		asmFile << "\tlenDisplayMsg equ $-displayMsg" << endl;
		asmFile << "\tnewline db 0xA" << endl;
		asmFile << "\tTen DW 10" << endl;
		asmFile << "\tprintTempchar db 'Tempchar = : '" << endl;
		asmFile << "\tlenprintTempchar equ $-printTempchar" << endl;
		asmFile << "\tResult db 'Ans = '" << endl;
		asmFile << "\tResultValue db 'aaaaa'" << endl;
		asmFile << "\tdb	0xA" << endl;
		asmFile << "\tResultEnd equ $-Result" << endl;
		asmFile << "\tnum times 6 db 'ABCDEF'" << endl;
		asmFile << "\tnumEnd equ $-num" << endl;

		asmFile << "" << endl;
		for(int i = 1; i < symbolTable.size(); i++){

			if(symbolTable[i].value != "0"){
				cout << symbolTable[i].token << " " << symbolTable[i].value <<endl;
				if(symbolTable[i].value == symbolTable[i].token){
        			asmFile << "\tLit" << symbolTable[i].token << " DW " << symbolTable[i].value << endl;
				}
				else{
        			asmFile << "\t" << symbolTable[i].token << " DW " << symbolTable[i].value << endl;
				}
			}

		}

		asmFile << "" << endl;
        asmFile << "section .bss ;used to declare uninitialized variables" << endl;
        asmFile << "" << endl;
        asmFile << "\tTempChar RESB 1" << endl;
        asmFile << "\ttestchar RESB 1" << endl;
        asmFile << "\tReadInt RESW 1" << endl;
        asmFile << "\ttempint RESW 1" << endl;
        asmFile << "\tnegflag RESB 1" << endl;
        asmFile << "" << endl;


		for(int i = 1; i < symbolTable.size(); i++){

			if(symbolTable[i].value == "0"){
        		asmFile << "\t" << symbolTable[i].token << " RESW 1" << endl;
			}

		}
        asmFile << "" << endl;
		asmFile.close();
	}

	// Generates the Symbol Table
	void symbolTableGenerator(vector<token> tokenTable, int tempCount){
		vector<symbol> symbolTable;
		Boolean alreadyExists = false;
		string lineClass = "";
		int locationDS = 0;

		//cout << "Temps Needed: " << tempCount << endl;
	
		// We only care about the tokens that are variables, numbers, and temporary integers
		for(int i = 0; i < tokenTable.size(); i++){
			symbol newSymbol;

			// We first check if our line starts with a reserved word
			// Helps us define other variables to their respective types
			if(tokenTable[i].name == "CLASS"){
				newSymbol.token = tokenTable[i + 1].name;
				newSymbol.classification = "$CLASS";
				newSymbol.value = "0";
				newSymbol.address = "0";
				newSymbol.segment = "CS";
				symbolTable.push_back(newSymbol);
				i += 2;
			}
		
			else if(tokenTable[i].name == "CONST"){
				lineClass = tokenTable[i].classification;
				//cout << lineClass << endl;
			}

			else if(tokenTable[i].name == "VAR"){
				lineClass = tokenTable[i].classification;
				//cout << lineClass << endl;
			}

			// Ensures we don't reclassify variables incorrectly
			else if(tokenTable[i].name == ";"){
				lineClass = "";
			}

			// If the current token is a variable
			else if(tokenTable[i].classification == "<var>"){
				// Check if the symbol already exists within the symbol table
				for(int j = 0; j < symbolTable.size(); j++){
					// If it exists, no need to continue checking or add it to the symbol table
					if(tokenTable[i].name == symbolTable[j].token){
						alreadyExists = true;
						break;
					}
				}
					// Resets our boolean for the next token
					if(alreadyExists == true){
						alreadyExists = false;
					}
					
					// If the token doesn't exists in the symbol table, we add it.
					else if(alreadyExists == false){

						// Assigns symbol name
						newSymbol.token = tokenTable[i].name;
						// Determines if the symbol should be a CONST and assigns it's attributes accordingly
						if(lineClass == "$CONST"){
							newSymbol.classification = "$CONST";
							newSymbol.address = to_string(locationDS);
							newSymbol.segment = "DS";

							// Assigns a symbol its respective value
							if(tokenTable[i + 1].name == "=" && tokenTable[i + 2].classification == "<int>" && (tokenTable[i + 3].name == "," || tokenTable[i + 3].name == ";")){
								newSymbol.value = tokenTable[i + 2].name;
								i += 3;
							}

							locationDS += 2;							
						}
						// Determines if the symbol should be a VAR and assigns it's attributes accordingly (if we're on a line starting with VAR)
						else if(lineClass == "<var>"){
							newSymbol.classification = "<var>";
							newSymbol.address = to_string(locationDS);
							newSymbol.segment = "DS";
							
							// Assigns a symbol its respective value
							if(tokenTable[i + 1].name == "=" && tokenTable[i + 2].classification == "<int>" && (tokenTable[i + 3].name == "," || tokenTable[i + 3].name == ";")){
								newSymbol.value = tokenTable[i + 2].name;
								i += 3;
							}
							else{
								newSymbol.value = "0";
								i++;
							}

							locationDS += 2;
						}
						// Determines if the symbol should be a <var> and assigns it's attributes accordingly
						else if(lineClass == ""){
							newSymbol.classification = "<var>";
							newSymbol.address = to_string(locationDS);
							newSymbol.segment = "DS";
							locationDS += 2;
						}

						symbolTable.push_back(newSymbol);
					}

			}
			// If our token is a numeric literal
			else if(tokenTable[i].classification == "<int>"){
				// Check if the symbol already exists within the symbol table
				for(int j = 0; j < symbolTable.size(); j++){
					// If it exists, no need to continue checking or add it to the symbol table
					if(tokenTable[i].name == symbolTable[j].token){
						alreadyExists = true;
						break;
					}
				}
				// Resets our boolean for the next token
				if(alreadyExists == true){
						alreadyExists = false;
				}
					
				// If the token doesn't exists in the symbol table, we add it.
				else if(alreadyExists == false){
					newSymbol.token = tokenTable[i].name;
					newSymbol.classification = "$NumLit";
					newSymbol.value = tokenTable[i].name;
					newSymbol.address = to_string(locationDS);
					newSymbol.segment = "DS";
					locationDS += 2;
					symbolTable.push_back(newSymbol);
				}
			}
		}

		// Adds our Temps to the symbol table
		if(tempCount > 0){
			symbol newSymbol;
			for(int i = 1; i <= tempCount; i++){
				newSymbol.token = "T" + to_string(i);
				newSymbol.classification = "<var>";
				newSymbol.value = "0";
				newSymbol.address = to_string(locationDS);
				newSymbol.segment = "DS";
				locationDS += 2;
				symbolTable.push_back(newSymbol);
			}
		}

		// Prints the Symbol Table to a file called "SymbolTable.txt"
		ofstream STFile;
		STFile.open("SymbolTable.txt");
		STFile << left << "Token" << "\t\t" << "Class" << "\t\t\t" << "Value" << "\t\t" << "Address" << "\t\t" << "Segment" << endl;
		STFile << "---------------------------------------------------------------" << endl;

		for(int k = 0; k < symbolTable.size(); k++){
			// The if and else resolve spacing issues in formatting output
			if(symbolTable[k].token.size() > 3){
				STFile << symbolTable[k].token << "\t\t"
			           << symbolTable[k].classification << "\t\t\t"
				   	   << symbolTable[k].value << "\t\t\t"
				       << symbolTable[k].address << "\t\t\t"
				       << symbolTable[k].segment << endl;
			}

			else{
				STFile << symbolTable[k].token << "\t\t\t"
					   << symbolTable[k].classification << "\t\t\t"
					   << symbolTable[k].value << "\t\t\t"
					   << symbolTable[k].address << "\t\t\t"
					   << symbolTable[k].segment << endl;
			}
		}
		STFile.close();
		assemblyData(symbolTable);
	}

	vector<token> stateChanger(string program){
		char currentCharacter;
		vector<token> tokenTable;
		string tokenClass = "";
		string lineDataType = "";
		string currentToken = "";
		token newToken;
		int temporaryIntegersNeeded = 0;
		int operatorCounter = 0;
		int index = 0;


		int state = 0; // Current state
		// Iterates through program one character at a time
	    while(index < program.length()){
			currentCharacter = program[index];
			// Finds our new state
			state = stateTable[state][findColumn(currentCharacter)]; 

				switch (state){
				case 0:  // State: Start
					
					if((int)currentCharacter == 10){
						lineDataType = "";
					}
					currentToken = "";
					//cout << "State : Start - 0" << endl;
					index++;
					break;

				case 1:  // State: Creating Integer
					currentToken += currentCharacter;
					//cout << "State : CreatingInt - 1" << endl;
					index++;
					break;

				case 2:  // (Finish) State: Integer, <int>
					//cout << currentToken << " Integer, <int>\n";
					//cout << "State : Integer - 2" << endl;
					newToken.name = currentToken;
					newToken.classification = "<int>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					break;

				case 3:  // State: Creating Variable
					//cout << "State : CreatingVar - 3" << endl;
					currentToken += currentCharacter;
					index++;
					break;

				case 4:  // (Finish) State: Variable, <var>
					//cout << currentToken << " Variable, <var>\n"; // Add token to vector. Vector elements will contain (token, classification)
					//cout << "State : Variable - 4" << endl;
				
					// If our current character is whitespace, we skip it and create our token.
					if((int)currentCharacter == 32){
						index++;
					}

					tokenClass = ReservedWord(currentToken);
					newToken.name = currentToken;
					newToken.classification = tokenClass;
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					break;

				case 5:  // (Finish) State: *, <mop>
					//cout << currentToken << " *, <mop>\n";// Add token to vector. Vector elements will contain (token, classification)
					//cout << "State : * - 5" << endl;
					newToken.name = "*";
					newToken.classification = "<mop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					operatorCounter++;
					index++;
					break;

				case 6:  // State: Comment or /, <mop>
					//cout << "State : CommentOr/ - 6" << endl;
					index++;
					break;

				case 7:  // (Finish) State: /, <mop>
					//cout << currentToken << " /, <mop>\n";
					//cout << "State : / - 7" << endl;
					newToken.name = "/";
					newToken.classification = "<mop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					operatorCounter++;
					index++;
					break;

				case 8:  // State: Wanna close the comment?
					//cout << "Ignoring Comment" << endl;
					//cout << "State : wcComment1 - 8" << endl;
					index++;
					break;

				case 9:  // State: Wanna close the comment #2?
					//cout << "Ignoring Comment" << endl;
					//cout << "State : wcComment2 - 9" << endl;
					index++;
					break;

				case 10: // State: = or ==? 
					//cout << "State : =Or== - 10" << endl;
					currentToken += currentCharacter;
					index++;
					break;

				case 11: // (Finish) State: =, <assign>
					//cout << currentToken << " =, <assign>\n";
					//cout << "State : = - 11" << endl;
					newToken.name = currentToken;
					newToken.classification = "<assign>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;

				case 12: // (Finish) State: ==, <relop>
					currentToken += currentCharacter;
					//cout << currentToken << " ==, <relop>\n";
					//cout << "State : == - 12" << endl;
					newToken.name = currentToken;
					newToken.classification = "<relop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;

				case 13: // State: < or <=?
					//cout << "State : <Or<= - 13" << endl;
					currentToken += currentCharacter;
					index++;
					operatorCounter++;
					break;

				case 14: // (Finish) State: <, <relop> 
					//cout << currentToken << " <, <relop>\n";
					//cout << "State : < - 14" << endl;
					newToken.name = currentToken;
					newToken.classification = "<relop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					operatorCounter++;
					break;

				case 15: // (Finish) State: <=, <relop> 
					currentToken += currentCharacter;
					//cout << currentToken << " <=, <relop>\n";
					//cout << "State : <= - 15" << endl;
					newToken.name = currentToken;
					newToken.classification = "<relop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					operatorCounter++;
					break;

				case 16: // State: > or >=? 
					//cout << "State : >Or>= - 16" << endl;
					currentToken += currentCharacter;
					index++;
					break;

				case 17: // (Finish) State: >, <relop> 
					//cout << currentToken << " >, <relop>\n";
					//cout << "State : > - 17" << endl;
					newToken.name = currentToken;
					newToken.classification = "<relop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					operatorCounter++;
					break;

				case 18: // (Finish) State: >=, <relop> 
					currentToken += currentCharacter;
					//cout << currentToken << " >=, <relop>\n";
					//cout << "State : >= - 18" << endl;
					newToken.name = currentToken;
					newToken.classification = "<relop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					operatorCounter++;
					break;

				case 19: // (Finish) State: +, <addop> 
					//cout << currentCharacter << " +, <addop>\n";
					//cout << "State : + - 19" << endl;
					newToken.name = "+";
					newToken.classification = "<addop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					operatorCounter++;
					index++;
					break;

				case 20: // (Finish) State: -, <addop> 
					//cout << currentCharacter << " -, <addop>\n";
					//cout << "State : - - 20" << endl;
					newToken.name = "-";
					newToken.classification = "<addop>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					operatorCounter++;
					index++;
					break;

				case 21: // (Finish) State: (, <parenthesisL> 
					//cout << currentCharacter << " (, <parenthesisL>\n";
					//cout << "State : ( - 21" << endl;
					newToken.name = "(";
					newToken.classification = "<parenthesisL>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;

				case 22: // (Finish) State: ), <parenthesisR>
					//cout << currentCharacter << " ), <parenthesisR>\n";
					//cout << "State : ) - 22" << endl;
					newToken.name = ")";
					newToken.classification = "<parenthesisR>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;

				case 23: // (Finish) State: {, <braceL>
					//cout << currentCharacter << ", <braceL>\n";
					//cout << "State : { - 23" << endl;
					newToken.name = "{";
					newToken.classification = "<braceL>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;

				case 24: // (Finish) State: }, <braceR>
					//cout << currentCharacter << " }, <braceR>\n";
					//cout << "State : } - 24" << endl;
					newToken.name = "}";
					newToken.classification = "<braceR>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;

				case 25: // (Finish) State: ,, <comma>
					//cout << currentCharacter << " , <comma>\n";
					//cout << "State : , - 25" << endl;
					newToken.name = ",";
					newToken.classification = "<comma>";
					tokenTable.push_back(newToken);
					currentToken = "";
					state = 0;
					index++;
					break;
				
				case 26: // (Finish) State: ;, <semicolon>
					//cout << currentCharacter << " , <semicolon>\n";
					//cout << "State : ; - 26" << endl;
					newToken.name = ";";
					newToken.classification = "<semicolon>";
					tokenTable.push_back(newToken);
					lineDataType = "";
					currentToken = "";
					state = 0;
					index++;

					// Helps us determine how many temps we will need
					if(operatorCounter > temporaryIntegersNeeded){
						temporaryIntegersNeeded = operatorCounter;
					}
			
					operatorCounter = 0;
					break;

				case 27: // State: Other (Error Checking)
					//cout << "State : Other" << endl;
					state = 0;
					break;
				}			
		}
			
		// Prints the Token Table to a file called "TokenTable.txt"
		ofstream TCFile;
		TCFile.open("TokenTable.txt");
		TCFile << left << "Token" << "\t\t" << "Classification" << endl;
		TCFile << "----------------------------------" << endl;
		for(int k = 0; k < tokenTable.size(); k++){
			// The if and else resolve spacing issues in formatting output
			if(tokenTable[k].name.size() > 3){
				TCFile << tokenTable[k].name << "\t\t"
			           << tokenTable[k].classification << endl;
			}

			else{
				TCFile << left << tokenTable[k].name << "\t\t\t"
			       	   << left << tokenTable[k].classification << endl;
			}
		}
		TCFile.close();
		beginningAssemblyGeneration();
		symbolTableGenerator(tokenTable, temporaryIntegersNeeded);
		return tokenTable;
	}

	// Finds the column for our state table look-up
	int findColumn(char ch){

		// Converts the current character to its ASCII equivalent
		int asciiOfCh = (int)ch;

		//cout << "Finding Column! Current character: " << ch << endl;
		//cout << "Converted to ASCII: " << asciiOfCh << endl;

		// If the character is newline --> return to starting state
		if(asciiOfCh == 10){
			//cout << "New Line Found!" << endl;
			return 0;
		}

		// If the character is whitespace --> return whitespace's column
		else if(asciiOfCh == 32){
			//cout << "Whitespace Found!" << endl;
			return 0;
		}

		// The character is a number --> return number's column		
		else if(asciiOfCh >= 48 && asciiOfCh <= 57){
			//cout << "Number Found: " << ch << endl;
			return 1;
		}

		// The character is a letter --> return letter's column
		else if( (asciiOfCh >= 65 && asciiOfCh <= 90) || (asciiOfCh >= 97 && asciiOfCh <= 122)){
			//cout << "Letter Found: " << ch << endl;
			return 2;
		}

		// If the character is multiply operator (*) --> return multiply column
		else if(asciiOfCh == 42){
			//cout << "Multiply Operator Found!" << endl;
			return 3;
		}

		// If the character is division operator (/) --> return division column
		else if(asciiOfCh == 47){
			//cout << "Division Operator Found!" << endl;
			return 4;
		}

		// If the character is the equals operator (=) --> return equals column
		else if(asciiOfCh == 61){
			//cout << "Equals Operator Found!"<< endl;
			return 5;
		}

		// If the character is the less-than relational operator (<) --> return < column
		else if(asciiOfCh == 60){
			//cout << "Less Than Operator Found!"<< endl;
			return 6;
		}

		// If the character is the greater-than relational operator (>) --> return > column
		else if(asciiOfCh == 62){
			//cout << "Greater Than Operator Found!"<< endl;
			return 7;
		}

		// If the character is the add operator (+) --> return + column
		else if(asciiOfCh == 43){
			//cout << "Add Operator Found!"<< endl;
			return 8;
		}

		// If the character is the sub operator (-) --> return - column
		else if(asciiOfCh == 45){
			//cout << "Sub Operator Found!"<< endl;
			return 9;
		}

		// If the character is the left parenthesis ('(') --> return ( column
		else if(asciiOfCh == 40){
			//cout << "Left Parenthesis Found!"<< endl;
			return 10;
		}

		// If the character is the right parenthesis (')') --> return ) column
		else if(asciiOfCh == 41){
			//cout << "Right Parenthesis Found!"<< endl;
			return 11;
		}

		// If the character is the left brace ('{') --> return { column
		else if(asciiOfCh == 123){
			//cout << "Left Brace Found!"<< endl;
			return 12;
		}

		// If the character is the right brace ('}') --> return } column
		else if(asciiOfCh == 125){
			//cout << "Right Brace Found!"<< endl;
			return 13;
		}

		// If the character is the comma (,) --> return , column
		else if(asciiOfCh == 44){
			//cout << "Comma Found!"<< endl;
			return 14;
		}

		// If the character is the semi-colon (;) --> return ; column
		else if(asciiOfCh == 59){
			//cout << "Semi-Colon Found!"<< endl;
			return 15;
		}

		// For error checking --> Returns the Other column
		else{
			//cout << "Something Else was Found!"<< endl;
			//cout << asciiOfCh << " is the ascii found" << endl;
			return 16;
		}
	}
};