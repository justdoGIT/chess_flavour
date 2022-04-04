#include <algorithm>

#include "chess.h"

using namespace std;


string convert_comma_to_space(string input)
{
    replace(input.begin(), input.end(), ',', ' ');

    return input;
}

vector <string> convert_string_to_vector(string input)
{
    // Replacing the commas with the space in the input string
    string input_pieces = convert_comma_to_space(input);

    // Need to separate the Pieces and put it in a vector
    vector <string> str_pieces;

    // stringstream is used to parse the string
    stringstream ss(input_pieces);

    // Parse the string
    for (string i; ss >> i;)
    {
        str_pieces.push_back(i);
    }

    return str_pieces;
}

vector <Piece> create_piece_formation(vector <string> formation)
{
    unordered_map <string, Piece> const table = {{"P1", Piece::P1},
                                                {"P2", Piece::P2},
                                                {"P3", Piece::P3},
                                                {"P4", Piece::P4},
                                                {"P5", Piece::P5},
                                                {"H1", Piece::H1},
                                                {"H2", Piece::H2},
                                                {"H3", Piece::H3}};
    vector <Piece> new_formation;
    for (size_t i = 0; i < formation.size(); i++)
    {
        auto it = table.find(formation[i]);
        if (it != table.end())
        {
            new_formation.push_back(it->second);
        }
        else
        {
            cout << "Invalid Input Format. Try Again..." << endl;
        }
    }

    return new_formation;
}

Move convert_string_to_move_type(string str)
{
    unordered_map <string, Move> const table = {{"F", Move::F},
                                                {"B", Move::Back},
                                                {"L", Move::L},
                                                {"R", Move::R},
                                                {"FL", Move::FL},
                                                {"FR", Move::FR},
                                                {"BL", Move::BL},
                                                {"BR", Move::BR},
                                                {"RF", Move::RF},
                                                {"RB", Move::RB},
                                                {"LF", Move::LF},
                                                {"LB", Move::LB}};
    auto it = table.find(str);
    if (it != table.end())
    {
        return it->second;
    }
    else
    {
        cout << "Invalid Input Move Format. Try Again..." << endl;
        return Move::INVALID;
    }
}

void init_game(Board * chess_board)
{
    string input;
    vector <string> str_pieces;
    vector <Piece> formation;

	cout << "Player1 Input: ";

    // getline will take the comma separated Pieces (characters) as a single string
	getline(cin, input);
    if (input.length() < 15)
    {
        cout << "Invalid Input Piece Format. Input must be comma or space separated string of all 8 pieces. Ex: 'P1 P2 P3 P4 P5 H1 H2 H3'. Try Again..." << endl;
    }

    // convert string to upper case
    transform(input.begin(), input.end(), input.begin(), ::toupper);

    str_pieces = convert_string_to_vector(input);
    formation = create_piece_formation(str_pieces);

    // Check for duplicate Pieces
    vector <Piece> sorted_formation = formation;
    sort(sorted_formation.begin(), sorted_formation.end());
    if (adjacent_find(sorted_formation.begin(), sorted_formation.end()) != sorted_formation.end())
        cout << "Duplicate Pieces found. Try Again..." << endl;

    // Print the Board
    chess_board->set_board(formation, Player::A);

    cout << "Player2 Input: ";
    getline(cin, input);
    if (input.length() < 15)
    {
        cout << "Invalid Input Piece Format. Try Again..." << endl;
    }

    transform(input.begin(), input.end(), input.begin(), ::toupper);
    str_pieces = convert_string_to_vector(input);
    formation = create_piece_formation(str_pieces);

    // Check for duplicate Pieces
    sorted_formation = formation;
    sort(sorted_formation.begin(), sorted_formation.end());
    if (adjacent_find(sorted_formation.begin(), sorted_formation.end()) != sorted_formation.end())
        cout << "Duplicate Pieces found. Try Again..." << endl;

    chess_board->set_board(formation, Player::B);
}

int main()
{
    bool newgame = true;

    // clear the screen
    system("clear");

    string input = "";

    Board chess_board;

    init_game(&chess_board);

    while (newgame)
    {
        while(chess_board.play_game());
        cout << "Do you want to play again? (y for yes, anything else for no) ";
		cin >> input;
		if (input != "y")
			newgame = false;
	}

	return 0;
}