#ifndef PDSENUMCODE_H
#define PDSENUMCODE_H

enum e_pdsCommandCode
{
    //NOOP is short for “no operation” and can be used as a simple connectivity test or a heartbeat with the PDS daemon at runtime.
    PDS_HEARTBEAT_COMMAND = 0,

    //GetPallet is the central call of the PDS pick-side system. Clients call GetPallet on PDS in order localize the face of the pallet to be picked.
    PDS_GET_PALLET_COMMAND =1,

    //Makes a request of PDS to return array data associated with the last PDS detection attempt made on the currently connected socket.
    PDS_GET_ARRAY_COMMAND =2,

    //key word:calibration //The SaveReferenceForks command makes a request of the PDS to serialize an image of the reference forks for purposes of performing an out-of calibration check.
    PDS_SAVE_REFERENCE_FORKS_COMMAND = 3,

    //GetRack Command
    PDS_GET_RACK_COMMAND = 4,

    //The VolCheck command enables support for checking a generic volume for obstacles.
    PDS_VOL_CHECK_COMMAND =5,

    //Makes a request of PDS to return serialized configuration data.
    PDS_GET_CONFIG_COMMAND = 7,

    //Makes a request of PDS to update current configuration information with the provided configuration information.
    PDS_SET_CONFIG_COMMAND = 8,

    //Makes a request of PDS to save currently loaded configuration to the file system, overwriting previous configuration data.
    PDS_SAVE_CONFIG_COMMAND = 9,

    //Makes a request of PDS to restore factory configuration data.
    PDS_RESET_CONFIG_COMMAND = 10,

    //The SaveExtrinsics command allows clients to stash extrinsic transform information (the pose of the camera in a global coordinate frame of choice) within the PDS daemon running on the device.
    PDS_SAVE_EXTRINSICS_COMMAND =11,
};

#endif // PDSENUMCODE_H
