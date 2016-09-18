/* simple tic-tac-toe game */

#include <stdio.h>
#include <ncurses.h>	// for capturing arrow keys and for positioning

int main() {
	
	char p1 = 'X';
	char p2 = 'O';
	int player1 = 0;
	int winner = 0;
	int game = 1;
	int combo[3][2];
	
	// init ncurses
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	mvprintw(0, 0, "===========");
	mvprintw(1, 0, "Tic Tac Toe");
	mvprintw(2, 0, "===========");
	
	char board[3][3] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
 	};

	while(game) {
		
		player1 = !player1;
		
		char newChar = player1 ? p1 : p2;
		int xCoor = 0;
		int yCoor = 0;

		mvprintw(6, 0, "Current Player: %c", newChar);

		int getInput = 1;
		while(getInput) {	
			
			mvprintw(8, 0, " %c | %c | %c %c\n-----------",
				board[0][0], board[0][1], board[0][2], xCoor == 0 ? '<' : ' ');
			mvprintw(10, 0, " %c | %c | %c %c\n-----------",
				board[1][0], board[1][1], board[1][2], xCoor == 1 ? '<' : ' ');
			mvprintw(12, 0, " %c | %c | %c %c\n",
				board[2][0], board[2][1], board[2][2], xCoor == 2 ? '<' : ' ');
			mvprintw(13, 0, "%s", 
				yCoor == 0 ? " ^         " :
				(yCoor == 1 ? "     ^     " : "         ^ ")
			);
	
			mvprintw(4, 0, "Use arrow keys, then press enter: ");

			int input = getch();
			switch(input) {
				case KEY_UP:
					if(xCoor != 0)
						xCoor--;
					break;
				case KEY_DOWN:
					if(xCoor != 2)
						xCoor++;
					break;
				case KEY_LEFT:
					if(yCoor != 0)
						yCoor--;
					break;
				case KEY_RIGHT:
					if(yCoor != 2)
						yCoor++;
					break;
				case KEY_ENTER:
				case 10:	// ascii newline = 10
				case 13:	// ascii enter
					if(board[xCoor][yCoor] == ' ') {
						getInput = 0;
						board[xCoor][yCoor] = newChar;
					} else
						mvprintw(7, 0, "The spot (%d, %d) is taken.", xCoor, yCoor);
					break;
				default:
					mvprintw(7, 0, "Invalid input. Only UP, DOWN, LEFT, RIGHT, and ENTER are allowed. %d", input);

			}	
		
		}		
	
		int row, column;
		for(row = 0; row < 3; row++)
			if(board[row][0] != ' ' && board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
				winner = board[row][0] == p1 ? 1 : 2;
				combo[0][0] = row;
				combo[0][1] = 0;
				combo[1][0] = row;
				combo[1][1] = 1;
				combo[2][0] = row;
				combo[2][1] = 2;
				game = 0;
				break;
			}
		
		for(column = 0; column < 3; column++)
			if(board[0][column] != ' ' && board[0][column] == board[1][column] && board[1][column] == board[2][column]) {
				winner = board[0][column] == p1 ? 1 : 2;
				combo[0][0] = 0;
				combo[0][1] = column;
				combo[1][0] = 1;
				combo[1][1] = column;
				combo[2][0] = 2;
				combo[2][1] = column;
				game = 0;
				break;
			}
		
		int diag1;
		if(
			board[1][1] != ' ' &&
			((diag1 = board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
			(board[0][2] == board[1][1] && board[1][1] == board[2][0]))
		) {
			winner = board[1][1] == p1 ? 1 : 2;
			combo[0][0] = 0;
			combo[0][1] = diag1 ? 0 : 2;
			combo[1][0] = 1;
			combo[1][1] = 1;
			combo[2][0] = 2;
			combo[2][1] = diag1 ? 2 : 0;
			game = 0;
		}
		
		int i, j;
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				if(board[i][j] == ' ')
					i = 3;
				else if(i == 2 && j == 2)
					game = 0;
		
		if(!game) {
			int k;
			if(winner != 0)
				for(i = 0; i < 3; i++)
					for(j = 0; j < 3; j++)
						for(k = 0; k < 3; k++)
							if(i == combo[k][0] && j == combo[k][1])
								board[i][j] = '$';
			mvprintw(8, 0, " %c | %c | %c\n-----------",
				board[0][0], board[0][1], board[0][2]);
			mvprintw(10, 0, " %c | %c | %c\n-----------",
				board[1][0], board[1][1], board[1][2]);
			mvprintw(12, 0, " %c | %c | %c",
				board[2][0], board[2][1], board[2][2]);
		}

	}
	
	winner != 0 ?
		mvprintw(15, 0, "The winner is player %c!", winner == 1 ? p1 : p2) :
		mvprintw(15, 0, "No more spaces left. Tie!");
	
	mvprintw(17, 0, "Press any key to exit...");
	
	refresh();	// print to screen

	getch();

	endwin();	// end ncurses

	return 0;
	
}
