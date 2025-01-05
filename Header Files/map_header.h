#ifndef map_header_H
#define map_header_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <map>
#include <queue>
#include <limits>
#include <list>
#include <algorithm>
 
using namespace std;

class Node {

private:
    string id;
    double lat;
    double lon;
    map<string, double> dij_Data;
    //vector <pair<string, double>> connections;

public:
    string cityTag;

    //Constructor
    Node(string _id, double _lat, double _lon, string _cityTag) {
        id = _id;
        lat = _lat;
        lon = _lon;
        cityTag = _cityTag;
    }

    // Getter methods to access private members
    string getID() const {
        return id;
    }

    double getLat() const {
        return lat;
    }

    double getLon() const {
        return lon;
    }

    /*const vector<pair<string, double>>& getConnections() const {
        return connections;
    }*/

    //Connect a road to a location
    /*void addConnection(string connectedNodeId, double distance) {
        connections.push_back(make_pair(connectedNodeId, distance));
    }*/

};

//Temporarily removed for testing purposes
/*class Edge { //Road system
public:
    string source;
    string destination;
    double weight;

    Edge(string source, string destination, double weight) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
};
*/


class Map {
public:
    string mapName;//This is the root City for all nodes in this map
    vector<Node> nodes; //build a collection of individual Nodes.

    Map(string _mapName) {
        mapName = _mapName; //automatically assigns the map Object's name as cityTag of the nodes added
    }

    //add a new Node
    void addNode(string id, double _lat, double _lon) {
        Node newNode(id, _lat, _lon, mapName);
        nodes.push_back(newNode);
    }

    void saveNodes(const string& filename) {
        ofstream file(filename, ios::app); //Opens the file in append mode
        if (file.is_open()) {
            for (const auto& node : nodes) {
                file << node.getID() << " " << node.getLat() << " " << node.getLon() << " " << node.cityTag<<endl;
                //const auto& connections = node.getConnections();
                //for (const auto& conn : connections) {
                  //  file << conn.first << " " << conn.second << " ";
                //}
                file << endl;
            }
            file.close();
        }
        else {
            cerr << "Unable to access file for storage" << endl;
        }

    }
};


class Graph {
public:
    map<string, map<string, double>> roads; //This map contains data under each node which is the key (A,B,C...)
                                            //Each key contain another map with the nodes connected along with the distance to it.    
                             
   
    void next_location() {//This function is designed to automatically find next nearest location. Used in "Choose Destination" interface. 

    }

    //former dijkstra algorithm
    /*void Dij(string root) {
        vector<string> visited_nodes;
        vector<string> unvisited_nodes;

        ifstream inputFile("connections.csv");

        if (inputFile.is_open()) {
            string x;
            getline(inputFile, x);

            while (inputFile.good()) {
                string p, q, r;

                getline(inputFile, p, ',');
                getline(inputFile, q, ',');
                getline(inputFile, r, '\n');

                if (!inputFile.good()) break;

                // Check if the string is not in unvisited_nodes
                if (find(unvisited_nodes.begin(), unvisited_nodes.end(), p) == unvisited_nodes.end()) {
                    // Add the string to unvisited_nodes
                    unvisited_nodes.push_back(p);
                }

                if (find(unvisited_nodes.begin(), unvisited_nodes.end(), q) == unvisited_nodes.end()) {
                    // Add the string to unvisited_nodes
                    unvisited_nodes.push_back(q);
                }
                
            }

            inputFile.close();
        }
                
        map<string, tuple<double, string>> dij_Table; //Works as the table, where creates the Dijkstra table in the header format: Node, shortest path to this Node, Previous Node.
        
        for (const auto& pnt: unvisited_nodes) {
            dij_Table[pnt] = make_tuple(INFINITY, "");
        }
        dij_Table[root] = make_tuple(0, "");
        
        //The first step is seperate. Algorithm starts from the "root"
        for (auto itr = roads[root].begin(); itr != roads[root].end(); itr++) {
            string node = itr->first;
            double shortestDist = itr->second;
            dij_Table[node] = make_tuple(shortestDist, root);
        }
        visited_nodes.push_back(root); //Insert starting point (root) to Visited Nodes list(vector)
        auto it = remove(unvisited_nodes.begin(), unvisited_nodes.end(), root);
        unvisited_nodes.erase(it, unvisited_nodes.end());//Remove starting point (root) to Visited Nodes list(vector)

        //The end of the first step of completing the Dijkstra Table

        //Next step should start with the least weight, unvisited Node. To find least weight, unvisited Node
        {
            double next_Closest = INFINITY;
            string next_Closest_str;
            for (auto unvis = unvisited_nodes.begin(); unvis != unvisited_nodes.end(); unvis++) {
                double temp = get<0>((dij_Table[*unvis]));
                if (temp < next_Closest) {
                    next_Closest = temp;
                    string next_Closest_str = *unvis;
                }
            }
            //Now next_Closest_str contains the information for the djikstra to proceed. The next node should be next_Closest_str
        }

    }

    {
        double next_Closest = INFINITY;
        string next_Closest_str;
        for (auto unvis = unvisited_nodes.begin(); unvis != unvisited_nodes.end(); unvis++) {
            double temp = get<0>((dij_Table[*unvis]));
            if (temp < next_Closest) {
                next_Closest = temp;
                string next_Closest_str = *unvis;
            }
        }
        //Now next_Closest_str contains the information for the djikstra to proceed. The next node should be next_Closest_str
    }
    */

    //Dijkstra algorithm
    map<string, double> dijkstra(map<string, map<string, double>> mp, string start) {
        map<string, double> out;
        map<string, double> visited;
        for (auto itr = mp.begin(); itr != mp.end(); itr++) {
            pair<string, double> p(itr->first, 0);
            visited.insert(p);

            pair<string, double> pp(itr->first, INFINITY);
            out.insert(pp);
        }
        out[start] = 0;

        do {
            for (auto itr = mp[start].begin(); itr != mp[start].end(); itr++) {
                if (out[itr->first] > itr->second + out[start]) {
                    out[itr->first] = itr->second + out[start];
                }
            }
            visited[start] = 1;
            double low = INFINITY;
            for (auto itr = mp.begin(); itr != mp.end(); itr++) {
                if (out[itr->first] < low && visited[itr->first] == 0) {
                    start = itr->first;
                    low = out[itr->first];
                }
            }

        } while (visited[start] == 0);

        return out;
    }

    
    //Importing node data from CSV file "connections". 
    //This file contains all the connnections between different locations
    void readFrom_connectionsFile(const string& filename) {
        ifstream inputFile(filename);

        if (inputFile.is_open()) {
            string line;

            //skip the header line
            getline(inputFile, line);
            //

            while (inputFile.good()) {//load data from "connections.csv" to the "roads" hashmap.
               
                string point1, point2;
                string weight_str;
                double weight;

                getline(inputFile, point1, ',');
                getline(inputFile, point2, ',');
                getline(inputFile, weight_str, '\n');

                if (!inputFile.good()) break;


                weight = stod(weight_str);

                //cout << "point1: " << point1 << " point2: " << point2 << " weight: " << weight << endl;

                // Update route data for point1
                roads[point1][point2] = weight;

                //graph is undirected, therefore update route data for point2 as well
                roads[point2][point1] = weight;
            }
        }

        else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    //void dij(string start) {
      //  list <string> unvisited;





};


#endif // !map_header_H