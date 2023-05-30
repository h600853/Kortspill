#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

enum Symbol {
	Heart = 3,
	Club = 5,
	Diamond = 4,
	Spade = 6
};


class Kort {
private:
	Symbol symbol;
	int verdi;

public:
	Kort() {

	}
	
	Kort(Symbol symbol, int verdi) {
		this->symbol = symbol;
		this->verdi = verdi;
	}
	Symbol getSymbol() {
		return symbol;
	}
	int getVerdi() {
		return verdi;
	}
	void setSymbol(Symbol symbol) {
		this->symbol = symbol;
	}
	void setVerdi(int verdi) {
		this->verdi = verdi;
	}
	void skrivUt() {
		wcout << "Kort: " << char(symbol) << " " << verdi << endl;

	}
};
class Spiller {
private:
	wchar_t navn[100];
	Kort kort[5];
	int antallkort;

public:
	Spiller(wchar_t navn[]) {
		wcsncpy_s(this->navn, navn, 99);
		antallkort = 0;
	}
	void skrivUtNavn() {
		wcout << "Navn: " << navn << endl;
	}
	void skrivUtKort() {
		for (int i = 0; i < 5; i++) {
			kort[i].skrivUt();
		}
	}
	Kort* getKort() {
		return kort;
	}
	void addKort(Kort k) {
		if (antallkort < 5) {
			kort[antallkort] = k;
			antallkort++;
		}
		else {
			wcout << "Du har for mange kort" << endl;
		}
	}

};

class Kortstokk {
private:
	Kort kort[52];
	int kortindex;

public:

	Kortstokk() {
		kortindex = 0;
		int i = 0;
		for (int symbol = 3; symbol < 6; symbol++) {

			for (int verdi = 1; verdi <= 13; verdi++) {
				kort[i] = Kort(Symbol(symbol), verdi);
				i++;
			}
		}
	}

	void stokk() {
		random_device random;
		mt19937 rng(random());
		shuffle(begin(kort), end(kort), random);
	}

	void skrivUt() {
		for (int i = 0; i < 52; i++) {
			kort[i].skrivUt();
		}
	}
	//del ut 5 kort til spiller
	void delUt(Spiller* spiller) {
		for (int i = 0; i < 5; i++) {
			spiller->addKort(kort[kortindex]);
			kortindex++;
		}
	}
};

class KortSpill {
private:
	vector<Spiller> spillere;

public:
	KortSpill() {
		spillere = vector<Spiller>();
	}
	void antallspillere() {
		int antallspillere;
		wchar_t navn[100];
		wcout << L"Velg antall spillere: " << endl;
		wcin >> antallspillere;
		for (int i = 0; i < antallspillere; i++) {
			wcout << L"Navn: " << endl;
			wcin >> navn;
			Spiller spiller(navn);
			spillere.push_back(spiller);
		}


	}

	void start() {

		wcout << L"Spiller med høyest sum vinner" << endl << L"Spillet starter..." << endl;
		antallspillere();
	}
	void skrivUtSpillere() {
		for (int i = 0; i < spillere.size(); i++) {
			spillere[i].skrivUtNavn();
		}
	}

};

int main()
{
   KortSpill spill;
   spill.start();
   wcout << L"Spillere: " << endl;
   spill.skrivUtSpillere();
}
