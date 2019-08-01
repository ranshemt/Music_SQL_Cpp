#include "Database.h"
#include <iostream>
void clearCin() {
	string temp;
	getline(cin, temp);
}

Database* Database::instance = 0;
Database::Database() : driver(get_driver_instance()) {
	connection_properties["hostName"] = DB_HOST;
	connection_properties["port"] = DB_PORT;
	connection_properties["userName"] = DB_USER;
	connection_properties["password"] = DB_PASS;
	connection_properties["OPT_RECONNECT"] = true;
	// use database
	try {
		Connection* con = driver->connect(connection_properties);
		try {
			con->setSchema(DB_NAME);
		}
		catch (SQLException& e) {
			cout << "Loading Data Base. This May Take a While...." << endl;
			Statement* stmt = con->createStatement();
			string q = "CREATE DATABASE IF NOT EXISTS ";
			q.append(DB_NAME);
			stmt->execute(q);
			con->setSchema(DB_NAME);
			//
			//musician
			stmt->execute("CREATE TABLE IF NOT EXISTS musician( "
				"musician_id VARCHAR(45) NOT NULL, "
				"mobile VARCHAR(45) NOT NULL, "
				"name VARCHAR(45) NOT NULL, "
				"address VARCHAR(45) NOT NULL, "
				"isPlayer boolean NULL, "
				"isSinger boolean NULL, "
				"PRIMARY KEY(musician_id)"
				")");
			//
			//album
			stmt->execute("CREATE TABLE IF NOT EXISTS album("
				"album_id VARCHAR(45) NOT NULL,"
				"songsAmount INT(11) NOT NULL,"
				"name VARCHAR(45) NOT NULL,"
				"start_date DATE NOT NULL,"
				"end_date DATE NOT NULL,"
				"PRIMARY KEY(album_id)"
				")");
			//
			//producer
			stmt->execute("CREATE TABLE IF NOT EXISTS producer("
				"producer_id VARCHAR(45) NOT NULL,"
				"name varchar(45) NOT NULL,"
				"PRIMARY KEY(producer_id)"
				")");
			//
			//composer
			stmt->execute("CREATE TABLE IF NOT EXISTS composer("
				"composer_id VARCHAR(45) NOT NULL,"
				"name varchar(45) NOT NULL,"
				"PRIMARY KEY(composer_id)"
				")");
			//
			//writer
			stmt->execute("CREATE TABLE IF NOT EXISTS writer("
				"writer_id varchar(45) NOT NULL,"
				"name varchar(45) NOT NULL,"
				"PRIMARY KEY(writer_id)"
				")");
			//
			//instrument
			stmt->execute("CREATE TABLE IF NOT EXISTS instrument("
				"instrument_id varchar(45) NOT NULL,"
				"name varchar(100) NOT NULL,"
				"type varchar(100) NOT NULL,"
				"manufacturer varchar(45) NOT NULL,"
				"PRIMARY KEY(instrument_id)"
				")");
			//
			//track
			stmt->execute("CREATE TABLE IF NOT EXISTS track("
				"track_id VARCHAR(45) NOT NULL,"
				"length int(11) NOT NULL,"
				"genre varchar(11) NOT NULL,"
				"record_date date NOT NULL,"
				"techinician_id varchar(45) NOT NULL,"
				"writer_id varchar(45) NOT NULL,"
				"composer_id varchar(45) NOT NULL,"
				"album_id varchar(45) NOT NULL,"
				"musician_id varchar(45) NOT NULL,"
				"PRIMARY KEY(track_id),"
				"FOREIGN KEY (writer_id) REFERENCES writer(writer_id),"
				"FOREIGN KEY (composer_id) REFERENCES composer(composer_id),"
				"FOREIGN KEY (musician_id) REFERENCES musician(musician_id),"
				"FOREIGN KEY (album_id) REFERENCES album(album_id)"
				")");
			//
			//prodcuersAlbums
			stmt->execute("CREATE TABLE IF NOT EXISTS prodcuersAlbums("
				"producer_id VARCHAR(45) NOT NULL,"
				"album_id varchar(45) NOT NULL,"
				"PRIMARY KEY(producer_id, album_id),"
				"FOREIGN KEY (producer_id) REFERENCES producer(producer_id),"
				"FOREIGN KEY (album_id) REFERENCES album(album_id)"
				")");
			//
			//insturmentsMusicians
			stmt->execute("CREATE TABLE IF NOT EXISTS insturmentsMusicians("
				"musician_id varchar(45) NOT NULL,"
				"instrument_id varchar(45) NOT NULL,"
				"PRIMARY KEY(musician_id, instrument_id),"
				"FOREIGN KEY (musician_id) REFERENCES musician(musician_id),"
				"FOREIGN KEY (instrument_id) REFERENCES instrument(instrument_id)"
				")");
			//
			//tracksMusicians
			stmt->execute("CREATE TABLE IF NOT EXISTS tracksMusicians("
				"musician_id varchar(45) NOT NULL,"
				"track_id varchar(45) NOT NULL,"
				"PRIMARY KEY(musician_id, track_id),"
				"FOREIGN KEY (musician_id) REFERENCES musician(musician_id),"
				"FOREIGN KEY (track_id) REFERENCES track(track_id)"
				")");
			//
			//
			cout << "inserting all" << endl;
			insertMusicians();
			insertWriters();
			insertComposers();
			insertAlbums();
			insertProducers();
			insertInstruments();
			insertTracks();
			insertInsturmentsMusicians();
			insertProdcuersAlbums();

			delete stmt;
		}
		//
		delete con;
		cout << "Data Base Loaded!" << endl;
	}
	catch (SQLException& e) {
		cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
	}
}
//
//
Database& Database::getInstance() {
	if (Database::instance == 0) {
		instance = new Database();
	}
	return *instance;
}
Connection* Database::getConnection() {
	try {
		Connection* con = driver->connect(connection_properties);
		con->setSchema(DB_NAME);
		return con;
	}
	catch (SQLException& e) {
		cout << e.what();
	}
	return 0;
}
//
//
void Database::insertMusicians() {
	cout << "insertMusicians" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO musician (musician_id, name, mobile, isPlayer, isSinger, address) VALUES"
		"('mid_1', 'Shay Cohen', '0549652142', TRUE, FALSE,'ashdod'),"
		"('mid_2', 'Yotam Cohen', '0522252142', TRUE,FALSE,'ramat gan'),"
		"('mid_3', 'Shay Yona', '0549652142', TRUE, FALSE,'bnei brak'),"
		"('mid_4', 'Nati Yonas', '0549652142', TRUE, FALSE, 'ashdod'),"
		"('mid_5', 'David Yonas', '0549582142', TRUE,TRUE, 'tel aviv'),"
		"('mid_6', 'Moria Shay', '0549652142', TRUE, TRUE, 'ramat gan'),"
		"('mid_7', 'Hodaya Cohen', '054332142', FALSE, TRUE, 'herzlliya'),"
		"('mid_8', 'Sharon Huri', '0548622142', TRUE, TRUE, 'ashdod'),"
		"('mid_9', 'Beni Hen', '0541112142', FALSE, TRUE, 'ramat gan'),"
		"('mid_10', 'Yoni C', '0540002142', TRUE, TRUE, 'herzliya'),"
		"('mid_11', 'Sy Cn', '0543332142', FALSE, TRUE, 'tel aviv')"
	);
	delete con;
	delete stmt;
}
void Database::insertAlbums() {
	cout << "insertAlbums" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO `album` (`album_id`, `songsAmount`, `name`, `start_date`, `end_date`) VALUES"
		"('aid_1', 5,	'Album1', '2000-01-01', '2000-01-22'),"
		"('aid_2', 10,	'Album2', '2000-03-22', '2000-04-22'),"
		"('aid_3', 2,	'Album3','2000-07-22', '2000-08-22'),"
		"('aid_4', 7,	'Album4', '2000-11-22', '2000-11-25'),"
		"('aid_5', 12,	'Album5', '2000-03-22', '2000-05-22'),"
		"('aid_6', 11,	'Album6', '2000-04-22', '2000-06-22'),"
		"('aid_7', 6,	'Album7',  '2000-02-22', '2000-07-22'),"
		"('aid_8', 12,	'Album8',  '2000-05-10', '2000-08-22'),"
		"('aid_9',  9,	'Album9',  '2000-03-22', '2000-09-22'),"
		"('aid_10', 6,	'Album10', '2000-07-21', '2000-10-22')"
	);
	delete con;
	delete stmt;
}
void Database::insertProducers() {
	cout << "insertProducers" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO `producer` (`producer_id`, `name`) VALUES"
		"('pid_1', 'Yaakov'),"
		"('pid_2', 'Shlomo'),"
		"('pid_3', 'Tzion'),"
		"('pid_4', 'Yuval'),"
		"('pid_5', 'Kim'),"
		"('pid_6', 'Amit'),"
		"('pid_7', 'Moshe'),"
		"('pid_8', 'Haim'),"
		"('pid_9', 'Roberto'),"
		"('pid_10', 'Yossi')"
	);
	delete con;
	delete stmt;
}
void Database::insertComposers() {
	cout << "insertComposers" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO `composer` (`composer_id`, `name`) VALUES"
		"('cid_1', 'Hadar'),"
		"('cid_2', 'Yoni'),"
		"('cid_3', 'Ran'),"
		"('cid_4', 'Tal'),"
		"('cid_5', 'Yuval'),"
		"('cid_6', 'Dan'),"
		"('cid_7', 'Avi'),"
		"('cid_8', 'Mor'),"
		"('cid_9', 'Haim'),"
		"('cid_10', 'Yosef')"
	);
	delete con;
	delete stmt;
}
void Database::insertWriters() {
	cout << "insertWriters" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO `writer` (`writer_id`, `name`) VALUES"
		"('wid_1', 'Hani'),"
		"('wid_2', 'Yoram'),"
		"('wid_3', 'Rami'),"
		"('wid_4', 'Tal'),"
		"('wid_5', 'Yam'),"
		"('wid_6', 'David'),"
		"('wid_7', 'Alon'),"
		"('wid_8', 'Moshe'),"
		"('wid_9', 'Hodaya'),"
		"('wid_10', 'Etai')"
	);
	delete con;
	delete stmt;
}
void Database::insertInstruments() {
	cout << "insertInstruments" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO `instrument` (`instrument_id`, `name`, `type`, `manufacturer`) VALUES"
		"('iid_1', 'Guitar',			'String instrument',		'A.C.'),"
		"('iid_2', 'Recorder',			'Wind instrument',			'BBC'),"
		"('iid_3', 'Electric guitar',	'String instrument',		'A.C.'),"
		"('iid_4', 'Bass guitar',		'String instrument',		'A.C.'),"
		"('iid_5', 'Violin',			'String instrument',		'BBC'),"
		"('iid_6', 'Triangle',			'Percussion instrument',	'IBG120'),"
		"('iid_7', 'Cello',				'String instrument',		'ABC'),"
		"('iid_8', 'fff',				'String instrument',		'ABC'),"
		"('iid_9', 'ggg',				'String instrument',		'MUSICFORLIFE'),"
		"('iid_10', 'nnnn',				'String instrument',		'A.C.'),"
		"('iid_11', 'Tambourine',		'Percussion instrument',	'MUSICFORLIFE')"
	);
	delete con;
	delete stmt;
}
void Database::insertTracks() {
	cout << "insertTracks" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	stmt->execute("INSERT INTO `track` (`track_id`, `length`, `genre`, `record_date`, `composer_id`, `writer_id`, `techinician_id`, `album_id`, `musician_id`) VALUES"
		"('t1', 3, 'Rock',	'2000-01-03', 'cid_1', 'wid_2',	'techA',	'aid_1', 'mid_1'),"
		"('t2', 5, 'Pop',	'2000-03-25', 'cid_3', 'wid_4',	'techB',	'aid_2', 'mid_2'),"
		"('t3', 2, 'House',	'2000-07-25', 'cid_2', 'wid_4',	'techC',	'aid_3', 'mid_3'),"
		"('t4', 4, 'Pop',	'2000-11-23', 'cid_3', 'wid_6',	'techA',	'aid_4', 'mid_4'),"
		"('t5', 5, 'Pop',	'2000-04-25', 'cid_9', 'wid_7',	'techB',	'aid_5', 'mid_5'),"
		"('t6', 4, 'House',	'2000-04-25', 'cid_5', 'wid_8',	'techA',	'aid_6', 'mid_6'),"
		"('t7', 1, 'Rock',	'2000-05-25', 'cid_8', 'wid_9',	'techB',	'aid_7', 'mid_7'),"
		"('t8', 5, 'House',	'2000-06-25', 'cid_6', 'wid_10','techA',	'aid_8', 'mid_8'),"
		"('t9', 1, 'Pop',	'2000-04-25', 'cid_7', 'wid_5',	'techA',	'aid_9', 'mid_9'),"
		"('t10', 7, 'Rock',	'2000-08-25', 'cid_4', 'wid_1',	'techB',	'aid_10', 'mid_10'),"
		"('t11', 8, 'Pop',	'2000-03-24', 'cid_2', 'wid_3',	'techC',	'aid_2', 'mid_11'),"
		"('t12', 3, 'House','2000-07-29', 'cid_10', 'wid_3','techA',    'aid_3', 'mid_2')"
	);
	delete con;
	delete stmt;
}
void Database::insertInsturmentsMusicians() {
	cout << "insertInsturmentsMusicians" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	//instruments: iid_1 - iid_11, musicians: mid_1 - mid_11
	stmt->execute("INSERT INTO `insturmentsMusicians` (`musician_id`, `instrument_id`) VALUES"
		"('mid_1', 'iid_1'),"
		"('mid_2', 'iid_2'),"
		"('mid_3', 'iid_3'),"
		"('mid_4', 'iid_4'),"
		"('mid_5', 'iid_5'),"
		"('mid_6', 'iid_6'),"
		"('mid_7', 'iid_7'),"
		"('mid_8', 'iid_8'),"
		"('mid_9', 'iid_9'),"
		"('mid_10', 'iid_10'),"
		"('mid_11', 'iid_11'),"
		"('mid_1', 'iid_2'),"
		"('mid_2', 'iid_10')"
	);
	delete con;
	delete stmt;
}
void Database::insertProdcuersAlbums() {
	cout << "insertProdcuersAlbums" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	//producers: pid_1 - pid_10 , album: aid_1 - aid_10
	stmt->execute("INSERT INTO `prodcuersAlbums` (`producer_id`, `album_id`) VALUES"
		"('pid_1', 'aid_1'),"
		"('pid_2', 'aid_2'),"
		"('pid_3', 'aid_3'),"
		"('pid_4', 'aid_4'),"
		"('pid_5', 'aid_5'),"
		"('pid_6', 'aid_6'),"
		"('pid_7', 'aid_7'),"
		"('pid_8', 'aid_8'),"
		"('pid_9', 'aid_9'),"
		"('pid_10', 'aid_10'),"
		"('pid_1', 'aid_9'),"
		"('pid_2', 'aid_10')"
	);
	delete con;
	delete stmt;
}
void Database::insertTracksMusicians() {
	cout << "insertTracksMusicians" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	Statement* stmt = con->createStatement();
	//tracks: t1 - t12  ,  musicians: mid_1 - mid_11
	stmt->execute("INSERT INTO `insertTracksMusicians` (`track_id`, `musician_id`) VALUES"
		"('t1', 'mid_1'),"
		"('t2', 'mid_2'),"
		"('t3', 'mid_3'),"
		"('t4', 'mid_4'),"
		"('t5', 'mid_5'),"
		"('t6', 'mid_6'),"
		"('t7', 'mid_7'),"
		"('t8', 'mid_8'),"
		"('t9', 'mid_9'),"
		"('t10', 'mid_10'),"
		"('t11', 'mid_11'),"
		"('t12', 'mid_1')"
	);
	delete con;
	delete stmt;
}
//
//
void Database::_1_albumsBetweenDates(string& start_date, string& end_date) {
	cout << "Showing all albums recorded between: " << start_date << " to: " << end_date << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT * FROM album "
			"WHERE start_date >= ? AND end_date <= ?"
		";"
	);
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	rset = pstmt->executeQuery();
	int counter = 0;
	rset->beforeFirst();
	while (rset->next()) {
		cout << counter+1 << ") " << rset->getString("name") << "  --  ";
		++counter;
	}
	cout << "\ntotal albums found: " << counter << endl;
	delete con;
	delete pstmt;
	delete rset;
}
void Database::_2_tracksOfMusicianBetweenDates(string& start_date, string& end_date, string& name) {
	cout << "Showing all tracks of musician " << name << " recorded between: " << start_date << " to: " << end_date << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT musician_id FROM music.track "
			"WHERE record_date >= ? "
			"AND record_date <= ? "
			"AND musician_id LIKE "
				"(SELECT musician_id FROM music.musician "
					"WHERE name LIKE ?"
				")"
		";"
	);
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	pstmt->setString(3, name);
	rset = pstmt->executeQuery();
	int counter = 0;
	if (rset->first()) {
		cout << "\ntotal tracks found: " << rset->rowsCount() << endl;
	}
	
	delete con;
	delete pstmt;
	delete rset;
}
void Database::_3_albumsOfMusicianBetweenDates(string& start_date, string& end_date, string& name){
	cout << "Showing all albums of musician " << name << " recorded between: " << start_date << " to: " << end_date << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT album_id FROM music.track "
			"WHERE record_date >= ? AND record_date <= ? "
				"AND musician_id LIKE "
					"(SELECT musician_id FROM music.musician "
						"WHERE name LIKE ?"
					")"
		";"
	);
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	pstmt->setString(3, name);
	rset = pstmt->executeQuery();
	int counter = 0;
	if (rset->first()) {
		cout << "\ntotal albums found: " << rset->rowsCount() << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_4_mostPopularInstrument() {
	cout << "Showing most popular instrument " << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT name FROM instrument "
			"WHERE instrument_id LIKE "
				"(SELECT instrument_id FROM insturmentsMusicians "
					"GROUP BY instrument_id "
					"ORDER BY COUNT(*) "
					"DESC LIMIT 1"
				")"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nThe most popular instrument is: " << rset->getString("name") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_5_instrumentsOfAlbum(string& name) {
	cout << "Showing all instruments of album " << name << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT * FROM instrument "
			"WHERE instrument_id in "
				"(SELECT instrument_id FROM insturmentsMusicians "
					"WHERE musician_id IN "
						"(SELECT musician_id FROM track "
							"WHERE album_id LIKE "
								"(SELECT album_id FROM album "
									"WHERE name LIKE ?"
								")"
						")"
				")"
		";"
	);
	pstmt->setString(1, name);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	int counter = 0;
	while (rset->next()) {
		cout << rset->getString("name") << ", ";
		counter++;
	}
	cout << "total: " << counter << endl;

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_6_producerMaximumTracksBetweenDates(string& start_date, string& end_date) {
	cout << "Showing the most productive producer from " << start_date << " to: " << end_date << endl;
	try {
		Connection* con = driver->connect(connection_properties);
		con->setSchema(DB_NAME);
		ResultSet* rset;
		PreparedStatement* pstmt = con->prepareStatement(
			"SELECT name FROM music.producer "
				"WHERE producer_id LIKE "
					"(SELECT producer_id FROM music.prodcuersAlbums "
						"WHERE album_id LIKE "
							"(SELECT album_id FROM music.track "
								"WHERE record_date >= ? "
								"AND record_date <= ? "
								"GROUP BY album_id "
								"ORDER BY COUNT(*) "
								"DESC LIMIT 1"
							")"
					")"
			";"
		);
		pstmt->setString(1, start_date);
		pstmt->setString(1, end_date);
		rset = pstmt->executeQuery();
		if (rset->first()) {
			cout << "\nThe most productive producer between these dates is: " << rset->getString("name") << endl;
		}

		delete con;
		delete pstmt;
		delete rset;
	}
	catch (SQLException& e) {
		cout << "WHAT: " << e.what() << endl;
		cout << "getErrorCode: " << e.getErrorCode() << endl;
		cout << "getSQLState: " << e.getSQLState() << endl;
		cout << "getSQLStateCStr: " << e.getSQLStateCStr() << endl;
	}
}
void Database::_7_mostPopularManufacturer() {
	cout << "Showing the most popular manufacturer: ";
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT manufacturer FROM music.instrument "
			"WHERE instrument_id LIKE "
				"(SELECT instrument_id FROM music.insturmentsMusicians "
					"GROUP BY musician_id "
					"ORDER BY COUNT(*) "
					"DESC LIMIT 1"
				")"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nThe most popular manufacturer is: " << rset->getString("manufacturer") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_8_allMusiciains() {
	cout << "Showing how many musicians recorded over the years: ";
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT COUNT(musician_id) FROM musician"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nAll musicians over the years: " << rset->getInt("COUNT(musician_id)") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_9_mostCollaborativeMusician() {
	cout << "Showing the most collaborative musician: ";
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT name, musician_id FROM music.musician "
			"WHERE musician_id LIKE "
				"(SELECT musician_id FROM music.track "
					"GROUP BY album_id "
					"ORDER BY COUNT(*) "
					"DESC LIMIT 1"
				")"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nThe most collaborative musician is: " << rset->getString("name") << " with id: " << rset->getString("musician_id") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_10_mostPopularGenre() {
	cout << "Showing the most popular genre: ";
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT genre FROM track"
			" GROUP BY genre "
			"ORDER BY COUNT(*) "
			"DESC LIMIT 1"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nThe most popular genre is: " << rset->getString("genre") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_11_mostPopularTechinicianBetweenDates(string& start_date, string& end_date) {
	cout << "Showing the most popular technician from: " << start_date << " to: " << end_date << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT techinician_id FROM track "
			"WHERE record_date >= ? "
			"AND record_date <= ? "
			"GROUP BY techinician_id "
			"ORDER BY COUNT(*) "
			"DESC LIMIT 1"
		";"
	);
	pstmt->setString(1, start_date);
	pstmt->setString(2, end_date);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nThe most popular technician ID between these dates is: " << rset->getString("techinician_id") << endl;
	}
	delete con;
	delete pstmt;
	delete rset;
}
void Database::_12_firstAlbumRecorded() {
	cout << "The first album recorded in the studio" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT name FROM music.album "
			"WHERE start_date LIKE "
				"(SELECT MIN(start_date) FROM music.album"
				")"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nThe first album recorded: " << rset->getString("name") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
void Database::_13_tracksInMultipleAlbums() {
	cout << "tracks thar are in miltiple albums: none" << endl;
}
void Database::_14_techniciansRecordingFullAlbum() {
	cout << "The techinicians who recorded an album which all its songs were recorded in our studio" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT techinician_id FROM track "
			"WHERE album_id IN "
				"(SELECT album_id FROM album "
					"WHERE songsAmount IN "
						"(SELECT count(album_id) FROM track "
							"GROUP BY album_id"
						")"
				")"
		";"
	);
	rset = pstmt->executeQuery();
	rset->beforeFirst();
	while (rset->next()) {
		cout << rset->getString("techinician_id") << ", ";
	}
	cout << endl;
	delete con;
	delete pstmt;
	delete rset;
}
void Database::_15_mostDiverseMusician() {
	cout << "The musicians who recorde in most genres" << endl;
	Connection* con = driver->connect(connection_properties);
	con->setSchema(DB_NAME);
	ResultSet* rset;
	PreparedStatement* pstmt = con->prepareStatement(
		"SELECT name FROM music.musician "
			"WHERE musician_id LIKE "
				"(SELECT musician_id FROM music.track "
					"GROUP BY musician_id "
					"ORDER BY COUNT(*) "
					"DESC LIMIT 1"
				")"
		";"
	);
	rset = pstmt->executeQuery();
	if (rset->first()) {
		cout << "\nMost diverse musician: " << rset->getString("name") << endl;
	}

	delete con;
	delete pstmt;
	delete rset;
}
//tries, examples
