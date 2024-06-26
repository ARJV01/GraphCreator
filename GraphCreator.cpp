// Arjun Vinsel
// 4-JUN-2024
// This code is a graph and can find the shortest path using Dijktras.

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void addV(char aMatrix[21][21], vector<char> &verts);    // adds verticies
void addE(char aMatrix[21][21]);                         // add edges
void clearM(char aMatrix[21][21]);                       // clears the matrix
void printM(char aMatrix[21][21]);                       // prints the matrix
void removeE(char aMatrix[21][21]);                      // remove edges
void removeV(char aMatrix[21][21], vector<char> &verts); // remove verticies
void path(char aMatrix[21][21], vector<char> verts);     // finds the paths
void vD(vector<char> &verts, char x);                    // erases from the vector of verticies
void printPath(vector<char> pathF);                      // prints the path

int main()
{
    char aMatrix[21][21];
    clearM(aMatrix);
    bool sR = true;
    char input[80];
    vector<char> verts;

    while (sR == true)
    {
        cout << "please enter addV, addE, removeE, removeV, print, path or quit" << endl;
        cin >> input;
        if (strcmp(input, "addV") == 0)
        {
            addV(aMatrix, verts);
        }
        if (strcmp(input, "addE") == 0)
        {
            addE(aMatrix);
        }
        if (strcmp(input, "removeE") == 0)
        {
            removeE(aMatrix);
        }
        if (strcmp(input, "removeV") == 0)
        {
            removeV(aMatrix, verts);
        }
        if (strcmp(input, "print") == 0)
        {
            printM(aMatrix);
        }
        if (strcmp(input, "path") == 0)
        {
            path(aMatrix, verts);
        }
        if (strcmp(input, "quit") == 0)
        {
            sR = false;
        }
    }

    return 0;
}

void addV(char aMatrix[21][21], vector<char> &verts)
{ // adds verticies to the matrix
    char input = ' ';
    cout << "please enter a label" << endl;
    cin >> input;
    for (int i = 1; i < 21; i++)
    {
        if (aMatrix[0][i] == NULL)
        {
            aMatrix[0][i] = input;
            i = 21;
        }
    }
    for (int i = 1; i < 21; i++)
    {
        if (aMatrix[i][0] == NULL)
        {
            aMatrix[i][0] = input;
            i = 21;
        }
    }
    verts.push_back(input);
}

void addE(char aMatrix[21][21])
{ // adds edges to the matrix
    char start = ' ';
    cout << "please enter the start" << endl;
    cin >> start;
    char end = ' ';
    cout << "please enter the end" << endl;
    cin >> end;
    char w = ' ';
    cout << "please enter the weight" << endl;
    cin >> w;
    int rs = 0;
    int cs = 0;

    for (int row = 1; row < 21; row++)
    {
        if (aMatrix[row][0] == end)
        {
            rs = row;
        }
    }
    for (int column = 1; column < 21; column++)
    {
        if (aMatrix[0][column] == start)
        {
            cs = column;
        }
    }
    aMatrix[rs][cs] = w;
}

void clearM(char aMatrix[21][21])
{ // Clears the board
    for (int row = 0; row < 21; row++)
    {
        for (int column = 0; column < 21; column++)
        {
            aMatrix[row][column] = NULL;
        }
    }
}

void printM(char aMatrix[21][21])
{ // Prints board
    for (int row = 0; row < 21; row++)
    {
        for (int column = 0; column < 21; column++)
        {
            cout << aMatrix[row][column] << " ";
        }
        cout << endl;
    }
}

void removeE(char aMatrix[21][21])
{ // removes edges
    char start = ' ';
    cout << "please enter the start" << endl;
    cin >> start;
    char end = ' ';
    cout << "please enter the end" << endl;
    cin >> end;
    int rs = 0;
    int cs = 0;

    for (int row = 1; row < 21; row++)
    {
        if (aMatrix[row][0] == end)
        {
            rs = row;
        }
    }
    for (int column = 1; column < 21; column++)
    {
        if (aMatrix[0][column] == start)
        {
            cs = column;
        }
    }
    aMatrix[rs][cs] = NULL;
}

void removeV(char aMatrix[21][21], vector<char> &verts)
{ // remove verticies
    char v;
    cout << "enter the point you wish to delete" << endl;
    cin >> v;
    for (int column = 0; column < 21; column++)
    {
        if (aMatrix[0][column] == v)
        {
            for (int row = 0; row < 21; row++)
            {
                aMatrix[row][column] = NULL;
            }
        }
    }
    for (int row = 0; row < 21; row++)
    {
        if (aMatrix[row][0] == v)
        {
            for (int column = 0; column < 21; column++)
            {
                aMatrix[row][column] = NULL;
            }
        }
    }
    vD(verts, v);
}

void vD(vector<char> &verts, char x)
{ // removes verticies from the vector
    vector<char>::iterator itr;

    for (itr = verts.begin(); itr < verts.end(); itr++)
    {
        if (*itr == x)
        {
            verts.erase(itr);
        }
    }
}

void path(char aMatrix[21][21], vector<char> verts)
{ // finds the shortest path to a given point
    map<char, int> distances;
    map<char, bool> visited;
    map<char, char> paths;

    char start;
    cout << "please enter the start node" << endl;
    cin >> start;
    char end;
    cout << "please enter the end node" << endl;
    cin >> end;

    vector<char>::iterator itr;

    for (itr = verts.begin(); itr < verts.end(); itr++)
    {
        distances.insert({*itr, INT_MAX});
        visited.insert({*itr, false});
        paths.insert({*itr, '\0'});
    }

    distances[start] = 0;
    char previous = start;

    while (true)
    { // trust
        int shortest = INT_MAX;
        char shortestV = '\0'; // Initialize to some invalid character

        for (char v : verts)
        { // v is the char is the vector
            if ((visited[v] == false) && distances[v] < shortest)
            {                            // if it has not been visited and of the distance is shorter thand shortest
                shortest = distances[v]; // shortest is the new distance
                shortestV = v;           // shortest vert is the new vert(the thing we will look from the next time in loop)
            }
        }

        if (shortestV == '\0')
        { // if there is nothing more to iterate(this is how we break out)
            break;
        }

        visited[shortestV] = true; // Find the new node and more it as visited

        for (int column = 1; column < 21; column++)
        { // look though columns
            if (aMatrix[0][column] == shortestV)
            { // if it is the shortest V
                for (int row = 1; row < 21; row++)
                { // look through rows
                    if (aMatrix[row][column] != NULL && visited[aMatrix[row][0]] == false)
                    { // if its not NULL and its not visited
                        if (distances[aMatrix[row][0]] > distances[shortestV] + (aMatrix[row][column] - '0'))
                        { //
                            distances[aMatrix[row][0]] = distances[shortestV] + (aMatrix[row][column] - '0');
                            paths[aMatrix[row][0]] = shortestV;
                        }
                    }
                }
            }
        }
        previous = shortestV;
    }
    vector<char> pathF;
    char current = end;
    pathF.push_back(end);
    if (paths[end] != false)
    { // if there is a path
        while (current != start)
        {
            current = paths[current];
            pathF.push_back(current);
        }
        reverse(pathF.begin(), pathF.end());
        printPath(pathF);
        cout << "Distance: " << distances[end] << endl;
    }
    else
    { // if there is no path to end
        cout << "No path found" << endl;
    }
}

void printPath(vector<char> pathF)
{ // prints out the path
    vector<char>::iterator itr;

    for (itr = pathF.begin(); itr < pathF.end(); itr++)
    {
        cout << *itr << ",";
    }
    cout << endl;
}