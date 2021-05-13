#ifndef GRID_H
#define GRID_H

#include"cell.h"
#include<vector>
#include<iostream>

using namespace std;

// itt vannak p�ld�nyos�tva a sejtek, �s kapnak �rt�ket az elej�n
// a t�bla felt�lt�se �rt�kekkel (1/0)
class grid
{

private:
	cell** table;
	int height;
	int width;

public:

	cell** gettable() {
		return table;
	}

	//init 2d tomb ami a palya lesz, ebben a tombben lesznek tarolva az egyes cellak peldanyai 2d-ben
	//ennek majd irni constructor(alap 10x10 ures tabla) EZ NEM J� K�RDEZNI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	grid() {
		height = 10;
		width = 10;

		//2d dinamikus tabla letrehozasa a memoriaba
		table = new cell*[width];
		for (int i = 0; i < width; i++)
			table[i] = new cell[height];

		cell nullsejt;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				table[i][j] = nullsejt; //alapbol halott sejtet rak bele, feltolti nullakkal a tablat
			}
		}
	}

	grid(int h, int w) {
		height = h;
		width = w;

		//2d dinamikus tabla letrehozasa a memoriaba
		table = new cell*[height];
		for (int i = 0; i < height; i++)
			table[i] = new cell[width];

		cell nullsejt;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				table[i][j] = nullsejt; //alapbol halott sejtet rak bele, feltolti nullakkal a tablat
			}
		}

		//glider bet�lt�se
		int glidarr[3][3] = { 1,1,1,1,0,0,0,1,0 };

			for (int i = 0; i < 3; i++) { 
				for (int j = 0; j < 3; j++) {
					table[2 - i][2 - j].setstate(glidarr[i][j]);
				}
			}

	}

	~grid() {
		for (int i = 0; i < width; ++i) {
			delete[] table[i];
		}
		delete[] table;
	}

	//glider jobb als� sark�nak kezdeti pozi megad�sa
	// ehhez lehet kiv�telkezel�st �rni
	/*void gliderbonyi(vector<cell> cells, int glidx, int glidy); //a vektorba betolt egy 3x3 as cells-t glider alakban*/

	/*void printcells(vector<cell> cells, int height, int width) const {

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int k = 0; k < cells.size(); k++) {
					if (cells[k].getx() == j && cells[k].gety() == i) {
						if (cells[k].getstate()) { cout << "1"; }
					}
					else cout << "0";
				}
			}
		}
	}*/

	void evolfun(vector<cell> cells, int height, int width);

	//evolfun 2d tombre
	void evol(); 

	void operatorprint(ostream &os)const{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				os << table[i][j].getstate();
			}os << endl;
		}
	}

	void print()const {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << table[i][j].getstate();
			}cout << endl;
		}
	}
};

ostream& operator<<(ostream &os, const grid table) {
	table.operatorprint(os);
	return os;
}
#endif