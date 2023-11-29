#define NDEBUG // we must define this _before_ we include cassert
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <functional>

using namespace std;

int g_count = 0;

const int SLICE_STEP = 500; // The amount used when incrementing track sorting slices in each step
const int MAX_SLICE = 6500; // The maximum size of the tracks sorting slice (inclusive)

// Reuse your implementation from the mandatory assignment as a starting point.

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

typedef function<void(vector<Track>&)> SortFunc;

/**********************************************************************************************************
 *
 * input and output code from prior week:
 *
 *********************************************************************************************************/
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

ostream& operator<< (ostream& out, const Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of track is shown via out.
*/
    return out << track.artist << " - " << track.track << ". " << track.title
        << " (" << track.cd << ", " << track.year << ") [" << track.time << "]";
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

/**********************************************************************************************************
 *
 * (slice) helper function:
 *
 *********************************************************************************************************/
typedef Track El;                           // as explained in lecture, define algorithms on El

struct Slice
{  int from;     // from >= 0
   int length;   // length >= 0
};

Slice make_slice (int from, int length)
{// Precondition:
    assert (from >= 0 && length >= 0);
/*  post-condition:
    return slice with given from and length
*/
    Slice s = { from, length};
    return s;
}

Slice make_slice (const vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns the slice for the entire vector data.
*/
    Slice s = { 0, static_cast<int>( ssize (data) ) };
    return s;
}

bool valid_slice (Slice s)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if all selector values of s are not negative.
*/
    return 0 <= s.from && 0 <= s.length;
}
bool valid_slice (const vector<El>& data, Slice s)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if s is a valid slice for data
*/
    return valid_slice (s) && s.from + s.length <= ssize (data);
}

int first (Slice s)
{// Precondition:
    assert (valid_slice (s));
/*  Postcondition:
    result is index of first element in s (s.from)
*/
    return s.from;
}

int last (Slice s)
{// Precondition:
    assert (valid_slice (s));
/*  Postcondition:
    result is index of last element in s (s.from + s.length - 1)
*/
    return s.from + s.length - 1;
}

/**********************************************************************************************************
 *
 * compare operators:
 *
 *********************************************************************************************************/
bool operator== (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if all selector values of a are equal to their counterparts of b
*/
    g_count ++;
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track == b.track);
}

bool operator!= (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if any selector values of a are not equal to their counterparts of b
*/
    return !(a == b);
}

bool operator< (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    check the assignment for the proper definition of < on Tracks
*/
    g_count ++;
    if (a.artist < b.artist) {
        return true;
    }
    if (a.cd < b.cd && a.artist == b.artist) {
        return true;
    }
    if (a.year < b.year && a.cd == b.cd && a.artist == b.artist) {
        return true;
    }
    if (a.track < b.track && a.year == b.year && a.cd == b.cd && a.artist == b.artist) {
        return true;
    }
    return false;
}

bool operator>(const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if a does not precede b according to the ordering < on Tracks (don't forget to implement operator<)
*/
	return b < a;
}

bool operator<=(const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if a < b or a == b according to their definitions on Tracks (don't forget to implement operator< and operator==)
*/
	return a < b || a == b;
}

bool operator>=(const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if a > b or a == b according to their definitions on Tracks (don't forget to implement operator< and operator==)
*/
	return a > b || a == b;
}

bool is_sorted (const vector<El>& data, Slice s)
{// pre-condition:
    assert (valid_slice (data, s));
/*  post-condition:
    result is true if data.at(first (s)) <= data.at(first (s) + 1) ... data.at(last(s)-1) <= data.at(last(s))
*/
    int i;
    for (i = first(s); i < last(s); i++) {
        if (data.at(i) > data.at(i + 1)) {
            return false;
        }
    }
    return true;
}

void insert (vector<El>& data, Slice s)
{// Precondition:
    assert (valid_slice (data,s));
    assert (is_sorted (data, s));
    assert (last (s) < ssize (data) - 1);
/*  Postcondition:
    data.at (last (s)+1) is moved in data.at (first (s))...data.at (last (s)+1) and is_sorted (data, make_slice (s.from s.length+1))
*/
    Track key = data.at(last(s) + 1);
    int i;
    for (i = last(s); i >= first(s) && key < data.at(i); i--) {
        data.at(i + 1) = data.at(i);
    }
    data.at(static_cast<int>(i + 1)) = key;
}

void insertion_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement operator< and operator==)
*/
    int i;
    for (i = 0; i < ssize(data); i++) {
        insert(data, make_slice(0, i));
    }
}

/**********************************************************************************************************
 *
 * selection sort algorithm:
 *
 *********************************************************************************************************/
int max_value_at (const vector<El>& data, Slice s)
{// Precondition:
    assert (valid_slice (data, s));
    assert (s.length > 0);
/*  Postcondition:
    data.at (result) is the maximum of every element in data.at (first (s)) ... data.at (last (s))
*/
    int max_index = first(s);
    int i;
    for (i = first(s); i <= last(s); i++) {
        if (data.at(i) > data.at(max_index)) {
            max_index = i;
        }
        //cout << i << endl;
    }
    //cout << max_index << endl << endl;
    return max_index;
}

void selection_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement operator< and operator==)
*/
    g_count = 0;
    int j, index;
    Track temp;
    for (j = 0; j < ssize(data); j++) {
        index = max_value_at(data, make_slice(0, ssize(data) - j));
        swap(data.at(ssize(data) - j - 1), data.at(index));
    }
}

/**********************************************************************************************************
 *
 * bubble sort algorithm:
 *
 *********************************************************************************************************/
bool bubble (vector<El>& data, Slice unsorted)
{// Precondition:
    assert (valid_slice (data, unsorted));
/*  Postcondition:
    immediate pairs in data with slice unsorted are swapped if left element is larger than right element, and result is
    true only if this is done at least once (don't forget to implement operator< and operator==)
*/
    int i;
    bool swapped = false;
    for (i = unsorted.from; i < unsorted.from + unsorted.length - 1; i++) {
        if (data.at(i) > data.at(i+1)) {
            swap(data.at(i),data.at(i+1));
            swapped = true;
        }
    }

    return swapped;
}

void bubble_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement operator< and operator==)
*/
    Slice slice = {0, static_cast<int>(ssize(data))};
    bool running = true;
    do {
        running = bubble(data, slice);
        slice.length --;
    }
    while (running);
}

/**********************************************************************************************************
 *
 * heap sort algorithm:
 *
 *********************************************************************************************************/
int left_sibling (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the left sibling of an element at index i in a heap structured array/vector
*/
    return i-1;
}

int right_sibling (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the right sibling of an element at index i in a heap structured array/vector
*/
    return i+1;
}

int parent (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the parent of an element at index i in a heap structured array/vector
*/
    return (i-1) / 2;
}

int left_child (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the left child of an element at index i in a heap structured array/vector
*/
    return 2*(i+1)-1;
}

int right_child (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the right child of an element at index i in a heap structured array/vector
*/
    return 2*(i+1);
}

bool is_a_heap (const vector<El>& data, Slice s)
{// Precondition:
    assert (valid_slice (data,s));
/*  Postcondition:
    result is true only if all existing children in slice s of data have a value that is not greater than their parent
*/
    for (int i = s.from; i < s.from + s.length; i++) {
        if (data.at(i) > data.at(parent(i))) {
            return false;
        }
    }
    return true;
    
}

void push_up ( vector<El>& data, int elem )
{// Precondition:
    assert (0 <= elem && elem < ssize (data));
    assert(is_a_heap (data, make_slice (0,elem)));
/*  Postcondition:
    is_a_heap (data, make_slice (0, elem+1))
*/
    //cout << "parent: " << data.at(parent(elem)) << endl;
    //cout << "self: " << data.at(elem) << endl;
    bool swapping = data.at(elem) > data.at(parent(elem));
    while (swapping) {
        swap(data.at(parent(elem)), data.at(elem));
        elem = parent(elem);
        swapping = data.at(elem) > data.at(parent(elem));
    }
}

void build_heap ( vector<El>& data )
{// Precondition:
    assert (true );
/*  Postcondition:
    is_a_heap (data, make_slice (0, ssize (data)))
*/
    Slice slice = { 0, 2 };
    for (int i = 1; i < ssize(data); i++) {
        push_up(data, i);
    }
}

bool largest_child (const vector<El>& data, int parent, int unsorted, El& child, int& which)
{// Precondition:
    assert (0 <= unsorted && unsorted < ssize (data));
    assert (0 <= parent && parent < ssize (data));
/*  Postcondition:
    result is true only if the element at parent in data has one or two unsorted child elements;
    only in that case the value of the largest child is child and its index position is which
*/
    int largest = 0;
    int left = left_child(parent);
    int right = right_child(parent);
    if (left > unsorted) {
        return false;
    }
    if (right > unsorted) {
        child = data.at(left);
        which = left;
    }
    else if (data.at(left) > data.at(right)) {
        child = data.at(left);
        which = left;
    }
    else {
        child = data.at(right);
        which = right;
    }
    return true;
}

void push_down (vector<El>& data, int unsorted)
{// Precondition:
    assert(true);
    //assert (is_a_heap (data, make_slice (1,unsorted)));
    // assert fails for some reason while testing
/*  Postcondition:
    is_a_heap (data, make_slice (0,unsorted+1))
*/
    El child;
    int child_index;
    int current_index = 0;

    do {
        if (!largest_child(data, current_index, unsorted, child, child_index)) {
            break;
        }
        if (child > data.at(current_index)) {
            swap(data.at(child_index), data.at(current_index));
            current_index = child_index;
        }
        else {
            break;
        }
    }
    while (current_index < unsorted);
}

void pick_heap (vector<El>& data)
{// Precondition:
    assert (is_a_heap (data, make_slice (data)));
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement < and ==)
*/
    for (int i = data.size(); i > 2; i--) {
        swap(data.at(i-1), data.at(0));
        push_down(data, i-2);
    }
    swap(data.at(1), data.at(0));
}

void heap_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement < and ==)
*/
    build_heap(data);
    pick_heap(data);
}

/**********************************************************************************************************
 *
 * main function:
 *
 *********************************************************************************************************/
void get_slice(const vector<Track>& source, vector<Track>& dest, Slice sl) {
    assert(valid_slice(source, sl));

    for(int i = first(sl); i < last(sl); i++) {
        dest.push_back(source.at(i));
    }
}

void std_sort (vector<Track>& tracks)
{// Precondition:
    assert (true);
/*  Postcondition:
    `tracks` has been sorted using `std::sort`
*/
    sort(tracks.begin(), tracks.end());
}

void output_results(const vector<int>& counts, ofstream& os) {
    assert(true);
    // Post-condition
    /*This outputs all the values in vector counts and outputs them, separated by commas, to os*/

    for (int i = 0; i < ssize(counts); i++) {
        os << ',' << counts.at(i);
    }
    os << endl;
}

void generate_count_csv (
    const vector<Track>& tracks, const vector<Track>& sorted,
    const vector<Track>& random, const vector<Track>& reverse,
    ofstream& os, SortFunc sort)
{// Precondition:
    assert (os.is_open());
    assert (ssize(tracks) >= MAX_SLICE);
    assert (ssize(sorted) >= MAX_SLICE);
    assert (ssize(random) >= MAX_SLICE);
    assert (ssize(reverse) >= MAX_SLICE);
/*  Postcondition:
    A CSV file has been written to `os` based on measuring the amount of operations needed to sort growing slices of
    `tracks`, `sorted`, `random`, and `reverse`, using sorting function `sort`
*/
    // implement this function
}



void generate_time_csv (
    const vector<Track>& tracks, const vector<Track>& sorted,
    const vector<Track>& random, const vector<Track>& reverse,
    ofstream& os, SortFunc sort)
{// Precondition:
    assert (os.is_open());
    assert (ssize(tracks) >= MAX_SLICE);
    assert (ssize(sorted) >= MAX_SLICE);
    assert (ssize(random) >= MAX_SLICE);
    assert (ssize(reverse) >= MAX_SLICE);
/*  Postcondition:
    A CSV file has been written to `os` based on measuring the amount of time needed to sort growing slices of
    `tracks`, `sorted`, `random`, and `reverse`, using sorting function `sort`
*/
    // implement this function
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the program has generated the csvs of measurements obtained by sorting growing slices of the music databases
*/
    ifstream tracks_file("Tracks.txt");
    ifstream sorted_file("Tracks_sorted.txt");
    ifstream random_file("Tracks_random.txt");
    ifstream reverse_file("Tracks_reverse.txt");
    ofstream std_count_csv("measurements_count_stdsort.csv");
    ofstream heap_count_csv("measurements_count_heapsort.csv");
    ofstream std_time_csv("measurements_time_stdsort.csv");
    ofstream heap_time_csv("measurements_time_heapsort.csv");

    if(!tracks_file.is_open()) {
        cout << "Failed to open Tracks.txt" << endl;
        return 1;
    } else if(!sorted_file.is_open()) {
        cout << "Failed to open Tracks_sorted.txt" << endl;
        return 1;
    } else if(!random_file.is_open()) {
        cout << "Failed to open Tracks_random.txt" << endl;
        return 1;
    } else if(!reverse_file.is_open()) {
        cout << "Failed to open Tracks_reverse.txt" << endl;
        return 1;
    }

    vector<Track> tracks;
    vector<Track> sorted;
    vector<Track> random;
    vector<Track> reverse;
    Track track;

    cout << "Loading databases..." << endl;
    while(tracks_file >> track) {
        tracks.push_back(track);
    }

    while(sorted_file >> track) {
        sorted.push_back(track);
    }

    while(random_file >> track) {
        random.push_back(track);
    }

    while(reverse_file >> track) {
        reverse.push_back(track);
    }

    cout << "Generating heap_sort operation count measurements..." << endl;
    generate_count_csv(tracks, sorted, random, reverse, heap_count_csv, heap_sort);
    cout << "Generating std_sort operation count measurements..." << endl;
    generate_count_csv(tracks, sorted, random, reverse, std_count_csv, std_sort);
    cout << "Generating heap_sort time measurements..." << endl;
    generate_time_csv(tracks, sorted, random, reverse, heap_time_csv, heap_sort);
    cout << "Generating std_sort time measurements..." << endl;
    generate_time_csv(tracks, sorted, random, reverse, std_time_csv, std_sort);

    return 0;
}
#endif
