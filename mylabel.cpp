#include "mylabel.h"
using namespace std;




myLabel::myLabel(QWidget *parent):QLabel(parent)
{
    tooth[0].load(":/image/image/teeth_png/teeth_0.png");
    tooth[1].load(":/image/image/teeth_png/teeth_1.png");
    tooth[2].load(":/image/image/teeth_png/teeth_2.png");
    tooth[3].load(":/image/image/teeth_png/teeth_3.png");

    index=0;
    keyPointOfLines[0]=2;
    keyPointOfLines[1]=3;
    keyPointOfLines[2]=6;
    keyPointOfLines[3]=6;
    keyPointOfLines[4]=7;
    keyPointOfLines[5]=7;
    keyPointOfLines[6]=15;
    keyPointOfLines[7]=22;
    keyPointOfLines[8]=32;
    keyPointOfLines[9]=45;
    keyPointOfLines[10]=46;
    keyPointOfLines[11]=49;

    //前4条线
    assistpointsize[2]=3;
    assistpointsize[3]=3;
    assistpointsize[4]=3;
    assistpointsize[5]=14;
    assistpointsize[6]=6;
    assistpointsize[7]=2;
    //上轮廓
    assistpointsize[8]=1;
    assistpointsize[9]=2;
    assistpointsize[10]=2;
    assistpointsize[11]=3;
    assistpointsize[12]=2;
    assistpointsize[13]=1;
    assistpointsize[14]=2;
    assistpointsize[15]=2;
    //下轮廓
    assistpointsize[16]=2;
    assistpointsize[17]=2;
    assistpointsize[18]=3;
    assistpointsize[19]=2;
    assistpointsize[20]=1;
    assistpointsize[21]=1;
    assistpointsize[22]=3;
    //下颚
    assistpointsize[27]=3;
    assistpointsize[28]=1;
    assistpointsize[29]=3;
    assistpointsize[30]=1;
    assistpointsize[31]=1;
    assistpointsize[32]=1;


    assistpointsize[33]=1;
    assistpointsize[34]=5;
    assistpointsize[35]=4;
    assistpointsize[45]=4;
    assistpointsize[49]=2;



    QFile file(":/text/text/assistShift.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
    QTextStream in(&file);
    for(int i=0;i<numPt;i++)
    {
        for(int j=0;j<assistpointsize[i];j++)
        {
            int x=in.readLine().toInt();
            int y=in.readLine().toInt();
            shiftX[i].push_back(x);
            shiftY[i].push_back(y);
        }
    }
    file.close();

}
point qpTop(QPoint qp)
{
    point p;
    p.setPoint(qp.x(),qp.y());
    return p;

}

void myLabel::getlines()
{
    //lines
    if(pointSettled[keyPointOfLines[0]]==true)
    {
        lines2[0] = QVector<QPoint>()
                << points[2]
                << assistPoints[2][0]
                << assistPoints[2][1]
                << assistPoints[2][2]
                << points[2];
        line2Toline(0);
    }
    if(pointSettled[keyPointOfLines[1]]==true)
    {
        lines2[1] = QVector<QPoint>()
                << points[3]
                << assistPoints[3][0]
                << assistPoints[3][1]
                << assistPoints[3][2];
        line2Toline(1);
    }
    if(pointSettled[keyPointOfLines[2]]==true)
    {
        lines2[2] = QVector<QPoint>()
                << points[6]
                << assistPoints[6][0]
                << assistPoints[6][1]
                << assistPoints[6][2];
        line2Toline(2);
    }
    if(pointSettled[keyPointOfLines[3]]==true)
    {
        lines2[3] = QVector<QPoint>()
                << assistPoints[6][2]
                << assistPoints[6][3]
                << assistPoints[6][4]
                << assistPoints[6][5];
        line2Toline(3);
    }
    if(pointSettled[keyPointOfLines[4]]==true)
    {
        lines2[4] = QVector<QPoint>()
                << points[7]
                << assistPoints[5][0]
                << assistPoints[5][1]
                << assistPoints[5][2]
                << assistPoints[5][3]
                << assistPoints[5][4]
                << assistPoints[5][5]
                << assistPoints[5][6]
                << assistPoints[5][7]
                << assistPoints[5][8]
                << assistPoints[5][9]
                << assistPoints[5][10]
                << assistPoints[5][11]
                << assistPoints[5][12]
                << assistPoints[5][13];
        line2Toline(4);
        /*lines[4].clear();
        lines[4].push_back(qpTop(points[7]));
        for(int i=0;i<14;i++)
        {
            lines[4].push_back(qpTop(assistPoints[5][i]));
        }*/
    }
    if(pointSettled[keyPointOfLines[5]]==true)
    {
        lines2[5] = QVector<QPoint>()
                << points[7]
                << assistPoints[7][0]
                << assistPoints[7][1]
                << points[4]
                << assistPoints[4][0]
                << assistPoints[5][11]
                << assistPoints[4][1]
                << assistPoints[4][2];
        line2Toline(5);
    }
    if(pointSettled[keyPointOfLines[6]]==true)
    {
        lines2[6] = QVector<QPoint>()
                << points[8]
                << assistPoints[8][0]
                << points[9]
                << assistPoints[9][0]
                << assistPoints[9][1]
                << points[10]
                << assistPoints[10][0]
                << assistPoints[10][1]
                << points[11]
                << assistPoints[11][0]
                << assistPoints[11][1]
                << assistPoints[11][2]
                << points[12]
                << assistPoints[12][0]
                << points[13]
                << assistPoints[13][0]
                << points[14]
                << assistPoints[14][0]
                << assistPoints[14][1]
                << points[15]
                << assistPoints[15][0]
                << assistPoints[15][1];
        line2Toline(6);
    }
    if(pointSettled[keyPointOfLines[7]]==true)
    {
        lines2[7] = QVector<QPoint>()
                << assistPoints[16][0]
                << assistPoints[16][1]
                << points[16]
                << assistPoints[17][0]
                << assistPoints[17][1]
                << points[17]
                << assistPoints[18][0]
                << assistPoints[18][1]
                << assistPoints[18][2]
                << points[18]
                << assistPoints[19][0]
                << assistPoints[19][1]
                << points[19]
                << assistPoints[20][0]
                << points[20]
                << assistPoints[21][0]
                << points[21]
                << assistPoints[22][0]
                << assistPoints[22][1]
                << assistPoints[22][2]
                << points[22];
        line2Toline(7);
    }
    if(pointSettled[keyPointOfLines[8]]==true)
    {
        lines2[8] = QVector<QPoint>()
                << points[26]
                << assistPoints[27][2]
                << assistPoints[27][1]
                << assistPoints[27][0]
                << points[27]
                << assistPoints[28][0]
                << points[28]
                << assistPoints[31][0]
                << points[31]
                << assistPoints[32][0]
                << points[32]
                << assistPoints[30][0]
                << points[30]
                << assistPoints[29][2]
                << assistPoints[29][1]
                << assistPoints[29][0]
                << points[29];
        line2Toline(8);

    }
    if(pointSettled[keyPointOfLines[9]]==true)
    {
        lines2[9] = QVector<QPoint>()
                << points[42]
                << points[23]
                << points[24]
                << points[25]
                << points[26]
                << assistPoints[45][3]
                << assistPoints[45][2]
                << assistPoints[45][1]
                << assistPoints[45][0]
                << points[45];

        line2Toline(9);
    }
    if(pointSettled[keyPointOfLines[10]]==true)
    {
        lines2[10] = QVector<QPoint>()
                << points[46]
                << assistPoints[33][0]
                << points[33]
                << assistPoints[34][0]
                << points[34]
                << assistPoints[34][1]
                << assistPoints[34][2]
                << assistPoints[34][3]
                << assistPoints[34][4]
                << assistPoints[35][1]
                << assistPoints[35][0]
                << points[35];
        line2Toline(10);
    }
    if(pointSettled[keyPointOfLines[11]]==true)
    {
        lines2[11] = QVector<QPoint>()
                << points[35]
                << assistPoints[35][2]
                << assistPoints[35][3]
                << assistPoints[49][1]
                << assistPoints[49][0]
                << points[49];
        line2Toline(11);
    }

}

QPainterPath getCurvePath(QVector<QPoint> points,bool flag_round)
{
    QPainterPath path(points[0]);
    int numPt=points.size();
    double scale=0.6;
    QPoint *midPoints=new QPoint[numPt];
    for(int i=0;i<numPt-1;i++)
    {
        int nexti=(i+1)%numPt;
        midPoints[i].setX((points[i].x()+points[nexti].x())/2);
        midPoints[i].setY((points[i].y()+points[nexti].y())/2);
    }

    QPoint *extraPoints=new QPoint[2*numPt];

    //平移
    for(int i=0;i<numPt;i++)
    {
        int nexti=(i+1)%numPt;
        int backi=(i+numPt-1)%numPt;
        QPoint midmid;
        midmid.setX((midPoints[i].x()+midPoints[backi].x())/2);
        midmid.setY((midPoints[i].y()+midPoints[backi].y())/2);
        int offsetx=points[i].x()-midmid.x();
        int offsety=points[i].y()-midmid.y();


        int extraIndex=2*i;
        extraPoints[extraIndex].setX(midPoints[backi].x()+offsetx);
        extraPoints[extraIndex].setY(midPoints[backi].y()+offsety);
        //收缩
        int addx=(extraPoints[extraIndex].x()-points[i].x())*scale;
        int addy=(extraPoints[extraIndex].y()-points[i].y())*scale;
        extraPoints[extraIndex].setX(points[i].x()+addx);
        extraPoints[extraIndex].setY(points[i].y()+addy);


        int extranexti=(extraIndex+1)%(2*numPt);
        extraPoints[extranexti].setX(midPoints[i].x()+offsetx);
        extraPoints[extranexti].setY(midPoints[i].y()+offsety);
        //收缩
        addx=(extraPoints[extranexti].x()-points[i].x())*scale;
        addy=(extraPoints[extranexti].y()-points[i].y())*scale;
        extraPoints[extranexti].setX(points[i].x()+addx);
        extraPoints[extranexti].setY(points[i].y()+addy);

    }
    if(flag_round==true)
    {
        for(int i=1;i<numPt;i++)
        {
            path.cubicTo(extraPoints[2*i-1],extraPoints[2*i],points[i]);
        }
        path.cubicTo(extraPoints[2*numPt-1],extraPoints[0],points[0]);
    }
    else
    {
        extraPoints[0]=points[0];
        extraPoints[1]=points[0];
        extraPoints[2*numPt-2]=points[numPt-1];
        extraPoints[2*numPt-1]=points[numPt-1];
        for(int i=1;i<numPt;i++)
        {
            path.cubicTo(extraPoints[2*i-1],extraPoints[2*i],points[i]);
        }
    }
    delete []midPoints;
    delete []extraPoints;


    return path;
}

void myLabel::line2Toline(int index_line)
{
    lines[index_line].clear();
    for(int i=0;i<lines2[index_line].size();i++)
    {
        lines[index_line].push_back(qpTop(lines2[index_line][i]));
    }
}



void myLabel::clearAllSlot()
{
    for(int i=0;i<numPt;i++)
    {
        pointSettled[i]=false;
        assistPoints[i].clear();

    }
    for(int i=0;i<numLine;i++)
    {
        lines[i].clear();
        lines2[i].clear();
    }
}

void myLabel::saveSlot()
{
    QFile file("1.txt");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);
    for(int i=0;i<numPt;i++)
    {
        for(int j=0;j<assistpointsize[i];j++)
        {
            int x=assistPoints[i][j].x()-points[i].x();
            int y=assistPoints[i][j].y()-points[i].y();
            out<<x<<endl;
            out<<y<<endl;

            /*int x=in.readLine().toInt();
            int y=in.readLine().toInt();
            shiftX[i].push_back(x);
            shiftY[i].push_back(y);*/
        }
    }
    file.close();


    QFile file2("2.txt");

    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out2(&file2);
    for(int i=0;i<numPt;i++)
    {
        int x=points[i].x();
        int y=points[i].y();

        out2<<x<<endl;
        out2<<y<<endl;
    }
    file2.close();
}

void myLabel::templetSlot()
{
    flag_start=true;
    QFile file(":/text/text/templet.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
    QTextStream in(&file);
    for(index=0;index<numPt;index++)
    {
        int x=in.readLine().toInt();
        int y=in.readLine().toInt();
        points[index].setX(x);
        points[index].setY(y);
        for(int j=0;j<assistpointsize[index];j++)
        {
            QPoint pt(points[index].x()+shiftX[index][j],points[index].y()+shiftY[index][j]);
            assistPoints[index].push_back(pt);
        }
        pointSettled[index]=true;
    }
    file.close();
    update();
}



double distancep2p(QPoint a,QPoint b)
{
    return sqrt((a.x()-b.x())*(a.x()-b.x())+(a.y()-b.y())*(a.y()-b.y()));
}



void myLabel::mousePressEvent(QMouseEvent* event)
{
    /*
    QPoint qp(event->pos());
    point p;
    p=qpTop(qp);
    qDebug()<<qp<<" "<<p.x<<" "<<p.y;
    */
    if(flag_start==false){
        return;
    }
    flag_mousepressed=true;
    for(int i=0;i<numPt;i++)
    {
        int acc=5;
        if(pointSettled[i]==true){
            QPoint mouseNow=event->pos();
            if(distancep2p(mouseNow,points[i])<=acc)
            {

                selectedPoint_i=i;
                flag_pointselected=true;
                type_Pointselected=1;
                return;
            }
            for(int j=0;j<assistPoints[i].size();j++)
            {
                if(distancep2p(mouseNow,assistPoints[i][j])<=acc)
                {
                    selectedPoint_i=i;
                    selectedPoint_j=j;
                    flag_pointselected=true;
                    type_Pointselected=2;
                    return;
                }
            }
        }
    }


    if(index<numPt)
    {

        points[index]=event->pos();
        selectedPoint_i=index;
        index++;
        instructSignal(index);
        update();
    }
    else if(index==numPt)
    {
        flag_start=false;
    }
    else
    {
        return;
    }

    update();

    //int x = QCursor::pos().x();
    //int y = QCursor::pos().y();
    int x=event->pos().x();
    int y=event->pos().y();
    ScaleSignal2(x,y);


    /*
    if(hasMouseTracking()&&flag_point2==false)
    {

        point2=event->pos();
        flag_point2=true;
    }
    else if(hasMouseTracking()&&flag_point2==true)
    {
        setMouseTracking(false);
        flag_point3=true;
        flag_start=false;
        signal1();

    }
    else if(!hasMouseTracking()&&flag_point2==false)
    {
        point1 = point2 =point3= event->pos();
        setMouseTracking(true);
        update();
    }
    else
    {
        flag_point3=true;

    }*/
}




void myLabel::mouseMoveEvent(QMouseEvent* event)
{

    //int x = QCursor::pos().x();
    //int y = QCursor::pos().y();
    int x=event->pos().x();
    int y=event->pos().y();

    update();
    ScaleSignal2(x,y);
    if(flag_start==false)
    {
        return;
    }


    if(flag_mousepressed==true)
    {
        if(flag_pointselected==true&&type_Pointselected==2)
        {
            assistPoints[selectedPoint_i][selectedPoint_j]=event->pos();
        }
        else
        {

            points[selectedPoint_i]=event->pos();
        }
    }

    update();
    ScaleSignal2(x,y);

}



void myLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(flag_start==false)
    {
        return;
    }
    if(flag_mousepressed==true)
    {
        if(pointSettled[selectedPoint_i]==false)
        {
            int numAssist= assistpointsize[selectedPoint_i];
            for(int i=0;i<numAssist;i++)
            {
                QPoint pt(points[selectedPoint_i].x()+shiftX[selectedPoint_i][i],points[selectedPoint_i].y()+shiftY[selectedPoint_i][i]);
                assistPoints[selectedPoint_i].push_back(pt);

            }
            pointSettled[selectedPoint_i]=true;

        }
    }
    if(flag_pointselected==true)
    {
        flag_pointselected=false;
    }
    if(flag_mousepressed==true)
    {
        flag_mousepressed=false;
    }


    //int x = QCursor::pos().x();
    //int y = QCursor::pos().y();
    int x=event->pos().x();
    int y=event->pos().y();
    update();
    ScaleSignal2(x,y);
}

QPainterPath getPath(std::vector<point> line)
{
    int size=line.size();
    spline* s;
    QPainterPath path;
    point* p = new point[size];
    for(int i=0;i<size;i++){
        p[i].x = line[i].x;
        p[i].y = line[i].y;
    }
    s = new spline(p,size,20,0.5);
    //point *knots=s->knots;
    size=s->size();
    if(s->size()>0){
        path=QPainterPath(QPoint(s->getX(0),s->getY(0)));
        for(int i=0;i<s->size()-1;i++){
            path.lineTo(QPoint(s->getX(i+1),s->getY(i+1)));
        }
    }
    delete s;
    return path;
}

double getRatio1(QPoint a,QPoint b)
{
    const double pi = 3.1415927;
    if(a.y()==b.y())
    {
        return 0;
    }
    else if(a.x()==b.x())
    {
        return 90;
    }
    else
    {
        double tan=(double)(b.y()-a.y())/(b.x()-a.x());
        qDebug()<<tan;
        double theta=atan(tan);
        return theta/(2*pi)*360;
    }

}


void myLabel::paintEvent(QPaintEvent* event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    //上磨牙
    if(pointSettled[39]==true)
    {
        int width=(int)distancep2p(points[38],points[39]);
        int height=tooth[0].height()*width/tooth[0].width();
        double ratio=getRatio1(points[38],points[39]);
        painter.translate(points[36]);
        painter.rotate(ratio);
        painter.drawPixmap(-width/2,-height*175/192,width,height,tooth[0]);
        painter.rotate(-ratio);
        painter.translate(-points[36].x(),-points[36].y());

    }
    //下磨牙
    if(pointSettled[41]==true)
    {
        int width=(int)distancep2p(points[40],points[41]);
        int height=tooth[1].height()*width/tooth[1].width();
        double ratio=getRatio1(points[40],points[41]);
        painter.translate(points[37]);
        painter.rotate(ratio);
        painter.drawPixmap(-width/2,-height*22/164,width,height,tooth[1]);

        painter.rotate(-ratio);
        painter.translate(-points[37].x(),-points[37].y());
    }
    //下切牙
    if(pointSettled[44]==true)
    {
        int height=(int)distancep2p(points[43],points[44]);
        int width=tooth[2].width()*height/tooth[2].height();
        double ratio=getRatio1(points[44],points[43])+90;
        painter.translate(points[43]);
        painter.rotate(ratio);
        painter.drawPixmap(-width*43/82,0,width,height,tooth[2]);

        painter.rotate(-ratio);
        painter.translate(-points[43].x(),-points[43].y());
    }
    //上切牙
    if(pointSettled[48]==true)
    {
        int height=(int)distancep2p(points[47],points[48]);
        int width=tooth[3].width()*height/tooth[3].height();
        double ratio=getRatio1(points[48],points[47])-90;
        qDebug()<<ratio;
        painter.translate(points[47]);
        painter.rotate(ratio);
        painter.drawPixmap(-width*31/61,-height,width,height,tooth[3]);

        painter.rotate(-ratio);
        painter.translate(-points[47].x(),-points[47].y());
    }



    //画线

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0,255,0,150),2,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));

    getlines();
    if(pointSettled[keyPointOfLines[0]]==true)
    {
       QPainterPath path=getPath(lines[0]);
       painter.drawPath(path);
    }
    for(int i=1;i<numLine;i++)
    {
        if(lines2[i].size()>0)
        {

            if(pointSettled[keyPointOfLines[i]]==true)
            {
               QPainterPath path=getCurvePath(lines2[i],false);
               painter.drawPath(path);
            }
        }
    }
    /*
    for(int i=1;i<numLine;i++)
    {
        if(lines[i].size()>0)
        {

            if(pointSettled[keyPointOfLines[i]]==true)
            {
               QPainterPath path=getPath(lines[i]);
               painter.drawPath(path);
            }
        }
    }*/


    /**/

    //画点
    if(flag_drawPoint==true)
    {
        painter.setPen(QPen(Qt::black, 1));
        painter.setBrush(Qt::red);
        for(int i=0;i<numPt;i++)
        {
            if(pointSettled[i]==true){
                painter.drawEllipse(points[i], 3, 3);
            }

        }
        painter.setPen(QPen(Qt::white, 3));
        for(int i=0;i<numPt;i++)
        {
            if(pointSettled[i]==true){
                int assNum=assistPoints[i].size();
                for(int j=0;j<assNum;j++)
                {
                    painter.drawPoint(assistPoints[i][j]);
                }

            }

        }
    }

}






