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
#include <math.h>
#include <QVector>
#include <QTableWidgetItem>
#include <QScreen>
#include <QPicture>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

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
    //bool pointSettled[51]={false};
    //QPoint orginpoints[51];

    cv::Mat originmat;
    bool flag_sharpened=false;
    QImage originimage_backup;
    QPixmap originPixmap;

    QString points_detail[51];
    QScreen *screen;
    QPixmap grabpixmap;




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

    void instructSlot(int index);
    void imageupdate();
    void ScaleSlot(int x,int y);
    void ScaleSlot2(int x,int y);

    void on_savePushButton_clicked();

    void on_templetPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
