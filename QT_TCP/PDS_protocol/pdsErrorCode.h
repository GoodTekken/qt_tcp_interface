#ifndef PDSERRORCODE_H
#define PDSERRORCODE_H

enum e_pdsErrorCode
{
    //OK
    PDS_NO_ERRORS = 0,

    //An error was trapped, but the cause of it is unknown
    PDS_ERR_UNKNOWN = -1000,
};

#endif // PDSERRORCODE_H
