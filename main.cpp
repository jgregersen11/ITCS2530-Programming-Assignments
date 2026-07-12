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
void calculateaverage();
int changecolor();
void setColor(int colorCode);
//new class that now holds functions and data for the movie tracker
class MovieTracker {
private:
	static const int MAXMOVIES = 5;
	MovieSession sessions[MAXMOVIES];
	int sessionCount;

public:
	MovieTracker() {
		sessionCount = 0; 
	}

	void showMenu();
	void addSession();
	void showReport() const;
	void saveReportToFile(const string& filename) const;
	double computeAverageDuration() const;
};
//main function got significantly smaller
int main()
{
	MovieTracker tracker;
	tracker.showMenu();
	return 0;
}

void MovieTracker::showMenu() {
	int choice = 0;
	int currentcolor = 7;
	do { 
		setColor(currentcolor);
		banner();
		choice = getchoice();

		switch (choice) {
		case 1: addSession(); break;
		case 2: showReport(); break;
		case 3: calculateaverage(); break;
		case 4: currentcolor = changecolor(); setColor(currentcolor); break;
		case 5: cout << "exiting program, adios!\n"; break;
		default: cout << "Unrecognised input, go again\n"; break;
		}
	} while (choice != 5);
}

void MovieTracker::addSession() {
	if (sessionCount >= MAXMOVIES) {
		cout << "Storage full, check the Lifetime Report instead." << endl;
		return;
	}

	int addCount;
	cout << "How many movies do you want to add? (up to " << MAXMOVIES - sessionCount << ")" << endl;
	cin >> addCount;
	while (addCount < 1 || addCount > MAXMOVIES - sessionCount) { 
		cout << "Enter between 1 and " << MAXMOVIES - sessionCount << ": ";
		cin >> addCount;
	}
	cin.ignore();

	for (int i = 0; i < addCount; i++) { 
		MovieSession m;

		cout << "Enter date of watch (ex 6/3/2026): ";
		getline(cin, m.date);

		cout << "What movie? ";
		getline(cin, m.movieName);

		cout << "Movie Type\n1.Classic\n2.Action\n3.Comedy\n4.Horror\nChoice: ";
		int typeChoice;
		cin >> typeChoice;
		m.genre = (Moviegenre)typeChoice;

		cout << "How long was the movie in minutes? ";
		cin >> m.minutes;

		cout << "Rating out of 5 stars? ";
		cin >> m.rating;
		cin.ignore();

		
		if (m.minutes > 0 && (m.rating >= 1 && m.rating <= 5)) {
			m.score = 100 - (m.minutes / (m.rating + 1));

			switch (m.genre) { 
			case Classic: cout << "Classic Movie" << endl; break;
			case action:  cout << "Action Movie" << endl; break;
			case comedy:  cout << "Comedy Movie" << endl; break;
			case Horror:  cout << "Horror Movie" << endl; break;
			}

			sessions[sessionCount] = m;
			sessionCount++;
			cout << "Score: " << fixed << setprecision(2) << m.score << " %" << endl;
		}
		else {
			cout << "Invalid minutes or rating, entry skipped." << endl;
		}
	}

	cout << fixed << setprecision(2)
		<< "Average length so far: " << computeAverageDuration() << " minutes" << endl;
	saveReportToFile("report.txt");
}

double MovieTracker::computeAverageDuration() const {
	if (sessionCount == 0) return 0;
	double minutesOnly[MAXMOVIES];
	for (int i = 0; i < sessionCount; i++) minutesOnly[i] = sessions[i].minutes;
	return findaverage(minutesOnly, sessionCount);
}

void MovieTracker::saveReportToFile(const string& filename) const {
	ofstream outputFile(filename, ios::app);
	if (outputFile.is_open()) {
		for (int i = 0; i < sessionCount; i++) {
			outputFile << left << setw(25) << sessions[i].movieName
				<< left << setw(15) << sessions[i].minutes
				<< left << fixed << setprecision(2) << sessions[i].score << " % " << setw(7) << ""
				<< left << setw(15) << sessions[i].date << endl;
		}
		outputFile.close();
		cout << "Saved report :)" << endl;
	}
	else {
		cout << "Error saving report." << endl;
	}
}

void MovieTracker::showReport() const {
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