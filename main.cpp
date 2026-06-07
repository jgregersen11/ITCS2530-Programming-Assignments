#include <iostream>
#include <string> //added initialy so i coudl put spaces into what movie name
#include <iomanip> // added for setprecision to cutoff decimal places
#include <fstream> // added for output file
using namespace std;


int main()
{
	int choice; // Menue option 1,2,3
	bool Continue; // bool to continue
	cout << string(74, '-') << endl;
	cout << "Welcome to the Movie Rating Database, Use the following options to begin. " << endl;
	cout << "(1) Add to Database" << endl << "(2) Recent Additions" << endl << "(3) Lifetime Report" << endl << "(4) Exit Menu" << endl;
	cin >> choice;
	cin.ignore();
	

	switch (choice) {
	case 1: {
		//created variables, string for words, float so you can add decimals for time watched and in for rating whole numbers.
		string movie;
		double time_watched;
		int rating;
		string date;
		bool validdata;
		validdata = true;
		// begin gathering infromaiton from console
		// grab movie name
		cout << "enter todays date ex; 6/3/2026" << endl;
		getline(cin, date);
		cout << "What movie did you last watch?" << endl;
		getline(cin, movie); // so you can put spaces. ex, star wars  
		// grabing minutes of movie, alos validation input type
		cout << "How long was the movie in minutes?" << endl;
		if (cin >> time_watched) {
			cout << fixed << setprecision(2);
			cout << time_watched << " minutes ty. " << endl;
			}
		else {
			cout << "invalid input try again." << endl;

			validdata=false;

			}
		// grabing rating, and validate
		cout << "Give a rating out of 5 stars?" << endl;

		if (cin >> rating)
			cout << rating << " stars ty." << endl;
		else {

			cout << "invalid input try again" << endl;
			validdata = false;
		}
		if (validdata == true) { // added for bool statement, only thing "new" to case 1

			// this is my attempt at a "rotten meter", determins score from minutes watched and rating in stars
			double score;
			score = 100 - (time_watched / rating + 1);
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
			// saving file to txt 

			cout << "Attempting to Save Report..." << endl;
			ofstream outputFile("report.txt", ios::app);
			if (outputFile.is_open()) {
				outputFile << left << setw(25) << movie
					<< left << setw(15) << time_watched
					<< left << fixed << setprecision(2) << score << " % " << setw(7) << ""
					<< left << setw(15) << date << endl;
				outputFile.close();
				cout << "Saved report :)" << endl;
			}
			else {
				cout << "Error transpired :(" << endl;
			}
		}
		else { cout << "invalid data detected, try again..."<< endl; }
		break;
	
		} // end case 1
	case 2: {
		string L1, L2, L3, L4, L5; // each line read gets a string variable, possible to with loops later,
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
				break;
				}

			}
		else {
			cout << "Error transpired :(" << endl;
			break;
		}
		break;
	}

	case 3: {
		cout << "calculating Averages..." << endl;
		ifstream outputFile("report.txt");

		if (outputFile.is_open() ) {

			string n1, n2, n3, n4, n5; // names    
			string d1, d2, d3, d4, d5; // dates
			double m1, m2, m3, m4, m5; // minutes
			double s1, s2, s3, s4, s5; // scores
			string percent; // this is here because in my file the % was filling into the next variable
			
			outputFile >> n1 >> m1 >> s1 >> percent >> d1;
			outputFile >> n2 >> m2 >> s2 >> percent >> d2; 
			outputFile >> n3 >> m3 >> s3 >> percent >> d3; // percent is just to catch the % in file format;		andor                    50             87.5 %         6/3/26     
			outputFile >> n4 >> m4 >> s4 >> percent >> d4; //																									 ^ this guy gave me problems
			outputFile >> n5 >> m5 >> s5 >> percent >> d5; // this block goes line by line in report.txt storing each item, all i need in this case is minutes and score, the rest is not used.

			double avgminutes = (m1 + m2 + m3 + m4 + m5) / 5;
			double avgscore = (s1 + s2 + s3 + s4 + s5) / 5;
			cout << "Average Minutes " << avgminutes << " mins" << endl;
			cout << "Average Score " << fixed << setprecision(2) << avgscore << "%" << endl;
			outputFile.close();
			break;			
		}
		else {
			cout << "error, Statistic report requires 5 points of data, run report 2 first?"<< endl;
			break;
			}
		}


	case 4: {
		cout << "exiting program, adios!\n";
			break;
	}
	default: {
		cout << "Unrecognised input, go again\n";
		break;
	}
	}// end choice
	

	return 0;
}