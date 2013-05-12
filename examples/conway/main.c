#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXROWS 20
#define MAXCOLUMNS 20

enum CELLSTATUS
{
	DEAD,
	ALIVE
};

struct cell
{
	int x;
	int y;
	enum CELLSTATUS state;
	enum CELLSTATUS neighborCell;
};

void drawBoard( struct cell[MAXROWS][MAXCOLUMNS] );
void determineNextMove( struct cell[MAXROWS][MAXCOLUMNS] );
enum CELLSTATUS getNextMove( struct cell activeIndex, struct cell board[MAXROWS][MAXCOLUMNS], int column, int row );
int calculateNeigbors( struct cell activeIndex, struct cell board[MAXROWS][MAXCOLUMNS], int column, int row );

int main(){

	struct cell board[MAXROWS][MAXCOLUMNS];
	int i = 0;
	int j = 0;
	int moves = 0;
	int randNumb;
	srand((long)time(NULL));

	for( i = 0; i < MAXROWS; i++ ){
		for( j = 0; j < MAXCOLUMNS; j++ ){
			struct cell temp;
			temp.x = i;
			temp.y = j;
			randNumb = rand() % 10;
			if( randNumb < 8){
				temp.state = DEAD;
			}else{
				temp.state = ALIVE;
			}
			board[i][j] = temp;
		}
	}


	while( moves < 100 ){
		
		drawBoard( board );
		//http://stackoverflow.com/questions/338273/why-does-sleep-execute-before-my-printf-the-opposite-order-of-my-code
		fflush(stdout);
		sleep(1);
		system("clear");
		printf("[%i]\n", moves);
		determineNextMove( board );
		moves++;
	}
	
	

}

void drawBoard( struct cell board[MAXROWS][MAXCOLUMNS] ){
	int i = 0;
	int j = 0;
	for( i = 0; i < MAXROWS; i++ ){ // prints the column
		for( j = 0; j < MAXCOLUMNS; j++ ){ // prints the row
			struct cell temp = board[i][j];
			if( temp.state == DEAD ){
				printf( " " );
			}else{
				printf("*" );
			}
			printf("\t");			
		}
		printf("\n");
	}
}

void determineNextMove( struct cell board[MAXROWS][MAXCOLUMNS] ){
	struct cell nextMove[MAXROWS][MAXCOLUMNS];
	int i = 0;
	int j = 0;
	for( i = 0; i < MAXROWS; i++ ){
		for( j = 0; j < MAXCOLUMNS; j++ ){
			board[i][j].state = getNextMove( board[i][j], board, i, j );
			//printf("%i (%i, %i)\t", board[i][j].state, calculateNeigbors( board[i][j], board, i, j ), getNextMove( board[i][j], board, i, j ));
		}

	printf("\n");
	}
}

//http://en.wikipedia.org/wiki/Conway's_Game_of_Life#Rules
enum CELLSTATUS getNextMove( struct cell activeIndex, struct cell board[MAXROWS][MAXCOLUMNS], int row, int column ){

	int totalNeigbors = 0;

	totalNeigbors = calculateNeigbors( activeIndex, board, row, column );
	if( activeIndex.state == ALIVE ){
		// Rule 1: Any live cell with fewer than two live neighbours dies, as if caused by under-population.
		if( totalNeigbors <= 1 ){
			return DEAD;
		}

		// Rule 2: Any live cell with two or three live neighbours lives on to the next generation.
		if( totalNeigbors == 2 || totalNeigbors == 3){
			return ALIVE;
		}

		// Rule 3: Any live cell with more than three live neighbours dies, as if by overcrowding.
		if( totalNeigbors > 3){
			return DEAD;
		}
	}else{
		// Rule 4: Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
		if( totalNeigbors == 3){
			return ALIVE;
		}else{
			return DEAD;
		}
	}

	
}
int calculateNeigbors( struct cell activeIndex, struct cell board[MAXROWS][MAXCOLUMNS], int row, int column ){

	int count = 0;
	
	// check above the cell
	
	if( (row - 1) >= 0 ){
		if( board[row-1][column].state == ALIVE ){
			count++;
		}
	}
	//check diagonal top-right
	if( (row - 1) >= 0 && (column + 1) <= MAXCOLUMNS-1 ){
		if( board[row-1][column + 1].state == ALIVE ){
			count++;
		}
	}
	//check right
	if( (column + 1) <= MAXCOLUMNS-1 ){
		if( board[row][column + 1].state == ALIVE ){
			count++;
		}
	}
	
	//check diagonal bottom-right
	if( (row + 1) <= MAXROWS-1 && (column + 1) <= MAXCOLUMNS-1 ){
		if( board[row + 1][column + 1].state == ALIVE ){
			count++;
		}
	}

	//check bottom
	if( (row + 1) <= MAXROWS-1 ){
		if( board[row + 1][column].state == ALIVE ){
			count++;
		}
	}
	//check diagonal bottom-left
	if( (row + 1) <= MAXROWS-1 && (column - 1) >= 0){
		if( board[row + 1][column - 1].state == ALIVE ){
			count++;
		}
	}

	//check left
	if( (column - 1) >= 0){
		if( board[row][column - 1].state == ALIVE ){
			count++;
		}
	}
	
	//check diagonal top-left
	if( (row - 1) >= 0 && (column - 1) >= 0){
		if( board[row - 1][column - 1].state == ALIVE ){
			count++;
		}
	}
	
	 return count;

}