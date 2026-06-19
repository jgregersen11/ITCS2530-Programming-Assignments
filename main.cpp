#include <iostream>
#include <string> //added initialy so i coudl put spaces into what movie name
#include <iomanip> // added for setprecision to cutoff decimal places
#include <fstream> // added for output file
#include <windows.h> // added for color
using namespace std;

void banner();
int getchoice();
void dataentry();
void savereport(string moviename, double minutes, double score, string date);
void lastfivereport();
void calculateaverage();

int changecolor();
void setColor(int colorCode);

int main()
{
	int choice = 0; // Menue option 1,2,3
	bool Continue; // bool to continue
	int currentcolor = 7;
	do { // do while to make menu continious
		setColor(currentcolor);
		banner();
		choice = getchoice();

		switch (choice) {
		case 1: {
			dataentry();	
			break;

		}
		case 2: {
			lastfivereport();
			break;
		}

		case 3: {
			calculateaverage();
			break;
		
		}
		case 4: {
			currentcolor = changecolor();
			setColor(currentcolor);
			break;
		}

		case 5: {
			cout << "exiting program, adios!\n";
			break;
		}
		default: {
			cout << "Unrecognised input, go again\n";
			break;
		}
		}
	} while (choice != 5); // end choice
	

	return 0;
}
void banner() {
	cout << string(74, '-') << endl;
	cout << "Welcome to the Movie Rating Database, Use the following options to begin. " << endl;
	cout << "(1) Add to Database" << endl << "(2) Recent Additions" << endl << "(3) Lifetime Report" << endl << "(4) Edit Colors" <<endl  << "(5) Exit Menu" << endl;

}
int getchoice() {
	cout << "Enter your choice: ";
	int choice = 0; // Menue option 1,2,3
	cin >> choice;
	cin.ignore();
	return choice;

}
void dataentry() {
	string movie;
	double time_watched;
	int rating;
	string date;
	bool validdata;
	int loopcount = 1;
	cout << "how many submission do you want to add?" << endl;

	cin >> loopcount;
	cin.ignore();
	for (int i = 1; i <= loopcount; i++) // conditional loop based on loopcount variable
	{
		validdata = true;
		// begin gathering infromaiton from console
		// grab movie name
		cout << "Enter date of watch; 6/3/2026" << endl;
		getline(cin, date);
		cout << "What movie?" << endl;
		getline(cin, movie); // so you can put spaces. ex, star wars  
		// grabing minutes of movie, alos validation input type
		cout << "How long was the movie in minutes?" << endl;
		if (cin >> time_watched) {
			cout << fixed << setprecision(2);
			cout << time_watched << " minutes ty. " << endl;
		}
		else {
			cout << "invalid input try again." << endl;
			cin.clear();
			validdata = false;

		}
		// grabing rating, and validate
		cout << "Give a rating out of 5 stars?" << endl;

		if (cin >> rating) {
			cout << rating << " stars ty." << endl;
			cin.ignore();
		}
		else {

			cout << "invalid input try again" << endl;
			validdata = false;

		}
		if (validdata == true) { // added for bool statement, only thing "new" to case 1

			// this is my attempt at a "rotten meter", determins score from minutes watched and rating in stars
			double score;
			score = 100 - (time_watched / (rating + 1));
			cout << "Based on time watched and rating, weve assigned a Movie Score of: " << score << endl;
			// table formating for info gathered
			cout << endl;
			cout << left << setw(25) << "Movie"
				<< left << setw(15) << "Minutes"
				<< left << setw(12) << "Score"
				<< left << setw(15) << "Date" << endl;

			cout << string(67, '-') << endl;

			cout << left << setw(25) << movie
				<< left << setw(15) << time_watched
				<< left << fixed << setprecision(2) << score << " % " << setw(7) << ""
				<< left << setw(15) << date << endl;

			cout << string(66, '-') << endl;
			cout << endl;
			savereport(movie, time_watched, score, date);

		}
		else {
			cout << "error transpired" << endl;
		}
	}
}

void savereport(string moviename, double minutes, double score, string date) {
	cout << "Attempting to Save Report..." << endl;
	ofstream outputFile("report.txt", ios::app);
	if (outputFile.is_open()) {
		outputFile << left << setw(25) << moviename
			<< left << setw(15) << minutes
			<< left << fixed << setprecision(2) << score << " % " << setw(7) << ""
			<< left << setw(15) << date << endl;
		outputFile.close();
		cout << "Saved report :)" << endl;
	}
	else {
		cout << "Error transpired :(" << endl;
	}
}

void lastfivereport() {
	string L1, L2, L3, L4, L5;
	bool Continue = true;
	cout << "Monthly Report opening..." << endl;
	ifstream outputFile("report.txt");
	if (outputFile.is_open()) {

		if (getline(outputFile, L1) &&
			getline(outputFile, L2) &&
			getline(outputFile, L3) &&
			getline(outputFile, L4) &&
			getline(outputFile, L5)) {

			Continue = true; // the sets up Continue Bool, if 5 line contain any string, then continue with report
		}
		else {
			Continue = false; // if no 5 lines, then no continue.
		}

		if (Continue == true) {

			cout << string(67, '-') << endl;
			cout << left << setw(25) << "Movie"
				<< left << setw(15) << "Minutes"
				<< left << setw(12) << "Score"
				<< left << setw(15) << "Date" << endl;
			cout << string(67, '-') << endl; // header for next lines

			cout << L1 << endl;
			cout << L2 << endl;
			cout << L3 << endl;
			cout << L4 << endl;
			cout << L5 << endl;

			outputFile.close();
			cout << "Report End" << endl;
		}
		else {
			cout << "insuficient data to create report... " << endl;
		}

	}
	else {
		cout << "Error transpired :(" << endl;
	}
}
void calculateaverage() {
	cout << "calculating Averages..." << endl;
	ifstream outputFile("report.txt");

	if (outputFile.is_open()) {

		string n1; // name    
		string d1; // date
		double m1; // minute
		double s1; // score
		string percent; // this is here because in my file the % was filling into the next variable

		double totalmin = 0;
		double totalscore = 0;
		int moviecount = 0;

		while (outputFile >> n1 >> m1 >> s1 >> percent >> d1) { // this goes line for line collectig each item in report, ends after no line to read
			totalmin += m1;
			totalscore += s1;
			moviecount++;
		}

		double avgminutes = totalmin / moviecount;
		double avgscore = totalscore / moviecount;
		cout << "Average Minutes " << fixed << setprecision(2) << avgminutes << " mins" << endl;
		cout << "Average Score " << fixed << setprecision(2) << avgscore << "%" << endl;
		outputFile.close();
	}
	else {
		cout << "error, Statistic report requires 5 points of data, run report 2 first?" << endl;
	}

}
int changecolor() {
	int colorSelection = 0;

	cout << "\n--- Select a Console Text Color ---" << endl;
	cout << "(1) White" << endl;
	cout << "(2) Green" << endl;
	cout << "(3) Blue" << endl;
	cout << "(4) Yellow" << endl;
	cout << "(5) Red" << endl;
	cout << "Enter your choice (1-5): ";
	cin >> colorSelection;
	cin.ignore(); // Clear the newline character from the buffer

	
	switch (colorSelection) {
	case 1:  return 7;  // Light Gray / White (Default)
	case 2:  return 2;  // Green
	case 3:  return 11; // Light Cyan
	case 4:  return 6;  // Yellow
	case 5:  return 4;  // Red
	default:
		cout << "Invalid choice! Keeping default color." << endl;
		return 7;       // Fallback to default
	}
}


void setColor(int colorCode) { // google gemini helped me with this
	// Gets a handle to the console window
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// Changes the text attributes to your number code
	SetConsoleTextAttribute(hConsole, colorCode);
}