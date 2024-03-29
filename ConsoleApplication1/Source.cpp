// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream> 
#include <string>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <algorithm>
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

void HillCipher(int** keyParameter, const int matrixSize, string filePath = "") {

	class HillCipher {
		public: int size = 3;
		public: string encrypt3x3(string text, int **key) {
			string c = "";
			size_t k = 0;
			int input[3];

			while (k < text.length()) {
				input[0] = text[k++] - 65;
				input[1] = text[k++] - 65;
				input[2] = text[k++] - 65;

				for (int i = 0; i < 3; i++) {
					int cipher = 0;
					for (int j = 0; j < 3; j++) {
						cipher += key[i][j] * input[j];
					}
					c += (cipher % 26) + 65;
				}
			}
			return c;
		}
		public: string encrypt2x2(string text, int **key) {
			string c = "";
			size_t k = 0;
			int input[2];

			while (k < text.length()) {
				input[0] = text[k++] - 65;
				input[1] = text[k++] - 65;

				for (int i = 0; i < 2; i++) {
					int cipher = 0;
					for (int j = 0; j < 2; j++) {
						cipher += key[i][j] * input[j];
					}
					c += (cipher % 26) + 65;
				}
			}
			return c;
		}
	};
	HillCipher hc;

	// MARK: - File IO
	ifstream inFile;
	ofstream myfile;
	int** key = NULL;
	if (filePath.length() == 0) {
		if (matrixSize == 2) {
			inFile.open("hill_plain_2x2.txt");
			myfile.open("hill_output_2x2.txt", ios::app);
			key = new int*[2];
			for (int i = 0; i < 2; ++i) {
				key[i] = new int[2];
			}
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					key[i][j] = keyParameter[i][j];
				}
			}
		}
		else {
			inFile.open("hill_plain_3x3.txt");
			myfile.open("hill_output_3x3.txt", ios::app);
			key = new int*[3];
			for (int i = 0; i < 3; ++i) {
				key[i] = new int[3];
			}
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					key[i][j] = keyParameter[i][j];
				}
			}
		}
	}
	else {
		inFile.open(filePath);
	}
	if (inFile.fail()) {
		cout << "Error opeing the file. Program will terminate" << endl;
		inFile.close();
		exit(1);
	}

	string result;
	for (string line; getline(inFile, line); )
	{
		// MARK: - Encryption
		if (matrixSize == 3)
			result = hc.encrypt3x3(line, key);
		else
			result = hc.encrypt2x2(line, key);

		// MARK: - Console output
		cout << "HILL CIPHER :: " << result << endl;
		// MARK: - File IO
		myfile << result << endl;
	}
	
	myfile << SEPARATOR;
	myfile.close();
	inFile.close();
	cout << SEPARATOR;
	for (int i = 0; i < matrixSize; ++i) {
		delete[] key[i];
	}
	delete[] key;

}

void VigenerCipher(string key, bool mode, string filePath = "") {

	class Vigenere
	{
	public:
		string key;

		Vigenere(string key)
		{
			for (size_t i = 0; i < key.size(); ++i)
			{
				if (key[i] >= 'A' && key[i] <= 'Z')
					this->key += key[i];
				else if (key[i] >= 'a' && key[i] <= 'z')
					this->key += key[i] + 'A' - 'a';
			}
		}

		string encryptRepeating(string text)
		{
			string out;
			for (int i = 0, j = 0; i < text.length(); ++i)
			{
				char c = text[i];

				if (c >= 'a' && c <= 'z')
					c += 'A' - 'a';
				else if (c < 'A' || c > 'Z')
					continue;

				out += (c + key[j] - 2 * 'A') % 26 + 'A';
				j = (j + 1) % key.length();
			}
			return out;
		}

		string encryptAuto(string text)
		{
			string out;
			int j = 0;
			while (key.length() != text.length()) {
				key += text[j];
				j++;
			}
			transform(key.begin(), key.end(), key.begin(), ::toupper);
			cout << "KEY IS :: " << key << endl;
			cout << "TEXT IS :: " << text << endl;
			for (int i = 0; i < text.length(); ++i)
			{
				char c = text[i];
				if (c >= 'a' && c <= 'z')
					c += 'A' - 'a';
				else if (c < 'A' || c > 'Z')
					continue;
				out += (c + key[i] - 2 * 'A') % 26 + 'A';
			}
			return out;
		}
	};

	// MARK: - File IO
	ifstream inFile;
	if (filePath.length() == 0) {
		inFile.open("vigenere_plain.txt");
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
	myfile.open("vigenere_output.txt", ios::app);



	string result;
	for (string line; getline(inFile, line); )
	{
		Vigenere cipher(key);
		// MARK: - Encryption
		if (mode) {
			// Auto
			result = cipher.encryptAuto(line);

		} else {
			// Repeating 
			result = cipher.encryptRepeating(line);
		}
		// MARK: - Console output
		cout << "VIGENERE CIPHER :: " << result << endl;
		// MARK: - File IO
		myfile << result << endl;
	}

	myfile << SEPARATOR;
	myfile.close();
	inFile.close();
	cout << SEPARATOR;

}

void VernamCipher(string key, string filePath = "") {
	class Vernam
	{
	public:
		string text, key, result = "";
		Vernam(string s, string k)
		{
			this->text = s;
			this->key = k;
		}
		string encrypt()
		{
			for (size_t i = 0; i < text.length(); i++)
			{
				int temp = int(text[i]-'A') + int(key[i]-'A');
				if (temp > 26) {
					temp -= 26;
				}
				temp += 'A';
				result += temp;
			}
			return result;
		}
	};

	// MARK: - File IO
	ifstream inFile;
	if (filePath.length() == 0) {
		inFile.open("vernam_plain.txt");
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
	myfile.open("vernam_output.txt", ios::app);
	string result = "";
	for (string line; getline(inFile, line); )
	{

		Vernam V(line, key);
		result = V.encrypt();
		// MARK: - Console output
		cout << "VERNAM CIPHER :: " << result << endl;
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
		CaeserCipher(3);
		CaeserCipher(6);
		CaeserCipher(12);

		// Call the PlayFairCipher
		PlayFairCipher("rats");
		PlayFairCipher("archangel");

		// Call the HillCipher

		int **key2x2 = new int*[2];
		for (int i = 0; i < 2; i++) {
			key2x2[i] = new int[2];
		}
		key2x2[0][0] = 5; key2x2[0][1] = 17; key2x2[1][0] = 8; key2x2[1][1] = 3;
		HillCipher(key2x2, 2);
		for (int i = 0; i < 2; ++i) {
			delete[] key2x2[i];
		}
		delete[] key2x2;

		int **key3x3 = new int*[3];
		for (int i = 0; i < 3; i++) {
			key3x3[i] = new int[3];
		}
		key3x3[0][0] = 2; key3x3[0][1] = 4; key3x3[0][2] = 12;
		key3x3[1][0] = 9; key3x3[1][1] = 1; key3x3[1][2] = 6;
		key3x3[2][0] = 7; key3x3[2][1] = 5; key3x3[2][2] = 3;
		HillCipher(key3x3, 3);
		for (int i = 0; i < 3; ++i) {
			delete[] key3x3[i];
		}
		delete[] key3x3;


		// Call the VigenerCipher
		VigenerCipher("pie", false);
		VigenerCipher("aether", true);

		// Call the VernamCipher
		VernamCipher("SPARTANS");

	}
	else if (choice == 2) {
		cout << "Please enter the name of your .txt file. Make sure it exists within the same directory as this file." << endl;
		cout << SEPARATOR;
		cin >> filePath;

		// Call the CaeserCipher
		CaeserCipher(3, filePath);
		CaeserCipher(6, filePath);
		CaeserCipher(12, filePath);

		// Call the PlayFairCipher
		PlayFairCipher("rats", filePath);
		PlayFairCipher("archangel", filePath);

		// Call the HillCipher

		int **key2x2 = new int*[2];
		for (int i = 0; i < 2; i++) {
		key2x2[i] = new int[2];
		}
		key2x2[0][0] = 5; key2x2[0][1] = 17; key2x2[1][0] = 8; key2x2[1][1] = 3;
		HillCipher(key2x2, 2, filePath);
		for (int i = 0; i < 2; ++i) {
		delete[] key2x2[i];
		}
		delete[] key2x2;

		int **key3x3 = new int*[3];
		for (int i = 0; i < 3; i++) {
		key3x3[i] = new int[3];
		}
		key3x3[0][0] = 2; key3x3[0][1] = 4; key3x3[0][2] = 12;
		key3x3[1][0] = 9; key3x3[1][1] = 1; key3x3[1][2] = 6;
		key3x3[2][0] = 7; key3x3[2][1] = 5; key3x3[2][2] = 3;
		HillCipher(key3x3, 3, filePath);
		for (int i = 0; i < 3; ++i) {
		delete[] key3x3[i];
		}
		delete[] key3x3;
		
		// Call the VigenerCipher
		VigenerCipher("pie", false, filePath);
		VigenerCipher("aether", true, filePath);

		// Call the VernamCipher
		VernamCipher("SPARTANS", filePath);
	}
	return 0;
}
