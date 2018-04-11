#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;




int main () {
    
    string config;
    ifstream configfile("/root/OccupancyServer/OccupancyServer.conf");  
    
    
    configfile.seekg(0, std::ios::end);   
    config.reserve(configfile.tellg());
    configfile.seekg(0, std::ios::beg);

    config.assign((std::istreambuf_iterator<char>(configfile)),
    std::istreambuf_iterator<char>());

    configfile.close();
    
    cout<<"Content-type: text/plain"<<endl<<endl; 
    
    cout<<config<<endl; 

    
    return 0;
}




