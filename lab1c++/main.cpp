// lab1c++.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "circle.h"
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>


using namespace std;

char *splitter = ",";

const char *changeSize = "R";
const char *circuitOfCirc = "C";
const char *areaOfCirc = "A";
const char *infoAboutCirc = "P";

void writeInfo(circle *circles, ostream *stream);
circle** parseCirclesFStr(int num, char **arguments);
int getArgumentsCount(char *string, char splitter);
char** getArgumentsFromString(char* string, char* splitter);

int main()
{
	cout << "Content-type: text/html" << endl << endl;
	cout << "<html><body>" << endl;
	cout << "<title>Lab</title>" << endl;

	cout << " R : Resize <br>";
	cout << " C : Calculate circuit of a circle <br>";
	cout << " A : Calculate area of a circle <br>";
	cout << " P : Print circle <br>";

	char *stringS = getenv("QUERY_STRING");
	if (stringS) {
		char **arguments = getArgumentsFromString(stringS, splitter);

		int num = atoi(arguments[0]),
			count = getArgumentsCount(stringS, splitter[0]);

		circle** circles = parseCirclesFStr(num, arguments + 1);

		for (int i = 0; i < num; i++)
			writeInfo(circles[i], &cout);

		int pointer = num + 1;

		while (pointer < count) {
			int index = atoi(arguments[pointer++]) - 1;

			char *command = arguments[pointer++];

			cout << "<p><strong>Circle</strong> " << (index + 1)
				<< ", <strong>command</strong> - " << command << "</p>";

			if (strcmp(command, changeSize) == 0) {
				int percent = atoi(arguments[pointer++]);

				circles[index]->changeSize(percent);

				cout << "<p>After increasing</p>";

				writeInfo(circles[index], &cout);
			}
			else if (strcmp(command, circuitOfCirc) == 0) {
				cout << circles[index]->Circuit() << endl;
			}
			else if (strcmp(command, areaOfCirc) == 0) {
				cout << "<p><strong>Area</strong> = "
					<< circles[index]->Area() << "</p>";
			}
			else if (strcmp(command, infoAboutCirc) == 0) {
				writeInfo(circles[index], &cout);
			}
			else {
				cout << "<p><strong>Incorrect command!</strong></p>";
			}
		}
	}
	cout << "</body></html>" << endl;
    return 0;
}

void writeInfo(circle *circles, ostream *stream) {
	*stream << "Radius = " << circles->rad << "<br>";
}

circle** parseCirclesFStr(int num, char **arguments) {
	circle **result = new circle*[num];

	for (int i = 0; i < num; i++) {
		double radius = atoi(arguments[i]);

		result[i] = new circle(radius);
	}

	return result;
}

int getArgumentsCount(char *string, char splitter) {
		int count = 1;

		for (int i = 0; i < strlen(string); i++)
			if (string[i] == splitter)
				count++;

		return count;
}

char** getArgumentsFromString(char* string, char* splitter) {
		int count = getArgumentsCount(string, splitter[0]);
		int j = 0;
		char *copyString = new char[256]{ NULL };
		strcpy(copyString, string);

		char** arguments = new char*[count] { NULL };
		for (int i = 0; i < count; i++)
			arguments[i] = new char[10]{ NULL };

		char *p = strtok(copyString, splitter);

		while (p != NULL) {
			strcpy(arguments[j], p);
			p = strtok(NULL, splitter);

			j++;
		}

		delete copyString;
		return arguments;
}

