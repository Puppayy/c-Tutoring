/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char **, int, int);

// main function to read, solve maze, and print result
int main(int argc, char *argv[])
{
   int rows, cols, result;
   char **mymaze = NULL;

   if (argc < 2)
   {
      cout << "Please provide a maze input file" << endl;
      return 1;
   }

   mymaze = read_maze(argv[1], &rows, &cols);

   if (mymaze == NULL)
   {
      cout << "Invalid maze." << endl;
      return 1;
   }
   //================================
   // When working on Checkpoint 3, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
   result = maze_search(mymaze, rows, cols);

   // examine value returned by maze_search and print appropriate output
   if (result == 1)
   { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0)
   { // no path :(
      cout << "No path could be found!" << endl;
   }
   else if (result == -2) {
      cout << "Error, input format incorrect." << endl;
   }
   else
   { // result == -1
      cout << "Invalid maze." << endl;
   }

   //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated

   // Free's each subarray
   for (int i = 0; i < rows; i++) {
      delete[] mymaze[i];
   }

   delete[] mymaze;
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char **maze, int rows, int cols)
{
   //Creates 2D array to track predcessor and visited
   bool **visited = new bool*[rows];

   for (int i = 0; i < rows; i++) {
      bool *row = new bool[cols];
      for (int j = 0; j < cols; j++) {
         row[j] = false;
      }
      visited[i] = row;
   }

   Location **predcessor = new Location*[rows];
   for (int i = 0; i < rows; i++) {
      Location *row = new Location[cols];
      for (int j = 0; j < cols; j++) {
         Location *newLoc = new Location();
         row[j] = *newLoc;
         delete newLoc;
      }
      predcessor[i] = row;
   }


   //Finds starting point and checks for correct amount of start/finish
   int startFinish = 0;
   Location start;
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
         if (maze[i][j] == 'S') {
            start.row = i;
            start.col = j;
            startFinish++;
         } else if (maze[i][j] == 'F')
            startFinish++; 
         else if (maze[i][j] != '.' && maze[i][j] != '#' && maze[i][j] != 'F' && maze[i][j] != 'S')
            return -2;
      }
   }

   if (startFinish != 2)  {
      return -1;
   }
   cout << rows << " " << cols << endl;
   visited[start.row][start.col] = true;
   predcessor[start.row][start.col].row = -1;
   predcessor[start.row][start.col].col = -1;

   //Creates queue and adds start
   Queue *q = new Queue(rows * cols);
   q->add_to_back(start);

   //Begins alogrithm
   while (!(q->is_empty())) {
      //Declares current
      Location current = q->remove_from_front();

      //Checks each of the surrounding four squares for either . or F
      for (int i = -1; i < 2; i+=2){
         //Checks North and South
         if ((current.row + i < rows && current.row + i >= 0) && (maze[current.row + i][current.col] == '.' && !visited[current.row+i][current.col])) {
            predcessor[current.row+i][current.col] = current;
            visited[current.row + i][current.col] = true;
            Location newLoc = current;
            newLoc.row += i;
            q->add_to_back(newLoc);
         }

         //Checks East and West
         if ((current.col + i) < cols && (current.col + i) >= 0 && (maze[current.row][current.col + i] == '.' && !visited[current.row][current.col + i])) {
            visited[current.row][current.col + i] = true;
            predcessor[current.row][current.col+i] = current;
            Location newLoc = current;
            newLoc.col += i;
            q->add_to_back(newLoc);
         }
         //Checks if F
         if (((current.col + i >= 0 && current.col + i < cols) && maze[current.row][current.col+i] == 'F') || ((current.row + i >= 0 && current.row + i < rows) && (maze[current.row + i][current.col] == 'F'))) {
            //Changes all previous to *
            visited[current.row][current.col + i] = true;
            while(current.row != start.row || current.col != start.col) {
               maze[current.row][current.col] = '*';
               current = predcessor[current.row][current.col];
            }

            for(int i = 0; i < rows; i++) {
               delete[] visited[i];
               delete[] predcessor[i];
            }
            delete[] visited;
            delete[] predcessor;

            delete q;
            return 1;
         }
      }
   }

   delete q;
   return 0;
}



