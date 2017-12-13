#include <iostream>
#include <fstream>

#include "TinyGPS.h"

using namespace std;

const string EXAMPLES_FILE_STR = "examples.txt";

char read_character(ifstream& infile) {
	char c;

	if (infile.is_open()) {
		infile.read(&c, 1);
		return c;
	}
	return '\n';
}


int main(void) {
	bool valid = false;
	TinyGPS gps;
	ifstream infile(EXAMPLES_FILE_STR);

	while (!infile.eof()) {
		char c = read_character(infile);
		valid = gps.encode(c);
		cout << "read character " << hex << int(c) << " (" << c << ") valid?" << valid << endl;
	}

	infile.close();
	return 0;
}
