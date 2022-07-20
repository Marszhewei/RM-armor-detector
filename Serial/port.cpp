#include "../include/Port.h"
#include <string.h>
#include <sys/ioctl.h>
using namespace std;



int Port::OpenPort(const char * devName)
{
    int fd = open(devName,O_RDWR|O_NOCTTY|O_NDELAY);//以读写方式打开；不影响终端设备；进程将一直在休眠状态，直到DCD信号线为0。
    if(fd == -1)
    {
        perror("Can't Open Serial Port");
    }

    else  {
        fcntl(fd, F_SETFL, 0);
        perror("port is open.");
    }
    return fd;
}

int Port::ConfigurePort(int fd)
{
    struct termios port_settings;              
    cfsetispeed(&port_settings, B115200);       // 设定io波特率
    cfsetospeed(&port_settings, B115200);

    port_settings.c_cflag &= ~PARENB;           // 不进行奇偶判断
    port_settings.c_cflag &= ~CSTOPB;           //停止位
    port_settings.c_cflag &= ~CSIZE;            //字符长度
    port_settings.c_cflag |= CS8;

    tcsetattr(fd, TCSANOW, &port_settings);     // apply the settings to the port
    return(fd);
}


bool Port::sendPOS(int fd, double * pos){
    uint8_t send_bytes[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE };
    if(NULL == pos){
        return false;
    }

    *(short*)(send_bytes+1)=(short)pos[0];
    *(short*)(send_bytes+3)=(short)pos[1];
    *(short*)(send_bytes+5)=(short)pos[2];
    
    void swap(uint8_t& a, uint8_t& b);
    swap(send_bytes[1], send_bytes[2]);
    swap(send_bytes[3], send_bytes[4]);
    swap(send_bytes[5], send_bytes[6]);


    // short * data_ptr = (short *)(send_bytes + 1);
    // data_ptr[0] = (short)pos[0];
    // data_ptr[1] = (short)pos[1];
    // data_ptr[2] = (short)pos[2];
    // cout << pos[0] << " " << pos[1] << " " << pos[2] << endl;

    cout << hex;
    for(int i=0; i<8; i++)  {
        cout << (short)send_bytes[i] << endl;
    }

    cout << dec;

    if (8 == write(fd, send_bytes, 8))
        return true;
}


void Port::ClosePort(int fd)
{
    close(fd);
}

void swap(uint8_t& a, uint8_t& b)   {
    uint8_t temp;
    temp = a;
    a = b;
    b = temp;
}

