#include <iostream>

using namespace std;

int count_delims(char delim, char* str)
{
    char *strCopy = str;
    int count = 0; 
    while (*strCopy != '\0'){
        if (*strCopy == delim){
            count++;
        }
        strCopy++;
    }
    return count; 
}

char** split(char delim, char* str, int *size) 
{
    *size = count_delims(delim, str) + 1;
    char **delimLines = new char *[*size];

    //Gets max length of string
    char *strCopy = str;

    int length = 0;
    while (*strCopy != '\0') {
        length++;
        strCopy++;
    }

    strCopy = str;

    //Gets each substring
    for (int i = 0; i < *size; i++) {
        char *line = new char[length], *lineptr = line;
        while (*strCopy != '\0' && *strCopy != delim) {
            *lineptr = *strCopy;
            strCopy++;
            lineptr++;
        }
        lineptr++;
        *lineptr = '\0';
        strCopy++;
        delimLines[i] = line;
    }

    return delimLines;
}

#ifndef TEST
int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cout << "Please enter a delimter and a string as arguments." << endl;
        return 1;
    }
    //do not make any changes to main! If changes to main are needed to make your code work, you have a bug elsewhere!
    int n;
    char** w = split(argv[1][0], argv[2], &n);
    for(int i=0;i<n;i++)
    {
        cout << i << ":" << w[i] << endl;
    }
    delete[] w;
}
#endif