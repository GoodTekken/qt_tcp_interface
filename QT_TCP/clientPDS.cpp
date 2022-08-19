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
//                qtcout(array.toHex());
                ui->textEditRead->append(array);
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

void ClientPDS::on_pushButtonSend_clicked()
{

    QByteArray array;
    uint32_t commandID = 3;
    uint16_t palletType = 2;
    PalletRequestClass palletRequest(commandID,palletType);
    array = palletRequest.ToArray();
    tcpSocket->write(array);
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
