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

#include <cgi.h> 


using namespace std;




int main () {
    s_cgi *cgiArg;
    
    string json;
    char* value;
    int intval;

    cout<<"Content-type: text/plain"<<endl<<endl;
    
    cgiArg= cgiInit();
   

    
    value=cgiGetValue (cgiArg, "value");
    
    if(value == NULL){
        cout<<"value not set"<<endl;
        cout<<"Possible values are:"<<endl;
        cout<<"value=0 stop the JsonClient service if running and disable it at boot"<<endl;
        cout<<"value=1 start the JsonClient service if not running and enable it at boot"<<endl;
        cout<<"value=2 stop the JsonClient service if running"<<endl;
        cout<<"value=3 start the JsonClient service if not running"<<endl;
        cout<<"value=4 disable the JsonClient service (it will not start during boot)"<<endl;
        cout<<"value=5 enable the JsonClient service (it will start automatically during boot)"<<endl;

    }
    else{
        intval=atoi(value);
        
        switch(intval){
            case 0:
                system("/etc/init.d/mica-jsonclient stop");
                cout<<"JsonClient Service Stop"<<endl;
                system("/etc/init.d/mica-jsonclient disable");
                system("rm -r /tmp/KinseiClient.json");
                cout<<"JsonClient Service Disabled"<<endl;
                break;
            case 1:
                system("/etc/init.d/mica-jsonclient start");
                cout<<"JsonClient Service Started"<<endl;
                system("/etc/init.d/mica-jsonclient enable");
                cout<<"JsonClient Service Enabled"<<endl;
                break;
            case 2:
                system("/etc/init.d/mica-jsonclient stop");
                system("rm -r /tmp/KinseiClient.json");
                cout<<"JsonClient Service Stop"<<endl;
                break;
            case 3:
                system("/etc/init.d/mica-jsonclient start");
                cout<<"JsonClient Service Started"<<endl;
                break;
            case 4:
                system("/etc/init.d/mica-jsonclient disable");
                system("rm -r /tmp/KinseiClient.json");
                cout<<"JsonClient Service Disabled"<<endl;
            case 5:
                system("/etc/init.d/mica-jsonclient enable");
                cout<<"JsonClient Service Enabled"<<endl;
                break;
            default:
                cout<<"Not recognized"<<endl;
        
        }
    }
    
    cgiFree(cgiArg);
   

    
    return 0;
}




