#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QPoint>
#include <QDebug>
#include <QPainterPath>
#include <QPainter>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

#include <spline.h>
#include <cmath>

const int numPt=50;
const int numLine=20;
class myLabel : public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget *parent = 0);

    int index;
    bool flag_start=false;
    bool pointSettled[numPt]={false};
    QPoint points[numPt];
    QVector<QPoint> assistPoints[numPt];
    int assistpointsize[numPt]={0};
    QVector<int> shiftX[numPt];
    QVector<int> shiftY[numPt];
    std::vector<point> lines[numLine];
    QVector<QPoint> lines2[numLine];
    int keyPointOfLines[numLine] = {0};
    QPixmap tooth[4];
    //移动点数据
    //flag_selectedPoints=0是points，flag_selectedPoints=1是assistPoints
    bool flag_pointselected=false;
    int type_Pointselected=0;
    int selectedPoint_i;
    int selectedPoint_j;


    int currentWidth;
    int currentHeight;

    //int radius=50;
    int event_selected_dx=0;
    int event_selected_dy=0;

    bool flag_mousepressed=false;
    bool flag_drawPoint=true;

    void getlines();
    void line2Toline(int index_line);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);

signals:
    void instructSignal(int index);
    void updateSignal();
    void ScaleSignal(int x,int y);
    void ScaleSignal2(int x,int y);
private slots:
    void clearAllSlot();
    void saveSlot();
    void templetSlot();

};

#endif // MYLABEL_H
