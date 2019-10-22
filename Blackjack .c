/*
 * Blackjack.c
 *
 *  Created on: Oct 21, 2019
 *      Author: thiag
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DECK_SIZE 52
#define RESULTS "Blackjack.txt"


enum Suit {HEARTS = 0, DIAMONDS, SPADES, CLUBS};

enum Value {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};


struct card {
	enum Suit suit;
	enum Value value;
};


void play(struct card deck[DECK_SIZE], char *suits[], int *win, int *loss);
void shuffle(struct card deck[DECK_SIZE], int times);
void fileresults(int won, int loss);

int main() {
	char *suits[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	int win = 0;
	int loss = 0;
	struct card deck[DECK_SIZE] = {
			{HEARTS, ACE}, {HEARTS, TWO}, {HEARTS, THREE}, {HEARTS, FOUR}, {HEARTS, FIVE}, {HEARTS, SIX}, {HEARTS, SEVEN}, {HEARTS, EIGHT}, {HEARTS, NINE}, {HEARTS, TEN}, {HEARTS, JACK}, {HEARTS, QUEEN}, {HEARTS, KING},
			{DIAMONDS, ACE}, {DIAMONDS, TWO}, {DIAMONDS, THREE}, {DIAMONDS, FOUR}, {DIAMONDS, FIVE}, {DIAMONDS, SIX}, {DIAMONDS, SEVEN}, {DIAMONDS, EIGHT}, {DIAMONDS, NINE}, {DIAMONDS, TEN}, {DIAMONDS, JACK}, {DIAMONDS, QUEEN}, {DIAMONDS, KING},
			{SPADES, ACE}, {SPADES, TWO}, {SPADES, THREE}, {SPADES, FOUR}, {SPADES, FIVE}, {SPADES, SIX}, {SPADES, SEVEN}, {SPADES, EIGHT}, {SPADES, NINE}, {SPADES, TEN}, {SPADES, JACK}, {SPADES, QUEEN}, {SPADES, KING},
			{CLUBS, ACE}, {CLUBS, TWO}, {CLUBS, THREE}, {CLUBS, FOUR}, {CLUBS, FIVE}, {CLUBS, SIX}, {CLUBS, SEVEN}, {CLUBS, EIGHT}, {CLUBS, NINE}, {CLUBS, TEN}, {CLUBS, JACK}, {CLUBS, QUEEN}, {CLUBS, KING}
	};

	printf("Welcome to my BlackJack Simulator! Below are the basic rules:\n- Beat the dealer's  hand without going over 21.\n- Face cards are worth 10, Aces are worth 1 or 11, whichever makes a better hand.\n- ");
	printf("Each player starts with two cards, and one of the dealer's cards is hidden until the end.\n- Type 'hit' to ask for another card. Type 'stand' to hold your total and end your turn.\n- If you go over 21 you bust, ");
	printf("and the dealer wins regardless of his hand.\n- If you are dealt 21 from the start (Ace & 10), you got a blackjack.\n- Remember: Type 'hit' to get another card, and 'stand' to hold. \nType 'play' to begin. At any time, you may type 'help' to get a list of valid commands.\n");

	char input[20];
	fgets(input, 20, stdin);
	if(input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
	if(input[strlen(input) - 1] == '\r')
		input[strlen(input) - 1] = '\0';

	while (strcmp(input, "quit") != 0)
	{
		if (strcmp(input, "play") == 0)
		{
			shuffle(deck, 200);
			play(deck, suits, &win, &loss);
		}
		else if (strcmp(input, "help") == 0)
		{
			printf("Type 'play' to begin the game.\n");
		}
		printf("Type 'play' to begin the game.\n");
		scanf("%s", input);
	}
	if(strcmp(input, "quit") == 0){
		fileresults(win, loss);
		printf("Thank you for playing");
		char c;
		FILE *fpresults;
		fpresults = fopen(RESULTS, "r");
		if (fpresults == NULL)
		{
			printf("Cannot open file \n");
			exit(0);
		}

		c = fgetc(fpresults);
		while (c != EOF)
		{
			printf ("%c", c);
			c = fgetc(fpresults);
		}

		fclose(fpresults);
		return 0;
	}
}



void shuffle(struct card deck[DECK_SIZE], int times) {
	int card1, card2;
	struct card dummy;
	srand((unsigned) time(0));
	for(int i = 0; i < times; i++){
		card1 = rand() % 52;
		card2 = rand() % 52;
		dummy = deck[card1];
		deck[card1] = deck[card2];
		deck[card2] = dummy;
	}
}

void play(struct card deck[DECK_SIZE], char *suits[], int *win, int *loss){
	char input[6];
	int card1, card2, card3, total, c1, c2, c3, aceCheck;
	int table1, table2, table3, tableTotal, t1, t2, t3;
	srand((unsigned) time(0));
	card1 = rand() %DECK_SIZE;
	card2 = rand() %DECK_SIZE;
	c1 = deck[card1].value;
	if ( c1 > 10 ) {
		c1 = 10;
	}
	c2 = deck[card2].value;
	if ( c2 > 10 ){
		c2 = 10;
	}
	total = c1 + c2;
	if (total <=11){
		if(deck[card1].value == 1){
			c1 = 11;
		}
		else if(deck[card2].value == 1){
			c2 = 11;
		}
	}
	total = c1 + c2;
	printf("%s %d ", suits[deck[card1].suit], (int)deck[card1].value);
	printf("%s %d ", suits[deck[card2].suit], (int)deck[card2].value);
	printf("\nYour total is: %d\n", total);
	while (total < 21){
		printf("\nType 'hit' for another card or type 'stand' to keep your cards:\n");
		scanf("%s", input);
		while (strcmp(input, "stand") != 0)
		{
			if (strcmp(input, "hit") == 0)
			{
				card3 = rand() % DECK_SIZE;
				c3 = deck[card3].value;
				if ( c3 > 10 ){
					c3 = 10;
				}
				aceCheck = total + c3;
				if (aceCheck <=11){
					if(deck[card3].value == 1){
						c3 = 11;
					}
				}
				total = total + c3;
				printf("%s %d, ", suits[deck[card3].suit], deck[card3].value);
				printf("\nYour total is: %d\n", total);
				if ( total >= 21){
					break;
				}
				printf("\nType 'hit' for another card or type 'stand' to keep your cards:\n");
				scanf("%s", input);
			}
			else {
				printf("Unknown command, type 'hit' or 'stand'\n");
				scanf("%s", input);
			}

		}
		if ( strcmp(input, "stand") == 0){
			table1 = rand() % DECK_SIZE;
			table2 = rand() % DECK_SIZE;
			t1 = deck[table1].value;
			if ( t1 > 10 ) {
				t1 = 10;
			}
			t2 = deck[table2].value;
			if ( t2 > 10 ){
				t2 = 10;
			}
			tableTotal = t1 + t2;
			printf("%s %d, ", suits[deck[table1].suit], deck[table1].value);
			printf("%s %d, ", suits[deck[table2].suit], deck[table2].value);
			printf("\nThe tables total is: %d\n", tableTotal);
			while (tableTotal < 17){
				table3 = rand() % DECK_SIZE;
				t3 = deck[table3].value;
				if ( t3 > 10 ){
					t3 = 10;
				}
				tableTotal = tableTotal + t3;
				printf("%s %d, ", suits[deck[table3].suit], deck[table3].value);
				printf("\nThe tables total is: %d\n", tableTotal);

			}
			if( total > tableTotal || tableTotal > 21){
				printf("\nYou win!\n");
				(*win)++;
				break;
			}
			else if (total < tableTotal){
				printf("\nYou lose!\n");
				(*loss)++;
				break;
			}
			else if (total == tableTotal){
				printf("\nIts a draw!\n");
				break;
			}
		}
		if ( total == 21 ){
			printf("\nYou got a blackjack! You won!\n");
			(*win)++;
		}

		else if ( total > 21){
			printf("\nYou busted! You lose!\n");
			(*loss)++;
		}

	}
}
void fileresults(int won, int loss)
{
	FILE *fpresults;
	fpresults = fopen(RESULTS, "w");
	if(fpresults == NULL)
	{
		printf("\nError: File Missing\n");
		system("pause");
		exit(1);
	}
	else
	{
		fprintf(fpresults,"\n\t RESULTS");
		fprintf(fpresults,"\n\t---------\n");
		fprintf(fpresults,"\nYou Have Won %d Times\n", won);
		fprintf(fpresults,"\nYou Have Lost %d Times\n", loss);
	}
	fclose(fpresults);
	return;
}

