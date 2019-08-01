// SQL_31.cpp
#include "Database.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
//
void _1_albumsBetweenDates();
void _2_tracksOfMusicianBetweenDates();
void _3_albumsOfMusicianBetweenDates();
void _4_mostPopularInstrument();
void _5_instrumentsOfAlbum();
void _6_producerMaximumTracksBetweenDates();
void _7_mostPopularManufacturer();
void _8_allMusiciains();
void _9_mostCollaborativeMusician();
void _10_mostPopularGenre();
void _11_mostPopularTechinicianBetweenDates();
void _12_firstAlbumRecorded();
void _13_tracksInMultipleAlbums();
void _14_techniciansRecordingFullAlbum();
void _15_mostDiverseMusician();
void _U_clearCin();
//
int main()
{
    std::cout << "Welcome to Ran & Hodaya DB project!\n";
	Database& db = Database::getInstance();
	//db.allMusicians();
	int decision = -1;
	cout << endl << endl << endl;
	while (decision != 0) {
		cout
			<< "Select option number" << endl
			<< " 0) Quit" << endl
			<< " 1) How many albums were recorded between 2 dates" << endl
			<< " 2) How many tracks musician X recorded between 2 dates" << endl
			<< " 3) In how many albums musician X participated between 2 dates" << endl
			<< " 4) Most popular instrument" << endl
			<< " 5) Instruments of album" << endl
			<< " 6) The producer with maximum tracks between 2 dates" << endl
			<< " 7) Most poplar manufacturer" << endl
			<< " 8) How many musicians recorded" << endl
			<< " 9) Most collaborative musician" << endl
			<< " 10) Most popular genre" << endl
			<< " 11) Most popular techinician between dates" << endl
			<< " 12) First album recorded in the studio" << endl
			<< " 13) All tracks in 2 albums or more" << endl
			<< " 14) List all the techinicians who recorded a full album" << endl
			<< " 15) Most varied musician measured by genre diversity" << endl
			<< " Your Choice: ";
		cin >> decision;

		switch (decision) {
			case 0: {
				cout << "Thank you!" << endl;
				return 0;
			}
			case 1: {
				_1_albumsBetweenDates();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 2: {
				_2_tracksOfMusicianBetweenDates();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 3: {
				_3_albumsOfMusicianBetweenDates();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 4: {
				_4_mostPopularInstrument();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 5: {
				_5_instrumentsOfAlbum();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 6: {
				_6_producerMaximumTracksBetweenDates();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 7: {
				_7_mostPopularManufacturer();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 8: {
				_8_allMusiciains();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 9: {
				_9_mostCollaborativeMusician();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 10: {
				_10_mostPopularGenre();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 11: {
				_11_mostPopularTechinicianBetweenDates();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 12: {
				_12_firstAlbumRecorded();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 13: {
				_13_tracksInMultipleAlbums();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 14: {
				_14_techniciansRecordingFullAlbum();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			case 15: {
				_15_mostDiverseMusician();
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
			default: {
				cout << "\ninvalid decision" << endl;
				decision = -1;
				cin.clear();	cin.ignore(10000, '\n');
				break;
			}
		}//switch(decision)
	}//while(1)
}//main
//
//
void _1_albumsBetweenDates() {
	cout << "\n---\n---\nQuery albums between 2 dates" << endl;
	string start_date = "0000-00-00", end_date = "0000-00-00";
	cout << "enter start date: ";
	_U_clearCin();
	getline(cin, start_date);
	cout << "enter end date: ";
	getline(cin, end_date);
	Database& db = Database::getInstance();
	db._1_albumsBetweenDates(start_date, end_date);
	cout << "---\n---" << endl;
}
void _2_tracksOfMusicianBetweenDates() {
	cout << "\n---\n---\nQuery tracks of musician between 2 dates" << endl;
	string start_date = "0000-00-00", end_date = "0000-00-00", name="";
	cout << "enter start date: ";
	_U_clearCin();
	getline(cin, start_date);
	cout << "enter end date: ";
	getline(cin, end_date);
	cout << "enter musician NAME: ";
	getline(cin, name);
	Database& db = Database::getInstance();
	db._2_tracksOfMusicianBetweenDates(start_date, end_date, name);
	cout << "---\n---" << endl;
}
void _3_albumsOfMusicianBetweenDates() {
	cout << "\n---\n---\nQuery albums of musician between 2 dates" << endl;
	string start_date = "0000-00-00", end_date = "0000-00-00", name = "";
	cout << "enter start date: ";
	_U_clearCin();
	getline(cin, start_date);
	cout << "enter end date: ";
	getline(cin, end_date);
	cout << "enter musician NAME: ";
	getline(cin, name);
	Database& db = Database::getInstance();
	db._3_albumsOfMusicianBetweenDates(start_date, end_date, name);
	cout << "---\n---" << endl;
}
void _4_mostPopularInstrument() {
	cout << "\n---\n---\nQuery most popular instrument" << endl;
	Database& db = Database::getInstance();
	db._4_mostPopularInstrument();
	cout << "---\n---" << endl;
}
void _5_instrumentsOfAlbum() {
	cout << "\n---\n---\nQuery all the instruments of specific album" << endl;
	string name = "";
	cout << "enter album NAME: ";
	_U_clearCin();
	getline(cin, name);
	Database& db = Database::getInstance();
	db._5_instrumentsOfAlbum(name);
	cout << "---\n---" << endl;
}
void _6_producerMaximumTracksBetweenDates() {
	cout << "\n---\n---\nQuery the producer with maximum tracks between 2 dates" << endl;
	string start_date = "0000-00-00", end_date = "0000-00-00";
	cout << "enter start date: ";
	_U_clearCin();
	getline(cin, start_date);
	cout << "enter end date: ";
	getline(cin, end_date);
	Database& db = Database::getInstance();
	db._6_producerMaximumTracksBetweenDates(start_date, end_date);
	cout << "---\n---" << endl;
}
void _7_mostPopularManufacturer() {
	cout << "\n---\n---\nQuery most popular manufacturer" << endl;
	Database& db = Database::getInstance();
	db._7_mostPopularManufacturer();
	cout << "---\n---" << endl;
}
void _8_allMusiciains() {
	cout << "\n---\n---\nQuery all musicians AMOUNT" << endl;
	Database& db = Database::getInstance();
	db._8_allMusiciains();
	cout << "---\n---" << endl;
}
void _9_mostCollaborativeMusician() {
	cout << "\n---\n---\nQuery the musician who collaborated with most other musicians" << endl;
	Database& db = Database::getInstance();
	db._9_mostCollaborativeMusician();
	cout << "---\n---" << endl;
}
void _10_mostPopularGenre() {
	cout << "\n---\n---\nQuery most popular genre" << endl;
	string start_date = "2010-01-01", end_date = "2018-07-01";
	Database& db = Database::getInstance();
	db._10_mostPopularGenre();
	cout << "---\n---" << endl;
}
void _11_mostPopularTechinicianBetweenDates() {
	cout << "\n---\n---\nQuery most popular techinician between dates" << endl;
	string start_date = "0000-00-00", end_date = "0000-00-00";
	cout << "enter start date: ";
	_U_clearCin();
	getline(cin, start_date);
	cout << "enter end date: ";
	getline(cin, end_date);
	Database& db = Database::getInstance();
	db._11_mostPopularTechinicianBetweenDates(start_date, end_date);
	cout << "---\n---" << endl;
}
void _12_firstAlbumRecorded() {
	cout << "\n---\n---\nQuery the first album recorded in the studio" << endl;
	string start_date = "2010-01-01", end_date = "2018-07-01";
	Database& db = Database::getInstance();
	db._12_firstAlbumRecorded();
	cout << "---\n---" << endl;
}
void _13_tracksInMultipleAlbums() {
	cout << "\n---\n---\nQuery all the tracks thar are in 2 albums or more" << endl;
	Database& db = Database::getInstance();
	db._13_tracksInMultipleAlbums();
	cout << "---\n---" << endl;
}
void _14_techniciansRecordingFullAlbum() {
	cout << "\n---\n---\nQuery all the the techinicians who recorded an album" << endl;
	Database& db = Database::getInstance();
	db._14_techniciansRecordingFullAlbum();
	cout << "---\n---" << endl;
}
void _15_mostDiverseMusician() {
	cout << "\n---\n---\nQuery the most diverse musician (recorded the most genres)" << endl;
	Database& db = Database::getInstance();
	db._15_mostDiverseMusician();
	cout << "---\n---" << endl;
}
void _U_clearCin() {
	string t;
	getline(cin, t);
}