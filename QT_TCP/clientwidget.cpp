#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;

    tcpSocket = new QTcpSocket(this);

    setWindowTitle("Client");

    ui->textEditWrite->setPlainText("73 74 61 72 00 00 00 01 00 00 00 07 00 04 3f 99 99 9a 00 73 74 6f 70 0d 0a");

//     abc_test = 1;

    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
            {
                ui->textEditRead->setText("Success to connect with Host!");
            }
            );

    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                QByteArray array = tcpSocket->readAll();
//                qtcout(array.toHex());
                ui->textEditRead->append(array);
            }
            );
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void string_to_hex(QString hex,QByteArray &qbyte)
{
    hex=hex.trimmed();
    QStringList sl=hex.split(" ");
    foreach(QString s,sl)
    {
        if(!s.isEmpty())
        {
            qbyte.append((char)s.toInt(0,16)&0xFF);
        }
    }

}

void ClientWidget::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toUInt();

//    tcpSocket->connectToHost(ip,port);
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientWidget::on_pushButtonSend_clicked()
{
//    QString str = ui->textEditWrite->toPlainText();
//    tcpSocket->write(str.toUtf8().data());

    QString str = ui->textEditWrite->toPlainText();
    QByteArray arr;
    string_to_hex(str,arr);
    tcpSocket->write(arr);
//    double leftHole_x = ui->lineEditLeftHole_X->text().toDouble();
//    double leftHole_y = ui->lineEditLeftHole_Y->text().toDouble();
//    double rightHole_x = ui->lineEditRightHole_X->text().toDouble();
//    double rightHole_y = ui->lineEditRightHole_Y->text().toDouble();

//    QPoint leftHole = QPoint(static_cast<int>(leftHole_x),static_cast<int>(leftHole_y));
//    QPoint rightHole = QPoint(static_cast<int>(rightHole_x),static_cast<int>(rightHole_y));
//    QPoint middlePoint = GetMiddlePoint(leftHole,rightHole);
//    line_struct a = TwoPointToLine(leftHole,rightHole);
//    g_AGV_ptr->RackPosition = CoordinateClass(-middlePoint.y(),middlePoint.x(),0,a.angle);
}

void ClientWidget::on_pushButtonClose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

void ClientWidget::on_pushButtonEnter_clicked()
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

void ClientWidget::on_pushButtonLeave_clicked()
{
    //0, 0, 18000, 1500, 300, 18000
    //ExternalPathCoordinateSet Agv_Coordinate(53907, 22995, 9000, 53907, 20315, 9000);
    ExternalPathCoordinateSet Agv_Coordinate(g_AGV_ptr->LayoutStartPosition,g_AGV_ptr->LayoutEndPosition);
    QByteArray data = Agv_Coordinate.GetExternalPathByteFromEndToStart_Byte();
    tcpSocket->write(data);
}
