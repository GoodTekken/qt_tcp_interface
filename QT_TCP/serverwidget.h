#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextCodec>
//#include <QDebug>
#include "AGVMessage/AGV_Struct.h"
#include "AGVMessage/AGV_Message.h"
#include "AGVMessage/AgvExternalPara.h"

#include"PDS_protocol/pdsStruct.h"
#include "Spline/ExternalPathCoordinateSet.h"
#include "Math/UserMatrix.h"
#include "main.h"


#define qtcout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void on_buttonSend_clicked();

    void on_buttonClose_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // SERVERWIDGET_H
