#include "CommunicationClass.h"

CommunicationClass::CommunicationClass()
{
    ;
}

CommunicationClass::~CommunicationClass()
{
    ;
}

CommunicationClass::CommunicationClass(std::string ip, std::string port)
{
    IP = ip;
    Port = port;
}


void CommunicationClass::ToString()
{
//    printf("IP:{ %s } Port:{ %s }", this::IP, this::Port);
}
