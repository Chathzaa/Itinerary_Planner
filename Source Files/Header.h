//#pragma once

#ifndef Header_h
#define Header_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


using namespace std;

//extern Trip current;

struct User {
    string username;
    string password;
    string Contact_Details;
};

class Stack {
public:
    int capacity;
    int top;
    int* data;

    Stack();
    ~Stack();
    void push(int val);
    void pop();
    int topValue() const;
    bool empty() const;
};

class Des_Lis_Q {
public:
    int front;
    int rear;
    int size;
    int capacity = 100;
    string* dest;

    Des_Lis_Q() {
        size = 0;
        front = 0;
        rear = 0;
        dest = new string[capacity];
    }
    void enQueue(string val) {
        dest[rear] = val;
        rear = (rear + 1) % capacity;
        size++;
    }

    void cancel() {
        while (size != 0) {
            string temp = dest[front];
            front = (front + 1) % capacity;
            size--;
        }
        //cout << "Trip is deleted sucessfully" << endl;

    }
    
    void print() {
        int index = front;
        for (int i = 0; i < size; i++) {
            cout << dest[index] << endl;
            index = (index + 1) % capacity;
        }
        cout << endl;
        
    }

    

    //Function for saving trip data for users
    void saveToFile(string username,bool isPublic,string Date, const string& filename) const {

        ofstream outputFile(filename, ios::app);  // Append mode to add new lines for each queue
        if (!outputFile.is_open()) {
            cerr << "Error: Unable to open the file " << filename << " for writing." << endl;
            return;
        }

        outputFile << username;
        outputFile << ",";
        outputFile << isPublic;
        outputFile << ",";
        outputFile << Date;
        outputFile << ",";


        for (int i = 0; i < size; i++) {
            outputFile << dest[(front + i) % capacity];
            if (i < size - 1) {
                outputFile << ","; // Add a comma between values
            }
        }

        outputFile << "\n";  // New line for each queue

        cout << "Trip saved to " <<  " successfully." << endl;
        system("cls");
        
    }

    void loadUserFav(const string& filename, string user) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
            return;
        }

        cancel(); // Clear existing data
        
        //previous code. just uncomment and new code after this
        /*cancel(); // Clear existing data
        string line;           
        while (getline(inputFile, line, ',')) {
            enQueue(line);
        }*/

        /*while (inputFile.good()) {
            getline(inputFile, line, ',');
            if (line == "a") {
                getline(inputFile, line);
                enQueue(line);
            }
            else {
                getline(inputFile, line);
            }
        }*/


        string line;
        int cnt = 0;
        while (getline(inputFile, line)) {
            istringstream lineStream(line);
            string column;
            getline(lineStream, column, ',');
            
            if (column == user) {
                cnt++;
                while (getline(lineStream, column, ',')) { //skips 2nd column
                    cout << cnt << "\t";
                    getline(lineStream, column, ','); // Skips 3rd column
                    
                    //enqueue from 4th column onwards
                    while (getline(lineStream, column, ',')) {
                        //enQueue(column);
                        cout << column << "   ";
                    }
                    cout << endl;
                }
            }
            
        }
    }

    void delUserFav(int num, string username, const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
            return;
        }

        vector<string> temp_Data; //This stores the filtered lines of data
                                  //to be rewritten when overwriting "trip.csv"
        

        string line;
        int counter = 0;
        while (getline(inputFile, line)) {
            istringstream lineStream(line);
            string column;
            getline(lineStream, column, ',');

            if (column == username) {
                counter++;
                if (counter != num) {
                    temp_Data.push_back(line);
            }
                
            
            }
            else {
                temp_Data.push_back(line);
            }
        }

        inputFile.close();

        ofstream outputFile(filename, ios::trunc); 
        if (!outputFile.is_open()) {
            cerr << "Error: " << filename << " is unresponsive" << endl;
            return;
        }
        
        for(const auto& updatedLine: temp_Data){
            outputFile << updatedLine << endl;
        }

        outputFile.close();

        
    }
    

    ~Des_Lis_Q() {
        delete[] dest;
    }

};


class Trip {
public:
    Des_Lis_Q cur_trip; //contains the list of location to be visited
    string username;//Contains exactly the member of Struct User X
    string Date;                   //X.username = this->username
    void print() {
        cur_trip.print();
        cout << endl;
        cout << username << endl;
        cout << Date << endl;
    }

    bool isPublic = false;

};

void saveUser(User& user);
bool userExists(string& username, string& password);
void MainMenu();
void displayMainMenuScreen();
void Plan_A_Trip(Stack& screenStack);
void Find_A_Trip(string user);
void rootscreen();
void choose_des(Stack& screenStack);
void cout_loc(string start);
vector<pair<string, double>> sort_Loc(map<string, double> A);
void printDestList(vector<pair<string, double>> B);
void favTrip(Stack& screenStack);


#endif 

