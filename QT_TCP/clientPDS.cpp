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
    uint32_t commandID = 3;
    uint16_t palletType = 2;
    pdsPalletRequestClass palletRequest(commandID,palletType);
    array = palletRequest.ToArray();
    tcpSocket->write(array);
}



<<<<<<< HEAD
void ClientPDS::on_pushButtonClean_clicked()
{
    ui->textEditRead->clear();

}
=======
>>>>>>> 948bbca6c4525cb13a279f22aed3b1ddd45c78a6

