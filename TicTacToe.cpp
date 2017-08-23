#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

//use as matrix of the tic tac toe board, which will be used by all functions
string T[17] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};

//MIN or MAX (for minimax node)
enum MMValue
{
	MAX = 1,
	MIN = 2
};

//the minimax tree node which includes if it is min or max, the alpha and beta value
//the tic tac toe board at it's current state, the height of the tree at the node
struct miniMaxNode {
	miniMaxNode() {}
	miniMaxNode(string G[], MMValue P, int a, int b, int h): player(P), alpha(a), beta(b), tHeight(h) {
		for(int i = 0; i < 17; i++) {
			data[i] = G[i];
		}
	}
	MMValue player;
	string data[17];
	int alpha;
	int beta;
	int tHeight;
	int value;
};

//counts the number of rows, columns and diagonals where O or X (depending on what is inputed)
//are, and it sends a vector back with the number of rows with 3 x's as the first element
//of the vector, and then number of 2 x's and then 1 x's (or O's)
vector<int> countNumInRCD(string G[], string mark) {
	vector<int> results;
	bool marks[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int r1 = 0;
	int r2 = 0;
	int r3 = 0;
	int c1 = 0;
	int c2 = 0;
	int c3 = 0;
	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	int numRow = 0;
	int numCol = 0;
	int numDiag = 0;
	if(mark == "X" || mark == " X") {
		for(int i = 0; i < 17; i++) {
			if(G[i] == "X" || G[i] == " X") marks[i] = 1;
		}
	}
	else if(mark == "O" || mark == " O") {
		for(int i = 0; i < 17; i++) {
			if(G[i] == "O" || G[i] == " O") marks[i] = 1;
		}
	}

	//check rows
	numRow = marks[1]+marks[2]+marks[3]+marks[4];
	if(numRow == 1) r1++;
	else if(numRow == 2) r2++;
	else if(numRow == 3) r3++;
	numRow = 0;
	numRow = marks[5]+marks[6]+marks[7]+marks[8];
	if(numRow == 1) r1++;
	else if(numRow == 2) r2++;
	else if(numRow == 3) r3++;
	numRow = 0;
	numRow = marks[9]+marks[10]+marks[11]+marks[12];
	if(numRow == 1) r1++;
	else if(numRow == 2) r2++;
	else if(numRow == 3) r3++;
	numRow = 0;
	numRow = marks[13]+marks[14]+marks[15]+marks[16];
	if(numRow == 1) r1++;
	else if(numRow == 2) r2++;
	else if(numRow == 3) r3++;
	numRow = 0;

	//check columns
	numCol = marks[1]+marks[5]+marks[9]+marks[13];
	if(numCol == 1) c1++;
	else if(numCol == 2) c2++;
	else if(numCol == 3) c3++;
	numCol = 0;
	numCol = marks[2]+marks[6]+marks[10]+marks[14];
	if(numCol == 1) c1++;
	else if(numCol == 2) c2++;
	else if(numCol == 3) c3++;
	numCol = 0;
	numCol = marks[3]+marks[7]+marks[11]+marks[15];
	if(numCol == 1) c1++;
	else if(numCol == 2) c2++;
	else if(numCol == 3) c3++;
	numCol = 0;
	numCol = marks[4]+marks[8]+marks[12]+marks[16];
	if(numCol == 1) c1++;
	else if(numCol == 2) c2++;
	else if(numCol == 3) c3++;
	numCol = 0;	

	//check diagonals
	numDiag = marks[4]+marks[7]+marks[10]+marks[13];
	if(numDiag == 1) d1++;
	else if(numDiag == 2) d2++;
	else if(numDiag == 3) d3++;
	numDiag = 0;
	numDiag = marks[1]+marks[6]+marks[11]+marks[16];
	if(numDiag == 1) d1++;
	else if(numDiag == 2) d2++;
	else if(numDiag == 3) d3++;
	numDiag = 0;

	int numThree = r3+c3+d3;
	int numTwo = r2+c2+d2;
	int numOne = r1+c1+d1;
	results.push_back(numThree);
	results.push_back(numTwo);
	results.push_back(numOne);
	return results;
}

//returns 1 if player 1 wins, returns 2 if player 2 wins, returns 0 if draw, returns 3 is still playing
int win(miniMaxNode G) {
	//check if x won
	if(G.data[1] == "X" && G.data[2] == "X" && G.data[3] == "X" && G.data[4] == "X") return 1;
	else if(G.data[5] == "X" && G.data[6] == "X" && G.data[7] == "X" && G.data[8] == "X") return 1;
	else if(G.data[9] == "X" && G.data[10] == " X" && G.data[11] == " X" && G.data[12] == " X") return 1;
	else if(G.data[13] == " X" && G.data[14] == " X" && G.data[15] == " X" && G.data[16] == " X") return 1;
	else if(G.data[1] == "X" && G.data[5] == "X" && G.data[9] == "X" && G.data[13] == " X") return 1;
	else if(G.data[2] == "X" && G.data[6] == "X" && G.data[10] == " X" && G.data[14] == " X") return 1;
	else if(G.data[3] == "X" && G.data[7] == "X" && G.data[11] == " X" && G.data[15] == " X") return 1;
	else if(G.data[4] == "X" && G.data[8] == "X" && G.data[12] == " X" && G.data[16] == " X") return 1;
	else if(G.data[1] == "X" && G.data[6] == "X" && G.data[11] == " X" && G.data[16] == " X") return 1;
	else if(G.data[4] == "X" && G.data[7] == "X" && G.data[10] == " X" && G.data[13] == " X") return 1;

	//check if o won
	if(G.data[1] == "O" && G.data[2] == "O" && G.data[3] == "O" && G.data[4] == "O") return 2;
	else if(G.data[5] == "O" && G.data[6] == "O" && G.data[7] == "O" && G.data[8] == "O") return 2;
	else if(G.data[9] == "O" && G.data[10] == " O" && G.data[11] == " O" && G.data[12] == " O") return 2;
	else if(G.data[13] == " O" && G.data[14] == " O" && G.data[15] == " O" && G.data[16] == " O") return 2;
	else if(G.data[1] == "O" && G.data[5] == "O" && G.data[9] == "O" && G.data[13] == " O") return 2;
	else if(G.data[2] == "O" && G.data[6] == "O" && G.data[10] == " O" && G.data[14] == " O") return 2;
	else if(G.data[3] == "O" && G.data[7] == "O" && G.data[11] == " O" && G.data[15] == " O") return 2;
	else if(G.data[4] == "O" && G.data[8] == "O" && G.data[12] == " O" && G.data[16] == " O") return 2;
	else if(G.data[1] == "O" && G.data[6] == "O" && G.data[11] == " O" && G.data[16] == " O") return 2;
	else if(G.data[4] == "O" && G.data[7] == "O" && G.data[10] == " O" && G.data[13] == " O") return 2;

	//check if draw
	bool cont = 1;
	for(int i = 1; i < 17; i++) {
		if(G.data[i]!= "X" && G.data[i]!= " X" && G.data[i]!= "O" && G.data[i]!= " O") {
			cont = 0;
			break;
		}
	}
	if(cont == 1) return 0;
	return 3;
}

//generates the next tic tac toe nodes from the state sent in, returns a vector of pairs
//the pair contains the tic tac toe board with a child state as the first value, and the
//second value of the pair is the index which the child state was changed, as in
//where the X or O was put
vector<pair<miniMaxNode,int>> generateChildren(miniMaxNode G) {
	vector<pair<miniMaxNode,int>> children;
	if(G.player == MAX) {
		for(int i = 1; i < 17; i++) {
			if(G.data[i]!= "X" && G.data[i]!= " X" && G.data[i]!= "O" && G.data[i]!= " O") {
				string temp = G.data[i];
				if(i < 10) G.data[i] = "X";
				else G.data[i] = " X";
				miniMaxNode N(G.data,MIN,G.alpha,G.beta,G.tHeight+1);
				pair<miniMaxNode,int> P = {N,i};
				children.push_back(P);
				G.data[i] = temp;
			}
		}
	}
	else {
		for(int i = 1; i < 17; i++) {
			if(G.data[i]!= "X" && G.data[i]!= " X" && G.data[i]!= "O" && G.data[i]!= " O") {
				string temp = G.data[i];
				if(i < 10) G.data[i] = "O";
				else G.data[i] = " O";
				miniMaxNode N(G.data,MAX,G.alpha,G.beta,G.tHeight+1);
				pair<miniMaxNode,int> P = {N,i};
				children.push_back(P);
				G.data[i] = temp;
			}
		}
	}
	return children;
}

//deletes all remaining children of tic tac toe node, pruning in other terms
void cutNode(vector<pair<miniMaxNode,int>>& G, int i) {
	if(G.size() > i) {
		for(int j = i+1; j < G.size(); j++) {
			G.pop_back();
		}
	}
}

//the alpha beta algorithm
pair<int,int> alphaBetaSearch(miniMaxNode G, const int height, int i) {
	int winner = win(G);
	//if the MAX or X wins, returns 1000 and the index (place on board) to cause win
	if(winner == 1) {
		G.value = 1000;
		return {G.value,i};
	}

	//if the MIN or O wins, returns -1000 and the index (place on board) to cause win
	else if(winner == 2) {
		G.value = -1000;
		return {G.value,i};
	}

	//if there is a draw
	else if(winner == 0) {
		G.value = 0;
		return {G.value,i};
	}

	//if the height of the tree reaches the cut-off, then the evaluation function is used
	//to determine the the value
	if(G.tHeight == height) {
		int EvalS;
		vector<int> Xn = countNumInRCD(G.data,"X");
		vector<int> On = countNumInRCD(G.data,"O");
		EvalS = 6*Xn[0] + 3*Xn[1] + Xn[2] - (6*On[0] + 3*On[1] + On[2]);
		if(EvalS > 0) return {1000, i};
		else if(EvalS < 0) return {-1000, i};
		else return {0,i};
	}

	//if max node, check the child nodes and when returns, checks the max of the alpha of itself
	//and the alpha of its child, if the child wins, then that is the next value (max)
	if(G.player == MAX) {
		vector<pair<miniMaxNode,int>> children = generateChildren(G);
		int index;
		for(int j = 0; j < children.size(); j++) {
			pair<int, int> tempVal = alphaBetaSearch(children[j].first,height,children[j].second);
			if(G.alpha >= tempVal.first) {
				G.alpha = G.alpha;
				index = i;
			}
			else {
				G.alpha = tempVal.first;
				index = tempVal.second;
			}
			if(G.beta <= G.alpha) cutNode(children,j);
		}
		return {G.alpha, index};
	}

	//if min node, check the child nodes and when returns, checks the min of the beta of itself
	//and the beta of its child, if the child wins, then that is the next value (min)
	else {
		vector<pair<miniMaxNode,int>> children = generateChildren(G);
		int index;
		for(int j = 0; j < children.size(); j++) {
			pair<int,int> tempVal = alphaBetaSearch(children[j].first,height,children[j].second);
			if(G.beta <= tempVal.first) {
				G.beta = G.beta;
				index = i;
			}
			else {
				G.beta = tempVal.first;
				index = tempVal.second;
			}
			if(G.beta <= G.alpha) cutNode(children,j);
		}
		return {G.beta, index};	
	}
}

//to display the current status of game to user
void dispBoard() {
	cout << "     |     |     |     " << endl;
	cout << "  " << T[1] << "  |  " << T[2] << "  |  " << T[3] << "  |  " << T[4] << endl;
	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;
	cout << "  " << T[5] << "  |  " << T[6] << "  |  " << T[7] << "  |  " << T[8] << endl;
	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;
	cout << "  " << T[9] << "  | " << T[10] << "  | " << T[11] << "  | " << T[12] << endl;
	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;
	cout << " " << T[13] << "  | " << T[14] << "  | " << T[15] << "  | " << T[16] << endl;
	cout << "     |     |     |     " << endl;
}

//check if the computer (being X) wins
bool playerTwoWin() {
	if(T[1] == "X" && T[2] == "X" && T[3] == "X" && T[4] == "X") return 1;
	else if(T[5] == "X" && T[6] == "X" && T[7] == "X" && T[8] == "X") return 1;
	else if(T[9] == "X" && T[10] == " X" && T[11] == " X" && T[12] == " X") return 1;
	else if(T[13] == " X" && T[14] == " X" && T[15] == " X" && T[16] == " X") return 1;
	else if(T[1] == "X" && T[5] == "X" && T[9] == "X" && T[13] == " X") return 1;
	else if(T[2] == "X" && T[6] == "X" && T[10] == " X" && T[14] == " X") return 1;
	else if(T[3] == "X" && T[7] == "X" && T[11] == " X" && T[15] == " X") return 1;
	else if(T[4] == "X" && T[8] == "X" && T[12] == " X" && T[16] == " X") return 1;
	else if(T[1] == "X" && T[6] == "X" && T[11] == " X" && T[16] == " X") return 1;
	else if(T[4] == "X" && T[7] == "X" && T[10] == " X" && T[13] == " X") return 1;
	else return 0;
}

//check if the user (being O) wins
bool playerOneWin() {
	if(T[1] == "O" && T[2] == "O" && T[3] == "O" && T[4] == "O") return 1;
	else if(T[5] == "O" && T[6] == "O" && T[7] == "O" && T[8] == "O") return 1;
	else if(T[9] == "O" && T[10] == " O" && T[11] == " O" && T[12] == " O") return 1;
	else if(T[13] == " O" && T[14] == " O" && T[15] == " O" && T[16] == " O") return 1;
	else if(T[1] == "O" && T[5] == "O" && T[9] == "O" && T[13] == " O") return 1;
	else if(T[2] == "O" && T[6] == "O" && T[10] == " O" && T[14] == " O") return 1;
	else if(T[3] == "O" && T[7] == "O" && T[11] == " O" && T[15] == " O") return 1;
	else if(T[4] == "O" && T[8] == "O" && T[12] == " O" && T[16] == " O") return 1;
	else if(T[1] == "O" && T[6] == "O" && T[11] == " O" && T[16] == " O") return 1;
	else if(T[4] == "O" && T[7] == "O" && T[10] == " O" && T[13] == " O") return 1;
	else return 0;
}

//check if the game is a draw
bool checkDraw() {
	bool cont = 1;
	for(int i = 1; i < 17; i++) {
		if(T[i]!= "X" && T[i]!= " X" && T[i]!= "O" && T[i]!= " O") {
			cont = 0;
			break;
		}
	}
	if(cont == 1) return true;
	else return false;
}

//check if the current spot is empty 
bool checkAvailable(int fm) {
	if(T[fm]!= "X" && T[fm]!= " X" && T[fm]!= "O" && T[fm]!= " O") return true;
	else return false;
}

//controls the play of the game
void play() {
	int difficulty;
	int height;
	int ran = 0;
	bool userTurn = false;
	bool compTurn = false;
	bool someOneWin = false;
	int moveIdx = 0;
	srand(time(NULL));
	cout << endl;
	cout << "Tic Tac Toe" << endl;
	cout << endl;
	cout << "You are player 1 (O), the computer is player 2 (X)." << endl;
	cout << endl;
	cout << "What level of difficulty would you like to play: (1)easy, (2)medium, or (3)hard?" << endl;
	cout << endl;
	cin >> difficulty;
	while(difficulty != 1 && difficulty !=2 && difficulty != 3) {
		cout << "Please choose a valid choice: (1)easy, (2)medium, or (3)hard!" << endl;
	}
	if(difficulty == 1) height = 5;
	else if(difficulty == 2) height = 7;
	else if(difficulty == 3) height = 9;
	cout << endl;
	cout << "To see who will go first, select a random number between 1 and 100: " << endl;
	cout << endl;
	cin >> ran;
	if(rand()%100 + 1 > ran) {
		cout << "It is your turn first." << endl;
		userTurn = true;
		compTurn = false;
	}
	else {
		cout << "It is the computer's turn first." << endl;
		userTurn = false;
		compTurn = true;
	}
	int countT = 0;
	bool p1Win = false;
	bool p2Win = false;
	bool aDraw = false;
	if (userTurn == true) dispBoard();
	while(!someOneWin) {
		countT++;
		if(userTurn == true) {
			cout << "\n" << countT << ": Your turn" << endl;
			cout << "\n\nEnter the number you want to put your mark in: " << endl;
			cin >> moveIdx;
			while( moveIdx > 16) {
				cout << "Incorrect move, choose a number listed in the tic tac toe board!" << endl;
				cin >> moveIdx;
			}
			if(moveIdx > 9) T[moveIdx] = " O";
			else T[moveIdx] = "O";
			dispBoard();
			p1Win = playerOneWin();
			compTurn = true;
			userTurn = false;
		}
		else if(compTurn == true) {
			cout << "\n" << countT << ": Computer's turn \n" << endl;
			miniMaxNode CompMove(T,MAX,-1000,1000,0);
			int firstMove = rand()%16 + 1;
			if(countT == 1 || countT == 2) {
				if(firstMove > 9) T[firstMove] = " X";
				else T[firstMove] = "X";
				dispBoard();
			}
			else {
				while(!checkAvailable(firstMove)) {
					firstMove = rand()%16 + 1;
				}
				pair<int,int> computerMove = alphaBetaSearch(CompMove,height,firstMove);
				moveIdx = computerMove.second;
				if(moveIdx > 9) T[moveIdx] = " X";
				else T[moveIdx] = "X";
				dispBoard();
			}
			p2Win = playerTwoWin();
			compTurn = false;
			userTurn = true;
		}
		if(p1Win == true) {
			someOneWin = true;
			cout << "\n\nYou win!!!!" << endl;
		}
		else if(p2Win == true) {
			someOneWin = true;
			cout << "\n\nThe computer wins!" << endl;
		}
		else {
			aDraw = checkDraw();
			if(aDraw == true) {
				someOneWin = true;
				cout << "\n\nThere is a draw!" << endl;
			}
		}
	}
}

int main() {
	play();
}