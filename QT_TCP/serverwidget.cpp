#include "serverwidget.h"
#include "ui_serverwidget.h"

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

    byte* px;
    externalPath* ptr;


    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
            {
                tcpSocket = tcpServer->nextPendingConnection();
                QString ip = tcpSocket->peerAddress().toString();
                quint16 port = tcpSocket->peerPort();
                QString temp = QString("[%1:%2]:Connect Successful!").arg(ip).arg(port);
                ui->textEditRead->setText(temp);

                connect(tcpSocket,&QTcpSocket::readyRead,
                        [=]()mutable
                        {
                            QByteArray array = tcpSocket->readAll();
                            ui->textEditRead->append(array.toHex());
                            QByteArray byte1 = array.toHex();
                            QByteArray buf = QByteArray::fromHex(byte1);
                            int leng =buf.count();
                            char a = buf.at(3);


                            int count = array.count();
                            char szText[100];
                            bool ok;
                            memset(szText,0,100);
                            for(int i = 0;i<count;i++)
                            {
//                                szText[i]=array.data()[i];
                                szText[i]=array.at(i);
                            }

                            qDebug("%d",count);
                            if(count==25)
                            {
                                getPalletRequest *data = (getPalletRequest*)array.data();
//                                externalPath* ptr = reinterpret_cast<externalPath*>(array.data());
                                qDebug("commandID:%d",data->commandID);
                                qDebug("argsLen:%d",data->argsLen);
                                qDebug("palletType:%d",data->palletType);
                                qDebug("depthHint:%f",data->depthHint);
                                qDebug("filterMask:%d",data->filterMask);
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
