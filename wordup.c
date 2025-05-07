//Author: Jose Vasquez
//Final Project
//Date: 04/30/25

#include <stdio.h>
#define COLUMNS 6 //  Max word size + null
#define ROWS 6
#define WORD_FILE "word.txt"
#define STR_CAP 50

void CheckPhrase(char temp[], int length, int p);
void CopyString(char guess[][COLUMNS], char temp[], int COL, int R);
int checkPunctuation(char phrase[], int length);
void Decapitalize_phrase(char phrase[], int length);
int Capitalize_Phrase(char phrase[], char correct[], char used_letters[], int length);
void indicate(char indicator[][COLUMNS], char correct[], char temp[], char used_letters[], int COL, int R);
int display_entries(int correct_letters, char guess[][COLUMNS], char indicator[][COLUMNS], int repeat);
int displayWin(int guess_number, char guess[][COLUMNS]);

int main(){
	char correct_word[COLUMNS];

	//FILE IO
	FILE* wordptr; 
	wordptr = fopen(WORD_FILE, "r");
	if (wordptr == NULL){
		printf("Cannot open %s file.\nGoodbye.\n", WORD_FILE);
		return 0;
		}
		
	//Getting word
	fscanf(wordptr, "%s", correct_word); //Saves text file word
	fclose(wordptr);

	//Start of game:
	int counter = 1;
	char guesses[ROWS][COLUMNS];
	char indications[ROWS][COLUMNS];
	for (int i = 0; i < ROWS + 1; i++){
		char temp_phrase[STR_CAP];
			if (counter < 6){
				printf("GUESS %d! Enter your guess: ", counter);
			}
			if (counter == 6){
				printf("FINAL GUESS : ");
			}
			if (counter == 7){
				printf("You lost, better luck next time!\n");
				return 0;
			}
			
		scanf("%s", temp_phrase);
		
		//   String length of temp_phrase
		int string_length = 0;
		for (int j = 0; temp_phrase[j] != '\0'; j++){
			string_length++;
			}
		
		int punctuation = checkPunctuation(temp_phrase, string_length);
		
		CheckPhrase(temp_phrase, string_length, punctuation); //  Checks for Punctuation and word size input

		Decapitalize_phrase(temp_phrase, COLUMNS - 1); //  Decapitalize both to compare safely
		Decapitalize_phrase(correct_word, COLUMNS - 1);
		
		//  If a letter is already capitalized, they will be stored here to avoid indication.
		char used[COLUMNS];  
		
		int correct_letter_count = Capitalize_Phrase(temp_phrase, correct_word, used, COLUMNS - 1); 
		
		indicate(indications, correct_word, temp_phrase, used, COLUMNS, counter - 1);
		CopyString(guesses, temp_phrase, COLUMNS, counter - 1); // Stores 1D array into 2D array
		printf("================================\n");
		
		//  Display past words and/or win display
		int winning_word = display_entries(correct_letter_count, guesses, indications, counter);
		if (winning_word == 1){
			return 0;
		}
		counter++;
		}
	return 0;
}

int checkPunctuation(char phrase[], int length){
	int symbols = 0;
	for (int j = 0; j < length; j++){
			if ((phrase[j] < 'A' && phrase[j] >= '!') || (phrase[j] > 'Z' && phrase[j] < 'a') || (phrase[j] > 'z' && phrase[j] <= '~')){
			symbols++;
			}}
		return symbols;
}

void CheckPhrase(char temp[], int length, int p){
	if (length != 5 || p > 0){
			do{
			if (p < 5 && length != 5 || p > 5){
				if (p == 0){
					printf("Your guess must be 5 letters long. \nPlease try again: ");
				}else{
					printf("Your guess must be 5 letters long. Your guess must contain only letters. \nPlease try again: ");
				}
				scanf("%s", temp);
			}
			if (p == 5 || (length == 5 && p < 5)){
				printf("Your guess must contain only letters. \nPlease try again: ");
				scanf("%s", temp);
			}
			//Reading new string length
			length = 0;
			for (int j = 0; temp[j] != '\0'; j++){
				length++;
				}	
			
			p = checkPunctuation(temp, length); //Checks for any punctuation
			
			}while(length != 5 || p > 0);
		}
}

void CopyString(char guess[][COLUMNS], char temp[], int COL, int R){
	for(int i = 0; i < COL; i++){
		guess[R][i] = temp[i];
	}
	guess[R][COL] = '\0';	
}

void Decapitalize_phrase(char phrase[], int length){
	for (int i = 0; i < length; i++){
		if (phrase[i] >= 'A' && phrase[i] <= 'Z'){
			phrase[i] = phrase[i] + 32;
		}
	}
}

int Capitalize_Phrase(char phrase[], char correct[], char used_letters[], int length){ //Capitalizes correct letters
	int correct_letters = 0;
	
	for (int i = 0; i < length; i++){ //Resets used letters for each loop
		used_letters[i] = ' ';
	}
	
	for (int i = 0; i < length; i++){
		if (phrase[i] == correct[i]){
			used_letters[i] = phrase[i]; //Saves capital letters for comparison later
			phrase[i] = phrase[i] - 32;
			correct_letters++;
		}
	}
	return correct_letters;
}

void indicate(char indicator[][COLUMNS], char correct[], char temp[], char used_letters[], int COL, int R){
	for (int i = 0; i < COL - 1; i++){
		indicator[R][i] = ' ';
		for (int j = 0; j < COL - 1; j++){
			if (temp[i] == correct[j] && temp[j] != correct[j] &&used_letters[j] != temp[i]){
				indicator[R][i] = '^';
			}
		}
		indicator[R][COL] = '\0';
	}
}

int display_entries(int correct_letters, char guess[][COLUMNS], char indicator[][COLUMNS], int repeat){
	if (correct_letters == 5){
		int end_value = displayWin(repeat, guess);
		return end_value;
	}else{
		for (int i = 0; i < repeat; i++){
			printf("%s\n", guess[i]);
			printf("%s\n", indicator[i]);
		}
		return 0;
	}
}

int displayWin(int guess_number, char guess[][COLUMNS]){
	printf("                %s\n", guess[guess_number - 1]);
	printf("        You won in %d guesses!\n", guess_number);
	switch (guess_number){
		case 1:
			printf("                Goated!\n");
			break;
		case 2:
		case 3:
			printf("                Amazing!\n");
			break;
		case 4:
		case 5:
			printf("                Nice!\n");
			break;
		case 6:
			break;
		
	}
	return 1;

}
