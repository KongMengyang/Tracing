#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QColor>
#include <QIcon>
#include <QStringList>
#include <QString>
#include <QTextStream>
#include <QVector>
#include <QTableWidgetItem>
#include <QScreen>
#include <QPicture>
#include <QDialog>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <math.h>
#include "reportdialog.h"

using namespace std;

class tclObj
{

public:
    double max,min;
    int type;
    QPoint points[4];
    tclObj(void)
    {
        /*max=0;
        min=0;
        type=0;
        points[4]={-1};*/
    }

    tclObj(double a,double b,int  c,QPoint  p0,QPoint  p1,QPoint  p2,QPoint  p3)
    {

        max=a;
        min=b;
        type=c;
        points[0]=p0;
        points[1]=p1;
        points[2]=p2;
        points[3]=p3;

    }


};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QImage originimage;
    QImage currentimage;
    double length_10mm=1;
    int initialWidth;
    int initialHeight;
    int currentWidth;
    int currentHeight;
    int rThreshold=127;
    int gThreshold=127;
    int bThreshold=127;
    int numTclObj=17;
    //bool pointSettled[51]={false};
    //QPoint orginpoints[51];

    cv::Mat originmat;
    bool flag_sharpened=false;
    QImage originimage_backup;
    QPixmap originPixmap;

    QString points_detail[51];
    //QScreen *screen;
    QPixmap grabpixmap;

    tclObj  targetObj[15];
    double results[15];



    void QImageToMat();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
    void clearAllSignal();
    void saveSignal();
    void templetSignal();


private slots:
    void on_openPushbutton_clicked();
    void on_contrastSlider_valueChanged(int value);
    void on_brightnessSlider_valueChanged(int value);
    void on_sharpenPushButton_clicked();
    void on_clearPushbutton_clicked();
    void on_measurePushbutton_clicked();
    void on_savePushButton_clicked();
    void on_templetPushButton_clicked();
    void on_pointDispalyPushButton_clicked();
    void on_completePushButton_clicked();

    void instructSlot(int index);
    void imageupdate();
    void ScaleSlot(int x,int y);
    void ScaleSlot2(int x,int y);
    double angle_2lines(QPoint a,QPoint b,QPoint c,QPoint d);
    double distance_pointtoline(QPoint a, QPoint b, QPoint c);
    double distancep2p(QPoint a,QPoint b);
    void getResults();
    void getObjResult(int x);


private:
    Ui::MainWindow *ui;
    reportDialog *rd;
};

#endif // MAINWINDOW_H
