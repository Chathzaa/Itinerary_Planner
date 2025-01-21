
#ifndef Header_h
#define Header_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


using namespace std;


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

    //constructor
    Des_Lis_Q();
    void enQueue(string val);
    void cancel();
    void print();
    void saveToFile(string username, bool isPublic, string Date, const string& filename);
    void loadUserFav(const string& filename, string user);
    void delUserFav(int num, string username, const string& filename);


    

    ~Des_Lis_Q() {
        delete[] dest;
    }

};


class Trip {
public:
    Des_Lis_Q cur_trip; //contains the list of location to be visited
    string username;//Contains exactly the member of Struct User X
    string Date;                   //X.username = this->username
    void print();
    
    
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
string get_Contact(string user);


#endif 

