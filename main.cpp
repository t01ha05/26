//set up main function structure
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

//file name and test code constant
const string FILE_NAME = "codes.txt";
const string TEST_CODE = "TESTCODE";

//function prototypes for operations on vector list and set
void readVector(vector<string>& vecCodes, long long& timeTaken);
void readList(list<string>& listCodes, long long& timeTaken);
void readSet(set<string>& setCodes, long long& timeTaken);
void sortVector(vector<string>& vecCodes, long long& timeTaken);
void sortList(list<string>& listCodes, long long& timeTaken);
void insertVector (vector<string>&vecCodes, long long& timeTaken);
void insertList(list<string>& listCodes, long long& timeTaken);
void insertSet(set<string>& setCodes, long long& timeTaken);
void deleteVector(vector<string>& vecCodes, long long& timeTaken);
void deleteList (list<string>& listCodes, long long& timeTaken);
void deleteSet (set<string>& setCodes, long long& timeTaken);
string formatTime(long long timeTaken);

int main() {
    //containers to store codes from the file
    vector<string> vecCodes;
    list<string> listCodes;
    set<string> setCodes;
    
    //structure to store time taken for each operation
    struct Timings {
        long long readTime;
        long long sortTime;
        long long insertTime;
        long long deleteTime;
    };

    //initializing time structure for vector list and set
    Timings vecTimings = {0, 0, 0, 0};
    Timings listTimings = {0, 0, 0, 0};
    Timings setTimings = {0, 0, 0 ,0};

    //reading data from file to vec list and set
    readList(listCodes, listTimings.readTime);
    readVector(vecCodes, vecTimings.readTime);
    readSet(setCodes, setTimings.readTime);

    //sorting vector and list but not set
    sortList(listCodes, listTimings.sortTime);
    sortVector(vecCodes, vecTimings.sortTime);
    setTimings.sortTime = -1;

    //inserting test code into middle of vector list and set
    insertVector(vecCodes, vecTimings.insertTime);
    insertList(listCodes, listTimings.insertTime);
    insertSet(setCodes, setTimings.insertTime);

    //deleteing middle element from vector list and test code from set
    deleteVector(vecCodes, vecTimings.deleteTime);
    deleteList(listCodes, listTimings.deleteTime);
    deleteSet(setCodes, setTimings.deleteTime);

    //OUTPUT timing results from each operation
    cout << setw(5) << "Operation" << setw(5) << "Vector" << setw(5) << "List" << setw(5) << "Set" <<endl;
    cout << setw(5) << "Read" << setw(5) << formatTime(vecTimings.readTime) << setw(5) << formatTime(listTimings.readTime) << setw(5) << formatTime(setTimings.readTime) << endl;
    cout << setw(5) << "Sort" << setw(5) << formatTime(vecTimings.sortTime) << setw(5) << formatTime(listTimings.sortTime) <<setw(5) << formatTime(setTimings.sortTime) << endl;
    cout << setw(5) << "Insert" << setw(5) << formatTime(vecTimings.insertTime) << setw(5) << formatTime(listTimings.insertTime) << setw(10) << formatTime(setTimings.insertTime) << endl;
    cout << setw(5) << "Delete" << setw(5) << formatTime(vecTimings.deleteTime) << setw(5) << formatTime(listTimings.deleteTime) << setw(10) << formatTime(setTimings.deleteTime) << endl;

    return 0;
}

//function to read strings from file into vector
void readVector(vector<string>& vecCodes, long long& timeTaken) {
    ifstream inFile(FILE_NAME);
    //checl if file opens
    if (!inFile) {
        cerr << "Error opening file: " << FILE_NAME << endl;
        exit(1); //exit if cannot be opened

    }

    string code;
    auto start = high_resolution_clock::now(); //start time
    while (getline(inFile, code)) {
        vecCodes.push_back(code); //add each line to vector
    }  
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<milliseconds>(end - start).count();

    inFile.close(); //close the file
}

//
void readList(list<string>& listCodes, long long& timeTaken){
    ifstream inFile(FILE_NAME);

    if(!inFile) {
        cerr << "Error" << FILE_NAME << endl;
        exit(1);
    }

    string code;
    auto start = high_resolution_clock::now();
    while (getline(inFile, code)) {
        listCodes.push_back(code);
    }
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<milliseconds>(end - start).count();

    inFile.close();

}

void readSet(set<string>& setCodes, long long& timeTaken) {
    ifstream inFile(FILE_NAME);

    if(!inFile) {
        cerr << "Error opening file: "<< FILE_NAME << endl;
        exit(1);
    }

    string code;
    auto start = high_resolution_clock::now();
    while (getline(inFile, code)) {
        setCodes.insert(code);
    }
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<milliseconds>(end - start).count();

    inFile.close();
}

//implement sorting func
void sortVector (vector<string>& vecCodes, long long& timeTaken) {
    auto start = high_resolution_clock::now();
    sort(vecCodes.begin(), vecCodes.end());
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<milliseconds>(end - start).count();
}
//add sortlist and sortset (placeholder)
void sortList(list<string>& listCodes, long long& timeTaken){
    auto start = high_resolution_clock::now();
    listCodes.sort();
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<milliseconds>(end - start).count();
}
void insertVector(vector<string>& vecCodes, long long& timeTaken){
    size_t midPos = vecCodes.size() / 2;

    if(vecCodes.empty()) {
        midPos = vecCodes.size();
    }
    auto start = high_resolution_clock::now();
    vecCodes.insert(vecCodes.begin() + midPos, TEST_CODE);
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<microseconds>(end - start).count();
}

//add insert functions
void insertList(list<string>& listCodes, long long& timeTaken) {
    auto it = listCodes.begin();
    advance(it, listCodes.size() / 2);
    auto start = high_resolution_clock::now();
    listCodes.insert(it, TEST_CODE);
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<microseconds>(end - start).count();
}

void insertSet(set<string>& setCodes, long long& timeTaken) {
    auto start = high_resolution_clock::now();
    setCodes.insert(TEST_CODE);
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<microseconds>(end - start).count();
}

void deleteVector (vector<string>& vecCodes, long long& timeTaken) {
    size_t midPos= vecCodes.size()/2;
    auto start = high_resolution_clock::now();
    if (!vecCodes.empty() && midPos < vecCodes.size()) {
        vecCodes.erase(vecCodes.begin() + midPos);
    }
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<microseconds>(end - start).count();
}

void deleteList (list<string>& listCodes, long long& timeTaken) {
    auto it = listCodes.begin();
    advance(it, listCodes.size() / 2);

    auto start = high_resolution_clock::now();
    if (it != listCodes.end()) {
        listCodes.erase(it);
    }
}


//add delete functions 

void deleteSet(set<string>& setCodes, long long& timeTaken) {
    auto start = high_resolution_clock::now();
    setCodes.erase(TEST_CODE);
    auto end = high_resolution_clock::now();
    timeTaken = duration_cast<microseconds>(end - start).count();
}
//add formTime function to display timing result

string formatTime(long long timeTaken) {
    if (timeTaken == -1)
        return "-1";
    else
        return to_string(timeTaken) + " ms";
}