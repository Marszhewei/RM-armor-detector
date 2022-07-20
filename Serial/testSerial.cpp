#include "../include/Port.h"

// #define DEBUG_


bool TestSerial(double yaw, double pitch, double distance, int fd)
{
    // uint8_t buff[] = { 0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFE};
    // 0XFF:帧头 buff[1]~buff[2]:yaw*100 buff[3]~buff[4]:pitch*100
    // buff[5]~buff[6]: distance*100  0XFE:帧尾


    try {
        Port port;

        double pos[3] = {(yaw+90)*100, (pitch+90)*100, distance};

        #ifdef DEBUG_
        cout << pos[0] << endl;
        cout << pos[1] << endl;
        cout << pos[2] << endl;
        #endif

        port.sendPOS(fd, pos);
        usleep(5000);
               
    }
    catch(...)   {
        return false;
    }

    return true;
}