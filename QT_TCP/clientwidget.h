#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

#include "AGVMessage/AgvExternalPara.h"
#include "Spline/ExternalPathCoordinateSet.h"
#include "Math/UserMatrix.h"
#include "main.h"

//#define qtcout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]";

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();


private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonEnter_clicked();

    void on_pushButtonLeave_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;
};

#endif // CLIENTWIDGET_H
