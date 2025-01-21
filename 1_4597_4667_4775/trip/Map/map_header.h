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

    

};


class Map {
public:
    string mapName;//This is the root City for all nodes in this map
    vector<Node> nodes; //build a collection of individual Nodes.

    Map(string _mapName) {
        mapName = _mapName; //automatically assigns the map Object's name as cityTag of the nodes added
    }

    //add a new Node
    void addNode(string id, double _lat, double _lon);
    
    void saveNodes(const string& filename);


   
};


class Graph {
public:
    map<string, map<string, double>> roads; //This map contains data under each node which is the key (A,B,C...)
                                            //Each key contain another map with the nodes connected along with the distance to it.    
                             
    //Dijkstra algorithm
    map<string, double> dijkstra(map<string, map<string, double>> mp, string start);

    //Importing node data from CSV file "connections". 
    //This file contains all the connnections between different locations
    void readFrom_connectionsFile(const string& filename);

};


#endif // !map_header_H