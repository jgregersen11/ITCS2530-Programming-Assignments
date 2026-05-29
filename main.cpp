#include <iostream>
#include <string> //added initialy so i coudl put spaces into what movie name
using namespace std;

//comments 

int main()
{
	//created variables, string for words, float so you can add decimals for time watched and in for rating whole numbers.
	string movie;
	float time_watched;
	int rating;
	float seconds;

	// begin gathering infromaiton from console
	cout << "What movie did you last watch? (no spaces)" << endl;
	cin >> movie;
	//getline(cin, movie); // so you can put spaces. ex, star wars      commented out for assigment requirements

	cout << "How long was the movie in minutes?" << endl;
	cin >> time_watched;

	cout << "Give a rating out of 5 stars?" << endl;
	cin >> rating;

	//one line output for informaion gathered,
	cout << "Thanks\nSo you watched: " << movie << ", with length of: " << time_watched << " minutes, and gave a rating of: " << rating << " stars" << endl;
	seconds = time_watched * 60;
	cout << time_watched <<" minutes is " << seconds << " seconds! WOW!"<< endl;
	return 0;
}