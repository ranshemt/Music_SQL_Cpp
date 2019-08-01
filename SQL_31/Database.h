#ifndef _DB_H
#define _DB_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace sql;
using namespace std;
#define DB_NAME "music"
#define DB_HOST "tcp://127.0.0.1/"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "313613226"

class Database {
private:
	// singleton instance
	static Database* instance;
	Driver* driver;
	ConnectOptionsMap connection_properties;
	// private CTOR (singleton)
	Database();
public:
	static Database& getInstance();
	Connection* getConnection();
	virtual ~Database() {}
	//
	//insert functions
	void insertMusicians();
	void insertAlbums();
	void insertProducers();
	void insertComposers();
	void insertWriters();
	void insertTracks();
	void insertInstruments();
	void insertInsturmentsMusicians();
	void insertProdcuersAlbums();
	void insertTracksMusicians();
	//
	//queries
	void _1_albumsBetweenDates(string& start_date, string& end_date);
	void _2_tracksOfMusicianBetweenDates(string& start_date, string& end_date, string& name);
	void _3_albumsOfMusicianBetweenDates(string& start_date, string& end_date, string& name);
	void _4_mostPopularInstrument();
	void _5_instrumentsOfAlbum(string& name);
	void _6_producerMaximumTracksBetweenDates(string& start_date, string& end_date);
	void _7_mostPopularManufacturer();
	void _8_allMusiciains();
	void _9_mostCollaborativeMusician();
	void _10_mostPopularGenre();
	void _11_mostPopularTechinicianBetweenDates(string& start_date, string& end_date);
	void _12_firstAlbumRecorded();
	void _13_tracksInMultipleAlbums();
	void _14_techniciansRecordingFullAlbum();
	void _15_mostDiverseMusician();
};


#endif