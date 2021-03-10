#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main(){
    char command[50];
    while(1){
        read(0, command, 50);
        if(strncmp(command, "xboard", strlen("xboard"))) {
            read(0, command, 50);
            write(0, "feature sigint=0\n", 50);
            write(0, "feature san=0\n", 50);
            write(0, "feature myname=\"Capablanca\"\n", 50);
        }
        else {
            // write(0, "move e2e4\n", 50);
            break;
        }
    }
}

/*
using namespace std;

int main(){
    char N[3];
    cout.setf(ios::unitbuf);
    cin.rdbuf()->setbuf(NULL, 0);
    char command[50];
    while(1){
        cin >> command;
        if(strcmp(command, "xboard")){
            cin >> command;
            cin >> N;
            cout<<"feature sigint=0"<<'\n';
            cout<<"feature san=0"<<'\n';
            cout<<"feature myname=\"Capablanca\""<<'\n';
        }
    }
}
*/