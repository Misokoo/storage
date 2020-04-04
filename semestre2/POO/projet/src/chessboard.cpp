#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/chessboard.h"
#include "../include/piece.h"
using namespace std;
#define min(a, b) (a < b ? 1 : 0)
#define max(a, b) (a > b ? 1 : 0)

ssize_t origin_inf_to_dest(Square o, Square d, int num_coord)
{
    return min(o.get_coord()[num_coord], d.get_coord()[num_coord]);
}

bool Chessboard::is_on_check(Piece *p, Square origin, Square dest)
{
	Piece *piece_on_mvnt = this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]];
    this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]] = nullptr; //pour delete
    piece_on_mvnt->set_pos(dest);
    this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] = piece_on_mvnt;

	Piece *king;
	int k_i, k_j;
	cout << "on est la" << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j(0); j < 8; j++)
		{
			if (chessboard[i][j] &&
				chessboard[i][j]->get_is_white() == p->get_is_white())
			{
				cout << i << j;
				cout << chessboard[i][j]->get_name()<< endl;
				if (chessboard[i][j]->get_is_king())
				{
					king = chessboard[i][j];
					k_i = i;
					k_j = j;
					cout << "king is "<< king->get_name() << endl;
				}
			}
		}
	}
	for (int i(0); i < 8; i++)
	{
		for (int j(0); j < 8; j++)
		{
			if (chessboard[i][j] &&
				chessboard[i][j]->get_is_white() != p->get_is_white())
			{
				cout << "current piece "<<chessboard[i][j]->get_name() << endl;
				Square square_enemi (7-i,j);
				Square square_king (7-k_i,k_j);
				if (allow_to_move(square_enemi, square_king))
				{
					cout << "you are on check, sry bro" << endl;
					cancel_deplacement(origin, dest);
					return true;
				}
			}
		}
	}
	return false;
}

bool Chessboard ::nothing_in_da_way_diagonally(Square o, Square d)
{
    ssize_t incre0, incre1;
    if (origin_inf_to_dest(o, d, 0))
        incre0 = 1;
    else
        incre0 = -1;
    if (origin_inf_to_dest(o, d, 1))
        incre1 = 1;
    else
        incre1 = -1;

    ssize_t j = o.get_coord()[1] + incre1;
    for (size_t i = o.get_coord()[0] + incre0; i != d.get_coord()[0]; i += incre0)
    {
        Square test_piece = Square(i, j);
        if (this->chessboard[invert_posx(i)][test_piece.get_coord()[1]] != nullptr)
        {
            cout << "error, you are passing through a piece (diag move)" << endl;
            return false;
        }
        j += incre1;
    }
    return true;
}

bool Chessboard ::da_way_straight(Square o, Square d)
{
    ssize_t dir = 1, incre;
    if (d.get_coord()[1] == o.get_coord()[1])
        dir = 0;
    if (origin_inf_to_dest(o, d, dir))
        incre = 1;
    else
        incre = -1;
    ssize_t j = o.get_coord()[!dir];
    for (size_t i = o.get_coord()[dir] + incre; i != d.get_coord()[dir]; i += incre)
    {
        if (dir)
            Square test_piece = Square(j, i);
        else
            Square test_piece = Square(i, j);
        if (dir == 0 && this->chessboard[invert_posx(i)][j] != nullptr)
        {
            cout << "error, you are passing through a piece (straight move)" << endl;
            return false;
        }
        else if (dir == 1 && this->chessboard[invert_posx(j)][i] != nullptr)
        {
            cout << "error, you are passing through a piece (straght move)" << endl;
            return false;
        }
    }
    return true;
}

bool Chessboard::da_way_queen(Square o, Square d)
{
    if (d.get_coord()[1] == o.get_coord()[1] || d.get_coord()[0] == o.get_coord()[0])
        return da_way_straight(o, d);
    return nothing_in_da_way_diagonally(o, d);
}


void Chessboard::drop_piece(Piece *_piece)
{
    size_t i = _piece->get_pos().get_coord()[0];
    size_t j = _piece->get_pos().get_coord()[1];
    this->chessboard[i][j] = _piece;
}

void Chessboard::print() const
{

    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(7); i >= 0; i--)
    {
        cout << i + 1 << " "; // numérotation ligne dans affichage
        for (int j(0); j < 8; j++)
        {
            cout << "|";
            if (chessboard[invert_posx(i)][j])
            {
                cout << "\u0020"; //U+0020 est un esapce utf-8 taille police
                chessboard[invert_posx(i)][j]->print();
                cout << "\u0020"; //<< ";
            }
            else
                cout << space5; // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}

bool Chessboard::allow_to_move(Square origin, Square dest)
{
    bool ok_moove(false);
    Piece *piece_on_mvnt = this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]];
    if (piece_on_mvnt->get_is_pawn())
    {
        cout << "youre mooving a pawn" << endl;
        if (piece_on_mvnt->movment_legal(origin, dest) &&
            this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] == NULL)
            ok_moove = true;
        else if (diagonal_move_pawn(origin, dest, piece_on_mvnt->get_color()) &&
                 this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] != NULL &&
                 this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]]->get_is_pawn())
            ok_moove = true;
    }
    else if (piece_on_mvnt->get_is_rock())
    {
        if (piece_on_mvnt->movment_legal(origin, dest) && da_way_straight(origin, dest))
        {
            cout << "ok Rock you didnt cross any pieces" << endl;
            ok_moove = true;
        }
    }
    else if (piece_on_mvnt->get_is_bishop())
    {
        if (piece_on_mvnt->movment_legal(origin, dest) && nothing_in_da_way_diagonally(origin, dest))
        {
            cout << "ok Bishop, you didnt cross any pieces" << endl;
            ok_moove = true;
        }
    }
    else if (piece_on_mvnt->get_is_queen())
    {
        if (piece_on_mvnt->movment_legal(origin, dest) && da_way_queen(origin, dest))
        {
			cout << origin.get_coord()[0] << origin.get_coord()[1] << endl;
			cout << dest.to_string() << endl;
            cout << "ok Queen, you didnt cross any pieces" << endl;
            ok_moove = true;
        }
    }
    else if (piece_on_mvnt->movment_legal(origin, dest))
        ok_moove = true;
    return ok_moove;
}

bool Chessboard::deplacement(Square origin, Square dest, bool ok_moove)
{
    Piece *piece_on_mvnt = this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]];
    if (!this->is_on_check(piece_on_mvnt, origin, dest) && ok_moove)
    {
        this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]] = nullptr; //pour delete
        piece_on_mvnt->set_pos(dest);
        this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] = piece_on_mvnt;
        piece_on_mvnt->piece_mooved();
		//this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]]->set_pos(dest);
        return true;
    }
    return false;
}


void Chessboard::cancel_deplacement(Square origin, Square dest)
{
    Piece *piece_on_mvnt = this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]];
    this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] = nullptr; //pour delete
    piece_on_mvnt->set_pos(origin);
    this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]] = piece_on_mvnt;
    //piece_on_mvnt->piece_mooved(); faudra gerer le cas ou elle a pas bougé
	//this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]]->set_pos(dest);
}

Piece *
Chessboard::piece_on_cb(size_t i, size_t j) const
{
    return this->chessboard[i][j];
}
