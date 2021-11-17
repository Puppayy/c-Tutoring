#include <iostream>
#include <fstream>
#include <string>
#include "banner.h"

using namespace std;

#ifdef RF  
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
#endif

#ifdef MB
Banner make_banner(string message, Letter* font)
{
    Banner *b = new Banner();
    b.message = message;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < message.length(); j++) {
            b->output[i] += font[(int) b.message[j] - 32];
        }
    }

    Banner a = *b;
    Delete b;
    return a; 
}
#endif

#ifdef PB
void print_banner(Banner b)
{
    for(int i=0;i<8;i++)
    {
        cout << b.output[i] << endl;
    }
}
#endif

#ifdef MAIN
int main(int argc, char* argv[])
{
    if (argc < 1) {
        cout << "No font file given." << endl;
        return 1;
    }

    Letter* fonts = read_font(argv[1]);

    if (fonts == NULL){
        cout << "Unable to read font file." << endl;
        return 2;
    }
    
    cout << "Enter your message"<<endl;
    
    string input;
    getline(cin, input); 
    Banner b = make_banner(input, fonts);
    print_banner(b);
}
#endif
