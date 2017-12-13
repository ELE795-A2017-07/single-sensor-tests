#include <iostream>
#include <fstream>

#include "TinyGPS.h"

using namespace std;

const string EXAMPLES_FILE_STR = "data/examples.txt";
const string GPS_LOG_FILE_STR = "data/gps_cmds.log";

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
	//ifstream infile(EXAMPLES_FILE_STR);
	ifstream infile(GPS_LOG_FILE_STR);

	int line = 0;
	int col = 0;
	while (!infile.eof()) {
		char c = read_character(infile);
		valid = gps.encode(c);

		if (valid) {
			//cout << "read character " << hex << int(c) << " (" << c << ") valid?" << valid << endl;
			cout << "valid sentence at line " << line << " column " << col << endl;
		}

		if (c == '\n') {
			col = 0;
			line++;
		} else {
			col++;
		}
	}

	infile.close();
	return 0;
}
