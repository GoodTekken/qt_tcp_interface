#ifndef COMMUNICATIONCLASS_H
#define COMMUNICATIONCLASS_H

#include <string>


class CommunicationClass
{
public:
    std::string IP;
    std::string Port;

    CommunicationClass();
    ~CommunicationClass();
    CommunicationClass(std::string ip, std::string port);

    void ToString();
};

#endif // COMMUNICATIONCLASS_H
