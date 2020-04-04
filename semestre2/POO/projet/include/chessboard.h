#ifndef CHESSBOARD_HEADER
#define CHESSBOARD_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/piece.h"

using namespace std;

class Chessboard
{
private:
    Piece *piecesB[8];
    Piece *piecesW[8];
    Pawn *pawnB[8];
    Pawn *pawnW[8];
    Piece *chessboard[8][8];

public:
    void drop_piece(Piece *_piece);
    void print() const;
    bool allow_to_move(Square origin, Square dest);
    bool deplacement(Square origin, Square dest, bool ok_moove);
	void cancel_deplacement(Square origin, Square dest);
    Piece *piece_on_cb(size_t i, size_t j) const;	// pour y acceder à partir de la classe Game
    bool nothing_in_da_way_diagonally(Square o, Square d);
    bool da_way_straight(Square o, Square d);
    bool da_way_queen(Square o, Square d);
	bool is_on_check(Piece *p, Square origin, Square dest);
    Chessboard()
    {

        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                this->chessboard[i][j] = nullptr;
            }
        }

        this->piecesW[0] = new Rock("Black", " \u2656 ", Square(0, 0));
        this->piecesW[1] = new Knights("Black", " \u2658 ", Square(0, 1));
        this->piecesW[2] = new Bishops("Black", " \u2657 ", Square(0, 2));
        this->piecesW[3] = new Queen("Black", " \u2655 ", Square(0, 3));
        this->piecesW[4] = new King("Black", " \u2654 ", Square(0, 4));
        this->piecesW[5] = new Bishops("Black", " \u2657 ", Square(0, 5));
        this->piecesW[6] = new Knights("Black", " \u2658 ", Square(0, 6));
        this->piecesW[7] = new Rock("Black", " \u2656 ", Square(0, 7));
        this->piecesB[0] = new Rock("White", " \u265C ", Square(7, 0));
        this->piecesB[1] = new Knights("White", " \u265E ", Square(7, 1));
        this->piecesB[2] = new Bishops("White", " \u265D ", Square(7, 2));
        this->piecesB[3] = new Queen("White", " \u265B ", Square(7, 3));
        this->piecesB[4] = new King("White", " \u265A ", Square(7, 4));
        this->piecesB[5] = new Bishops("White", " \u265D ", Square(7, 5));
        this->piecesB[6] = new Knights("White", " \u265E ", Square(7, 6));
        this->piecesB[7] = new Rock("White", " \u265C ", Square(7, 7));

        // allocation of panws
        for (unsigned char i(0); i < 8; i++)
        {
            this->pawnW[i] = new Pawn("Black", " \u2659 ", Square(1, i));
            this->pawnB[i] = new Pawn("White", " \u265F ", Square(6, i));
        }

        for (size_t i = 0; i < 8; i++)
        {
            drop_piece(this->piecesW[i]);
            drop_piece(this->piecesB[i]);
            drop_piece(this->pawnW[i]);
            drop_piece(this->pawnB[i]);
        }
    }

    //void moove()
};

#endif
