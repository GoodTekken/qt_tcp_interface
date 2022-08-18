#ifndef PDSERRORCODE_H
#define PDSERRORCODE_H

enum e_pdsErrorCode
{
    //OK
    PDS_NO_ERRORS = 0,

    //An error was trapped, but the cause of it is unknown
    PDS_ERR_UNKNOWN = -1000,


    //The requested pallet type is unsupported
    PDS_TYPE_UNSUPPORTED =-1001

    //Error IO to a file descriptor(socket )
    PDS_IO_ERROR =-1002

    //Error when parsing YAML file
    PDS_YAML_ERROR=-1003
    
    //The filesystem layout on the embedded device is not as expected
    PDS_FILESYSTEM_ERROR=-1004

    //An array or image data or pixel type is not supported
    PDS_DATATYPE_ERROR=-1005

    //Dimensions of a pallet/template are incorrect
    PDS_TEMPLATE_SIZE_ERROR=-1006

    //None of the segmented pockets are clear/empty
    PDS_NO_EMPTY_POCKETS_ERROR=-1007

    //None of the segmented pockets are framed
    PDS_NO_FRAMED_POCKETS_ERROR=-1008

    //Less than two pockets were segmented
    PDS_LESS_THAN_TWO_POCKETS_ERROR=-1009

    //An image processing algorithm has stepped outside the bounds of the image
    PDS_IMAGE_LIMITS_EXCEEDED_ERROR=-1010

    //An array data structure has an unexpected shape for the algorithm in question
    PDS_ARRAY_SIZE_ERROR=-1011

    //Could not segment out the pallet frame, it is occluded
    PDS_FRAME_PATCH_OCCLUDED_ERROR=-1012

    //The estimated yaw angle of the pallet exceeds the configured allowable tolerance
    PDS_YAW_TOO_HARSH =-1013

    //Could not instantiate a model of the pallet face with enough pixel support
    PDS_NO_FACE =-1014

    //Error reading/writing to H5
    PDS_H5_ERROR=-1015

    //Malformed packet header received on socket
    PDS_DAEMON_BAD_HEADER=-1016

    //Malformed packet footer received on socket
    PDS_DAEMON_BAD_FOOTER=-1017
    
    //Unknown command sent to daemon on socket
    PDS_DAEMON_BAD_CMD=-1018

    //Timeout waiting for image data from the camera
    PDS_CAMERA_TIMEOUT=-1019

    //Invalid ID passed as an array argument to GET_ARRAY
    PDS_BAD_ARRAY_ID=-1020

    //ICP could not align point clouds
    PDS_ICP_DID_NOT_CONVERGE=-1021

    //Not enough pixels on the pallet frame to estimate pose
    PDS_NOT_ENOUGH_PIXELS_ON_THE_PATCHES=-1022

    //When looking for the pallet frame, less than two patches were found. THIS HAS BEEN DEPRECATED
    PDS_LESS_THAN_TWO_PATCHES=-1023

    //No combination of the segmented pockets make a valid pallet
    PDS_COULD_NOT_PAIR_POCKETS=-1024

    //Daemon thread explicitly asked to stop
    PDS_THREAD_INTERRUPTED=-1025

    //Denial of service attack on daemon detected
    PDS_DAEMON_BUFFER_LIMIT=-1026

    //A PDS feature being accessed is not currently implemented by the daemon
    PDS_FEATURED_NOT_IMPLEMENTED=-1027

    //Unknown horizontal drop position was specified
    PDS_INVALID_RACK_HPOS =-1028

    //Unknown vertical drop position was specified
    PDS_INVALID_RACK_VPOS =-1029

    //invalid camera position specified
    PDS_INVALID_RACK_CPOS=-1030

    //PDS algorithm aborted because no data were available
    PDS_NO_PIXELS=-1031

    //PDS required a rack upright or beam but none could be found
    PDS_NO_BARS =-1032

    //PDS could not find the horizontal beam
    PDS_NO_BEAM=-1033

    //Plane fitting failed (could be beam face, upright face, floor, etc.)
    PDS_NO_VALID_PLANES=-1034

    //Could not pull the floor on a FLOOR or BOTTOM_RAIL drop
    PDS_NO_FLOOR=-1035

    //Not enough sides to construct pockets
    PDS_NOT_ENOUGH_POCKET_SIDES=-1036

    //Not enough corners to construct sides
    PDS_NOT_ENOUGH_CORNERS=-1037

    //Pallet could not be localized because not enough stringers could be segmented.
    PDS_STRINGER_REPRESENTATION_ERROR=-1038

    //The center stringer has a gap which could be a composed pallet
    PDS_STRINGER_GAP_DETECTED=-1039

    //Obstacle detected in block-stacking drop volume
    PDS_VOL_CHECK_OBST=-1040

    //Composed pallet y-translation is out-out-bounds
    PDS_COMPOSED_Y_TRANSLATION_ERROR=-1041

    //Composed pallet center stringer size is out-of-bounds
    PDS_COMPOSED_CENTER_STRINGER_RATIO_ERROR=-1042

    //PDS has detected unsupported hardware and will not function
    PDS_UNSUPPORTED_HARDWARE=-1043

    //An error occurred at the ROS client layer
    CLIENT_ERROR=-2000

    //The connection to the ROS client was terminated
    CLIENT_ERROR_CONNECTION_TERMINATED=-2001

    //Operation currently in progress (used for CAN deployments only)
    PDS_IN_PROGRESS=-3000
};


#endif // PDSERRORCODE_H
