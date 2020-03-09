#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/chessboard.h"
#include "../include/piece.h"
using namespace std;

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

/*
 problème quand on essaye de bouger les cases a1, ya meme des segfault pour
 * a7a2 b1a2
 */
bool Chessboard::moove_piece(Square origin, Square dest)
{
    bool reponse(false);
    bool allow_to_moove(false);
    Piece *piece_on_mvnt = this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]];
    //Piece* piece_dst = this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]];
    if (piece_on_mvnt->get_is_pawn())
    {
        cout << "youre mooving a pawn" << endl;
        if (piece_on_mvnt->movment_legal(origin, dest) && 
        this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]]== NULL) 
            allow_to_moove = true;
        else if(diagonal_move_pawn(origin, dest, piece_on_mvnt->get_color()) &&
        this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] != NULL &&
        this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]]->get_is_pawn())
            allow_to_moove = true;
    }
    else if (piece_on_mvnt->movment_legal(origin, dest))
    {
        allow_to_moove = true;
    }

    if (allow_to_moove)
    {
        this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]] = nullptr; //pour delete
        piece_on_mvnt->set_pos(dest);
        this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] = piece_on_mvnt;
        piece_on_mvnt->piece_mooved();
        reponse = true;
    }
    else
        cout << "moove not allowed!" << endl;
    return reponse;
}

Piece *
Chessboard::piece_on_cb(size_t i, size_t j) const
{
    return this->chessboard[i][j];
}
