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
#define SCORE 9
#define SIGNUP -1


using namespace std;

typedef struct header_t {
	ssize_t nb_books;
	ssize_t nb_libraries = 0;
	ssize_t days_for_scan;
	vector<ssize_t> scores;
} header_t;


typedef struct library_t {
	ssize_t state;
	double time_to_scan;
	ssize_t max_score;
	double potential;
	ssize_t nb_books;
	ssize_t signedup_time;
	ssize_t ship;
	vector<ssize_t> books;
	vector<ssize_t> books_scanned;
	ssize_t order = - 1;
} library_t;

void print_lib(library_t lib)
{
	cout << endl;
	cout << lib.state << endl;
	cout << lib.time_to_scan << endl;
	cout << lib.max_score << endl;
	cout << lib.potential << endl;
	cout << lib.nb_books << endl;
	cout << lib.signedup_time << endl;
	cout << lib.ship << endl;
	cout << lib.order << endl;
	cout << "books" <<endl;
	for (size_t i(0); i < lib.books.size(); i++)
		cout << lib.books[i] << " ";
	cout << "books scanned" <<endl;
	cout << endl;
	for (size_t i(0); i < lib.books_scanned.size(); i++)
		cout << lib.books_scanned[i] << " ";
	cout << endl;
	cout << endl;
}

void calc_potential(library_t & l)
{
	l.potential = TIME*l.time_to_scan 
				+ SCORE*l.max_score 
				+ SIGNUP*l.signedup_time;
}

ssize_t get_max_score(header_t h, library_t l) {
	ssize_t sum = 0;

	for (size_t i = 0; i < l.books.size(); i++) {
		sum += h.scores[l.books[i]];
	}	

	return sum;
}	

void get_param(header_t& h, library_t& l) {

	l.time_to_scan = l.nb_books / l.ship;
	l.max_score = get_max_score(h, l);
}

ssize_t get_best_books(ssize_t *scanned_books, library_t l, header_t h)
{
	ssize_t idx_max=-1;
	ssize_t val_max_book = 0;
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

	vector<ssize_t> scores;
	for (ssize_t i(0); i<(*header).nb_books; i++)
	{
		ssize_t id_book;
		flux_fichier >> id_book;
		scores.push_back(id_book);
	}
	(*header).scores = scores;

	while (flux_fichier.good())
    {
		library_t library;
		library.state = WAIT_FOR_SCAN;
		vector<ssize_t> books;
		flux_fichier >> library.nb_books;
		flux_fichier >> library.signedup_time;
		flux_fichier >> library.ship;

		for (ssize_t i(0); i<library.nb_books; i++)
		{
			ssize_t id_book;
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
	int total_score = 0;
	checkArgs(argc);
	header_t header;
	vector<library_t> libraries;
	ssize_t nb_libraries_scanned = 0;
	ssize_t order = 0;
	
	// ssize_t *scanned_books;
	// scanned_books = 
	// 	(ssize_t*)calloc(header.nb_books,(header.nb_books)*sizeof(ssize_t));


	parse(argv[1],&header,libraries);

	ssize_t *scanned_books;
	scanned_books = 
		(ssize_t*)calloc(header.nb_books,(header.nb_books)*sizeof(ssize_t));


	for (ssize_t i = 0; i < header.nb_libraries; i++)
	{
		get_param(header, libraries[i]);
		calc_potential(libraries[i]);
	}
	ssize_t scanning = 0;
	ssize_t library_scanned = -1;
	for (ssize_t i = 0; i < header.days_for_scan; i++)
	{
		if(scanning <= 0)
		{
			ssize_t index_max_potential = -1;
			double ref_potential = -1;
			for (ssize_t j = 0; j < header.nb_libraries; j++)
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
				libraries[index_max_potential].order = order;
				scanning = libraries[index_max_potential].signedup_time;
				library_scanned = index_max_potential;
				nb_libraries_scanned++;
				order++;
			}
		}

		for (ssize_t k = 0; k < header.nb_libraries; k++)
		{
			if (libraries[k].state == SCANNED)
			{
				ssize_t index = get_best_books(scanned_books, libraries[k], header);
				ssize_t ship = 0;
				while (index != -1 && ship <= libraries[k].ship)
				{
					//change le calloc si != -1
					scanned_books[index] = 1;
					libraries[k].books_scanned.push_back(index);
					//nouveau livre

					total_score += header.scores[index];					
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

	// for (ssize_t i = 0; i < header.nb_libraries; i++)
	// {
	// 	print_lib(libraries[i]);
	// }
	
//	cout << "scanned" << endl;
	// for (ssize_t i = 0; i < header.nb_books; i++)
	// {
	// 	cout << scanned_books[i] <<">";
	// }
	



	ofstream flux_fichier_out;
	flux_fichier_out.open("res.out");
	 if(flux_fichier_out.bad())    
    {
        raler("Erreur système : création fichier.hpp");
    }

	vector<library_t> libraries_scanned(nb_libraries_scanned);

	for(int i(0); i<header.nb_libraries; i++)
	{
		flux_fichier_out << libraries[i].order << endl;
		libraries_scanned[libraries[i].order] = libraries[i];
	}
	flux_fichier_out << nb_libraries_scanned << endl;
	
	for (ssize_t j = 0; j < nb_libraries_scanned; j++)
	{
		flux_fichier_out << j << " " << libraries_scanned[j].books_scanned.size();
		flux_fichier_out << endl;
		for (size_t i = 0; i < libraries_scanned[j].books_scanned.size(); i++)
		{
			flux_fichier_out << libraries_scanned[j].books_scanned[i] << " ";
		}
		flux_fichier_out << endl << endl;		
	}
	

	flux_fichier_out.close();
	
	cout << "total_score = " << total_score << endl;
	return 0;
}