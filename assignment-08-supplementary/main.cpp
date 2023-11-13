#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

struct Track
{
	string artist;                          // name of artist
	string cd;                              // cd title
	int    year;                            // year of appearance (if known)
	int    track;							// track number
	string title;                           // track title
	string tags;                            // tags
	Length time;							// playing time
	string country;                         // main countr(y/ies) of artist
};

struct TrackDisplay
{
	bool showArtist;						// if true, show name of artist
	bool showAlbum;							// if true, show cd title
	bool showYear;							// if true, show year of appearance
	bool showTrack;							// if true, show track number
	bool showTitle;							// if true, show track title
	bool showTags;                          // if true, show tags
	bool showLength;						// if true, show playing time
	bool showCountry;                       // if true, show countr(y/ies) of artist
};

bool match (string sub, string source)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    Result is true only if sub is a literal (case sensitive) sub string of source.
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/
    string seconds;
    if (length.seconds < 10) {
        out << length.minutes << ":0" << length.seconds;
    } else {
        out << length.minutes << ':' << length.seconds;
    }

    return out;
}

istream& operator>> (istream& in, Length& length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length has been read from in: first minutes, then ':', then seconds
*/
    int minutes, seconds;
    char colon;
    in >> minutes >> colon >> seconds;
    if (colon == ':')
        length = {minutes, seconds};

    return in;
}

Length operator+ (const Length& a, const Length& b)
{// Precondition:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postcondition:
    Result is the sum of a and b.
*/
    int minutes, seconds;

    minutes = a.minutes + b.minutes;
    seconds = a.seconds + b.seconds;
    if (seconds >= 60) {
        minutes++;
        seconds -= 60;
    }

    return {minutes, seconds};
}

void show_track (Track track, TrackDisplay lt, ostream& os)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    only the members of track are shown for which the corresponding member in lt is true.
*/
    if (lt.showArtist) {
        os << track.artist << endl;
    }
    if (lt.showAlbum) {
        os << track.cd << endl;
    }
    if (lt.showYear) {
        os << track.year << endl;
    }
    if (lt.showTrack) {
        os << track.track << endl;
    }
    if (lt.showTitle) {
        os << track.title << endl;
    }
    if (lt.showTags) {
        os << track.tags << endl;
    }
    if (lt.showLength) {
        os << track.time << endl;
    }
    if (lt.showCountry) {
        os << track.country << endl;
    }
    cout << endl; // Line added for bonus, for easier readability
}

istream& operator>> (istream& in, Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    The following (empty) line from in has also been read.
*/
    string temp; // temp is used to remove trailing endlines from te buffer after in >> is used.
    getline(in, track.artist);
    getline(in, track.cd);
    in >> track.year;
    in >> track.track;
    getline(in, temp); // removes trailing \n so the next getline works
    getline(in, track.title);
    getline(in, track.tags);
    in >> track.time;
    getline(in, temp); // removes trailing \n so the next getline works
    getline(in, track.country);
    getline(in, temp);
    return in;
}


bool string_in_vector(const vector<string>& vec, string val) {
    assert(true);
/*  Postcondition:
    This this function uses linear search to find string val in vector vec,
    If it finds val in vec, it returns true, otherwise it returns false.
*/

    for (int i = 0; i < ssize(vec); i++) {
        if (vec.at(i) == val)
            return true;
    }
    return false;
}

int match_tracks (const vector<Track>& tracks, string track, bool display)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have a title matching `title`
    if `display` is true, all matched tracks have been printed to `cout`
*/
    int num = 0;
    TrackDisplay lt = {true, true, true, true, true, true, true, true};
    for (int i = 0; i < ssize(tracks); i++) {
        if (match(track, tracks.at(i).title)) {
            if (display)
                show_track(tracks.at(i), lt, cout);
            num++;
        }
    }
    return num;
}

int match_artists (const vector<Track>& tracks, string artist, bool display)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have an artist matching `artist`, where each artist is only matched once
    if `display` is true, all matched tracks have been printed to `cout`
*/

    int num = 0;
    TrackDisplay lt = {true};
    vector<string> artists;
    for (int i = 0; i < ssize(tracks); i++) {
        if (match(artist, tracks.at(i).artist) && !string_in_vector(artists, tracks.at(i).artist)) {
            artists.push_back(tracks.at(i).artist);
            if (display)
                show_track(tracks.at(i), lt, cout);
            num++;
        }
    }
    return num;
}

int match_cds (const vector<Track>& tracks, string artist, bool display)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have an artist matching `artist`, where each (artist, cd) pair is only matched once
    if `display` is true, all matched tracks have been printed to `cout`
*/
    int num = 0;
    TrackDisplay lt = {true, true, true};
    vector<string> cds;
    for (int i = 0; i < ssize(tracks); i++) {
        if (match(artist, tracks.at(i).artist) && !string_in_vector(cds, tracks.at(i).cd)) {
            if (display)
                show_track(tracks.at(i), lt, cout);
            num++;
            cds.push_back(tracks.at(i).cd);
            cout << "HI" << endl;
        }
    }
    return num;
}

int number_of_cds (const vector<Track>& tracks)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have an unique (artist, cd) pair, where each pair is counted once
*/
    vector<string> seen_tracks;
    for(int i = 0; i < ssize(tracks); i++) {
        if(!string_in_vector(seen_tracks, tracks.at(i).cd)) {
            seen_tracks.push_back(tracks.at(i).cd);
        }
    }
    
    return ssize(seen_tracks);
}

int read_tracks (string filename, vector<Track>& tracks, bool show_content)
{// Precondition:
    assert (true);
/*  Postcondition:
    tracks is a copy of the tracks that are found in the file with file name filename, and result
    is the number of tracks that have been read.
    Only if show_content, then all read tracks are shown on screen.
*/
    int num_of_tracks = 0;
    ifstream input(filename);
    TrackDisplay lt = {true, true, true, true, true, true, true, true};

    while (!input.fail()) {
        Track in;
        input >> in;
        
        if (!input.fail()) {
            tracks.push_back(in);
            if (show_content) {
                show_track(tracks.at(ssize(tracks)-1), lt, cout);
            }
            num_of_tracks ++;
        }
    }

    return num_of_tracks;
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true) ;

    vector<Track> db;

    read_tracks("Tracks.txt", db, false);

    string command, target, purge;
    int hits = 0;

    do {
        cout << ">";
        cin >> command;

        if (command == "track") {
            getline(cin, target, '\n');
            target = target.substr(1, ssize(target));

            hits = match_tracks(db, target, true);
            cout << "Found " << hits << " hit(s)" << endl;
        }

        else if (command == "artist") {
            getline(cin, target, '\n');
            target = target.substr(1, ssize(target));

            hits = match_artists(db, target, true);
            cout << "Found " << hits << " hit(s)" << endl;
        }

        else if (command == "cds") {
            getline(cit, target, '\n');
            target = target.substr(1, ssize(target));

            hits = match_cds(db, target, true);
            cout << "Found " << hits << " hit(s)" << endl;
        }

        else if (command == "#cds") {
            hits = number_of_cds(db);
            cout << "Found " << hits << " CD(s)" << endl;
        }

        else if (command == "stop") {
            break;
        }
            
        else {
            cout << "That's not a valid command!" << endl;
        }

        if (command != "track" && command != "artist" && command != "cds") {
            getline(cin, purge);
        }


    }
    while (command != "stop");


	return 0;
}
#endif