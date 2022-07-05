#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

typedef int Boolean;

enum precedence{
    EQUALS,     // "="
    GIVES,      // "<"
    TAKES,      // ">"
    NO_RELATION // "No relation to one another"
};

enum operatorsAndSymbols{
    DELIMITER,  // "; OR ,"
    ASSIGN,     // "="
    ADD,        // "+"
    SUB,        // "-"
    L_PAREN,    // "("
    R_PAREN,    // ")"
    MOP,        // "*"
    DOP,         // "/"
    OTHER = -1 // For errors atm
};

class Quad{
public:

string left = "";
string right = "";
string oper = "";
string location = "";

};

class PushDownAutomaton {
private:
    int precedenceTable[17][17];

public:
    vector<string> Stack;
    vector<Quad> Quads;   
    Boolean hasOperator = false;
    string forlabel = "";
    string ifElse = "";
    int index = 0;
    int precedenceState = 0;
    int itemsInStack = 0;
    int operatorCount = 0;
    int tempIntegerCounter = 1;
    int lCounter = 1;
    int inAnIfOrElse = 0;

   // Table is read as: Row to Column
   // Example: "= < +" is read as = gives to +
    PushDownAutomaton(){
        precedenceTable[0][0] = 3; precedenceTable[0][1] = 3; precedenceTable[0][2] = 3; precedenceTable[0][3] = 3; precedenceTable[0][4] = 3; precedenceTable[0][5] = 3; precedenceTable[0][6] = 3; precedenceTable[0][7] = 3; precedenceTable[0][8] = 3; precedenceTable[0][9] = 3; precedenceTable[0][10] = 3; precedenceTable[0][11] = 3; precedenceTable[0][12] = 3; precedenceTable[0][13] = 3; precedenceTable[0][14] = 3; precedenceTable[0][15] = 3; precedenceTable[0][16] = 3;
        precedenceTable[1][0] = 2; precedenceTable[1][1] = 3; precedenceTable[1][2] = 1; precedenceTable[1][3] = 1; precedenceTable[1][4] = 1; precedenceTable[1][5] = 3; precedenceTable[1][6] = 1; precedenceTable[1][7] = 1; precedenceTable[1][8] = 3; precedenceTable[1][9] = 3; precedenceTable[1][10] = 3; precedenceTable[1][11] = 3; precedenceTable[1][12] = 3; precedenceTable[1][13] = 3; precedenceTable[1][14] = 3; precedenceTable[1][15] = 3; precedenceTable[1][16] = 3;
        precedenceTable[2][0] = 2; precedenceTable[2][1] = 3; precedenceTable[2][2] = 2; precedenceTable[2][3] = 2; precedenceTable[2][4] = 1; precedenceTable[2][5] = 2; precedenceTable[2][6] = 1; precedenceTable[2][7] = 1; precedenceTable[2][8] = 3; precedenceTable[2][9] = 2; precedenceTable[2][10] = 2; precedenceTable[2][11] = 2; precedenceTable[2][12] = 2; precedenceTable[2][13] = 2; precedenceTable[2][14] = 2; precedenceTable[2][15] = 2; precedenceTable[2][16] = 3;
        precedenceTable[3][0] = 2; precedenceTable[3][1] = 3; precedenceTable[3][2] = 2; precedenceTable[3][3] = 2; precedenceTable[3][4] = 1; precedenceTable[3][5] = 2; precedenceTable[3][6] = 1; precedenceTable[3][7] = 1; precedenceTable[3][8] = 3; precedenceTable[3][9] = 2; precedenceTable[3][10] = 2; precedenceTable[3][11] = 2; precedenceTable[3][12] = 2; precedenceTable[3][13] = 2; precedenceTable[3][14] = 2; precedenceTable[3][15] = 2; precedenceTable[3][16] = 3;
        precedenceTable[4][0] = 3; precedenceTable[4][1] = 3; precedenceTable[4][2] = 1; precedenceTable[4][3] = 1; precedenceTable[4][4] = 1; precedenceTable[4][5] = 0; precedenceTable[4][6] = 1; precedenceTable[4][7] = 1; precedenceTable[4][8] = 3; precedenceTable[4][9] = 3; precedenceTable[4][10] = 3; precedenceTable[4][11] = 3; precedenceTable[4][12] = 3; precedenceTable[4][13] = 3; precedenceTable[4][14] = 3; precedenceTable[4][15] = 3; precedenceTable[4][16] = 3;
        precedenceTable[5][0] = 2; precedenceTable[5][1] = 3; precedenceTable[5][2] = 2; precedenceTable[5][3] = 2; precedenceTable[5][4] = 3; precedenceTable[5][5] = 2; precedenceTable[5][6] = 2; precedenceTable[5][7] = 2; precedenceTable[5][8] = 3; precedenceTable[5][9] = 3; precedenceTable[5][10] = 3; precedenceTable[5][11] = 3; precedenceTable[5][12] = 3; precedenceTable[5][13] = 3; precedenceTable[5][14] = 3; precedenceTable[5][15] = 3; precedenceTable[5][16] = 3;
        precedenceTable[6][0] = 2; precedenceTable[6][1] = 3; precedenceTable[6][2] = 2; precedenceTable[6][3] = 2; precedenceTable[6][4] = 1; precedenceTable[6][5] = 2; precedenceTable[6][6] = 2; precedenceTable[6][7] = 2; precedenceTable[6][8] = 3; precedenceTable[6][9] = 2; precedenceTable[6][10] = 2; precedenceTable[6][11] = 2; precedenceTable[6][12] = 2; precedenceTable[6][13] = 2; precedenceTable[6][14] = 2; precedenceTable[6][15] = 2; precedenceTable[6][16] = 3;
        precedenceTable[7][0] = 2; precedenceTable[7][1] = 3; precedenceTable[7][2] = 2; precedenceTable[7][3] = 2; precedenceTable[7][4] = 1; precedenceTable[7][5] = 2; precedenceTable[7][6] = 2; precedenceTable[7][7] = 2; precedenceTable[7][8] = 3; precedenceTable[7][9] = 2; precedenceTable[7][10] = 2; precedenceTable[7][11] = 2; precedenceTable[7][12] = 2; precedenceTable[7][13] = 2; precedenceTable[7][14] = 2; precedenceTable[7][15] = 2; precedenceTable[7][16] = 3;
        precedenceTable[8][0] = 3; precedenceTable[8][1] = 3; precedenceTable[8][2] = 1; precedenceTable[8][3] = 1; precedenceTable[8][4] = 1; precedenceTable[8][5] = 3; precedenceTable[8][6] = 1; precedenceTable[8][7] = 1; precedenceTable[8][8] = 3; precedenceTable[8][9] = 0; precedenceTable[8][10] = 1; precedenceTable[8][11] = 1; precedenceTable[8][12] = 1; precedenceTable[8][13] = 1; precedenceTable[8][14] = 1; precedenceTable[8][15] = 1; precedenceTable[8][16] = 3;
        precedenceTable[9][0] = 3; precedenceTable[9][1] = 1; precedenceTable[9][2] = 3; precedenceTable[9][3] = 3; precedenceTable[9][4] = 3; precedenceTable[9][5] = 3; precedenceTable[9][6] = 3; precedenceTable[9][7] = 3; precedenceTable[9][8] = 1; precedenceTable[9][9] = 3; precedenceTable[9][10] = 3; precedenceTable[9][11] = 3; precedenceTable[9][12] = 3; precedenceTable[9][13] = 3; precedenceTable[9][14] = 3; precedenceTable[9][15] = 3; precedenceTable[9][16] = 3;
        precedenceTable[10][0] = 3; precedenceTable[10][1] = 3; precedenceTable[10][2] = 1; precedenceTable[10][3] = 1; precedenceTable[10][4] = 1; precedenceTable[10][5] = 3; precedenceTable[10][6] = 1; precedenceTable[10][7] = 1; precedenceTable[10][8] = 3; precedenceTable[10][9] = 2; precedenceTable[10][10] = 3; precedenceTable[10][11] = 3; precedenceTable[10][12] = 3; precedenceTable[10][13] = 3; precedenceTable[10][14] = 3; precedenceTable[10][15] = 3; precedenceTable[10][16] = 1;
        precedenceTable[11][0] = 3; precedenceTable[11][1] = 3; precedenceTable[11][2] = 1; precedenceTable[11][3] = 1; precedenceTable[11][4] = 1; precedenceTable[11][5] = 3; precedenceTable[11][6] = 1; precedenceTable[11][7] = 1; precedenceTable[11][8] = 3; precedenceTable[11][9] = 2; precedenceTable[11][10] = 3; precedenceTable[11][11] = 3; precedenceTable[11][12] = 3; precedenceTable[11][13] = 3; precedenceTable[11][14] = 3; precedenceTable[11][15] = 3; precedenceTable[11][16] = 3;
        precedenceTable[12][0] = 3; precedenceTable[12][1] = 3; precedenceTable[12][2] = 1; precedenceTable[12][3] = 1; precedenceTable[12][4] = 1; precedenceTable[12][5] = 3; precedenceTable[12][6] = 1; precedenceTable[12][7] = 1; precedenceTable[12][8] = 3; precedenceTable[12][9] = 2; precedenceTable[12][10] = 3; precedenceTable[12][11] = 3; precedenceTable[12][12] = 3; precedenceTable[12][13] = 3; precedenceTable[12][14] = 3; precedenceTable[12][15] = 3; precedenceTable[12][16] = 3;
        precedenceTable[13][0] = 3; precedenceTable[13][1] = 3; precedenceTable[13][2] = 1; precedenceTable[13][3] = 1; precedenceTable[13][4] = 1; precedenceTable[13][5] = 3; precedenceTable[13][6] = 1; precedenceTable[13][7] = 1; precedenceTable[13][8] = 3; precedenceTable[13][9] = 2; precedenceTable[13][10] = 3; precedenceTable[13][11] = 3; precedenceTable[13][12] = 3; precedenceTable[13][13] = 3; precedenceTable[13][14] = 3; precedenceTable[13][15] = 3; precedenceTable[13][16] = 3;
        precedenceTable[14][0] = 3; precedenceTable[14][1] = 3; precedenceTable[14][2] = 1; precedenceTable[14][3] = 1; precedenceTable[14][4] = 1; precedenceTable[14][5] = 3; precedenceTable[14][6] = 1; precedenceTable[14][7] = 1; precedenceTable[14][8] = 3; precedenceTable[14][9] = 2; precedenceTable[14][10] = 3; precedenceTable[14][11] = 3; precedenceTable[14][12] = 3; precedenceTable[14][13] = 3; precedenceTable[14][14] = 3; precedenceTable[14][15] = 3; precedenceTable[14][16] = 3;
        precedenceTable[15][0] = 3; precedenceTable[15][1] = 3; precedenceTable[15][2] = 1; precedenceTable[15][3] = 1; precedenceTable[15][4] = 1; precedenceTable[15][5] = 3; precedenceTable[15][6] = 1; precedenceTable[15][7] = 1; precedenceTable[15][8] = 3; precedenceTable[15][9] = 2; precedenceTable[15][10] = 3; precedenceTable[15][11] = 3; precedenceTable[15][12] = 3; precedenceTable[15][13] = 3; precedenceTable[15][14] = 3; precedenceTable[15][15] = 3; precedenceTable[15][16] = 3;
        precedenceTable[16][0] = 3; precedenceTable[16][1] = 3; precedenceTable[16][2] = 3; precedenceTable[16][3] = 3; precedenceTable[16][4] = 3; precedenceTable[16][5] = 3; precedenceTable[16][6] = 3; precedenceTable[16][7] = 3; precedenceTable[16][8] = 3; precedenceTable[16][9] = 3; precedenceTable[16][10] = 3; precedenceTable[16][11] = 3; precedenceTable[16][12] = 3; precedenceTable[16][13] = 3; precedenceTable[16][14] = 3; precedenceTable[16][15] = 3; precedenceTable[16][16] = 3;

    }

    Boolean isOperatorOrSymbol(token currentToken){

        if(currentToken.classification == "<addop>"        ||
           currentToken.classification == "<mop>"          ||
           currentToken.classification == "<assign>"       ||
           currentToken.classification == "<parenthesisL>" ||
           currentToken.classification == "<parenthesisR>" ||
           currentToken.classification == "<bracesL>"      ||
           currentToken.classification == "<bracesR>"      ||
           currentToken.classification == "<relop>"        ||
           currentToken.classification == "<comma>"        ||
           currentToken.classification == "<semicolon>"    ||
           currentToken.classification == "<comma>"        ||
           currentToken.classification == "$THEN"){
            return true;
        }
        return false;
    }

    int operatorToEnum(string currentToken){

        if(currentToken == ";" || currentToken == ","){
            //cout << "Returns 0" << endl;
            return 0;
        }
        else if(currentToken == "="){
            //cout << "Returns 1" << endl;
            return 1;
        }
        else if(currentToken == "+"){
            //cout << "Returns 2" << endl;
            return 2;
        }
        else if(currentToken == "-"){
            //cout << "Returns 3" << endl;
            return 3;
        }
        else if(currentToken == "("){
            //cout << "Returns 4" << endl;
            return 4;
        }
        else if(currentToken == ")"){
            //cout << "Returns 5" << endl;
            return 5;
        }
        else if(currentToken == "*"){
            //cout << "Returns 6" << endl;
            return 6;
        }
        else if(currentToken == "/"){
            //cout << "Returns 7" << endl;
            return 7;
        }
        else if(currentToken == "IF"){
            //cout << "Returns 8" << endl;
            return 8;
        }
        else if(currentToken == "THEN"){
            //cout << "Returns 9" << endl;
            return 9;
        }
        else if(currentToken == "=="){
            //cout << "Returns 10" << endl;
            return 10;
        }
        else if(currentToken == "!="){
            //cout << "Returns 11" << endl;
            return 11;
        }
        else if(currentToken == ">"){
            //cout << "Returns 12" << endl;
            return 12;
        }
        else if(currentToken == "<"){
            //cout << "Returns 13" << endl;
            return 13;
        }
        else if(currentToken == ">="){
            //cout << "Returns 14" << endl;
            return 14;
        }
        else if(currentToken == "<="){
            //cout << "Returns 15" << endl;
            return 15;
        }
        else if(currentToken == "{"){
            //cout << "Returns 16" << endl;
            return 16;
        }
        else if(currentToken == "}"){
            //cout << "Returns 17" << endl;
            return 17;
        }
        else{
            return -1; //Returns a -1                           
        }
    }

    void operatorPrecedence(string newestOperator){
        if(operatorCount > 0){

            if(newestOperator == "(" || newestOperator == "{"){
                precedenceState = precedenceTable[operatorToEnum(Stack[itemsInStack - 1])][operatorToEnum(newestOperator)];
                //cout << "Operator in Stack: " << Stack[itemsInStack - 1] << endl;
            }
            else{
                precedenceState = precedenceTable[operatorToEnum(Stack[itemsInStack - 2])][operatorToEnum(newestOperator)];
                //cout << "Operator in Stack: " << Stack[itemsInStack - 2] << endl;
            }

            //cout << "New operator: " << newestOperator << endl;
            //cout << "State: " << precedenceState << endl;

            // Determines course of action
            switch(precedenceState){

            case 0: //Equals --> We do something
                
                if(newestOperator == ")" && Stack[itemsInStack - 2] == "("){
                    //cout << "Popped from stack: " << Stack[itemsInStack - 2] << endl;
                    Stack.erase(Stack.begin() + (itemsInStack - 2));
                    operatorCount--;
                    itemsInStack--;  
                    index++;                 
                }
                break;

            case 1: //Gives --> We add the new operator to the stack

                //cout << Stack[itemsInStack - 2] << " gives " << newestOperator << endl;
                //cout << newestOperator << " was pushed in the stack" << endl;
                Stack.push_back(newestOperator);
                itemsInStack++;
                operatorCount++;
                index++;
                break;

            case 2: //Takes --> We create a quad(s) for the last operator in the stack (row)
                    
                //cout << Stack[itemsInStack - 2] << " takes " << newestOperator << endl;
                //cout << "Make a quad!" << endl;
                quadCreation(Stack[itemsInStack - 2]);
                itemsInStack -= 2;
                operatorCount--;
                if(operatorCount == 0){
                    hasOperator = false;
                }
                break;

            case 3: //No Relation --> We pop the operator in the stack and move on to the next token!
                //cout << "Popped from stack: " << Stack[itemsInStack - 2] << endl;
                Stack.erase(Stack.begin() + (itemsInStack - 2));
                operatorCount--;
                itemsInStack--;
                index++;                 
                break; 

            default:
                //cout << "State: Error" << endl;
                index++;
                break;                                                                          
            }   
        }
        else{
            index++;
        }        
    }

    string labelCreation(){

        // If we have a ">", we need to create a LE
        if(forlabel == ">"){
            return "LE";
        }

        // Else, we have a ">=", we need to create an L
        return "L";
    }

    void quadCreation(string currentToken){
        string op = "";
        string lOperand = "";
        string rOperand = "";
        string tInteger = "T";
        string label = "L";
        string newQuad = "";
        Quad Q;
        ofstream QFile;
		QFile.open("Quads.txt", ios::app);

        if(currentToken == "IF"){
            Q.left = "IF";
            Q.right = "?";
            Q.oper = "?";
            Q.location = "?";
            newQuad = Q.left + " " + Q.right + " " + Q.oper + " " + Q.location;
            QFile << newQuad << endl;
            Quads.push_back(Q);
        }
        else if(currentToken == "THEN"){
            label = label + to_string(lCounter);
            Q.left = "THEN";
            Q.right = label;
            Q.oper = labelCreation();
            Q.location = "?";
            newQuad = Q.left + " " + Q.right + " " + Q.oper + " " + Q.location;
            QFile << newQuad << endl;
            Quads.push_back(Q);
            ifElse = "THEN";
            lCounter++;
        }
        else if(currentToken == "}"){

            if(ifElse == "THEN"){
                label = label + to_string(lCounter);
                Q.left = "J" + label;
                Q.right = ":";
                Q.oper = "NOP";
                Q.location = "?";
                newQuad = Q.left + Q.right + " " + Q.oper;
                QFile << newQuad << endl;
                Quads.push_back(Q);
                ifElse = "";
            }
            else if(ifElse == "ELSE"){
                label = label + to_string(lCounter);
                Q.left = label;
                Q.right = ":";
                Q.oper = "NOP";
                Q.location = "?";
                newQuad = Q.left + Q.right + " " + Q.oper;
                QFile << newQuad << endl;
                Quads.push_back(Q);
            }
        }
        else if(currentToken == "ELSE"){
            label = label + to_string(lCounter - 1);
            Q.left = "ELSE";
            Q.right = label;
            Q.oper = "?";
            Q.location = "?";
            newQuad = Q.left + " " + Q.right + " " + Q.oper + " " + Q.location;
            QFile << newQuad << endl;
            Quads.push_back(Q);
            ifElse = currentToken;
        }
        else if(currentToken == "GET" || currentToken == "PUT"){
            Q.left = currentToken;
            Q.right = Stack[itemsInStack - 1];;
            Q.oper = "?";
            Q.location = "?";
            newQuad = Q.left + " " + Q.right + " " + Q.oper + " " + Q.location;
            QFile << newQuad << endl;
            Stack.pop_back();
            Quads.push_back(Q);

        }
        else if(Stack[itemsInStack - 2] == "=" || Stack[itemsInStack - 2] == ">" || Stack[itemsInStack - 2] == ">="){
            
            // Helps set us up for Label creation
            if(Stack[itemsInStack - 2] == ">" || Stack[itemsInStack - 2] == ">="){
                forlabel = Stack[itemsInStack - 2];
            }
            
            
            op = Stack[itemsInStack - 2];
            lOperand = Stack[itemsInStack - 3];
            rOperand = Stack[itemsInStack - 1];

            tempIntegerCounter = 1;
            //cout << "Temp count = " << tempIntegerCounter << endl;
            tInteger = tInteger + to_string(tempIntegerCounter);
            //cout << newQuad << endl;
            Q.left = lOperand;
            Q.right = rOperand;
            Q.oper = op;
            Q.location = tInteger;
            newQuad = Q.left + " " + Q.right + " " + Q.oper + " " + Q.location;
            QFile << newQuad << endl;
            Quads.push_back(Q);
            //cout << "Temp count after increase = " << tempIntegerCounter << endl;
            
            // Pops the current quad from the stack
            for(int i = 0; i < 3; i++){
                //cout << "Erasing: " << Stack[Stack.size() - 1] << endl;
                Stack.pop_back();
            }
            
            Stack.push_back(newQuad);

        }
        else{

            // Find our operator and operands for our quad
            op = Stack[itemsInStack - 2];
            lOperand = Stack[itemsInStack - 3];
            rOperand = Stack[itemsInStack - 1];
            tInteger = tInteger + to_string(tempIntegerCounter);

            //cout << "Temp count = " << tempIntegerCounter << endl;
            //cout << "tInteger = " << tInteger << endl;

            Q.left = lOperand;
            Q.right = rOperand;
            Q.oper = op;
            Q.location = tInteger;
            newQuad = Q.left + " " + Q.right + " " + Q.oper + " " + Q.location;
            Quads.push_back(Q);
            tempIntegerCounter++;
            QFile << newQuad << endl;
            //cout << "Temp count after increase = " << tempIntegerCounter << endl;
            
            // Pops the current quad from the stack
            for(int i = 0; i < 3; i++){
                //cout << "Erasing: " << Stack[Stack.size() - 1] << endl;
                Stack.pop_back();
            }
            
            Stack.push_back(tInteger);
           
        }
		QFile.close();
    }

    vector<Quad> findLine(vector<token> tokenTable){

        while(index < tokenTable.size()){
            //cout << tokenTable[index].name << endl;
            if(tokenTable[index].classification == "<var>" || tokenTable[index].classification == "$IF" || tokenTable[index].classification == "$ELSE" || tokenTable[index].classification == "GET" || tokenTable[index].classification == "PUT"){

                // If our token is the keyword VAR, we skip.
                if(tokenTable[index].classification == "<var>" && tokenTable[index + 1].name != "="){
                    //cout << "Skipping" << endl;
                    index++;
                    continue;
                }
                else{
                    
                    //cout << "We found our arithmetic line!" << endl;
                    //cout << "The line starts with: " << tokenTable[index].name << endl;


                    // We've found an arithmetic line.
                    while(index < tokenTable.size()){
                        
                        //cout << "Checking token: " << tokenTable[index].name << endl;

                        // If our token is a <var>, add it to the stack
                        if(tokenTable[index].classification == "<var>" || tokenTable[index].classification == "<int>"){
                            //cout << "We found a <var> or <int>" << endl;
                            //cout << tokenTable[index].name << " was pushed in the stack" << endl;
                            itemsInStack++;
                            Stack.push_back(tokenTable[index].name);
                            index++;
                        }
                        // If our token is an IF or a THEN, then we push it to the stack and create its Quad
                        else if(tokenTable[index].classification == "$IF" || tokenTable[index].classification == "$ELSE"){
                            //cout << "We found a $IF or $ELSE!" << endl;
                            //cout << tokenTable[index].name << " was pushed in the stack" << endl;
                            quadCreation(tokenTable[index].name);
                            inAnIfOrElse++;
                            index++;
                        }
                        else if(tokenTable[index].classification == "GET" || tokenTable[index].classification == "PUT"){
                            itemsInStack++;
                            Stack.push_back(tokenTable[index + 1].name);
                            quadCreation(tokenTable[index].name);
                            index += 2;
                            itemsInStack--;
                        }
                        else if(inAnIfOrElse > 0 && tokenTable[index].name == "}"){
                            //cout << "We've hit the end of our IF or Else! Time to print the L[x]!" << endl;
                            quadCreation(tokenTable[index].name);
                            inAnIfOrElse--;
                        }
                        // If our token is an operator
                        else if(isOperatorOrSymbol(tokenTable[index]) == true){
                            //cout << "Our token is an operator!" << endl;

                            // There are no operators in the stack to compare to, so we add the current operator to the stack
                            if(hasOperator == false){

                                if(tokenTable[index].name == ";" || tokenTable[index].name == "," || tokenTable[index].name == "{"){
                                    index++;
                                    //cout << "All quads have been generated for this line!" << endl;
                                    itemsInStack = 0;
                                    tempIntegerCounter = 1;
                                    Stack.clear(); // Stack must be empty at the start of each line
                                }

                                else if(tokenTable[index].classification == "$THEN"){
                                    //cout << "All quads have been generated for this line (IF line)!" << endl;
                                    quadCreation(tokenTable[index].name);
                                    itemsInStack = 0;
                                    index++;
                                    Stack.clear(); // Stack must be empty at the start of each line
                                }

                                else{
                                    //cout << "The stack has no operators!" << endl;
                                    //cout << tokenTable[index].name << " was pushed in the stack" << endl;
                                    Stack.push_back(tokenTable[index].name);
                                    itemsInStack++;
                                    index++;
                                    operatorCount++;
                                    hasOperator = true;                                 
                                }
                            }

                            // There is an operator to compare to. Let's compare precedences!
                            else{
                                string newestOperator = "";
                                newestOperator = tokenTable[index].name;
                                operatorPrecedence(newestOperator);
                            }
                        }
                        else{
                            index++;
                        }
                    }
                }
            }
            index++;
        }
        quadsToAssembly();
        return Quads;
    }

    void quadsToAssembly(){
        
        ofstream asmFile;
		asmFile.open("Assembly.asm", ios::app);
        asmFile << "section .text" << endl;
        asmFile << "global _start" << endl;
        asmFile << "_start: nop" << endl;
        asmFile << "" << endl;
        // Converts quads to assembly and outputs them to .asm file
        int i = 0;
        while(i < Quads.size()){

            char op = Quads[i].oper[0];

            switch(op){

                case '=':

                    if(Quads[i].oper == "=="){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "cmp ax, [" << Quads[i].right << "]" << endl;
                    }

                    else{
                            asmFile << "\t" << "mov ax, [" << Quads[i].right << "]" << endl;
                            asmFile << "\t" << "mov [" << Quads[i].left << "], ax" << endl;
                    }
                    break;
                
                case '+':
                    // Our operands are NOT numeric literals
                    if(isdigit(Quads[i].left[0]) == 0 && isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "add ax, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                   
                    // Our left operand is NOT a numeric literal, but our right IS.
                    else if(isdigit(Quads[i].left[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "add ax, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                    
                    // Our left operand is NOT a numeric literal, but our left IS.
                    else if(isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "add ax, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                    
                    // Both our operands are numeric literals
                    else{
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "add ax, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                    break;

                case '-':
                    // Our operands are NOT numeric literals
                    if(isdigit(Quads[i].left[0]) == 0 && isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "sub ax, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;  
                    }
                   
                    // Our left operand is NOT a numeric literal, but our right IS.
                    else if(isdigit(Quads[i].left[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "sub ax, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                    
                    // Our left operand is NOT a numeric literal, but our left IS.
                    else if(isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "sub ax, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                    
                    // Both our operands are numeric literals
                    else{
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "sub ax, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], ax" << endl;
                    }
                    break;

                case '*':
                    // Our operands are NOT numeric literals
                    if(isdigit(Quads[i].left[0]) == 0 && isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mul bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;                        
                    }
                   
                    // Our left operand is NOT a numeric literal, but our right IS.
                    else if(isdigit(Quads[i].left[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mul bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;   
                    }
                    
                    // Our left operand is NOT a numeric literal, but our left IS.
                    else if(isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mul bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;   
                    }
                    
                    // Both our operands are numeric literals
                    else{
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "mul bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;   
                    }
                    break;

                case '/':
                    asmFile << "\t" << "mov dx, 0" << endl;
                    
                    // Our operands are NOT numeric literals
                    if(isdigit(Quads[i].left[0]) == 0 && isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "div bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;
                    }
                   
                    // Our left operand is NOT a numeric literal, but our right IS.
                    else if(isdigit(Quads[i].left[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "div bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;
                    }
                    
                    // Our left operand is NOT a numeric literal, but our left IS.
                    else if(isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "div bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;
                    }
                    
                    // Both our operands are numeric literals
                    else{
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl;
                        asmFile << "\t" << "mov bx, [Lit" << Quads[i].right << "]" << endl;
                        asmFile << "\t" << "div bx" << endl;
                        asmFile << "\t" << "mov [" << Quads[i].location << "], eax" << endl;
                    }     
                    break;

                case '>': // Covers cases for both '>' and '>='
                    // Our operands are NOT numeric literals
                    if(isdigit(Quads[i].left[0]) == 0 && isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl; 
                        asmFile << "\t" << "cmp ax, [" << Quads[i].right << "]" << endl; 
                    }
                    
                    // Our left operand is NOT a numeric literal, but our right IS.
                    else if(isdigit(Quads[i].left[0]) == 0){
                        asmFile << "\t" << "mov ax, [" << Quads[i].left << "]" << endl; 
                        asmFile << "\t" << "cmp ax, [Lit" << Quads[i].right << "]" << endl;
                    }
                    
                    // Our right operand is NOT a numeric literal, but our left IS.
                    else if(isdigit(Quads[i].right[0]) == 0){
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl; 
                        asmFile << "\t" << "cmp ax, [" << Quads[i].right << "]" << endl;
                    }
                    
                    // Both our operands are numeric literals
                    else{
                        asmFile << "\t" << "mov ax, [Lit" << Quads[i].left << "]" << endl; 
                        asmFile << "\t" << "cmp ax, [Lit" << Quads[i].right << "]" << endl;
                    }     
                    break;

                default:

                    if(Quads[i].left == "THEN"){
                        //cout << "J" << Quads[i].oper << " " << l << endl;
                        asmFile << "\t" << "J" << Quads[i].oper << " " << Quads[i].right << endl;
                    }

                    else if(Quads[i].left == "ELSE"){
                        asmFile << "\t" << Quads[i].right << ": NOP" << endl; 
                    }

                    else if(Quads[i].left == "GET"){
                        asmFile << "\tcall PrintString" << endl; 
                        asmFile << "\tcall GetAnInteger" << endl; 
                        asmFile << "\tmov ax, [ReadInt]" << endl; 
                        asmFile << "\tmov [" << Quads[i].right << "], ax" << endl;  
                    }

                    else if(Quads[i].left == "PUT"){ // Print all of the PUT lines
                        asmFile << "\tmov ax, [" << Quads[i].right << "]" << endl; 
                        asmFile << "\tcall ConvertIntegerToString" << endl; 
                        asmFile << "\tmov eax, 4" << endl; 
                        asmFile << "\tmov ebx, 1" << endl; 
                        asmFile << "\tmov ecx, Result" << endl; 
                        asmFile << "\tmov edx, ResultEnd" << endl; 
                        asmFile << "\tint 80h" << endl; 
                    }

                    else if(Quads[i].left[0] == 'J'){
                        asmFile << "\t" << "Jmp " << Quads[i].left[1] << Quads[i].left[2] << endl;
                    }            

                    else if(Quads[i].left[0] == 'L'){
                        if(ifElse == "ELSE"){
                            asmFile << "\t" << Quads[i].left << ": NOP" << endl;
                            ifElse = "";
                        }

                        else{
                            asmFile << "\t" << "Jmp " << Quads[i].left[1] << Quads[i].left[2] << endl;
                        }
                    }
                    break;                                                                
            }
            i++; 
        }

        asmFile << "" << endl;
        asmFile << "Jmp finish" << endl;
        asmFile << "" << endl;

        // PrintString function
        asmFile << "PrintString:" << endl;
        asmFile << "\tpush ax" << endl;
        asmFile << "\tpush dx" << endl;
        asmFile << "\tmov eax, 4" << endl;
        asmFile << "\tmov ebx, 1" << endl;
        asmFile << "\tmov ecx, userMsg" << endl;
        asmFile << "\tmov edx, lenUserMsg" << endl;
        asmFile << "\tint 80h" << endl;
        asmFile << "\tpop dx" << endl;
        asmFile << "\tpop ax" << endl;
        asmFile << "\tret" << endl;
        asmFile << "" << endl;


        // GetAnInteger Function            
        asmFile << "GetAnInteger:" << endl;
        asmFile << "\tmov eax, 3 ;Read" << endl;
        asmFile << "\tmov ebx, 2 ;Device" << endl;
        asmFile << "\tmov ecx, num ;Buffer Address" << endl;
        asmFile << "\tmov edx, 6 ;Max Characters" << endl;
        asmFile << "\tint 0x80" << endl;
        asmFile << "\tmov edx, eax" << endl;
        asmFile << "\tmov eax, 4" << endl;
        asmFile << "\tmov ebx, 1" << endl;
        asmFile << "\tmov ecx, num" << endl;
        asmFile << "\tint 80h" << endl;
        asmFile << "" << endl;

        // ConvertStringToInteger Function            
        asmFile << "ConvertStringToInteger:" << endl;
        asmFile << "\tmov ax, 0 ;Hold Integer" << endl;
        asmFile << "\tmov [ReadInt], ax" << endl;
        asmFile << "\tmov ecx, num ;Read" << endl;
        asmFile << "\tmov bx, 0 ;Read" << endl;
        asmFile << "\tmov bl, byte [ecx] ;Read" << endl;
        asmFile << "" << endl;

        // Next Function
        asmFile << "Next:" << endl; 
        asmFile << "\tsub bl, '0'" << endl; 
        asmFile << "\tmov ax, [ReadInt]" << endl;
        asmFile << "\tmov dx, 10" << endl;
        asmFile << "\tmul dx" << endl;
        asmFile << "\tadd ax, bx" << endl;
        asmFile << "\tmov [ReadInt], ax" << endl;
        asmFile << "\tmov bx, 0" << endl;
        asmFile << "\tadd ecx, 1" << endl;
        asmFile << "\tmov bl, byte[ecx]" << endl;
        asmFile << "\tcmp bl, 0xA" << endl;
        asmFile << "\tjne Next" << endl;
        asmFile << "\tret" << endl;
        asmFile << "" << endl;

        // ConvertIntegerToString Function            
        asmFile << "ConvertIntegerToString:" << endl;
        asmFile << "\tmov ebx, ResultValue + 4" << endl;
        asmFile << "" << endl;

        // ConvertLoop        
        asmFile << "ConvertLoop:" << endl;    
        asmFile << "\tsub dx, dx" << endl;
        asmFile << "\tmov cx, 10" << endl;
        asmFile << "\tdiv cx" << endl;
        asmFile << "\tadd dl, '0'" << endl;
        asmFile << "\tmov [ebx], dl" << endl;
        asmFile << "\tdec ebx" << endl;
        asmFile << "\tcmp ebx, ResultValue" << endl;
        asmFile << "\tjge ConvertLoop" << endl;
        asmFile << "\tret" << endl;
        asmFile << "" << endl;

        // Exit
        asmFile << "Terminate:" << endl;
        asmFile << "finish:" << endl;
        asmFile << "" << endl;
        asmFile << "\tmov eax, sys_exit" << endl;
        asmFile << "\txor ebx, ebx" << endl;
        asmFile << "\tint 80h" << endl;
        asmFile << "" << endl;

        asmFile.close();

    }
};