#include "chess.h"

using namespace std;

Spot::Spot()
{
    piece = EMPTY;
	player = NONE;
}

void Spot::set_space(Spot* space)
{
	player = space->get_player();
	piece  = space->get_piece();
}

void Spot::set_empty()
{
	player = NONE;
	piece  = EMPTY;
}

Player Spot::get_player()
{
	return player;
}

Piece Spot::get_piece()
{
	return piece;
}

void Spot::set_piece_and_player(Piece p, Player pl)
{
	piece = p;
	player = pl;
}

void Board::print_board ()
{
    cout << "Current Grid:" << endl;

	for (int i = 0; i < 5; i++)
	{
        for (int j = 0; j < 5; j++)
		{
			Piece piece   = spot[i][j].get_piece();
			Player player = spot[i][j].get_player();

            switch (piece)
            {
            case P1: (player == A)? cout << " A-P1 ": cout << " B-P1 ";
                break;
            case P2: (player == A)? cout << " A-P2 ": cout << " B-P2 ";
                break;
            case P3: (player == A)? cout << " A-P3 ": cout << " B-P3 ";
                break;
            case P4: (player == A)? cout << " A-P4 ": cout << " B-P4 ";
                break;
            case P5: (player == A)? cout << " A-P5 ": cout << " B-P5 ";
                break;
            case H1: (player == A)? cout << " A-H1 ": cout << " B-H1 ";
                break;
            case H2: (player == A)? cout << " A-H2 ": cout << " B-H2 ";
                break;
            case H3: (player == A)? cout << " A-H3 ": cout << " B-H3 ";
                break;
            case EMPTY: cout << " ____ ";
                break;
            default: cout << "XXX";
                break;
            }
		}

		cout << endl;
	}
}

void Board::set_board(vector <Piece> formation, Player player)
{
    switch (player)
    {
        case A:

            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (i == 4)
                    {
                        spot[i][j].set_piece_and_player(formation[j], Player::A);
                        spot[i][j].set_row(i);
                        spot[i][j].set_column(j);
                    }
                    else if (i == 3 && j < 3)
                    {
                        spot[i][j].set_piece_and_player(formation[5 + j], Player::A);
                        spot[i][j].set_row(i);
                        spot[i][j].set_column(j);
                    }
                    else
                    {
                        spot[i][j].set_piece_and_player(EMPTY, NONE);
                        spot[i][j].set_row(i);
                        spot[i][j].set_column(j);
                    }
                }
            }
            break;

        case B:

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (i == 0)
                    {
                        spot[i][j].set_piece_and_player(formation[j], Player::B);
                        spot[i][j].set_row(i);
                        spot[i][j].set_column(j);
                    }
                    else if (i == 1 && j < 3)
                    {
                        spot[i][j].set_piece_and_player(formation[5 + j], Player::B);
                        spot[i][j].set_row(i);
                        spot[i][j].set_column(j);
                    }
                    else if ( i == 3 && j < 3)
                    {
                        continue;
                    }
                    else
                    {
                        spot[i][j].set_piece_and_player(EMPTY, NONE);
                        spot[i][j].set_row(i);
                        spot[i][j].set_column(j);
                    }
                }
            }
            break;

        case NONE:
            break;
    }

    print_board();
}

bool Board::play_game()
{
    system("clear");
	print_board();
    return do_move();
}

vector <Piece> get_piece_to_move(string input)
{
    string str = input.substr(0,2);
    vector <string> str_piece;
    str_piece = convert_string_to_vector(str);

    return create_piece_formation(str_piece);
}

void Board::get_current_piece_position(vector <Piece> piece, Position* current)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if (spot[i][j].get_piece() == piece[0] && spot[i][j].get_player() == turn)
            {
                current->x = i;
                current->y = j;
                break;
            }
        }
    }
}

void Board::get_new_piece_position(Position* current, Position* future, vector <Piece> piece, Move move_type)
{
    switch (move_type)
    {
        case L:
            future->x = current->x;
            future->y = current->y - 1;
            break;
        case R:
            future->x = current->x;
            future->y = current->y + 1;
            break;
        case F:
            if( turn == Player::A)
                future->x = current->x - 1;
            else
                future->x = current->x + 1;
            future->y = current->y;
            break;
        case Back:
            if (turn == Player::A)
                future->x = current->x + 1;
            else
                future->x = current->x - 1;
            future->y = current->y;
            break;
        default:
            cout << "Invalid Move for Piece. Try Again..." << endl;
            break;
    }
}

void Board::get_new_hero1_position(Position* current, Position* future, vector <Piece> piece, Move move_type)
{
    switch (move_type)
    {
        case L:
            future->x = current->x;
            future->y = current->y - 2;
            break;
        case R:
            future->x = current->x;
            future->y = current->y + 2;
            break;
        case F:
            if (turn == Player::A)
                future->x = current->x - 2;
            else
                future->x = current->x + 2;
            future->y = current->y;
            break;
        case Back:
            if (turn == Player::A)
                future->x = current->x + 2;
            else
                future->x = current->x - 2;
            future->y = current->y;
            break;
        default:
            cout << "Invalid Move. Try Agian..." << endl;
            break;
    }
}

void Board::get_new_hero2_position(Position* current, Position* future, vector <Piece> piece, Move move_type)
{
    switch (move_type)
    {
        case FL:
            if (turn == Player::A)
                future->x = current->x - 2;
            else
                future->x = current->x + 2;
            future->y = current->y - 2;
            break;
        case FR:
            if (turn == Player::A)
                future->x = current->x - 2;
            else
                future->x = current->x + 2;
            future->y = current->y + 2;
            break;
        case BL:
            if (turn == Player::A)
                future->x = current->x + 2;
            else
                future->x = current->x - 2;
            future->y = current->y - 2;
            break;
        case BR:
            if (turn == Player::A)
                future->x = current->x + 2;
            else
                future->x = current->x - 2;
            future->y = current->y + 2;
            break;
        default:
            cout << "Invalid Move. Try Again..." << endl;
    }
}

void Board::get_new_hero3_position(Position* current, Position* future, vector <Piece> piece, Move move_type)
{
    switch (move_type)
    {
        case FL:
            if (turn == Player::A)
                future->x = current->x - 2;
            else
                future->x = current->x + 2;
            future->y = current->y - 1;
            break;
        case FR:
            if (turn == Player::A)
                future->x = current->x - 2;
            else
                future->x = current->x + 2;
            future->y = current->y + 1;
            break;
        case BL:
            if (turn == Player::A)
                future->x = current->x + 2;
            else
                future->x = current->x - 2;
            future->y = current->y - 1;
            break;
        case BR:
            if (turn == Player::A)
                future->x =  current->x + 2;
            else
                future->x = current->x - 2;
            future->y = current->y + 1;
            break;
        case RF:
            if (turn == Player::A)
                future->x = current->x - 1;
            else
                future->x = current->x + 1;
            future->y = current->y + 2;
            break;
        case RB:
            if (turn == Player::A)
                future->x = current->x + 1;
            else
                future->x = current->x - 1;
            future->y = current->y + 2;
            break;
        case LF:
            if (turn == Player::A)
                future->x = current->x - 1;
            else
                future->x = current->x + 1;
            future->y = current->y - 2;
            break;
        case LB:
            if (turn == Player::A)
                future->x = current->x + 1;
            else
                future->x = current->x - 1;
            future->y = current->y - 2;
            break;
        default:
            cout << "Invalid Move. Try Again..." << endl;
    }
}
bool Board::do_move()
{
	using namespace std;
	string input;
    Position current;
    Position future;
	bool stop = false;
    vector <Piece> piece;

	while (!stop)
	{
		(turn == A) ? cout << "Player A's Move: ": cout << "Player B's Move: ";
        getline(cin, input);

        if (input.length() < 4)
        {
            cout << "You should type in this format 'P1:F' where P1 represents the 'P1' piece and 'F' represents move it forward. Try Again..." << endl;
        }

        // Convert input string to upper case
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        piece = get_piece_to_move(input);
        get_current_piece_position(piece, &current);

        string move = input.substr(3,2);
        Move move_type = convert_string_to_move_type(move);

        if (piece[0] == Piece::P1 || piece[0] == Piece::P2 || piece[0] == Piece::P3 || piece[0] == Piece::P4 || piece[0] == Piece::P5)
        {
            get_new_piece_position(&current, &future, piece, move_type);
        }

        else if (piece[0] == Piece::H1)
        {
            get_new_hero1_position(&current, &future, piece, move_type);
        }
        else if (piece[0] == Piece::H2)
        {
            get_new_hero2_position(&current, &future, piece, move_type);
        }
        else if (piece[0] == Piece::H3)
        {
            get_new_hero3_position(&current, &future, piece, move_type);
        }
        else
        {
            cout << "Invalid Input Format" << endl;
        }

		if (get_spot(&current)->get_player() == turn)
		{
			if (make_move(&current, &future) == false)
			{
				cout << "Invalid move, try again." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (get_spot(&future)->get_piece() == EMPTY)
    {
		if (get_spot(&current)->get_player() == A)
		{
			cout << "A WINS" << endl;
			return false;
		}
		else

		{
			cout << "B WINS" << endl;
			return false;
		}
    }

	if (turn == Player::B)
		turn = Player::A;
	else
		turn = Player::B;

	return true;
}

bool Board::move_hero1(Spot* start, Spot* end)
{

	int start_row = start->get_row();
	int start_column = start->get_column();
	int end_row = end->get_row();
	int end_column = end->get_column();
	bool invalid = false;
	if (start_row != end_row || start_column != end_column)
	{

		if (start_row == end_row)
		{
			int yIncrement = (end_column - start_column) / (abs(end_column - start_column));
			for (int i = start_column + yIncrement; i != end_column; i += yIncrement)
			{

				if (spot[end_row][i].get_player() == turn)
					return false;
                else
                    spot[end_row][i].set_empty();

			}
		}
		else
			if (start_column == end_column)
			{

				int xIncrement = (end_row - start_row) / (abs(end_row - start_row));
				for (int i = start_row + xIncrement; i != end_row; i += xIncrement)
				{
                    spot[i][end_column].set_empty();
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		end->set_space(start);
		start->set_empty();
		return true;
	}
	else
	{
		std::cout << "That is an invalid move for hero1. Try Again" << std::endl;
		return false;
	}
}

bool Board::move_hero2(Spot* start, Spot* end)
{
	int start_row = start->get_row();
	int start_column = start->get_column();
	int end_row = end->get_row();
	int end_column = end->get_column();
	bool invalid = false;

	if (abs(start_row - end_row) == abs(start_column - end_column))
	{
		int xIncrement = (end_row - start_row) / (abs(end_row - start_row));
		int yIncrement = (end_column - start_column) / (abs(end_column - start_column));

		for (int i = 1; i < abs(start_row - end_row); i++)
		{
            spot[start_row + xIncrement*i][start_column + yIncrement*i].set_empty();
		}
	}
	else
		return false;

	if (invalid == false)
	{
		end->set_space(start);
		start->set_empty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::move_hero3(Spot* start, Spot* end)
{
	int start_row = start->get_row();
	int start_column = start->get_column();
	int end_row = end->get_row();
	int end_column = end->get_column();

	if ((abs(start_row - end_row) == 2 && abs(start_column - end_column) == 1) || (abs(start_row - end_row) == 1 && abs(start_column - end_column) == 2))
	{
		end->set_space(start);
		start->set_empty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::move_piece(Spot* start, Spot* end)
{
	using namespace std;
	int start_row = start->get_row();
	int start_column = start->get_column();
	int end_row = end->get_row();
	int end_column = end->get_column();


	if (start->get_player() == A)
	{
		if ((start_row + 1 == end_row || start_row - 1 == end_row) && end_column == start_column  && (end->get_player() == NONE || end->get_player() == B))
		{
			end->set_space(start);
			start->set_empty();
			return true;
		}
		else
			if (start_row == end_row && (start_column + 1 == end_column || start_column - 1 == end_column)  && (end->get_player() == B || end->get_player() == NONE))
			{
				end->set_space(start);
				start->set_empty();
				return true;
			}
			else
				return false;
	}
	else
		if (start->get_player() == B)
		{
			if ((start_row + 1 == end_row || start_row - 1 == end_row) && end_column == start_column  && (end->get_player() == NONE || end->get_player() == B))
			{
				end->set_space(start);
				start->set_empty();
				return true;
			}
			else
				if ((start_row + 1 == end_row || start_row - 1 == end_row) && end_column == start_column  && (end->get_player() == NONE || end->get_player() == A))
				{
					end->set_space(start);
					start->set_empty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}

bool Board::make_move(Position* current, Position* future)
{
	using namespace std;
	if (current->x < 0 || current->x > 4 || current->y < 0 || current->y > 4 || future->x < 0 || future->x > 4 || future->y < 0 || future->y > 4)
	{
		std::cout << "One of your inputs was out of bounds" << std::endl;
		return false;
	}
	Spot* src  = get_spot(current);
	Spot* dest = get_spot(future);

	if (src->get_player() == dest->get_player() && dest->get_player() != NONE)
	{
		std::cout << "Invalid move: cannot land on your own piece" << std::endl;
		return false;
	}

	switch (src->get_piece())
	{
        case P1:
        case P2:
        case P3:
        case P4:
        case P5: return move_piece(src, dest);
            break;
        case H1: return move_hero1(src, dest);
            break;
        case H2: return move_hero2(src, dest);
            break;
        case H3: return move_hero3(src, dest);
            break;
        case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
            break;
        default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
            break;
	}

	return false;
}