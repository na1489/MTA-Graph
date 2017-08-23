#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

const int DEFAULT_VAL =  -1;      // must be less than 0
const string DEFAULT_VAL2 =  " ";      // must be less than 0


typedef unordered_map<string, list<string>> Graph;        // The graph is given in an adjacency list.
// Vertices are indexed from 0 to V-1
// The indices of the vertices adjacent to vertex i
// are in the list Graph[i].
// Graph can be directed or undirected.

struct vertexInf                    // Stores information for a vertex
{                                   
    int dist;  // distance to vertex from the source
    string prev;  // previous node in BFS tree
};

void printpath(string stopEnd, unordered_map<string,vertexInf>& vinfo)
{
    stack<string> t;
	
    string current = stopEnd;
    while (current != DEFAULT_VAL2)
    {
		t.push(current);
		current = vinfo[current].prev;
    }
    while (!t.empty())
    {
		cout << t.top() << " ";
		t.pop();
    }
}

// Breadth First Search
// The unweighted shortest path algorithm on the graph g, with vertex i as the source
// Prints the length (number of edges) of the shortest path from the source to every vertex
// in the graph

void sameTrainLine(unordered_map<string, list<string>>& theMTA, ifstream& MTAFile) {
    string theStop;
    getline(MTAFile,theStop);
    string theStopId;
    string prevStopId;
    getline(MTAFile,theStop);
    stringstream stopStream(theStop);
    getline(stopStream,prevStopId,',');
    prevStopId = prevStopId.substr(0,3);
    list<string> nextStop;
    theMTA[prevStopId] = nextStop;
    while(getline(MTAFile,theStop)) {
        string theStop1 = theStop.substr(0,3);
        if(prevStopId != theStop1) {
            stringstream stopStream(theStop);
            getline(stopStream,theStopId,',');
            theStopId = theStopId.substr(0,3);
            if(prevStopId[0] == theStopId[0]) {
                list<string> nextStop;
                theMTA[theStopId] = nextStop;
                theMTA[prevStopId].push_back(theStopId);
                theMTA[theStopId].push_back(prevStopId);
            }
            else {
                list<string> nextStop;
                theMTA[theStopId] = nextStop;
            }
            prevStopId = theStopId;
        }
    }
}

void printThis(const unordered_map<string, list<string>>& theMTA) {
    for(auto theStop : theMTA) {
        cout << theStop.first;
        auto itr = theStop.second.begin();
        while(itr!=theStop.second.end()) {
            cout << " -> " << *itr;
            itr++;
        }
        cout << endl;
    }
}

//FROM HW10
void transferingLines(unordered_map<string, list<string>>& theMTA, ifstream& MTAFile) {
    string theStop;
    string theTrainStop;
    string theTransfer;
    getline(MTAFile,theStop);
    while(getline(MTAFile,theStop)) {
        stringstream stopStream(theStop);
        getline(stopStream,theTrainStop,',');
        getline(stopStream,theTransfer,',');
        if(theTrainStop!=theTransfer) {
            theMTA[theTrainStop].push_back(theTransfer);
        }
    }
}


//MODIFIED FOR OUR TRAINSTOPS
void shortestpaths(Graph & g, string startStop, string endStop)
{
    queue<string> q;             // q is the queue of vertex numbers
	
    unordered_map<string, vertexInf> vertices(g.size());               // stores BFS info for the vertices
	
    for (auto theStop : g) {               // Initialize distances and prev values
        string theStopID = theStop.first;
        vertices[theStopID].dist = DEFAULT_VAL; 
        vertices[theStopID].prev = DEFAULT_VAL2; 
    }   
	
	
    vertices[startStop].dist = 0;
	
    q.push(startStop);
    while  (!q.empty() )
    {
		string v = q.front();
		q.pop();
		for (list<string>::const_iterator w = g[v].begin(); w != g[v].end(); w++)
		{ 
			
            if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
            {
                vertices[*w].dist = vertices[v].dist+1;
                vertices[*w].prev = v;
                if(*w == endStop) {
                    while(!q.empty()) {
                        q.pop();
                    }
                }
                else {
                    q.push(*w);
                }
            }
		}
    }
	cout << "stop1: " << startStop << endl;
	cout << "shortest path to stop2: " << endStop << endl; 
	printpath(endStop,vertices); 
	cout << endl;
}

int main()
{
    unordered_map<string, list<string>> theMTA;
    ifstream MTAData("MTA_train_stop_data.txt");
    if (!MTAData) {
        cout << "No file detected." << endl;
        exit(1);
    }
    ifstream MTATransfers("transfers.txt");
    if (!MTAData) {
        cout << "No file detected." << endl;
        exit(1);
    }
    cout << endl;
    cout << "-----------------QUICKEST PATH-------------------------" << endl;
    cout << endl;
    sameTrainLine(theMTA,MTAData);
    transferingLines(theMTA,MTATransfers);
    shortestpaths(theMTA,"F02","719");
}
