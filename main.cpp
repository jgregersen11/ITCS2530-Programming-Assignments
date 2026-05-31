#include <iostream>
#include <string> //added initialy so i coudl put spaces into what movie name
#include <iomanip> // added for setprecision to cutoff decimal places
#include <fstream> // added for output file
using namespace std;


int main()
{

	//created variables, string for words, float so you can add decimals for time watched and in for rating whole numbers.
	string movie;
	double time_watched;
	int rating;

	// begin gathering infromaiton from console
	// grab movie name
	cout << "What movie did you last watch? (no spaces)" << endl;
	getline(cin, movie); // so you can put spaces. ex, star wars  
	// grabing minutes of movie, alos validation input type
	cout << "How long was the movie in minutes?" << endl;
	if (cin >> time_watched) {
		cout << fixed << setprecision(2);
		cout << time_watched << " minutes ty. " << endl;
	}
	else{
		cout << "invalid input try again." << endl;
		cin.clear();
		cin.ignore(1000, '\n');
	
	}
	// grabing rating, and validate
	cout << "Give a rating out of 5 stars?" << endl;
	
	if (cin >> rating)
		cout << rating << " stars ty." << endl;
	else{
	
		cout << "invalid input try again" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	}

	// this is my attempt at a "rotten meter", determins score from minutes watched and rating in stars
	double score;
	score = 100 - (time_watched / rating);
	cout << "Based on time watched and rating, weve assigned a Movie Score of: " << score << endl;



	// table formating for info gathered
	cout << endl;
	cout << left << setw(25) << "Movie"
		<< left << setw(15) << "Minutes"
		<< left << setw(10) << "Score" << endl;

	cout << string(50, '-') << endl; 

	cout << left << setw(25) << movie
		<< left << setw(15) << time_watched
		<< left << setw(1) << score <<"%" << endl;

	cout << string(50, '-') << endl;
	cout << endl;

	// saving file to txt 

	cout << "Attempting to Save Report..." << endl;
	ofstream outputFile("report.txt");
	if (outputFile.is_open()) {
		outputFile << left << setw(25) << movie
				   << left << setw(15) << time_watched
				   << left << setw(1) << score << " % " << endl;
		outputFile.close();
		cout << "Saved report :)" << endl;
	}
	else {
		cout << "Error transpired :(" << endl;
	}

	return 0;
}










/* old code

//one line output for informaion gathered,
cout << "Thanks\nSo you watched: " << movie << ", with length of: " << time_watched << " minutes, and gave a rating of: " << rating << " stars" << endl;
seconds = time_watched * 60;
cout << time_watched << " minutes is " << seconds << " seconds! WOW!" << endl;


--------------------------------
Movie ------ Length ------ rating
---------------------------------
starwars     186           5/5


*/