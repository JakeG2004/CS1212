/*
mazeSolver.cpp
A program to solve mazes using an A* implementation
Jake Gendreau
April 1, 2024
*/

//boilerplate
#include <iostream>
#include <fstream>
#include "queueADT.cpp"

using namespace std;

//prototypes
int getDimension(string);
cell** getMaze(string, int);
void printMaze(cell**, int);
cell* findStart(cell**, int);
void solveMaze(cell*, cell**, int, Queue&);

bool checkGoal(cell*, cell**, int);
void addUnvisited(cell*, cell**, int, Queue&);
void printSolvedMaze(cell**, int);

/*
start - S
goal - G
wall - #
blank - .
*/

int main(int argc, char* argv[])
{
    //check proper usage
    if(argc != 2)
    {
        cout << "USAGE: ./a.out <map.txt>. Exiting program..." << endl;
        exit(-1); 
    }

    string fileName = argv[1];

    //init array
    int dimension = getDimension(fileName);
    cell** maze = getMaze(fileName, dimension);

    printMaze(maze, dimension);

    cell* agent = findStart(maze, dimension);

    Queue queue = Queue();

    solveMaze(agent, maze, dimension, queue);
    printSolvedMaze(maze, dimension);
}

void solveMaze(cell* agent, cell** maze, int dimension, Queue &queue)
{
    //check for goal cell
    if(checkGoal(agent, maze, dimension))
    {
        cout << "Found solution" << endl;
        return;
    }

    //add all unvisited neighbors
    addUnvisited(agent, maze, dimension, queue);

    //remove next element and make it current cell
    cell newAgent = queue.dequeue();
    solveMaze(&newAgent, maze, dimension, queue);
}

void printSolvedMaze(cell** maze, int dimension)
{
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            if(maze[i][j].type == 'S' || maze[i][j].type == 'G')
            {
                cout << maze[i][j].type;
            }
            else if(maze[i][j].visited == true)
            {
                cout << "#";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void addUnvisited(cell* agent, cell** maze, int dimension, Queue &queue)
{
    int x = agent -> x;
    int y = agent -> y;

    //check north
    if(y - 1 >= 0 && maze[y - 1][x].type == '.' && maze[y - 1][x].visited == false)
    {
        maze[y - 1][x].visited = true;
        queue.enqueue(maze[y - 1][x]);
    }
    
    //check south
    if(y + 1 < dimension && maze[y + 1][x].type == '.' && maze[y + 1][x].visited == false)
    {
        maze[y + 1][x].visited = true;
        queue.enqueue(maze[y + 1][x]);
    }

    //check west
    if(x - 1 >= 0 && maze[y][x - 1].type == '.' && maze[y][x - 1].visited == false)
    {
        maze[y][x - 1].visited = true;
        queue.enqueue(maze[y][x - 1]);
    }

    //check east
    if(x + 1 < dimension && maze[y][x + 1].type == '.' && maze[y][x + 1].visited == false)
    {
        maze[y][x + 1].visited = true;
        queue.enqueue(maze[y][x + 1]);
    }
}

bool checkGoal(cell* agent, cell** maze, int dimension)
{
    int x = agent -> x;
    int y = agent -> y;

    //check north
    if(y - 1 >= 0 && maze[y - 1][x].type == 'G')
        return true;
    
    //check south
    if(y + 1 < dimension && maze[y + 1][x].type == 'G')
        return true;

    //check west
    if(x - 1 >= 0 && maze[y][x - 1].type == 'G')
        return true;

    //check east
    if(x + 1 < dimension && maze[y][x + 1].type == 'G')
        return true;
    
    return false;
}

int getDimension(string fileName)
{
    //open file
    string word;
    fstream file;

    file.open(fileName);

    //check that file is valid and open
    if(!file.is_open())
    {
        cout << "ERROR OPENING FILE: " << fileName << ". Exiting program..." << endl;
        exit(-1);
    }

    //extract just the first word
    file >> word;

    //close the file
    file.close();

    //return the dimension
    return stoi(word);
}

cell** getMaze(string fileName, int dimension)
{
    //open file
    string line;
    fstream file;

    file.open(fileName);

    //check that file is valid and open
    if(!file.is_open())
    {
        cout << "ERROR OPENING FILE: " << fileName << ". Exiting program..." << endl;
        exit(-1);
    }

    //adjust file pointer to be start of the maze
    getline(file, line);

    cell** maze = new cell*[dimension];

    //read in the map
    for(int i = 0; i < dimension; i++)
    {
        maze[i] = new cell[dimension];
        //get this line
        getline(file, line);
        for(int j = 0; j < dimension; j++)
        {
            //write the chars of the current line into the array
            maze[i][j].type = line[j];
            maze[i][j].x = j;
            maze[i][j].y = i;
        }
    }

    //close the file
    file.close();

    return maze;
}

void printMaze(cell** maze, int dimension)
{
    //print the maze
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            cout << maze[i][j].type;
        }
        cout << endl;
    }
}

cell* findStart(cell** maze, int dimension)
{
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            if(maze[i][j].type == 'S')
            {
                return &maze[i][j];
            }
        }
    }

    cout << "ERROR: COULDN'T FIND START" << endl;
    exit(-1);
}


















