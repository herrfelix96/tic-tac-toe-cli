#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>

using namespace std;

bool	check_winner(char (*field)[3], char c);
bool	has_empty_field(char (*field)[3]);
void	print_field(char (*field)[3]);
void	array_init(char (*field)[3]);
bool	is_occupied(char (*field)[3], int column, int row);

int	main(void)
{
	// Create a 3x3 game field from char array
	char	field[3][3];
	// Fill the field with '-'
	array_init(field);

	do 
	{
		// Print the field on screen
		print_field(field);
	
		// Ask for user input
		cout << "Enter your move (e.g. A1):" << endl;
		string	userInput{""};
		cin >> userInput;
		cout << endl;
	
		// User input convert
		int	column {(userInput.at(0) - 17 - '0')}; // ASCII convert e.g. A->1
		int	row {userInput.at(1) - 1 - '0'}; // User's "1" is array's "0"
		assert(column >= 0 && column <= 2);
		assert(row >= 0 && row <= 2);

		// Mark user's chosen field as 'X'
		field[column][row] = 'X';

		// Check if user won
		if (check_winner(field, 'X'))
		{
			print_field(field);
			cout << "You won!" << endl;
			return 0;
		}

		// Copmuter's turn
		int	randomColumn{0}, randomRow{0};
		if (has_empty_field(field))
		{
			do
			{
				randomColumn = rand() % 3;
				randomRow = rand() % 3;
			}
			while (is_occupied(field, randomColumn, randomRow)); // Repeat if the coordinate is already taken

			assert(randomRow >= 0 && row <= 2);
			assert(randomColumn >= 0 && column <= 2);
			assert(field[randomColumn][randomRow] == '-');

		field[randomColumn][randomRow] = 'O'; // Is letter, not zero
		}
		// If there is no more free fields but the user didn't win yet -> it'a tie.
		else
		{
			print_field(field);
			cout << "It's a tie!" << endl;
			return 0;
		}

		// Check if the computer won
		if (check_winner(field, 'O'))
		{
			print_field(field);
			cout << "You lost!" << endl;
			return 0;
		}
	}
	while (has_empty_field(field));
	return 0;
}

bool	check_winner(char (*field)[3], char c)
{
	// Check vertical
	for (int i {0}; i < 3; i++)
		if (field[i][0] == c && field[i][1] == c && field[i][2] == c)
			return true;
	// Check horizontal
	for (int i {0}; i < 3; i++)
		if (field[0][i] == c && field[1][i] == c && field[2][i] == c)
			return true;
	// Check diagonals
	if (field[0][0] == c && field[1][1] == c && field[2][2] == c)
		return true;
	if (field[2][0] == c && field[1][1] == c && field[0][2] == c)
		return true;
	return false;
}

bool	is_occupied(char (*field)[3], int column, int row)
{
	if (field[column][row] == 'X')
		return true;
	if (field[column][row] == 'O')
		return true;
	return false;
}

bool	has_empty_field(char (*field)[3])
{
	for (int i{0}; i < 3; i++)
		for (int j{0}; j < 3; j++)
			if (field[i][j] == '-')
				return true;
	return false;
}

void	print_field(char (*field)[3])
{
	cout << "  123" << endl;
	cout << "A ";
	for (int i{0}; i < 3; i++)
		cout << field[0][i];
	cout << endl;
	cout << "B ";
	for (int i{0}; i < 3; i++)
		cout << field[1][i];
	cout << endl;
	cout << "C ";
	for (int i{0}; i < 3; i++)
		cout << field[2][i];
	cout << endl << endl;
	return ;
}

void	array_init(char (*field)[3])
{
	for (int i{0}; i < 3; i++)
		for (int j{0}; j < 3; j++)
			field[i][j] = '-';
	return ;
}
