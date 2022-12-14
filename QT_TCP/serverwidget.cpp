#include "serverwidget.h"
#include "ui_serverwidget.h"
#include "PDS_protocol/pdsProtocol.h"

typedef unsigned char byte;


ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    tcpServer = NULL;
    tcpSocket = NULL;

    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,55556);  //5678

    setWindowTitle("Server:Port_55556");

    connect(tcpServer,&QTcpServer::newConnection,this,
            [=]()
            {
                tcpSocket = tcpServer->nextPendingConnection();
                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]:Connect Successful!").arg(ip).arg(port);
                ui->textEditRead->setText(temp);

                connect(tcpSocket,&QTcpSocket::readyRead,this,
                        [=]()mutable
                        {
                            QByteArray array = tcpSocket->readAll();
                            ui->textEditRead->append(array.toHex());
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
                                            pds_get_pallet_command(array);
                                            break;

                                        case PDS_GET_ARRAY_COMMAND:
                                            pds_get_array_command(array);
                                            break;

                                        case PDS_SAVE_REFERENCE_FORKS_COMMAND:

                                            break;

                                        case PDS_GET_RACK_COMMAND:
                                            pds_get_rack_command(array);
                                            break;

                                        case PDS_VOL_CHECK_COMMAND:
                                            pds_vol_check_command(array);
                                            break;

                                        case PDS_GET_CONFIG_COMMAND:
                                            pds_get_config_command(array);
                                            break;

                                        case PDS_SET_CONFIG_COMMAND:
                                            pds_set_config_command(array);
                                            break;

                                        case PDS_SAVE_CONFIG_COMMAND:
                                            pds_save_config_command(array);
                                            break;

                                        case PDS_RESET_CONFIG_COMMAND:
                                            pds_reset_config_command(array);
                                            break;

                                        case PDS_SAVE_EXTRINSICS_COMMAND:
                                            pds_save_extrinsics_command(array);
                                            break;

                                        default:
                                            break;

                                    }
                            }
                        }
                        );

            }
            );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_buttonSend_clicked()
{
    if(tcpServer == NULL)
    {
        return;
    }
    QString str= ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_buttonClose_clicked()
{
    if(tcpServer == NULL)
    {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpServer = NULL;
}


void ServerWidget::pds_get_pallet_command(QByteArray array)
{
    int count = array.count();
    qDebug("%d",count);
    if(count==18){
        int errorcode=0;
        if(errorcode!=0){

        }
        else {
            tcpSocket->write("connected");
        }
    }
    if(count==25)
    {
        pdsPalletRequestClass palletRequest(array);
        QString str= "commandID:"+QString::number(palletRequest.palletRequestStruct.commandID) +
                     " palletType:"+QString::number(palletRequest.palletRequestStruct.palletType)+
                     " depthHint:"+QString::number(palletRequest.palletRequestStruct.depthHint);
//                                tcpSocket->write(str.toUtf8().data());
        int errorCode = 0;
        if(errorCode !=0 )
        {
            pdsPalletResponseClass palletResponse;
            palletResponse.response_failure(palletRequest.palletRequestStruct.commandID,errorCode);
            QByteArray array;
            array = palletResponse.ToFailureArray();
            tcpSocket->write(array);
        }
        else
        {
            float elapsedTime = 100.1;
            float confidence = 200.2;
            pds_point centerPoint = {.x=0.1,.y=0.2,.z=0.3};
            pds_point leftPoint = {.x=-1.1,.y=-2.2,.z=-3.3};
            pds_point rightPoint = {.x=1.1,.y=2.2,.z=3.3};
            pds_posture posture = {.roll=0.875,.pitch=0.625,.yaw=-0.375};
            pdsPalletCoordinateClass palletCoordinate(
                                     elapsedTime,
                                     confidence,
                                     centerPoint,
                                     leftPoint,
                                     rightPoint,
                                     posture);

            pdsPalletResponseClass palletResponse;
            palletResponse.response_success(palletCoordinate);
            QByteArray array;
            array = palletResponse.ToSuccessArray();
            tcpSocket->write(array);
        }
    }
}

void ServerWidget::pds_get_rack_command(QByteArray array)
{
    pdsRackRequestClass rackRequest(array);
    QString str= "commandID:"+QString::number(rackRequest.rackRequestStruct.commandID) + "\r\n"+
                " argsLen:"+QString::number(rackRequest.rackRequestStruct.argsLen)+ "\r\n"+
                " horizontalDropPos:"+QString::number(rackRequest.rackRequestStruct.horizontalDropPos)+ "\r\n"+
                " verticalDropPos:"+QString::number(rackRequest.rackRequestStruct.verticalDropPos)+  "\r\n"+
                " cameraPos:"+QString::number(rackRequest.rackRequestStruct.cameraPos)+  "\r\n"+
                " depthHint:"+QString::number(rackRequest.rackRequestStruct.depthHint)+  "\r\n"+
                " zHint:"+QString::number(rackRequest.rackRequestStruct.zHint)+  "\r\n"+
                " clearingDepth:"+QString::number(rackRequest.rackRequestStruct.clearingDepth)+  "\r\n"+
                " clearingWidth:"+QString::number(rackRequest.rackRequestStruct.clearingWidth)+  "\r\n"+
                " clearingHeight:"+QString::number(rackRequest.rackRequestStruct.clearingHeight)+  "\r\n"+
                " strayLightFilter:"+QString::number(rackRequest.rackRequestStruct.strayLightFilter)+  "\r\n"+
                 " ";
    qDebug("%s",qPrintable(str));

    int errorCode = 0;
    if(errorCode !=0 )
    {
        pdsRackResponseClass rackResponse;
        rackResponse.response_failure(rackRequest.rackRequestStruct.commandID,errorCode);
        QByteArray array;
        array = rackResponse.ToFailureArray();
        tcpSocket->write(array);
    }
    else
    {
        float elapsedTime = 100.1;
        float confidence = 200.2;
        pds_point pds_point = {.x=0.1,.y=0.2,.z=0.3};
        pds_posture rack_posture = {.roll=0.875,.pitch=0.625,.yaw=-0.375};
        uint8_t side = 12;
        uint32_t flag = 13;

        pdsRackCoordinateClass rackCoordinate(
                                                elapsedTime,
                                                confidence,
                                                pds_point,
                                                rack_posture,
                                                side,
                                                flag);

        pdsRackResponseClass rackResponse;
        rackResponse.response_success(rackCoordinate);
        QByteArray array;
        array = rackResponse.ToSuccessArray();
        tcpSocket->write(array);
    }
}


void ServerWidget::pds_vol_check_command(QByteArray array)
{
    pdsVolCheckRequestClass volCheckRequest(array);
    QString str= "commandID:"+QString::number(volCheckRequest.volCheckRequestStruct.commandID) + "\r\n"+
                " argsLen:"+QString::number(volCheckRequest.volCheckRequestStruct.argsLen)+ "\r\n"+
                " xmin:"+QString::number(volCheckRequest.volCheckRequestStruct.xmin)+ "\r\n"+
                " xmax:"+QString::number(volCheckRequest.volCheckRequestStruct.xmax)+  "\r\n"+
                " ymin:"+QString::number(volCheckRequest.volCheckRequestStruct.ymin)+  "\r\n"+
                " ymax:"+QString::number(volCheckRequest.volCheckRequestStruct.ymax)+  "\r\n"+
                " zmin:"+QString::number(volCheckRequest.volCheckRequestStruct.zmin)+  "\r\n"+
                " zmax:"+QString::number(volCheckRequest.volCheckRequestStruct.zmax)+  "\r\n"+
                " strayLightFilter:"+QString::number(volCheckRequest.volCheckRequestStruct.strayLightFilter)+  "\r\n"+
                 " ";
    qDebug("%s",qPrintable(str));

    int errorCode = -1001;
    int Npix = 2002;
    pdsVolCheckResponseClass pdsVolCheckResponse(errorCode,Npix);
    QByteArray sendArray;
    sendArray = pdsVolCheckResponse.ToArray();
    tcpSocket->write(sendArray);
}
void ServerWidget::pds_get_array_command(QByteArray array)
{
    char test[10]={'h','e','l','l','o','w','o','r','l','d'};
    arrayType tp={2,5,1,0};
    pdsGetArrayResponseClass response{10,test,&tp};
    QByteArray arr;
    arr.clear();
    arr=response.toArray();
    pdsGetArrayResponseClass fin{arr};
    arr.clear();
    arr=fin.toArray();
    qDebug("no array");
    //arr.clear();
    //arr=temp.toArray();

}


void ServerWidget::pds_get_config_command(QByteArray array)
{
    pdsGetConfigRequestClass pdsGetConfigRequest(array);
    QString str= "commandID:"+QString::number(pdsGetConfigRequest.getConfigRequestStruct.commandID) + "\r\n"+
                " argsLen:"+QString::number(pdsGetConfigRequest.getConfigRequestStruct.argsLen)+ "\r\n"+
                 " ";
    qDebug("%s",qPrintable(str));

//    pdsGetConfigResponseClass pdsGetConfigResponse;
//    QByteArray sendArray;
//    sendArray = pdsGetConfigResponse.ToArray();
//    tcpSocket->write(sendArray);

    uint32_t arrayLen = 6;
    char rawArrayData[6] = {1,2,3,4,5,6};
    pdsGetConfigResponseClass pdsGetConfigResponse(arrayLen,rawArrayData);
    QByteArray sendArray;
    sendArray = pdsGetConfigResponse.ToArray();
    tcpSocket->write(sendArray);
}
void ServerWidget::pds_save_config_command(QByteArray array)
{

    pdsSaveConfigRequestClass req{array};
    QByteArray arr=req.toArray();
    pdsSaveConfigResponseClass res{};
    arr.clear();
    arr=res.toArray();
    pdsSaveConfigResponseClass fin{arr};
    /*


    here call the function to save configs!!!!

     */
    tcpSocket->write("save config!");




}
void ServerWidget::pds_reset_config_command(QByteArray array)
{
    //pdsResetConfigRequestClass req{array};
    QByteArray arr;
    //pdsResetConfigRequestClass fin{arr};

    pdsResetConfigResponseClass response{};
    arr=response.toArray();
    pdsResetConfigResponseClass fin{arr};
    /*
    here is code reset configs



    */
    qDebug("reset success!!");





}

void ServerWidget::pds_save_extrinsics_command(QByteArray array)
{
    //pdsSaveExtrinsicsRequestClass req{array};

    QByteArray arr;
   pdsSaveExtrinsicsResponseClass res{};
    arr=res.toArray();
    pdsSaveExtrinsicsResponseClass fin{arr};

    qDebug("save success!!");






}

void ServerWidget::pds_set_config_command(QByteArray array)
{
    pdsSetConfigRequestClass pdsSetConfigRequest(array);
    QString str= "commandID:"+QString::number(pdsSetConfigRequest.setConfigRequestStruct.commandID) + "\r\n"+
                " argsLen:"+QString::number(pdsSetConfigRequest.setConfigRequestStruct.argsLen)+ "\r\n"+
                 " ";
    qDebug("%s",qPrintable(str));

    pdsSetConfigResponseClass pdsSetConfigResponse;
    QByteArray sendArray;
    sendArray = pdsSetConfigResponse.ToArray();
    tcpSocket->write(sendArray);
}

