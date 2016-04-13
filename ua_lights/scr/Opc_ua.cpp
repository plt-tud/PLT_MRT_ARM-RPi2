#include <unistd.h>      //sleep
#include <iostream>

#include "Opc_ua.h"

using namespace std;




Opc_ua::Opc_ua(){
    //ctor
}



Opc_ua::~Opc_ua(){
    //dtor
}


void Opc_ua::run_Opc_ua( bool* in_running ){
    cout << "entering Opc_ua::run()" << endl;


    //!do stuff...
    while( *in_running ){
        usleep(1000000);  //1.0 s
        //cout << "Opc_ua::run(): doing stuff" << endl;

    }


    cout << "leaving Opc_ua::run()" << endl;
}
