

class TableDrivenDFSA{
private:
	int stateTable[19][7]; //rows => states, cols => responce to question.

public:
    // Constructor
	TableDrivenDFSA();

    // Changes between states
	void stateChanger();

    // Finds the column to change to the correct state
	int findColumn(char);
};