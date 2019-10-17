// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream> 
#include <string>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;

int SIZE = 30;
string SEPARATOR = "-----------------------------\n";

// This function receives shift size and applies the Caeser Cipher on the text found inside the caesar_plain.txt file provided.
void CaeserCipher(int s, string filePath = "")
{
	// MARK: - File IO
	ifstream inFile;
	if (filePath.length() == 0) {
		inFile.open("caesar_plain.txt");
	}
	else {
		inFile.open(filePath);
	}
	if (inFile.fail()) {
		cout << "Error opeing the file. Program will terminate" << endl;
		inFile.close();
		exit(1);
	}
	ofstream myfile;
	myfile.open("caeser_output.txt", ios::app);

	for (string line; getline(inFile, line); )
	{
		// MARK: - Encryption
		string result = "";
		for (size_t i = 0; i<line.length(); i++)
		{
			if (isupper(line[i]))
				result += char(int(line[i] + s - 65) % 26 + 65);
			else
				result += char(int(line[i] + s - 97) % 26 + 97);
		}

		// MARK: - Console output
		cout << "CAESER CIPHER :: " << result << endl;

		// MARK: - File IO
		
		myfile << result << endl;
		
		
	}
	myfile << SEPARATOR;
	myfile.close();
	inFile.close();
	cout << SEPARATOR;
}

void PlayFairCipher(string key, string filePath = "") {
	class playfair
	{
	public:
		string doIt(string k, string t, bool ij)
		{
			createGrid(k, ij); getTextReady(t, ij);
			doIt(1);
			return display();
		}

	private:
		void doIt(int dir)
		{
			int a, b, c, d; string ntxt;
			for (string::const_iterator ti = _txt.begin(); ti != _txt.end(); ti++)
			{
				if (getCharPos(*ti++, a, b))
					if (getCharPos(*ti, c, d))
					{
						if (a == c) { ntxt += getChar(a, b + dir); ntxt += getChar(c, d + dir); }
						else if (b == d) { ntxt += getChar(a + dir, b); ntxt += getChar(c + dir, d); }
						else { ntxt += getChar(c, b); ntxt += getChar(a, d); }
					}
			}
			_txt = ntxt;
		}

		string display()
		{
			cout << "OUTPUT:" << endl;
			cout << SEPARATOR;
			string::iterator si = _txt.begin(); int cnt = 0;
			while (si != _txt.end())
			{
				
				cout << *si; si++; cout << *si << " "; si++;
				if (++cnt >= 26) cout << endl, cnt = 0;
			}
			cout << endl << endl;
			return _txt;
		}

		char getChar(int a, int b)
		{
			return _m[(b + 5) % 5][(a + 5) % 5];
		}

		bool getCharPos(char l, int &a, int &b)
		{
			for (int y = 0; y < 5; y++)
				for (int x = 0; x < 5; x++)
					if (_m[y][x] == l)
					{
						a = x; b = y; return true;
					}

			return false;
		}

		void getTextReady(string t, bool ij)
		{
			for (string::iterator si = t.begin(); si != t.end(); si++)
			{
				*si = toupper(*si); if (*si < 65 || *si > 90) continue;
				if (*si == 'J' && ij) *si = 'I';
				else if (*si == 'Q' && !ij) continue;
				_txt += *si;
			}

			string ntxt = ""; size_t len = _txt.length();
			for (size_t x = 0; x < len; x += 2)
			{
				ntxt += _txt[x];
				if (x + 1 < len)
				{
					if (_txt[x] == _txt[x + 1]) ntxt += 'X';
					ntxt += _txt[x + 1];
				}
			}
			_txt = ntxt;

			if (_txt.length() & 1) _txt += 'X';
		}

		void createGrid(string k, bool ij)
		{
			if (k.length() < 1) k = "KEYWORD";
			k += "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; string nk = "";
			for (string::iterator si = k.begin(); si != k.end(); si++)
			{
				*si = toupper(*si); if (*si < 65 || *si > 90) continue;
				if ((*si == 'J' && ij) || (*si == 'Q' && !ij))continue;
				if (nk.find(*si) == -1) nk += *si;
			}
			copy(nk.begin(), nk.end(), &_m[0][0]);
		}
		string _txt; char _m[5][5];
	};

	// MARK: - File IO
	ifstream inFile;
	if (filePath.length() == 0) {
		inFile.open("playfair_plain.txt");
	}
	else {
		inFile.open(filePath);
	}
	if (inFile.fail()) {
		cout << "Error opeing the file. Program will terminate" << endl;
		inFile.close();
		exit(1);
	}
	ofstream myfile;
	myfile.open("playfair_output.txt", ios::app);
	playfair pf;
	for (string line; getline(inFile, line); )
	{
		// MARK: - Encryption
		string result = pf.doIt(key, line, true);
		// MARK: - Console output
		cout << "PLAYFAIR CIPHER :: " << result << endl;
		// MARK: - File IO
		myfile << result << endl;
	}
	myfile << SEPARATOR;
	myfile.close();
	inFile.close();
	cout << SEPARATOR;

}

// Driver program to test the above function 
int main()
{
	int choice = 0, shift = 0;
	string filePath = "";
	cout << "Hello. Press 1 to encrypt the given input file and see the output, or press 2 to insert your own .txt files" << endl;	
	cout << SEPARATOR;
	cin >> choice;
	if (choice == 1) {
		// Call the CaeserCipher
		//CaeserCipher(3);
		//CaeserCipher(6);
		//CaeserCipher(12);

		// Call the PlayFairCipher
		//PlayFairCipher("rats");
		//PlayFairCipher("archangel");

		// Call the HillCipher

		// Call the VigenerCipher

		// Call the VernamCipher
	}
	else if (choice == 2) {
		cout << "Please enter the name of your .txt file. Make sure it exists within the same directory as this file." << endl;
		cout << SEPARATOR;
		cin >> filePath;

		// Call the CaeserCipher
		//CaeserCipher(3, filePath);
		//CaeserCipher(6, filePath);
		//CaeserCipher(12, filePath);

		// Call the PlayFairCipher
		//PlayFairCipher("rats", filePath);
		//PlayFairCipher("archangel", filePath);

		// Call the HillCipher

		// Call the VigenerCipher

		// Call the VernamCipher
		
	}

	return 0;
}

