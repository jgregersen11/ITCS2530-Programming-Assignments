#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

enum Moviegenre { Classic = 1, action, comedy, Horror };

// struct holds all info for one movie
struct MovieSession {
	string date;
	string movieName;
	double minutes;
	int rating;
	double score;
	Moviegenre genre;
};

double findaverage(double values[], int size);
void banner();
int getchoice();
bool fillSession(MovieSession& s);
void dataentry();
void savereport(const MovieSession& s);
void lastfivereport();
void calculateaverage();
int changecolor();
void setColor(int colorCode);

int main()
{
	int choice = 0;
	int currentcolor = 7;
	do { 
		setColor(currentcolor);
		banner();
		choice = getchoice();

		switch (choice) {
		case 1: dataentry(); break;
		case 2: lastfivereport(); break;
		case 3: calculateaverage(); break;
		case 4: currentcolor = changecolor(); setColor(currentcolor); break;
		case 5: cout << "exiting program, adios!\n"; break;
		default: cout << "Unrecognised input, go again\n"; break;
		}
	} while (choice != 5);

	return 0;
}

void banner() {
	cout << string(50, '-') << endl;
	cout << "Welcome to the Movie Rating Database" << endl;
	cout << "(1) Add Movies  (2) Recent Additions  (3) Lifetime Report  (4) Edit Colors  (5) Exit" << endl;
}

int getchoice() {
	cout << "Enter your choice: ";
	int choice = 0;
	cin >> choice;
	cin.ignore();
	return choice;
}

double findaverage(double values[], int size) {
	double total = 0;
	for (int i = 0; i < size; i++) total += values[i];
	return total / size;
}

//collects and validates input from the user, where the struc is being used
bool fillSession(MovieSession& s) {
	cout << "Date of watch: ";
	getline(cin, s.date);

	cout << "Movie name: ";
	getline(cin, s.movieName);

	cout << "Movie Type\n1.Classic\n2.Action\n3.Comedy\n4.Horror\nChoice: ";
	int typeChoice;
	cin >> typeChoice;
	s.genre = (Moviegenre)typeChoice;

	cout << "Minutes: ";
	cin >> s.minutes;

	cout << "Rating (1-5): ";
	cin >> s.rating;
	cin.ignore();

	
	if (s.minutes > 0 && (s.rating >= 1 && s.rating <= 5)) {
		s.score = 100 - (s.minutes / (s.rating + 1));
		return true;
	}
	else {
		cout << "Invalid minutes or rating." << endl;
		return false;
	}
}

void dataentry() {
	const int MAXMOVIES = 5;
	MovieSession sessions[MAXMOVIES];
	int count = 0;
	int loopcount;

	cout << "How many movies to add? ";
	cin >> loopcount;
	while (loopcount < 1 || loopcount > MAXMOVIES) { 
		cout << "Enter between 1 and " << MAXMOVIES << ": ";
		cin >> loopcount;
	}
	cin.ignore();

	for (int i = 0; i < loopcount; i++) {
		MovieSession s;
		if (fillSession(s)) {
			switch (s.genre) {
			case Classic: cout << "Classic Movie" << endl; break;
			case action:  cout << "Action Movie" << endl; break;
			case comedy:  cout << "Comedy Movie" << endl; break;
			case Horror:  cout << "Horror Movie" << endl; break;
			}
			sessions[count] = s;
			count++;
			cout << "Score: " << fixed << setprecision(2) << s.score << " %" << endl;
			savereport(s);
		}
	}

	double minutesOnly[MAXMOVIES];
	for (int i = 0; i < count; i++) minutesOnly[i] = sessions[i].minutes;
	if (count > 0)
		cout << "Average Length: " << fixed << setprecision(2)
			<< findaverage(minutesOnly, count) << " minutes" << endl;
}

void savereport(const MovieSession& s) {
	ofstream outputFile("report.txt", ios::app);
	if (outputFile.is_open()) {
		outputFile << left << setw(25) << s.movieName
			<< left << setw(15) << s.minutes
			<< left << fixed << setprecision(2) << s.score << " % " << setw(7) << ""
			<< left << setw(15) << s.date << endl;
		outputFile.close();
		cout << "Saved report :)" << endl;
	}
	else {
		cout << "Error saving report." << endl;
	}
}

void lastfivereport() {
	ifstream outputFile("report.txt");
	string line;
	int count = 0;

	if (outputFile.is_open()) {
		cout << left << setw(25) << "Movie" << setw(15) << "Minutes" << setw(12) << "Score" << setw(15) << "Date" << endl;
		while (getline(outputFile, line) && count < 5) {
			cout << line << endl;
			count++;
		}
		outputFile.close();
	}
	else {
		cout << "No report found yet." << endl;
	}
}

void calculateaverage() {
	ifstream outputFile("report.txt");
	if (!outputFile.is_open()) {
		cout << "No report found yet." << endl;
		return;
	}

	string name, date, percent;
	double minutes, score;
	double totalMin = 0, totalScore = 0;
	int count = 0;

	while (outputFile >> name >> minutes >> score >> percent >> date) {
		totalMin += minutes;
		totalScore += score;
		count++;
	}
	outputFile.close();

	if (count == 0) {
		cout << "No data yet." << endl;
		return;
	}

	double avgMin = totalMin / count;
	double avgScore = totalScore / count;
	cout << fixed << setprecision(2);
	cout << "Average Minutes: " << avgMin << endl;
	cout << "Average Score: " << avgScore << "%" << endl;

	if (avgScore >= 70 && avgMin <= 150) {
		cout << "Great, well-paced movies overall!" << endl;
	}
	else if (avgScore < 50 || avgMin > 180) {
		cout << "Your picks are running long or scoring low." << endl;
	}
	else {
		cout << "Decent mix of movies." << endl;
	}
}

int changecolor() {
	cout << "1.White 2.Green 3.Blue 4.Yellow 5.Red\nChoice: ";
	int choice;
	cin >> choice;
	cin.ignore();

	switch (choice) {
	case 1: return 7;
	case 2: return 2;
	case 3: return 11;
	case 4: return 6;
	case 5: return 4;
	default: return 7;
	}
}

void setColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}