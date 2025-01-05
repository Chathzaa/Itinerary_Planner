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
    UserFile.open("Users.txt", ios::app);
    if (UserFile.is_open()) {
        UserFile << user.username << ' ' << user.password << '\n';
        UserFile.close();
    }
    else {
        "Error: Failed to open the UserFile.\n";
        cout << endl;
    }
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
    fstream UserFile("Users.txt", ios::in);
    if (UserFile.is_open()) {
        string line;
        while (getline(UserFile, line)) {//read line by line and stores the lines to line variable 
            string storedUsername, storedPassword;
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
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
    cout << "(No specific date on mind? Press 'N' to skip)" << endl << endl;    //
    cout << "Enter the Date(DD/MM/YY): ";
    cin >> Date;

    cout << "(No specific date on mind? Press 'N' to skip)" << endl << endl;    //
    cout << "Where you planning to head at? " << endl; //
    cout << "1. Galle" << endl; //
    cout << "2. Kandy" << endl; //
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
                    cout << endl;
                    cout << "Plan for the day: " << endl;
                    while (getline(lineStream, column3, ',')) {  //start reading the visiting locations one by one: *continuing from column 4
                        //enQueue(column);

                        //getline(lineStream, column3, ',');
                        cout << column3 << "   ";                //print remaining columns starting from 4, until end of line in loop
                    }

                }
                cout << endl;
            }
        }
    }

    else if ((Date == "n") && (Loc == "n")) {
        displayMainMenuScreen();
        string line;
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

                cout << "Travel Buddy: " << column << "   "; //print username (creater of trip)
                cout << endl;
                cout << "Plan for the day: " << endl;

                // Read the rest of the line, starting from the Loc field (assuming it's the 4th column)
                while (getline(lineStream, column3, ',')) {
                    cout << column3 << "   "; //print remaining columns starting from 4, until the end of the line in loop
                }

                cout << endl;
            }
        }
    }
}

/*void Find_A_Trip(string username) {
    string Date;
    ifstream inputFile("trip.csv");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open the file " << "trip.csv" << " for reading." << endl;
        return;
    }
    cout << "==Find incredible trips tailored to your preferences. Let the journey begin!== " << endl;
    cout << endl;
    cout << "Enter the Date(DD/MM/YY): ";
    cin >> Date;
    displayMainMenuScreen();
    string line;
    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        string column;
        string column2;
        string column3;
        
        string date;
        getline(lineStream, column, ',');
        getline(lineStream, column2, ',');
        if (column != username && column2 == "1") {
            
            getline(lineStream, date, ',');
                if (date == Date) {
                    cout << "Travel Buddy: "<<column << "   ";
                    cout << endl;
                    cout << "Plan for the day: " << endl;
                    while (getline(lineStream, column3, ',')) {
                        //enQueue(column);

                        //getline(lineStream, column3, ',');
                        cout << column3 << "   ";
            }
            //cout << column << "   ";
            //while (getline(lineStream, column3, ',')) {
                //enQueue(column);
                
                //getline(lineStream, column3, ',');
                //cout << column3 << "   ";
            }
            cout << endl;
        }
    }

    

}*/

void Plan_A_Trip(Stack& screenStack) {
    bool planningTrip = true;
    screenStack.push(1);
    while(planningTrip){
    cout << "=======Plan your perfect trip by choosing destinations <3 =======" << endl;
    cout << endl;
    cout << "1.Enter your preferred date and let the countdown to your unforgettable adventure begin!" << endl;
    cout << endl;
    cout << "2. Back to the main menu ";
    int choice;
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
        // If the user chooses to go back, check if there's a previous screen on the stack
        if (!screenStack.empty()) {
            displayMainMenuScreen();
            screenStack.pop(); // Pop the current screen
            if (!screenStack.empty()) {
                // Display the previous screen based on what's on the top of the stack
                int previousScreen = screenStack.topValue();
                switch (previousScreen) {
                case 1:

                    displayMainMenuScreen();
                    break;
                    // Add more cases for other screens if needed
                }
            }
            if (!screenStack.empty()) {
                // Pop the stack again to go back the second time
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
    //Enter the couts for nearest towns
    //cout<<""
    //cout << "Enter the nearest town: " << endl;
    //cin >> nearest_town;
    bool Selecting_Destinations = true;
    while(Selecting_Destinations){

    cout << "1. Galle" << endl;
    cout << "2. Kandy" << endl;
    cout << "Enter the preffered destination" << endl;
    cout << "Enter 0 to go back";
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
    /*int i = 1;
    for (const auto& entry:B) {
        cout << i << ". " << entry.first << " : " << entry.second << " km away" << endl;
        ++i;
    }
    */
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

void favTrip(Stack& screenStack) {
    screenStack.push(4);
    cout << "=========Your favourite Trips=========" << endl;
    cout << endl;
    current.cur_trip.loadUserFav("trip.csv", current.username);
    current.cur_trip.delUserFav(2, current.username, "trip.csv");
    cout << endl;
    current.cur_trip.loadUserFav("trip.csv", current.username);
    int option;
    //cin >> option;
    do {
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
            // Continue with the function or handle other options
            // Add any additional logic here
        }
    } while (option != 0);


}