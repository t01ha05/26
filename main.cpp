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
const int SIMULATIONS = 15;


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
void calculateAverages(long long results[SIMULATIONS][4][3], long long avgResults[4][3]);


int main() {
    vector<string> vecCodes;
    list<string> listCodes;
    set<string> setCodes;
    
    long long results[SIMULATIONS][4][3] = {0}; // this will store the time taken for each operation on each data structure
    long long avgResults[4][3]

    //RUN SIMULATION
    for (int sim = 0; sim < SIMULATIONS; ++sim) {

    //structure to store time taken for each operation
    struct Timings {
        long long readTime, sortTime, insertTime, deleteTime;

    };
    


    //initializing time structure for vector list and set
    Timings vecTimings = {0, 0, 0, 0};
    Timings listTimings = {0, 0, 0, 0};
    Timings setTimings = {0, 0, 0 ,0};

    //reading data from file to vec list and set
    readList(listCodes, listTimings.readTime);
    readVector(vecCodes, vecTimings.readTime);
    results[sim][0][0] = vecTimings.readTime; //store vector read time for simulation
    readSet(setCodes, setTimings.readTime);

    //sorting vector and list but not set
    sortList(listCodes, listTimings.sortTime);
    sortVector(vecCodes, vecTimings.sortTime);
    setTimings.sortTime = -1;

    //inserting test code into middle of vector list and set
    insertVector(vecCodes, vecTimings.insertTime);
    insertList(listCodes, listTimings.insertTime);
    insertSet(setCodes, setTimings.insertTime);

    readVector(vecCodes, readTime);
    results[sim][0][0] = readTime;
    
    readList(listCodes, readTime);
    results[sim][0][1] = readTime;
    
    readSet(setCodes, readTime);
    results[sim][0][2] = readTime;
    
    sortVector(vecCodes, sortTime);
    results[sim][1][0] = sortTime;

    sortList(listCodes, sortTime);
    results[sim][1][1] = sortTime;

    sortList(setCodes, sortTime);
    results[sim][1][2] = sortTime;

    insertVector(vecCodes, insertTime);
    results[sim][2][0] = insertTime;

    insertList(listCodes, insertTime);
    results[sim][2][1] = insertTime;

    insertSet(setCodes, insertTime);
    results[sim][2][2] = insertTime;

    deleteVector(vecCodes, deleteTime);
    results[sim][3][0] = deleteTime;

    deleteList(listCodes, deleteTime);
    results[sim][3][1] = deleteTime;

    deleteSet(setCodes, deleteTime);
    results[sim][3][2] = deleteTime;
    }
    
    void calculateAverages(long long results[SIMULATIONS][4][3], long long avgResults[4][3]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; ++j) {
                long long sum = 0;
                for (int k = 0; k < SIMULATIONS; ++k) {
                    sum += results[k][i][j];
                }
                avgResults[i][j] = sum / SIMULATIONS;
            }
        }
    }
    
    //OUTPUT timing results from each operation
    cout << setw(5) << "Operation" << setw(5) << "Vector" << setw(5) << "List" << setw(5) << "Set" <<endl;
    cout << setw(5) << "Read" << setw(5) << formatTime(vecTimings.readTime) << setw(5) << formatTime(listTimings.readTime) << setw(5) << formatTime(setTimings.readTime) << endl;
    cout << setw(5) << "Sort" << setw(5) << formatTime(vecTimings.sortTime) << setw(5) << formatTime(listTimings.sortTime) <<setw(5) << formatTime(setTimings.sortTime) << endl;
    cout << setw(5) << "Insert" << setw(5) << formatTime(vecTimings.insertTime) << setw(5) << formatTime(listTimings.insertTime) << setw(10) << formatTime(setTimings.insertTime) << endl;
    cout << setw(5) << "Delete" << setw(5) << formatTime(vecTimings.deleteTime) << setw(10) << formatTime(listTimings.deleteTime) << setw(10) << formatTime(setTimings.deleteTime) << endl;

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