#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <string>


using namespace std;

enum Player { A, B, NONE };
enum Piece { P1, P2, P3, P4, P5, H1, H2, H3, EMPTY };
enum Move{ L, R, F, Back, FL, FR, BL, BR, RF, RB, LF, LB, INVALID};

struct Position
{
    int x;
    int y;
};

class Spot
{

	Piece piece;
	Player player;
	int row, column;
public:
	void set_space(Spot*);
	void set_empty();
	void set_piece_and_player(Piece, Player);
	Piece get_piece();
	Player get_player();
	void set_row(int i)
    {
        row = i;
    }
	void set_column(int j)
    {
        column = j;
    }
	int get_row()
    {
        return row;
    }
	int get_column()
    {
        return column;
    }
	Spot();
};

class Board
{
	Spot spot[5][5];
	Player turn = A;
	bool make_move(Position* current, Position* future);
    bool move_piece(Spot* start, Spot* end);
    bool move_hero1(Spot* start, Spot* end);
    bool move_hero2(Spot* start, Spot* end);
    bool move_hero3(Spot* start, Spot* end);
    void get_current_piece_position(vector <Piece>, Position*);
    void get_new_piece_position(Position* current, Position* future, vector <Piece>, Move);
    void get_new_hero1_position(Position* current, Position* future, vector <Piece>, Move);
    void get_new_hero2_position(Position* current, Position* future, vector <Piece>, Move);
    void get_new_hero3_position(Position* current, Position* future, vector <Piece>, Move);
    void print_board();
public:
	Spot* get_spot(Position* pos)
    {
		return &spot[pos->x][pos->y];
	}
	void set_spot(Spot * space, Position* pos)
    {
		spot[pos->x][pos->y] = *space;
	}
	bool do_move();
    void set_board(vector <Piece> formation, Player player);
	bool play_game();
};

void print_message(void);
vector <string> convert_string_to_vector(string input);
Move            convert_string_to_move_type(string str);
vector <Piece>  create_piece_formation(vector <string> formation);