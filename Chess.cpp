#include<iostream>
#include<string>

using namespace std;

void initboard(string board[8][8]);
void printboard(string board[8][8],int score[2]);
int endgame(string board[8][8]);
void point(int y1,int x1,int y2,int x2,string board[8][8],int score[2],string save[1]);
int moveQ(int y1,int x1,int y2,int x2,string board[8][8]);
int moveB(int y1,int x1,int y2,int x2,string board[8][8]);
int moveC(int y1,int x1,int y2,int x2,string board[8][8]);
int moveK(int y1,int x1,int y2,int x2,string board[8][8]);
int moveH(int y1,int x1,int y2,int x2,string board[8][8]);
int moveS(int y1,int x1,int y2,int x2,string board[8][8]);
int move(int y1,int x1,int y2,int x2,string board[8][8]);
void mark(int y1,int x1,string board[8][8]);
void clean(int y1,int x1,string board[8][8]);

int main() {
	string board[8][8];
	initboard(board);
	int score[2];
	string save[1];
	score[0]=0;
	string end;
	score[1]=0;
	printboard(board,score);
	int turn=0;
	while(!endgame(board)) {
		int y1,x1,y2,x2;
		while(1) {
			if(turn%2==0) {
				cout << "White its your turn" << endl;
			} else {
				cout << "Black its your turn" << endl;
			}
			cout << "Which piece you want to move: ";
			cin >> x1 >> y1;
			if(x1>8 || y1>8|| x1 <1 || y1 <1) {
				cout << "OUT OF BOARD!";
				continue;
			}
			x1 = x1-1;
			y1 = y1-1;
			if(turn%2==0 && board[y1][x1][1]== 'B') {
				cout << "IT IS WHITE TURN!" << endl;
				continue;
			}
			if(turn%2==1 && board[y1][x1][1]== 'W') {
				cout << "IT IS BLACK TURN!" << endl;
				continue;
			}
			if(board[y1][x1][1]== ' ') {
				cout << "YOU CAN'T MOVE A BLANK SPACE" << endl;
				continue;
			}
			mark(y1,x1,board);
			printboard(board,score);
			cout << "Where to go(0 0 for choosing new peice): " ;
			while(1) {
				cin >> x2 >> y2;
				x2 = x2-1;
				y2 = y2-1;
				if(x2>7 || y2>7|| x2 <-1 || y2 <-1) {
					cout << endl << "OUT OF BOARD!, choose Where to go again(0 0 for choosing new peice): ";
					continue;
				} else if(x2==-1 && y2 ==-1) {
					clean(y1,x1,board);
					printboard(board,score);
					break;
				} else if(move(y1,x1,y2,x2,board)==0) {
					cout << "YOUR MOVE NOT VALID!" << endl;
					continue;
				} else if(move(y1,x1,y2,x2,board)==1)
					break;
			}
			if(x2==-1 && y2 ==-1) {
				clean(y1,x1,board);
				printboard(board,score);
				continue;
			}

			clean(y1,x1,board);
			save[0]=board[y2][x2];
			break;

		}
		if((turn%2==0 && board[y1][x1][1]=='W')||(turn%2==1 && board[y1][x1][1]=='B')) {
			int valid = move(y1,x1,y2,x2,board);
			if(!valid) {
				cout << "MOVE IS NOT VALID!" << endl;
			} else {
				turn++;
				board[y2][x2] = board[y1][x1];
				board[y1][x1] = "  ";
				point(y1,x1,y2,x2,board,score,save);
				clean(y1,x1,board);
				printboard(board,score);
			}
		} else
			cout << "IT IS NOT YOUR TURN!" << endl;


	}
	if(score[0]>score[1]) {
		cout << "White wins!" << endl;
	} else if(score[1]>score[0]) {
		cout << "Black wins!" << endl;
	} else
		cout << "Tie!";
	cout << endl << "GAME OVER!";
	while(1) {
		cout << "Enter exit to quit game";
		cin >> end;
		if(end == "exit") {
			return 0;
		} else
			cout << "I said enter exit";
	}

}

void initboard(string board[8][8]) {
	for(int i =0 ; i<8; i++) {
		for(int j=0; j<8; j++) {
			board[i][j]="  ";
		}
	}

	board[0][0]="CW",board[0][7]="CW";
	board[0][1]="HW",board[0][6]="HW";
	board[0][2]="BW",board[0][5]="BW";
	board[0][3]="QW",board[0][4]="KW";
	for(int i=0; i<8; i++) {
		board[1][i] = "SW";
	}
	board[7][0]="CB",board[7][7]="CB";
	board[7][1]="HB",board[7][6]="HB";
	board[7][2]="BB",board[7][5]="BB";
	board[7][3]="QB",board[7][4]="KB";
	for(int i=0; i<8; i++) {
		board[6][i] = "SB";
	}
}
void printboard(string board[8][8],int score[2]) {
	system("cls");
	cout << "     1         2         3         4         5         6         7         8" << endl;
	for(int i =0 ; i<8; i++) {
		cout << "---------------------------------------------------------------------------------" << endl ;
		cout << "|         |         |         |         |         |         |         |         |" << endl;
		for(int j=0; j<8; j++) {
			cout <<  "|   " << board[i][j] << "    " ;
		}
		cout << "|  " << i+1 << endl;
		cout << "|         |         |         |         |         |         |         |         |" << endl;
	}
	cout << "---------------------------------------------------------------------------------" << endl ;
	cout << endl;
	cout << endl << "White score: " << score[0] << endl << "Black score: " << score[1] << endl;

}
int endgame(string board[8][8]) {
	for(int i=0; i<8; i++) {
		if(board[0][i]=="SB" || board[7][i]=="SW" ) {
			return 1;
		}
	}
	return 0;
}
int moveS(int y1,int x1,int y2,int x2,string board[8][8]) {
	if(board[y1][x1][1] == 'W') {
		if(((board[y2][x2]=="  " || board[y2][x2]=="()") && y1+1 == y2 && x1==x2) || (y1==01 && y2==03 && x1==x2)) {
			return 1;
		}
		if(board[y2][x2][1]=='B' && y1+1 == y2 && (x1+1==x2 || x1-1==x2)) {
			return 1;
		}
	}
	if(board[y1][x1][1] == 'B') {
		if(((board[y2][x2]=="  " && y1-1 == y2 && x1==x2 || board[y2][x2]=="()")) || (y1==06 && y2==04 && x1==x2)) {
			return 1;
		}
		if(board[y2][x2][1]== 'W' && y1-1 == y2 && (x1+1==x2 || x1-1==x2)) {
			return 1;
		}
	}
	return 0;
}
int moveH(int y1,int x1,int y2,int x2,string board[8][8]) {
	if((y2==y1+2 && x2==x1+1) || (y2==y1+2 && x2==x1-1) ||
	        (y2==y1-2 && x2==x1+1) || (y2==y1-2 && x2==x1-1) || (y2==y1+1 && x2==x1+2) ||
	        (y2==y1+1 && x2==x1-2) ||(y2==y1-1 && x2==x1+2) || (y2==y1-1 && x2==x1-2)) {
		if(board[y1][x1][1]!=board[y2][x2][1])
			return 1;
	} else
		return 0;
}

int moveK(int y1,int x1,int y2,int x2,string board[8][8]) {
	if((y2==y1+1 && x2==x1) || (y2==y1+1 && x2==x1+1) ||
	        (y2==y1-1 && x2==x1) || (y2==y1-1 && x2==x1-1) ||
	        (y2==y1 && x2==x1+1) || (y2==y1 && x2==x1-1) ||
	        (y2==y1+1 && x2==x1-1) || (y2==y1-1 && x2==x1+1)) {
		return 1;
	} else
		return 0;
}

int moveC(int y1,int x1,int y2,int x2,string board[8][8]) {
	if(x1!=x2 && y1!=y2) {
		return 0;
	}
	if((y1<y2 && x1==x2)) {
		for(int i=y1+1; i<y2; i++) {
			if(board[i][x2]!="  " && board[i][x2]!="()" ) {
				return 0;
			}
		}
	} else if((y1>y2 && x1==x2)) {
		for(int i=y2+1; i<y1; i++) {
			if(board[i][x2]!="  " && board[i][x2]!="()") {
				return 0;
			}
		}
	} else if((y1==y2 && x1<x2)) {
		for(int i=x1+1; i<x2; i++) {
			if(board[y2][i]!="  " && board[y2][i]!="()") {
				return 0;
			}
		}
	} else if((y1==y2 && x1>x2)) {
		for(int i=x2+1; i<x1; i++) {
			if(board[y2][i]!="  " && board[y2][i]!="()") {
				return 0;
			}
		}
	} else
		return 1;
}
void point(int y1,int x1,int y2,int x2,string board[8][8],int score[2],string save[1]) {
//	cout << endl << "board[y2][x2][1]: " << board[y2][x2][1] << "save[0][0]== 'S' && save[0][1]=='B'" << save[0][0] <<  save[0][1] << endl;
	if(board[y2][x2][1]=='W') {
		if(save[0][0]== 'S' && save[0][1]=='B') {
			score[0]= score[0] + 1;
		}
		if(save[0][0]== 'H' && save[0][1]=='B') {
			score[0]= score[0] + 3;
		}
		if(save[0][0]== 'B' && save[0][1]=='B') {
			score[0]= score[0] + 3;
		}
		if(save[0][0]== 'Q' && save[0][1]=='B') {
			score[0]= score[0] + 9;
		}
		if(save[0][0]== 'K' && save[0][1]=='B') {
			score[0]= score[0] + 4;
		}
		if(save[0][0]== 'C' && save[0][1]=='B') {
			score[0]= score[0] + 5;
		}
	}
	if(board[y2][x2][1]=='B') {
		if(save[0][0]== 'S' && save[0][1]=='W') {
			score[1]= score[1] + 1;
		}
		if(save[0][0]== 'B' && save[0][1]=='W') {
			score[1]= score[1] + 3;
		}
		if(save[0][0]== 'H' && save[0][1]=='W') {
			score[1]= score[1] + 3;
		}
		if(save[0][0]== 'Q' && save[0][1]=='W') {
			score[1]= score[1] + 9;
		}
		if(save[0][0]== 'K' && save[0][1]=='W') {
			score[1]= score[1] + 4;
		}
		if(save[0][0]== 'C' && save[0][1]=='W') {
			score[1]= score[1] + 5;
		}
	}
}
int moveB(int y1,int x1,int y2,int x2,string board[8][8]) {
	int B=y2-y1;
	int N=x2-x1;
	int W=x1-x2;
	if(B!=N && B!= W) {
		return 0;
	}

	// cout << "x1: " << x1 << " x2: " << x2 << " y1: " << y1 << " y2: " << y2 << " B: " << B << " N: " << N << " W:" << W << endl;
	if(B>0) {
		if((y1+B==y2 && x1+B==x2)) {
			for(int i=1; i<y2-y1; i++) {
				if(board[y1+i][x1+i]!="  " && board[y1+i][x1+i]!="()") {
					return 0;
				}
			}
		} else if((y1+B==y2 && x1-B==x2)) {
			for(int i=1; i<y2-y1; i++) {
				if(board[y1+i][x1-i]!="  " && board[y1+i][x1-i]!="()") {
					return 0;
				}
			}
		}
	} else if((y1-N==y2 && x1+N==x2)) {
		for(int i=1; i<N; i++) {
			if(board[y1-i][x1+i]!="  " && board[y1-i][x1+i]!="()") {
				return 0;
			}
		}
	} else if((y1-W==y2 && x1-W==x2)) {
		for(int i=1; i<W; i++) {
			if(board[y1-i][x1-i]!="  " && board[y1-i][x1-i]!="()") {
				return 0;
			}
		}
	} else
		return 1;
}
int moveQ(int y1,int x1,int y2,int x2,string board[8][8]) {
	if(moveC(y1,x1,y2,x2,board) || moveB(y1,x1,y2,x2,board))
		return 1;
	else
		return 0;
}

int move(int y1,int x1,int y2,int x2,string board[8][8]) {
	if(x1>7 || y1>7 || x2>7 || y2>7 || x1<0 || x2 <0 || y1<0 || y2<0 || (x1==x2 && y1==y2) || board[y1][x1][1]==board[y2][x2][1]) {
		return 0;
	}
	if(board[y1][x1][0] == 'S') {
		if(moveS(y1,x1,y2,x2,board)) {
			return 1;
		} else
			return 0;
	} else if(board[y1][x1][0] == 'H') {
		if(moveH(y1,x1,y2,x2,board)) {
			return 1;
		} else
			return 0;
	} else if(board[y1][x1][0] == 'K') {
		if(moveK(y1,x1,y2,x2,board)) {
			return 1;
		} else
			return 0;
	} else if(board[y1][x1][0] == 'C') {
		if(moveC(y1,x1,y2,x2,board)) {
			return 1;
		} else
			return 0;
	} else if(board[y1][x1][0] == 'B') {
		if(moveB(y1,x1,y2,x2,board)) {
			return 1;
		} else
			return 0;
	} else if(board[y1][x1][0] == 'Q') {
		if(moveQ(y1,x1,y2,x2,board)) {
			return 1;
		} else
			return 0;
	}
}
void mark(int y1,int x1,string board[8][8]) {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			if((move(y1,x1,i,j,board)==1) && board[i][j]=="  ") {
				//cout << i << "," << j << " was valid" << endl;
				board[i][j]= "()";
			}
		}
	}
}
void clean(int y1,int x1,string board[8][8]) {
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			if(board[i][j]=="()") {
				board[i][j]= "  ";
			}
		}
	}
}
