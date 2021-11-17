#include <iostream>
#include <fstream>
#include <string>
#include "banner.h"

using namespace std;

Letter* read_font(const char* fname)
{
    ifstream ifile(fname);
    if (ifile.fail()){
        return NULL; 
    }

    Letter* structarray = new Letter[95];
    
    for(int i = 0; i<95; i++){
        for (int j = 0; j < 8; j++) {
            getline(ifile, structarray[i].lines[j]);
            structarray[i].c = (char) (i + 32);
        }
    }
    return structarray; 
}

Banner make_banner(string message, Letter* font)
{
    Banner *b = new Banner();
    b->message = message;
    string temp = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < message.length(); j++) {
            b->output[i] += font[(int) (b->message[j]) - 32].lines[i];
        }
    }
    return *b; 
}

int main() {
    Letter* a = read_font("banner.font");

}