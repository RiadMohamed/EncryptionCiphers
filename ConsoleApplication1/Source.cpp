// A C++ program to illustrate Caesar Cipher Technique 
#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

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
		for (int i = 0; i<line.length(); i++)
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



// Driver program to test the above function 
int main()
{
	int choice = 0, shift = 0;
	string filePath = "";
	cout << "Hello. Press 1 to encrypt the given input file and see the output, or press 2 to insert the path of your own .txt files" << endl;	
	cout << SEPARATOR;
	cin >> choice;
	if (choice == 1) {
		// Call the CaeserCipher
		CaeserCipher(3);
		CaeserCipher(6);
		CaeserCipher(12);

		// Call the PlayFairCipher

		// Call the HillCipher

		// Call the VigenerCipher

		// Call the VernamCipher
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

		// Call the HillCipher

		// Call the VigenerCipher

		
	}

	return 0;
}
