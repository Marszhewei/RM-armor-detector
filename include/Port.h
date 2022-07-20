#include <stdio.h>
#include <iostream>      // standard input / output functions
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitionss

using namespace std;
class Port
{
public:
    int OpenPort(const char * devName);
    int ConfigurePort(int fd);
    bool sendPOS(int fd, double * pos);
    void ClosePort(int fd);
};

bool TestSerial(double yaw, double pitch, double distance, int fd);
