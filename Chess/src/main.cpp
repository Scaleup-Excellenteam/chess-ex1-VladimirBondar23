// Chess 
#include "Chess.h"
#include "Board.h"
int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	Board b = Board();
	char actionSide = 'w';
	//string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();
	while (res != "exit")
	{
	//	/* 
	//	codeResponse value : 
	//	Illegal movements : 
	//	11 - there is not piece at the source  
	//	12 - the piece in the source is piece of your opponent
	//	13 - there one of your pieces at the destination 
	//	21 - illegal movement of that piece 
	//	31 - this movement will cause you checkmate

	//	legal movements : 
	//	41 - the last movement was legal and cause check 
	//	42 - the last movement was legal, next turn 
	//	*/

	//	/**/ 
		{ // put your code here instead that code
			char currentSide = actionSide;
			char oppositeSide = actionSide == 'w' ? 'b' : 'w';

			char start_let = res[0];
			char end_let = res[2];
			int start_num = int(res[1]) - '0';
			int end_num = int(res[3]) - '0';
			Cell start = b.getCell(start_let, start_num);
			Cell end = b.getCell(end_let, end_num);
			codeResponse = b.isMoveValid(start, end, actionSide);

			if (codeResponse == 42) {
				if (!(b.updateBoard(start_num, start_let, end_num, end_let, actionSide)))
					codeResponse = 31;
				else if (b.isKingInCheck(oppositeSide)) {
					codeResponse = 41;
					actionSide = oppositeSide;
				}
				else
					actionSide = oppositeSide;
			}
		}
	//	/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput();
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}