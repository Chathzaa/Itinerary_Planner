#include "Header.h"
#include "map_header.h"
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

Trip current; //Current trip which user is building


void saveUser(User& user) {
    fstream UserFile;
    UserFile.open("Users.csv", ios::app);
    if (UserFile.is_open()) {
        UserFile << user.username << ',' << user.password << ',' << user.Contact_Details << '\n';
        UserFile.close();
    }
    else {
        "Error: Failed to open the UserFile.\n";
        cout << endl;
    }
}

Des_Lis_Q::Des_Lis_Q() {
    size = 0;
    front = 0;
    rear = 0;
    dest = new string[capacity];
}

void Des_Lis_Q::enQueue(string val) {
    dest[rear] = val;
    rear = (rear + 1) % capacity;
    size++;
}

void Des_Lis_Q::cancel() {
    while (size != 0) {
        string temp = dest[front];
        front = (front + 1) % capacity;
        size--;
    }

}

void Des_Lis_Q::print() {
    int index = front;
    for (int i = 0; i < size; i++) {
        cout << dest[index] << endl;
        index = (index + 1) % capacity;
    }
    cout << endl;

}



//Function for saving trip data for users
void Des_Lis_Q::saveToFile(string username, bool isPublic, string Date, const string& filename) {

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

    cout << "Trip saved to " << " successfully." << endl;


}

void Des_Lis_Q::loadUserFav(const string& filename, string user) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open the file " << filename << " for reading." << endl;
        return;
    }

    cancel(); // Clear existing data



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

void Des_Lis_Q::delUserFav(int num, string username, const string& filename) {
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

    for (const auto& updatedLine : temp_Data) {
        outputFile << updatedLine << endl;
    }

    outputFile.close();


}

void Trip::print() {
    cur_trip.print();
    cout << endl;
    cout << username << endl;
    cout << Date << endl;
}


Stack::Stack() {
    capacity = 100;
    data = new int[capacity];
    top = -1;
}

Stack::~Stack() {
    delete[] data;
}

void Stack::push(int val) {
    if (top < capacity - 1) {
        data[++top] = val;
    }
    else {
        cout << "Stack overflow! Cannot push element." << endl;
    }
}

void Stack::pop() {
    if (top >= 0) {
        top--;
    }
    else {
        cout << "Stack underflow! Cannot pop element." << endl;
    }
}

int Stack::topValue() const {
    if (top >= 0) {
        return data[top];
    }
    else {
        throw runtime_error("Stack is empty");
    }
}

bool Stack::empty() const {
    return top == -1;
}

void rootscreen() {
    vector<User> users;
    Stack screenStack;
    int SignUp_IN;

    do {
        cout << endl;
        cout << endl;
        cout<<"===================================Welcome to WayWander===================================" << endl;
        cout << endl;
        cout << "Choose an option" << endl;
        cout << endl;
        cout << "1. Sign up" << endl;
        cout << endl;
        cout << "2. Log in" << endl;
        cout << endl;
        cout << "Enter Your Choice: ";
        cin >> SignUp_IN;
        bool test = 1;
        system("cls");
        if (SignUp_IN == 1) {


            User newUser;
            cout << "Ready to embark on your journey? " << endl;
            cout << endl;
            cout<<"Secure your spot now and let's plan for adventure! :‑)" << endl;
            cout << endl;
            cout << "Enter a username: ";
            cin >> newUser.username;
            cout << endl;
            cout << "Enter a password: ";
            cin >> newUser.password;
            cout << endl;
            cout << "Enter your Contact Details: ";
            cin >> newUser.Contact_Details;
            cout << endl;
            saveUser(newUser);
            users.push_back(newUser); //vector
            displayMainMenuScreen();
            cout << "Account created successfully" << endl;
            cout << endl;


        }
        else if (SignUp_IN == 2) {
            cout << "==========Heyy!!Welcome back!==========" << endl;
            cout << endl;
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << endl;
            cout << "Enter your password: ";
            cin >> password;
            cout << endl;

            if (userExists(username, password)) {
                current.username = username;
                displayMainMenuScreen();
                cout << "login successful! :)" << endl;
                cout << endl;

                while (test == 1) {
                    int choice;
                    MainMenu();

                    cin >> choice;

                    switch (choice) {
                    case 1:
                        // Code for "Plan a Trip" goes here.
                        displayMainMenuScreen();
                        Plan_A_Trip(screenStack);
                        break;
                    case 2:
                        // Code for "Find a Trip" goes here.
                        displayMainMenuScreen();
                        Find_A_Trip(current.username);
                        
                        break;
                    case 3:
                        // Code for "Favorite Trips" goes here.
                        displayMainMenuScreen();
                        favTrip(screenStack);
                        //favTrip();
                        //current.cur_trip.print(); //**********************************************
                        
                        break;
                    case 4:
                        // Logout option. You can add code to log the user out and return to the welcome screen.
                        displayMainMenuScreen();
                        test = 0;
                        cout << "Logging out." << endl;
                        //test2 = 1;
                        break;
                    default:
                        cout << "Invalid choice. Please select a valid option." << endl;
                    }

                }//end of inner while loop

            }
            else {
                cout << "Login failed! :( ";
                displayMainMenuScreen();
            }
        }
        else {
            cout << "Invalid Option ";
        }

    } while (SignUp_IN != 4);
}

bool userExists(string& username, string& password) {
    fstream UserFile("Users.csv", ios::in);
    if (UserFile.is_open()) {
        string line;
        while (getline(UserFile, line)) {//read line by line and stores the lines to line variable 
            string storedUsername, storedPassword;
            istringstream lineStream(line);
            getline(lineStream, storedUsername, ',');
            getline(lineStream, storedPassword, ',');
            if (username == storedUsername) {
                if (password == storedPassword) {
                    return true;

                }
                else {
                    cout << "Incorrect Password" << endl;
                    UserFile.close();
                    return false;
                }
            }
        }
        UserFile.close();
    }
    return false;
}

void MainMenu() {
    cout << "Main Menu" << endl;
    cout << endl;
    cout << "1. Plan a Trip" << endl;
    cout << "2. Find a Trip" << endl;
    cout << "3. Favorite Trips" << endl;
    cout << "4. Logout" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

void displayMainMenuScreen() {
    system("cls");

}

void Find_A_Trip(string username) {
    string Date;
    string Loc;
    ifstream inputFile("trip.csv");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open the file " << "trip.csv" << " for reading." << endl;
        return;
    }
    cout << "Find the Trip you like" << endl;
    cout << endl;                                       //new code marked
    cout << "Enter the Date(DD/MM/YY): ";
    cout << "(No specific date on mind? Press 'n' to skip)" << endl << endl;
    cin >> Date;
    displayMainMenuScreen();
    cout << "Where you planning to head at? " << endl; //
    cout << "1. Galle" << endl; //
    cout << "2. Kandy" << endl; //
    cout << "(No specific date on mind? Press 'n' to skip)" << endl << endl;    //
    cin >> Loc;


    if ((Date != "n") && (Loc == "n")) { //When date is given, but no specific destination
        displayMainMenuScreen();
        string line;
        while (getline(inputFile, line)) {  //take line from trip.csv
            istringstream lineStream(line);
            string column;
            string column2;
            string column3;

            string date;
            getline(lineStream, column, ',');   //column = username
            getline(lineStream, column2, ',');  //column2 = public or private (1 or 0)
            if (column != username && column2 == "1") {  //if this line doesnt contain user's own data AND if line contains public data -> go

                getline(lineStream, date, ',');          //date = date of line
                if (date == Date) {                      //->go
                    cout << "Travel Buddy: " << column << "   "; //print username (creater of trip)
                    cout << "\t" << "Contact now! : " << get_Contact(column);
                    cout << endl;
                    cout << "Plan for the day: " << endl;
                    while (getline(lineStream, column3, ',')) {  //start reading the visiting locations one by one: *continuing from column 4
                        //enQueue(column);

                        //getline(lineStream, column3, ',');
                        cout << column3 << "   ";                //print remaining columns starting from 4, until end of line in loop
                    }

                }
                cout << endl;
                cout << endl;
            }
        }
    }

    else if ((Date == "n") && (Loc == "n")) {
        displayMainMenuScreen();
        string line;
        int count = 0;
        cout << endl << endl << endl << endl << endl;
        while (getline(inputFile, line)) {
            
            istringstream lineStream(line);
            string column;
            string column2;
            string column3;
            string date;
            
            getline(lineStream, column, ',');   //column = username
            getline(lineStream, column2, ',');  //column2 = public or private (1 or 0)
            if (column != username && column2 == "1") {
                
                getline(lineStream, date, ','); // Read the Date field directly
                
                count += 1;
                cout << count << ". ";
                cout << "Travel Buddy     : " << column ; //print username (creater of trip)
                cout << "\t" << "Contact now! : " << get_Contact(column);
                cout<<endl;
                cout << "   Plan for the day : " ;

                // Read the rest of the line, starting from the Loc field (assuming it's the 4th column)
                while (getline(lineStream, column3, ',')) {
                    
                    cout << column3 << "   "; //print remaining columns starting from 4, until the end of the line in loop
                    
                }
                cout << endl;
                cout << endl;
                
                
            }
        }
    }
    
    else if ((Date == "n") && (Loc != "n")) {           //when location is given with no date 
        displayMainMenuScreen();
        string line;
        int count = 0;
        while (getline(inputFile, line)) {          //take line from trip.csv
            istringstream lineStream(line);
            string column;
            string column2;
            string column3;
            string date;
            string loc;

            getline(lineStream, column, ',');   //column = username
            getline(lineStream, column2, ',');  //column2 = public or private (1 or 0)
            if (column != username && column2 == "1") {
                getline(lineStream, date, ','); // Read the Date field directly
                getline(lineStream, loc, ','); //Take start point (galle or kandy) to loc
                if (Loc == "1" && loc == "galle_fort") {
                    count += 1;
                    cout << count << ". ";
                    cout << "Travel Buddy: " << column << "   "; //print username (creater of trip)
                    cout << "\t" << "Contact now! : " << get_Contact(column);
                    cout << endl;
                    cout << "Plan for the day: " << endl;

                    while (getline(lineStream, column3, ',')) {  //start reading the visiting locations one by one: *continuing from column 4

                        cout << column3 << "   ";                //print remaining columns starting from 4, until end of line in loop

                    }
                    cout << endl;
                }
                else if (Loc == "2" && loc == "kandy_station") {
                    count += 1;
                    cout << count << ". ";
                    cout << "Travel Buddy: " << column << "   "; //print username (creater of trip)
                    cout << "\t" << "Contact now! : " << get_Contact(column);
                    cout << endl;
                    cout << "Plan for the day: " << endl;

                    while (getline(lineStream, column3, ',')) {  //start reading the visiting locations one by one: *continuing from column 4

                        cout << column3 << "   ";                //print remaining columns starting from 4, until end of line in loop

                    }
                    cout << endl;
                    cout << endl;
                }

            }
        }
    }

    else if ((Date != "n") && (Loc != "n")) { // when location and date are both user defined for search
        displayMainMenuScreen();
        string line;
        int count = 0;
        while (getline(inputFile, line)) {          //take line from trip.csv
            istringstream lineStream(line);
            string column;
            string column2;
            string column3;
            string date;
            string loc;

            getline(lineStream, column, ',');   //column = username
            getline(lineStream, column2, ',');  //column2 = public or private (1 or 0)

            if (column != username && column2 == "1") {
                getline(lineStream, date, ','); // Take the Date for the trip
                getline(lineStream, loc, ','); //Take start point (galle or kandy) to loc
                if (Loc == "1" && loc == "galle_fort" && date == Date) {
                    count += 1;
                    cout << count << ". ";
                    cout << "Travel Buddy: " << column << "   "; //print username (creater of trip)
                    cout << "\t" << "Contact now! : " << get_Contact(column);
                    cout << endl;
                    cout << "Plan for the day: " << endl;

                    while (getline(lineStream, column3, ',')) {  //start reading the visiting locations one by one: *continuing from column 4

                        cout << column3 << "   ";                //print remaining columns starting from 4, until end of line in loop

                    }
                    cout << endl;
                }
                if (Loc == "2" && loc == "kandy_station" && date == Date) {
                    count += 1;
                    cout << count << ". ";
                    cout << "Travel Buddy: " << column << "   "; //print username (creater of trip)
                    cout << "\t" << "Contact now! : " << get_Contact(column);
                    cout << endl;
                    cout << "Plan for the day: " << endl;

                    while (getline(lineStream, column3, ',')) {  //start reading the visiting locations one by one: *continuing from column 4

                        cout << column3 << "   ";                //print remaining columns starting from 4, until end of line in loop

                    }
                    cout << endl;
                    cout << endl;

                }

            }
        }
        }

    system("pause");
    displayMainMenuScreen();
    
}



void Plan_A_Trip(Stack& screenStack) {
    bool planningTrip = true;
    screenStack.push(1);
    while(planningTrip){
    cout << "===================Plan your perfect trip by choosing destinations <3 ====================" << endl;
    cout << endl;
    cout << "1.Enter your preferred date and let the countdown to your unforgettable adventure begin!" << endl;
    cout << endl;
    cout << "2. Back to the main menu "<<endl;
    int choice;
    cout << endl << "enter choice: ";
    cin >> choice;

    switch (choice){
    case 1:
        displayMainMenuScreen();
        screenStack.push(2);
        cout << "Enter preffered Date(DD/MM/YY): " << endl;
        cin >> current.Date;
        cout << endl;
    cout << "Choose Destination" << endl;
    choose_des(screenStack);
    break;
    case 2:
        // check if there's a previous screen on the stack
        if (!screenStack.empty()) {
            displayMainMenuScreen();
            screenStack.pop(); // Pop the current screen
            if (!screenStack.empty()) {
                // Display previous screens based on what's on the top of stack
                int previousScreen = screenStack.topValue();
                switch (previousScreen) {
                case 1:

                    displayMainMenuScreen();
                    break;
                    
                }
            }
            if (!screenStack.empty()) {
                screenStack.pop();
            }
            else {
                planningTrip = false;
            }// Exit the loop
        }
        else {
            cout << "Cannot go back further. Stack is empty." << endl;
        }
        break;
    default:
        cout << "Invalid choice. Please select a valid option." << endl;
    }
    }
}
     
    

void choose_des(Stack& screenStack) {
    displayMainMenuScreen();//clear screen
    //string nearest_town;
    int destination;
    screenStack.push(3);
    
    bool Selecting_Destinations = true;
    while(Selecting_Destinations){

    cout << "1. Galle" << endl;
    cout << "2. Kandy" << endl;
    cout << "Enter the preffered destination" << endl;
    cout << "Enter 0 to go back";
    cout << endl;
    cin >> destination;
    displayMainMenuScreen();//clear screen
    
    if (destination == 1) {
        //cout destinations in galle
        cout_loc("galle_fort");
        
    }
    else if (destination == 2) {
        //cout destinations in Kandy
        cout_loc("kandy_station");
    }
    else if (destination == 0) {
        if (!screenStack.empty()) {
            screenStack.pop();
            Selecting_Destinations = false;
        }
        else {
            cout << "Cannot go back further. Stack is empty." << endl;
        }
    }
    else {
        //incorrect and write the loop
        cout <<"Enter valid option"<< endl;
    }
    } //while (destination != 1 && destination != 2);
    if (!screenStack.empty()) {
        screenStack.pop();
    }

    

}



void cout_loc(string start) {
    
    Graph Test1;
    Test1.readFrom_connectionsFile("connections.csv");

    auto x = sort_Loc(Test1.dijkstra(Test1.roads, start)); //x is a map in the form of
                                                           //map<string, double>
    
    current.cur_trip.enQueue(start);  //copy starting point as first location
                                        //of the trip list (Des_Lis_Q)
    int nextStop;
    do {
        cout << "Choose the Attraction you'd like to visit " << endl;
        printDestList(x);
        cin >> nextStop; //enter the user's next preffered destination
        displayMainMenuScreen(); // clear screen
        if (nextStop != 0 && nextStop != 99) {
            string nextStop_str = x[nextStop - 1].first;
            current.cur_trip.enQueue(nextStop_str); //keep adding to the trip list (Des_Lis_Q)
            auto p1 = Test1.dijkstra(Test1.roads, nextStop_str);
            x = sort_Loc(p1);

        }
        else if(nextStop==0){
            current.cur_trip.cancel();
            displayMainMenuScreen();

            current.cur_trip.print();
        }

        else if (nextStop == 99) {
            cout << "Ready to share your adventure? Turn your trip into a public journey for others to join!!!" << endl;
            cout << "1.Yes,make it public!" << endl;
            cout << "2.No,Keep it private" << endl;
            cout << "Choose an option" << endl;

            string response;
            cin >> response;

            if (response == "1") {
                current.isPublic = true;
               
            }
            else
            {
                current.isPublic = false;
                
            }
            
            current.cur_trip.saveToFile(current.username, current.isPublic, current.Date, "trip.csv");

            current.cur_trip.cancel();

            
          
        }
        

    } while (nextStop != 0 && nextStop != 99);//stop creating the trip
}

vector<pair<string, double>> sort_Loc(map<string, double> A) {
    vector<pair<string, double>> B;//vector which stores the locations in a sorted method (ascending order of distances)

    //to remove the 0 distance location(itself). One individual loop is run.
    double minValue_O = INFINITY;
    string minKey_O;
    for (auto it = A.begin(); it != A.end(); ++it) {
        if (it->second <= minValue_O) {
            minValue_O = it->second;
            minKey_O = it->first;
        }
    }
    A.erase(minKey_O);
    //************************end of individual loop
    
    while (!A.empty()) {
        double minValue = INFINITY;
        string minKey;

        // Find the minimum value in map A
        for (auto it = A.begin(); it != A.end(); ++it) {
            if (it->second <= minValue) {
                minValue = it->second;
                minKey = it->first;
            }
        }

        // Insert the minimum value into map B
        if (minValue != INFINITY) {
            B.push_back({ minKey, minValue });
        }

        // Erase the corresponding entry from map A
        A.erase(minKey);
    }
   
    return B;

    
}

void printDestList(vector<pair<string, double>> B){
int i = 1;
for (const auto& entry : B) {
    cout << i << ". " << entry.first << " : " << entry.second << " km away" << endl;
    ++i;
}

cout << "Press 0 anytime to cancel the trip" << endl;
cout << "Press 99 to Save the trip." << endl;

}

void favTrip() {


    cout << "=========Your favourite Trips=========" << endl;
    cout << endl;
    current.cur_trip.loadUserFav("trip.csv", current.username);
    cout << endl;
    cout << "1. Delete from favourites " << endl;
    cout << "0. Go back" << endl;
    cout << endl;
    cout << "Enter choice " << endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << endl;
        cout << "Which plan do you wanna scratch off? ";
        int del;
        cin >> del;
        current.cur_trip.delUserFav(del, current.username, "trip.csv");
        displayMainMenuScreen();
        cout << endl << "Delete successful. ";
        system("pause");

    }

    displayMainMenuScreen();
    favTrip();

    



}

void favTrip(Stack& screenStack) {
    screenStack.push(4);
    cout << "=========Your favourite Trips=========" << endl;
    
    int option = 1;
    //cin >> option;
    do {
        current.cur_trip.loadUserFav("trip.csv", current.username);
        cout << endl;
        cout << "1. Delete from favourites " << endl;
        cout << "0. Go back" << endl;
        cout << endl;
        cout << "Enter choice " << endl;
        
        cout << "Enter 0 to go back to the main menu: ";
        cin >> option;

        if (option == 0) {
            // User wants to go back
            // Pop the stack to return to the previous menu
            screenStack.pop();
            displayMainMenuScreen();
            return;  // Exit the function
        }
        else {
            cout << endl;
            cout << "Which plan do you wanna scratch off? ";
            int del;
            cin >> del;
            current.cur_trip.delUserFav(del, current.username, "trip.csv");
            displayMainMenuScreen();
            cout << endl << "Delete successful. ";
            system("pause");
            // Continue with the function or handle other options
            // Add any additional logic here
        }
    } while (option != 0);




}


string get_Contact(string user) { //function to get the contact no. from Users.csv
    ifstream inputFile("Users.csv");
    string line;
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        string name;
        string contact;
        getline(lineStream, name, ','); //gets username for <name>
        getline(lineStream, contact, ','); //gets password for <contact> (should skip this)
        getline(lineStream, contact, ','); //finally gets the contact no for <contact>
        if (user == name) {
            return contact;
        }

    }

}