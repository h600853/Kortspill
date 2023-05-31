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
	
	Kort(Symbol symbol, int verdi) : symbol(symbol), verdi(verdi)  {
	
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
	int verdi;

public:
	Spiller() {
		antallkort = 0;
		verdi = 0;
	}
	Spiller(wchar_t navn[]) {
		wcsncpy_s(this->navn, navn, 99);
		antallkort = 0;
		verdi = 0;
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

	int getVerdi() {
		return verdi;
	}
	void calclulateVerdi() {
		for (int i = 0; i < 5; i++) {
			verdi += kort[i].getVerdi();
		}
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

	void tomKort() {
		antallkort = 0;		
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
		for (int symbol = 3; symbol <= 6; symbol++) {

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
			wcout << endl;
		}


	}
 
	void spillIgjen() {
		wcout << endl;
		wstring svar;
		wcout << L"Vil du spille igjen? (ja/nei)" << endl;
		wcin >> svar;
		if (svar == L"ja") {
			for (int i = 0; i < spillere.size(); i++) {
						spillere[i].tomKort();
			}
			spillRunde();
		}
		else {
			wcout << L"Ha det bra!" << endl;
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
		wcout << endl;
	}
	bool Uavgjort() {
		for (int i = 0; i < spillere.size(); i++) {
			for (int j = i + 1; j < spillere.size(); j++) {

				if (spillere[i].getVerdi() != spillere[j].getVerdi()) {
					return false; 
				}
			}
		}
		return true;
	}

	void spillRunde() {
		Kortstokk kortstokk;
		kortstokk.stokk();
		Spiller s;
		int max = 0;

		for (int i = 0; i < spillere.size(); i++) {
			auto spiller = spillere[i];
			kortstokk.delUt(&spiller);
			spiller.calclulateVerdi();
			wcout << L"Spiller: " << endl;
			spiller.skrivUtNavn();
			wcout << "Har Kort: " << endl;
			spiller.skrivUtKort();
			wcout << "Sum: " << spiller.getVerdi() << endl << endl;

			if (spiller.getVerdi() > max) {
				max = spiller.getVerdi();
				s = spillere[i];
			}
		}
		bool uavgjort = Uavgjort();
		if (uavgjort) {
		wcout << L"Vinner: " << endl;
		s.skrivUtNavn();
		wcout << endl;
		}
		else {
			wcout << "Det blei Uavgjort" << endl;
		}
	
		spillIgjen();
	}


};

int main()
{
   KortSpill* spill = new KortSpill();
   spill->start();
   wcout << L"Spillere: " << endl;
   spill->skrivUtSpillere();
   spill->spillRunde();
   delete spill;

   return 0;
}
