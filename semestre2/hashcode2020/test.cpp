#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "utils.hpp"

#define WAIT_FOR_SCAN 0
#define SCANNING 1
#define SCANNED 2
#define SIZE 1000000

#define TIME -1
#define SCORE 1
#define SIGNUP -1


using namespace std;

typedef struct header_t {
	size_t nb_books;
	size_t nb_libraries;
	size_t days_for_scan;
	vector<size_t> scores;
} header_t;


typedef struct library_t {
	size_t state;
	double time_to_scan;
	size_t max_score;
	double potential;
	size_t nb_books;
	size_t signedup_time;
	size_t ship;
	vector<size_t> books;
} library_t;

void calc_potential(library_t & l)
{
	l.potential = TIME*l.time_to_scan 
				+ SCORE*l.max_score 
				+ SIGNUP*l.signedup_time;
}

size_t get_max_score(header_t h, library_t l) {
	size_t sum = 0;

	for (size_t i = 0; i < l.books.size(); i++) {
		sum += h.scores[l.books[i]];
	}	

	return sum;
}	

void get_param(header_t& h, library_t& l) {

	l.time_to_scan = l.nb_books / l.ship;
	l.max_score = get_max_score(h, l);
	/* ... */

}

size_t get_best_books(size_t *scanned_books, library_t l, header_t h)
{
	size_t idx_max=-1;
	size_t val_max_book = 0;
	for(size_t i=0; i< l.books.size(); i++)
	{
		if((scanned_books[i] == 0) && (h.scores[l.books[i]]> val_max_book) )
		{
			val_max_book = h.scores[l.books[i]];
			idx_max = i;
		}
	}

	return idx_max;
}


void parse(string fichier, header_t* header, vector<library_t> & libraries)
{
	ifstream flux_fichier(fichier);

	if(!(flux_fichier.is_open()))
	{
		raler("Lecture fichier");
	}

	flux_fichier >> (*header).nb_books;
	flux_fichier >> (*header).nb_libraries;
	flux_fichier >> (*header).days_for_scan;

	vector<size_t> scores;
	for (size_t i(0); i<(*header).nb_books; i++)
	{
		size_t id_book;
		flux_fichier >> id_book;
		scores.push_back(id_book);
	}
	(*header).scores = scores;

	while (flux_fichier.good())
    {
		library_t library;
		vector<size_t> books;
		flux_fichier >> library.nb_books;
		flux_fichier >> library.signedup_time;
		flux_fichier >> library.ship;

		for (size_t i(0); i<library.nb_books; i++)
		{
			size_t id_book;
			flux_fichier >> id_book;
			books.push_back(id_book);
		}

		library.books = books;

		libraries.push_back(library);
	}
	flux_fichier.close();

}


int main(int argc, char **argv)
{
	checkArgs(argc);
	header_t header;
	vector<library_t> libraries;
	for (size_t i = 0; i < header.nb_libraries; i++)
	{
		get_param(header, libraries[i]);
		///
		calc_potential(libraries[i]);
	}
	
	size_t *scanned_books;
	scanned_books = 
		(size_t*)calloc(header.nb_books,(header.nb_books)*sizeof(size_t));
	
	parse(argv[1],&header,libraries);

	size_t scanning = 0;
	size_t library_scanned = -1;
	for (size_t i = 0; i < header.days_for_scan; i++)
	{
		if(scanning <= 0)
		{
			size_t index_max_potential = -1;
			double ref_potential = -1;
			for (size_t j = 0; j < header.nb_libraries; j++)
			{
				if (libraries[j].state == WAIT_FOR_SCAN
					&& ref_potential < libraries[j].potential)
				{
					index_max_potential = j;
					ref_potential = libraries[j].potential;
				}
			}
			if(index_max_potential != -1)
			{
				libraries[index_max_potential].state = SCANNING;
				scanning = libraries[index_max_potential].signedup_time;
				library_scanned = index_max_potential;
			}
		}

		for (size_t k = 0; k < header.nb_libraries; k++)
		{
			if (libraries[k].state == SCANNED)
			{
				size_t index = get_best_books(scanned_books, libraries[k]);
				size_t ship = 0;
				while (index != -1 && ship <= libraries[k].ship)
				{
					//change le calloc si != -1
					scanned_books[index] = 1;
					
					//nouveau livre
					index = get_best_books(scanned_books, libraries[k], header);
					ship ++;
				}
			}
		}

		scanning--;
		if (scanning == 0 && library_scanned != -1)
		{
			libraries[library_scanned].state = SCANNED;
		}
	}

	ofstream flux_fichier_out;
	flux_fichier_out.open("res.out");
	 if(flux_fichier_out.bad())    
    {
        raler("Erreur système : création fichier.hpp");
    }

	flux_fichier_out << "lol" << endl;

	flux_fichier_out.close();
	

	return 0;
}
