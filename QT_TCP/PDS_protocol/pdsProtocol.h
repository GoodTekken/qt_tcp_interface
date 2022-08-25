#ifndef PDSPROTOCOl_H
#define PDSPROTOCOl_H

#include <QObject>
//#include <QMutex>
//#include <QSharedPointer>
#include <cstdint>
#include <string>

#include "PDS_protocol/pdsEnumCode.h"
#include "PDS_protocol/pdsErrorCode.h"
#include "PDS_protocol/pdsStruct.h"

#include "PDS_protocol/pdsPalletRequestClass.h"
#include "PDS_protocol/pdsPalletResponseClass.h"
#include "PDS_protocol/pdsPalletCoordinateClass.h"

#include "PDS_protocol/pdsRackRequestClass.h"
#include "PDS_protocol/pdsRackResponseClass.h"
#include "PDS_protocol/pdsRackCoordinateClass.h"

#include "PDS_protocol/pdsVolCheckRequestClass.h"
#include "PDS_protocol/pdsVolCheckResponseClass.h"

#include"PDS_protocol/pdsSaveReferenceForkRequestclass.h"
#include"PDS_protocol/pdsSaveReferenceForkResponseclass.h"
#include"PDS_protocol/pdsGetArrayRequestClass.h"
#include"PDS_protocol/arrayid.h"
#include"PDS_protocol/pdsGetArrayResponseClass.h"

#include"PDS_protocol/pdsGetConfigRequestClass.h"
#include"PDS_protocol/pdsGetConfigResponseClass.h"

#include"PDS_protocol/pdsSetConfigRequestClass.h"
#include"PDS_protocol/pdsSetConfigResponseClass.h"


#endif // PDSPROTOCOl_H
