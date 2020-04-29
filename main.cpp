#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <climits>
#include "string.h"

using namespace std;

void Dijkstra(vector<vector<int> > graph, int source){
    //so_far = N
    vector<bool> so_far;
    //distances will hold the distances from the source node
    //The index represents the node itself
    vector<int> distances;
    //predecessors will hold the previous node in the path of the node at each index
    vector<int> predecessors;

    //nodes is a string that will hold N. It is for printing
    string nodes = "";
    for(int i = 0; i < graph[0].size(); i++){
        //Each of the distances from the source is initially set to infinity
        distances.push_back(INT_MAX);
        //Each of the predecessors is initially -1
        predecessors.push_back(-1);
        //None of the nodes start out in N
        so_far.push_back(false);
    }

    //The string format is used to format the top line of the table
    string format = "";

    //This part of the code prints the table headers
    //D(x) where x is a node represents its distance from the source
    //p(x) represents its predecessor
    cout << setw(5) << "Step" << setw(10) << "N";
    for(int i = 0; i < graph[0].size(); i++){
        if(i != source){
            format += "D(" + to_string(i) + "), " + "p(" + to_string(i) + ")";
            cout << setw(15) << format;
            format = "";
        }

        //cout << "D(" << i << "), " << "p(" << i << ")\t";
    }
    cout << endl;

    //Set the source's initial distance to 0
    distances[source] = 0;
    int min;
    int min_index;
    //so_far[source] = true;
    string output = "";
    //This code finds the node closest to the source such that it hasn't already been appended to N
    for(int i = 0; i < graph[0].size(); i++){
        int min = INT_MAX;
        for (int j = 0; j < graph[0].size(); j++){
            if (so_far[j] == false && distances[j] < min){
                min = distances[j];
                min_index = j;
            }
        }
        so_far[min_index] = true;

        //Add the node to the string for printing N
        nodes += to_string(min_index);

        //This is where dijkstra's algorithm is actually performed
        for(int j = 0; j < graph[0].size(); j++){
            if(!so_far[j] && graph[min_index][j] != INT_MAX && (distances[min_index] + graph[min_index][j]) < distances[j]){
                predecessors[j] = min_index;
                distances[j] = distances[min_index] + graph[min_index][j];
            }
        }

        //Print out the step and N
        cout << setw(5) << i << setw(10) << nodes;

        //Print out the distances and predecessors
        for(int k = 0; k < graph[0].size(); k++){
            if(k != source && distances[k] != INT_MAX){
                output += "" + to_string(distances[k]) + "," + to_string(predecessors[k]);
                //cout << setw(15) << distances[k] << "," << predecessors[k] << "\t";
            }
            else if(k != source){
                output += "infinity";
                //cout << setw(15) << "infinity\t";
            }
            if(k != source)
            cout << setw(15) << output;
            output = "";
        }
        cout << endl;
    }




}

int main(int argc, char** argv){
    int source;
    string in;
    if(argc != 3){
        cerr << "Need at least an input file and a source node" << endl;
        exit(1);
    }

    //set the input file to the first command line argument
    in = argv[1];
    //set the source node to the second command line argument
    source = stoi(argv[2]);
    int numNodes = 0;
    string line;
    ifstream infile(in);
    //Find the number of nodes so that we know how much to iterate to fill the matrix
    if(infile.is_open()){
        while(!infile.eof()){
            getline(infile,line);
            numNodes++;
        }
        infile.close();
    }
    else{
        cerr << "There was an error reading your input file" << endl;
        exit(1);
    }
    //reset input file
    infile.clear();
    infile.seekg(0, infile.beg);
    ifstream file(in);
    vector<vector<int> > graph;
    string entry;
    int num;
    vector<int> init;
    numNodes -= 1;
    //push all of the values from the input matrix into a 2d vector which will represent our graph
    for(int i = 0; i < numNodes; i++){
        graph.push_back(init);
        for(int j = 0; j < numNodes; j++){
            file >> entry;
            num = stoi(entry);
            if(num == -1) graph[i].push_back(INT_MAX);
            else{
                graph[i].push_back(num);
            }
        }
    }
    //Test to print out matrix to make sure file is read correctly
    /*for(int i = 0; i < numNodes; i++){
        for(int j = 0; j < numNodes; j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    */
    //Finally, run Dijkstra's algorithm
    Dijkstra(graph, source);
}
