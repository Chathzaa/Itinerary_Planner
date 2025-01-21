#include "Header.h"
#include "map_header.h"
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

//add a new Node
void Map::addNode(string id, double _lat, double _lon) {
    Node newNode(id, _lat, _lon, mapName);
    nodes.push_back(newNode);
}

void Map::saveNodes(const string& filename) {
    ofstream file(filename, ios::app); //Opens the file in append mode
    if (file.is_open()) {
        for (const auto& node : nodes) {
            file << node.getID() << " " << node.getLat() << " " << node.getLon() << " " << node.cityTag << endl;

            file << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to access file for storage" << endl;
    }

}

//Dijkstra algorithm
map<string, double> Graph::dijkstra(map<string, map<string, double>> mp, string start) {
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
void Graph::readFrom_connectionsFile(const string& filename) {
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
