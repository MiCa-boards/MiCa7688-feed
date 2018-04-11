#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <cgi.h> 


using namespace std;



/*! Try to get lock. Return its file descriptor or -1 if failed.
 *
 *  @param lockName Name of file used as lock (i.e. '/var/lock/myLock').
 *  @return File descriptor of lock file, or -1 if failed.
 */
int tryGetLock( char const *lockName )
{
    mode_t m = umask( 0 );
    int fd = open( lockName, O_RDWR|O_CREAT, 0666 );
    umask( m );
    if( fd >= 0 && flock( fd, LOCK_EX | LOCK_NB ) < 0 )
    {
        close( fd );
        fd = -1;
    }
    return fd;
}


/*! Get lock. Return its file descriptor or wait.
 *
 *  @param lockName Name of file used as lock (i.e. '/var/lock/myLock').
 *  @return File descriptor of lock file.
 */
int GetLock( char const *lockName )
{

    int fd=-1;

    while(fd == -1){
        mode_t m = umask( 0 );
        fd = open( lockName, O_RDWR|O_CREAT, 0666 );
        umask( m );
        if( fd >= 0 && flock( fd, LOCK_EX | LOCK_NB ) < 0 )
        {
            close( fd );
            fd = -1;
        }
        usleep(10000); //us
    }
    return fd;
}

/*! Release the lock obtained with tryGetLock( lockName ).
 *
 *  @param fd File descriptor of lock returned by tryGetLock( lockName ).
 *  @param lockName Name of file used as lock (i.e. '/var/lock/myLock').
 */
void releaseLock( int fd, char const *lockName )
{
    if( fd < 0 )
        return;
    remove( lockName );
    close( fd );
}

int main () {
    s_cgi *cgiArg;
    
    string json;
    char* callback;
    int fd;
    
    cout<<"Content-type: text/plain"<<endl<<endl;
    
    cgiArg= cgiInit();
    
   
    
    fd=GetLock("/tmp/KinseiJsonClientLock"); //lock


    
    ifstream jsonfile("/tmp/KinseiClient.json");


    jsonfile.seekg(0, std::ios::end);   
    json.reserve(jsonfile.tellg());
    jsonfile.seekg(0, std::ios::beg);

    json.assign((std::istreambuf_iterator<char>(jsonfile)),
    std::istreambuf_iterator<char>());

    jsonfile.close();
    

    
    releaseLock(fd,"/tmp/KinseiJsonClientLock"); //releaselock
    

    
    callback=cgiGetValue (cgiArg, "callback");

    
    if(callback == NULL)
        cout<<json<<endl;
    else
        cout<<callback<<"("<<json<<")"<<endl;

    
    cgiFree(cgiArg);
   

    
    return 0;
}




