#include "clientPDS.h"
#include "ui_clientPDS.h"

ClientPDS::ClientPDS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientPDS)
{
    ui->setupUi(this);
    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);
    setWindowTitle("ClientPDS");
    ui->textEditWrite->setPlainText("73 74 61 72 00 00 00 01 00 00 00 07 00 04 3f 99 99 9a 00 73 74 6f 70 0d 0a");

    connect(tcpSocket,&QTcpSocket::connected,this,
            [=]()
            {
                ui->textEditRead->setText("Success to connect with Host!");
            }
            );

    connect(tcpSocket,&QTcpSocket::readyRead,this,
            [=]()
            {
                QByteArray array = tcpSocket->readAll();
                if(array[0]=='s'&&array[1]=='t'&&array[2]=='a'&&array[3]=='r')
                {
                        int command = array[7];
                        qDebug("command:%d",command);
                        switch(command)
                        {
                            case PDS_HEARTBEAT_COMMAND:
                                qDebug("command:%d",command);
                                break;

                            case PDS_GET_PALLET_COMMAND:
                                pds_get_pallet_response_command(array);
                                break;

                            case PDS_GET_ARRAY_COMMAND:
                                break;

                            case PDS_SAVE_REFERENCE_FORKS_COMMAND:
                                break;

                            case PDS_GET_RACK_COMMAND:
                                pds_get_rack_response_command(array);
                                break;

                            case PDS_VOL_CHECK_COMMAND:
                                pds_vol_check_response_command(array);
                                break;

                            case PDS_GET_CONFIG_COMMAND:
                                pds_get_config_response_command(array);
                                break;

                            case PDS_SET_CONFIG_COMMAND:
                                pds_set_config_response_command(array);
                                break;

                            case PDS_SAVE_CONFIG_COMMAND:
                                break;

                            case PDS_RESET_CONFIG_COMMAND:
                                break;

                            case PDS_SAVE_EXTRINSICS_COMMAND:
                                break;

                            default:
                                break;

                        }
                }
            }
            );
}

ClientPDS::~ClientPDS()
{
    delete ui;
}

void ClientPDS::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toUInt();

//    tcpSocket->connectToHost(ip,port);
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientPDS::on_pushButtonClose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

void ClientPDS::on_pushButtonEnter_clicked()
{
    Matrix<double, 4, 4> temp1 = MatrixObject(g_AGV_ptr->AgvReferencePointPosition)*MatrixObject(g_AGV_ptr->CameraPosition);
    Matrix<double, 4, 4> temp2 = temp1*MatrixObject(g_AGV_ptr->RackPosition);

    g_AGV_ptr->RackParameter = CoordinateClass(-650,0,0,0); //3,
    Matrix<double, 4, 4> temp3 = temp2*MatrixObject(g_AGV_ptr->RackParameter);

    posture pallectCoordinate = GetPosture(temp3);



    g_AGV_ptr->LayoutEndPosition = CoordinateClass(pallectCoordinate.x,
                                              pallectCoordinate.y,
                                              pallectCoordinate.z,
                                              pallectCoordinate.angle);

    //0, 0, 18000, 1500, 300, 18000
    //ExternalPathCoordinateSet Agv_Coordinate(53907, 22995, 9000, 53907, 20315, 9000);
    ExternalPathCoordinateSet Agv_Coordinate(g_AGV_ptr->LayoutStartPosition,g_AGV_ptr->LayoutEndPosition);
    QByteArray data = Agv_Coordinate.GetExternalPathByteFromStartToEnd_Byte();
    tcpSocket->write(data);

}

void ClientPDS::on_pushButtonLeave_clicked()
{
    //0, 0, 18000, 1500, 300, 18000
    //ExternalPathCoordinateSet Agv_Coordinate(53907, 22995, 9000, 53907, 20315, 9000);
    ExternalPathCoordinateSet Agv_Coordinate(g_AGV_ptr->LayoutStartPosition,g_AGV_ptr->LayoutEndPosition);
    QByteArray data = Agv_Coordinate.GetExternalPathByteFromEndToStart_Byte();
    tcpSocket->write(data);
}

void ClientPDS::on_pushButtonClean_clicked()
{
    ui->textEditRead->clear();
}

void ClientPDS::on_pushButtonSend_clicked()
{
    QString str = ui->textEditWrite->toPlainText();
    QByteArray arr;
    string_to_hex(str,arr);
    tcpSocket->write(arr);
}

void ClientPDS::on_pushButtonHeartBeat_clicked()
{
    //
    QByteArray array;
    uint32_t commandID=0;
    pdsNoopRequest req{0};
    array=req.toArray();
    tcpSocket->write(array);
}

void ClientPDS::on_pushButtonSendGetPallet_clicked()
{
    QByteArray array;
    uint32_t commandID = 1;
    uint16_t palletType = 2;
    pdsPalletRequestClass palletRequest(commandID,palletType);
    array = palletRequest.ToArray();
    tcpSocket->write(array);
}

void ClientPDS::on_pushButtonSendCommand_clicked()
{
//    For Example:
//    (command 1)
//    QByteArray array;
//    uint32_t commandID = 1;
//    uint16_t palletType = 2;
//    pdsPalletRequestClass palletRequest(commandID,palletType);
//    array = palletRequest.ToArray();
//    tcpSocket->write(array);

//    (command 4)
//    QByteArray array;
//    uint32_t commandID = 4;
//    float depthHint = 2.345;
//    pdsRackRequestClass rackRequest(commandID,depthHint);
//    array = rackRequest.ToArray();
//    tcpSocket->write(array);

//    (command 5)
//    QByteArray array;
//    pds_point min = {.x=-1.1,.y=-2.2,.z=-3.3};
//    pds_point max = {.x=1.1,.y=2.2,.z=3.3};
//    pdsVolCheckRequestClass volCheck(min,max);
//    array = volCheck.ToArray();
//    tcpSocket->write(array);

//    (command 7)
//    QByteArray array;
//    pdsGetConfigRequestClass pdsGetConfigRequest;
//    array=pdsGetConfigRequest.ToArray();
//    tcpSocket->write(array);
//    (command 8)
//    QByteArray array;
//    pdsSetConfigRequestClass pdsSetConfigRequest;
//    array=pdsSetConfigRequest.ToArray();
//    tcpSocket->write(array);
        uint32_t arrayLen = 6;
        char rawArrayData[6] = {1,2,3,4,5,6};
        pdsSetConfigRequestClass pdsSetConfigRequest(arrayLen,rawArrayData);
        QByteArray sendArray;
        sendArray = pdsSetConfigRequest.ToArray();
        tcpSocket->write(sendArray);

}


void ClientPDS::pds_get_pallet_response_command(QByteArray array)
{
    int count = array.count();
    if(count == 22)
    {
        pdsPalletResponseClass palletResponse(array);
        QString str= "commandID:"+QString::number(palletResponse.palletResponseFailureStruct.commandID) +
                     " errorCode:"+QString::number(palletResponse.palletResponseFailureStruct.errorCode)+
                     " len:"+QString::number(palletResponse.palletResponseFailureStruct.len);
        ui->textEditRead->append(str);
    }
    else if(count == 78)
    {
        pdsPalletResponseClass palletResponse(array);
        QString str= "commandID:"+QString::number(palletResponse.palletResponseSuccessStruct.commandID) +"\r\n"+
        " errorCode:"+QString::number(palletResponse.palletResponseSuccessStruct.errorCode)+"\r\n"+
        " len:"+QString::number(palletResponse.palletResponseSuccessStruct.len)+"\r\n"+
        " elapsedTime:"+QString::number(palletResponse.palletResponseSuccessStruct.elapsedTime)+"\r\n"+
        " confidence:"+QString::number(palletResponse.palletResponseSuccessStruct.confidence)+"\r\n"+
        " palletX:"+QString::number(palletResponse.palletResponseSuccessStruct.palletX)+"\r\n"+
        " palletY:"+QString::number(palletResponse.palletResponseSuccessStruct.palletY)+"\r\n"+
        " palletZ:"+QString::number(palletResponse.palletResponseSuccessStruct.palletZ)+"\r\n"+
        " leftPocketX:"+QString::number(palletResponse.palletResponseSuccessStruct.leftPocketX)+"\r\n"+
        " leftPocketY:"+QString::number(palletResponse.palletResponseSuccessStruct.leftPocketY)+"\r\n"+
        " leftPocketZ:"+QString::number(palletResponse.palletResponseSuccessStruct.leftPocketZ)+"\r\n"+
        " rightPocketX:"+QString::number(palletResponse.palletResponseSuccessStruct.rightPocketX)+"\r\n"+
        " rightPocketY:"+QString::number(palletResponse.palletResponseSuccessStruct.rightPocketY)+"\r\n"+
        " rightPocketZ:"+QString::number(palletResponse.palletResponseSuccessStruct.rightPocketZ)+"\r\n"+
        " roll:"+QString::number(palletResponse.palletResponseSuccessStruct.roll)+"\r\n"+
        " pitch:"+QString::number(palletResponse.palletResponseSuccessStruct.pitch)+"\r\n"+
        " yaw:"+QString::number(palletResponse.palletResponseSuccessStruct.yaw)+"\r\n"
                ;
        ui->textEditRead->append(str);

    }
    else
    {
        ui->textEditRead->append(array);
    }
}



void ClientPDS::pds_get_rack_response_command(QByteArray array)
{
    int count = array.count();
    if(count == 22)
    {
        pdsRackResponseClass rackResponse(array);
        QString str= "commandID:"+QString::number(rackResponse.rackResponseFailureStruct.commandID) +
                     " errorCode:"+QString::number(rackResponse.rackResponseFailureStruct.errorCode)+
                     " len:"+QString::number(rackResponse.rackResponseFailureStruct.len);
        ui->textEditRead->append(str);
    }
    else if(count == 59)
    {
        pdsRackResponseClass rackResponse(array);
        QString str= "commandID:"+QString::number(rackResponse.rackResponseSuccessStruct.commandID) +"\r\n"+
        " errorCode:"+QString::number(rackResponse.rackResponseSuccessStruct.errorCode)+"\r\n"+
        " len:"+QString::number(rackResponse.rackResponseSuccessStruct.len)+"\r\n"+
        " elapsedTime:"+QString::number(rackResponse.rackResponseSuccessStruct.elapsedTime)+"\r\n"+
        " confidence:"+QString::number(rackResponse.rackResponseSuccessStruct.confidence)+"\r\n"+
        " X:"+QString::number(rackResponse.rackResponseSuccessStruct.X)+"\r\n"+
        " Y:"+QString::number(rackResponse.rackResponseSuccessStruct.Y)+"\r\n"+
        " Z:"+QString::number(rackResponse.rackResponseSuccessStruct.Z)+"\r\n"+
        " roll:"+QString::number(rackResponse.rackResponseSuccessStruct.roll)+"\r\n"+
        " pitch:"+QString::number(rackResponse.rackResponseSuccessStruct.pitch)+"\r\n"+
        " yaw:"+QString::number(rackResponse.rackResponseSuccessStruct.yaw)+"\r\n"
        " side:"+QString::number(rackResponse.rackResponseSuccessStruct.side)+"\r\n"
        " flag:"+QString::number(rackResponse.rackResponseSuccessStruct.flag)+"\r\n"
                ;
        ui->textEditRead->append(str);

    }
    else
    {
        ui->textEditRead->append(array);
    }
}

void ClientPDS::pds_vol_check_response_command(QByteArray array)
{
    pdsVolCheckResponseClass volCheckResponse(array);
    QString str= "commandID:"+QString::number(volCheckResponse.volCheckResponseStruct.commandID) +"\r\n"+
    " errorCode:"+QString::number(volCheckResponse.volCheckResponseStruct.errorCode)+"\r\n"+
    " len:"+QString::number(volCheckResponse.volCheckResponseStruct.len)+"\r\n"+
    " elapsedTime:"+QString::number(volCheckResponse.volCheckResponseStruct.elapsedTime)+"\r\n"+
    " Npix:"+QString::number(volCheckResponse.volCheckResponseStruct.Npix)+"\r\n"
            ;
    ui->textEditRead->append(str);
}

void ClientPDS::pds_get_config_response_command(QByteArray array)
{
    pdsGetConfigResponseClass pdsGetConfigResponse(array);
    QString str= "commandID:"+QString::number(pdsGetConfigResponse.getConfigResponseStruct.commandID) +"\r\n"+
    " errorCode:"+QString::number(pdsGetConfigResponse.getConfigResponseStruct.errorCode)+"\r\n"+
    " len:"+QString::number(pdsGetConfigResponse.getConfigResponseStruct.len)+"\r\n"+
            " ";
    ui->textEditRead->append(str);
}

void ClientPDS::pds_set_config_response_command(QByteArray array)
{
    pdsSetConfigResponseClass pdsSetConfigResponse(array);
    QString str= "commandID:"+QString::number(pdsSetConfigResponse.setConfigResponseStruct.commandID) +"\r\n"+
    " errorCode:"+QString::number(pdsSetConfigResponse.setConfigResponseStruct.errorCode)+"\r\n"+
    " len:"+QString::number(pdsSetConfigResponse.setConfigResponseStruct.len)+"\r\n"+
            " ";
    ui->textEditRead->append(str);
}
