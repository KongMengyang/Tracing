#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->setWindowTitle("投影测量");

    QObject::connect(ui->imageLabel,SIGNAL(instructSignal(int)),this,SLOT(instructSlot(int)));
    QObject::connect(ui->imageLabel,SIGNAL(ScaleSignal(int,int)),this,SLOT(ScaleSlot(int ,int)));
    QObject::connect(ui->imageLabel,SIGNAL(ScaleSignal2(int,int)),this,SLOT(ScaleSlot2(int,int)));
    QObject::connect(this,SIGNAL(clearAllSignal()),ui->imageLabel,SLOT(clearAllSlot()));
    QObject::connect(this,SIGNAL(saveSignal()),ui->imageLabel,SLOT(saveSlot()));
    QObject::connect(this,SIGNAL(templetSignal()),ui->imageLabel,SLOT(templetSlot()));


    //初始点信息
    QFile file0(":/text/text/points.txt");
    if (!file0.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
    QFile file1(":/text/text/points_details.txt");
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
    QTextStream in0(&file0);
    QTextStream in1(&file1);
    for(int i=0;i<51;i++)
    {
        QString point_name=in0.readLine();
        QListWidgetItem* lst = new QListWidgetItem(point_name,ui->pointslistWidget);
        ui->pointslistWidget->addItem(lst);
        points_detail[i]=in1.readLine();

    }


    //this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->scrollArea->setMouseTracking(true);
    ui->scrollAreaWidgetContents->setMouseTracking(true);
    ui->imageLabel->setMouseTracking(true);

    //screen = QGuiApplication::primaryScreen();










}

MainWindow::~MainWindow()
{
    delete ui;
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void MainWindow::on_openPushbutton_clicked()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(!filename.isEmpty())
    {
        if(originimage.load(filename))//读取图像
        {
            originimage_backup=originimage;
            originPixmap=QPixmap::fromImage(originimage);
            string str=qstr2str(filename);
            originmat=cv::imread(str);
            cout<<str<<endl;
            //qDebug()<<filename;
            initialWidth=originimage.width();
            initialHeight=originimage.height();
            currentWidth=initialWidth;
            currentHeight=initialHeight;

            ui->imageLabel->setFixedSize(QSize(initialWidth,initialHeight));
            currentimage=originimage;


            ui->imageLabel->setPixmap(QPixmap::fromImage(currentimage));

            //ui->instructimgLabel->setPixmap(NULL);

            //自适应大小
            for(int i=20;i<180;i=i+5)
            {
                if(initialWidth*i/100<ui->scrollArea->width()&&initialHeight*i/100<ui->scrollArea->height())
                {
                }
                else
                {

                    int value=i-5;
                    currentWidth=initialWidth*value/100;
                    currentHeight=initialHeight*value/100;
                    originimage=originimage.scaled(currentWidth,currentHeight);

                    ui->imageLabel->setFixedSize(QSize(currentWidth,currentHeight));
                    //ui->imageLabel->setScaledContents(false);
                    int blank=2;
                    if(ui->scrollArea->width()-blank>=currentWidth&&ui->scrollArea->height()-blank>=currentHeight)
                    {
                        ui->scrollAreaWidgetContents->setFixedSize(ui->scrollArea->width()-blank,ui->scrollArea->height()-blank);
                    }
                    else if(ui->scrollArea->width()-blank>=currentWidth&&ui->scrollArea->height()-blank<=currentHeight)
                    {
                        ui->scrollAreaWidgetContents->setFixedSize(ui->scrollArea->width()-blank,currentHeight);
                    }
                    else if(ui->scrollArea->width()-blank<=currentWidth&&ui->scrollArea->height()-blank>=currentHeight)
                    {
                        ui->scrollAreaWidgetContents->setFixedSize(currentWidth,ui->scrollArea->height()-blank);
                    }
                    else
                    {
                        ui->scrollAreaWidgetContents->setFixedSize(currentWidth,currentHeight);
                    }
                    ui->imageLabel->setPixmap(QPixmap::fromImage(originimage));
                    imageupdate();
                    break;
                }

            }







        }
        else
        {
            QMessageBox::information(this,QString::fromLocal8Bit("打开图像失败"),QString::fromLocal8Bit("打开图像失败!"));

            return;
        }
    }
    else
    {
        return;
    }
}

//Mat->QImage
QImage MatToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}




void MainWindow::imageupdate()
{
    if(flag_sharpened==true){

        cv::Mat imgSrc=originmat;
        cv::Mat imgBlurred;
        cv::Mat imgDst;
        cv::Mat lowContrastMask;
        double sigma = 3;
        int threshold = 0;
        float amount = 1;

        cv::GaussianBlur(imgSrc, imgBlurred, cv::Size(), sigma, sigma);
        lowContrastMask = abs(imgSrc-imgBlurred)<threshold;
        imgDst = imgSrc*(1+amount)+imgBlurred*(-amount);
        imgSrc.copyTo(imgDst, lowContrastMask);
        //qDebug()<<"111";


        originimage=MatToQImage(imgDst);
        originimage=originimage;
    }
    else
    {
        originimage=originimage_backup.scaled(currentWidth,currentHeight);;
    }

    QImage newImage=originimage.scaled(currentWidth,currentHeight);;
    //ui->imageLabel->setScaledContents(false);



    /**/
    QColor oldColor;
    int r=0,g=0,b=0;
    int delta;
    delta=ui->contrastSlider->value();
    for(int y=0; y<newImage.height(); y++)
    {
        for(int x=0; x<newImage.width(); x++)
        {
            oldColor = QColor(newImage.pixel(x,y));

            r=rThreshold+(oldColor.red()-rThreshold)*(100+delta)/100;
            if(r>255){r=255;}else if(r<0){r=0;}

            g=gThreshold+(oldColor.green()-gThreshold)*(100+delta)/100;
            if(g>255){g=255;}else if(g<0){g=0;}

            b=bThreshold+(oldColor.blue()-bThreshold)*(100+delta)/100;
            if(b>255){b=255;}else if(b<0){b=0;}

            newImage.setPixel(x,y, qRgb(r,g,b));
        }
    }

    delta = ui->brightnessSlider->value();
    for(int y=0; y<newImage.height(); y++)
    {
        for(int x=0; x<newImage.width(); x++)
        {
            oldColor = QColor(newImage.pixel(x,y));
            r = oldColor.red() + delta;
            if(r>255){r=255;}else if(r<0){r=0;}

            g = oldColor.green() + delta;
            if(g>255){g=255;}else if(g<0){g=0;}

            b = oldColor.blue() + delta;
            if(b>255){b=255;}else if(b<0){b=0;}

            newImage.setPixel(x,y, qRgb(r,g,b));
        }
    }

    //originPixmap=QPixmap::fromImage(newImage);
   //newImage=newImage.scaled(currentWidth,currentHeight);
    ui->imageLabel->setPixmap(QPixmap::fromImage(newImage));


}




void MainWindow::on_contrastSlider_valueChanged(int value)
{
    imageupdate();
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    imageupdate();
}

void MainWindow::on_sharpenPushButton_clicked()
{
    if(flag_sharpened==true)
    {
        flag_sharpened=false;
    }
    else
    {
        flag_sharpened=true;
    }
    imageupdate();
}

void MainWindow::on_clearPushbutton_clicked()
{
    ui->imageLabel->index=0;
    ui->imageLabel->flag_start=false;
    for(int i=0;i<50;i++)
    {
        //pointSettled[i]=false;
        ui->imageLabel->pointSettled[i]=false;
    }

    ui->imageLabel->update();
    clearAllSignal();
}

void MainWindow::on_measurePushbutton_clicked()
{
    if(originimage.isNull())
    {
        QMessageBox::information(this,QString("请先导入图像"),QString("请先导入图像!"));
        return;
    }
    if(ui->imageLabel->flag_start==true)
    {
        QMessageBox::information(this,QString("请先清空选点"),QString("请先清空选点!"));
        return;
    }
    ui->imageLabel->flag_start=true;
    ui->imageLabel->setCursor(Qt::CrossCursor);
    instructSlot(0);
}



void MainWindow::instructSlot(int index)
{
    if(index==0)
    {
        ui->imageLabel->flag_start=true;
    }

    QString filepath0=":/image/image/points/instruct"+QString::number(index)+"_0.png";
    QString filepath1=":/image/image/points/instruct"+QString::number(index)+"_1.png";

    QImage img0=QImage(filepath0);
    QImage img1=QImage(filepath1);

    //ui->instructimgLabel->setScaledContents(true);
    ui->instructLabel0->setPixmap(QPixmap::fromImage(img0));
    ui->instructLabel1->setPixmap(QPixmap::fromImage(img1));/**/
    ui->instructLabel4->setText(points_detail[index]);
    ui->pointslistWidget->setCurrentRow(index);
}



void MainWindow::ScaleSlot(int x,int y){


    /*int rx=initialWidth*x/currentWidth;
    int ry=initialHeight*y/currentHeight;
    QPixmap pix = originPixmap.copy(rx-100,ry-100,200,200);
    */
    //QPixmap pixmap = screen->grabWindow(0);
    //QImage image = ui->imageLabel->pixmap()->toImage();
    //pix=QPixmap::fromImage(image);
    //int rx=ui->imageLabel->x()+ui->scrollArea->x()+ui->scrollAreaWidgetContents->x()+ui->centralWidget->x();
    //int ry=ui->imageLabel->y()+ui->scrollArea->y()+ui->scrollAreaWidgetContents->y()+ui->centralWidget->y();
   /*
    QPixmap pix;
    pix=grabpixmap.copy(x-50,y-50,100,100);
    grabpixmap = screen->grabWindow(0);
    pix=pix.scaled(200,200);

    QPainter painter(&pix); //创建一直画笔
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawPoint(100,100);
    ui->ScaleLabel->setPixmap(pix);*/

}


void MainWindow::ScaleSlot2(int x,int y)
{

    //QPicture pic=ui->imageLabel->picture();
    QPixmap pix;
    pix=ui->imageLabel->grab(QRect(x-50,y-50,100,100));
    //QPixmap pix=ui->imageLabel->pixmap()->copy(x-50,y-50,100,100);


    pix=pix.scaled(200,200);

    QPainter painter(&pix); //创建一直画笔
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawPoint(100,100);
    ui->ScaleLabel->setPixmap(pix);


}

void MainWindow::on_savePushButton_clicked()
{
    //if(ui->imageLabel->index>0)
    saveSignal();
}










void MainWindow::on_templetPushButton_clicked()
{
    templetSignal();
}





void MainWindow::on_pointDispalyPushButton_clicked()
{
    if(ui->imageLabel->flag_drawPoint==true)
    {
        ui->imageLabel->flag_drawPoint=false;
    }
    else
    {
        ui->imageLabel->flag_drawPoint=true;
    }
    ui->imageLabel->update();

}

void MainWindow::on_completePushButton_clicked()
{
    if(ui->imageLabel->index<50)
    {
        QMessageBox::information(this,QString("请先完成选点"),QString("请先完成选点!"));
        return;
    }



    //新建一个窗口对象，其中的this指定了新的窗口的父对象是MainWindow，在销毁Mainwindow时也会销毁子对象，即该窗口对象
    rd = new reportDialog(this);
    //Modal属性决定了show()应该将弹出的dialog设置为模态还是非模态
    //默认情况下该属性为false并且show（）弹出的窗口是非模态的
    //把这个属性设置为true就详单与设置QWidget::windowModality为Qt::ApplicationModal
    //执行exec（）忽略这个Modal这个属性，并且把弹出的dialog设置为模态的
    getResults();
    rd->update();
    rd->setModal(false);    //此处ture为模态，false为非模态
    rd->show();
}

double MainWindow::angle_2lines(QPoint a,QPoint b,QPoint c,QPoint d)
{
    double result;
    double x1=a.x()-b.x();
    double x2=d.x()-c.x();
    double y1=a.y()-b.y();
    double y2=d.y()-c.y();
    double cosvalue=(x1*x2+y1*y2)/(sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2));
    result=acos(cosvalue)/3.1415*180;
    return result;
}
double MainWindow::distance_pointtoline(QPoint a, QPoint b, QPoint c)
{
    double result;
    if(b.x()==c.x())
    {
        result=a.x()-b.x();
    }
    else if(b.y()==c.y())
    {
        result=a.y()-b.y();
    }
    else
    {
        double k=(b.y()-c.y())/(b.x()-c.x());
        double bb=b.y()-k*b.x();
        result=(a.y()-k*a.x()-bb)/sqrt(1.0+k*k);
    }
    if(result<0)
    {
        result=-result;
    }
    result=result*10/length_10mm;
    return result;

}
double MainWindow::distancep2p(QPoint a,QPoint b)
{
    return sqrt((a.x()-b.x())*(a.x()-b.x())+(a.y()-b.y())*(a.y()-b.y()));
}


void MainWindow::getObjResult(int x)
{
    tclObj obj=targetObj[x];

    if(obj.type==1)
    {
        double result=angle_2lines(obj.points[0],obj.points[1],obj.points[3],obj.points[2]);

        QString strResult=QString::number(result, 10, 1);
        strResult+="°";
        int row=x;
        //QTableWidgetItem *newitem=new QTableWidgetItem(strResult);
        //newitem->setTextAlignment(Qt::AlignCenter);
        //ui->tableWidget->setItem(row,2,newitem);


        rd->results[x]=strResult;
        double min=obj.min;
        double max=obj.max;
        if(result<min)
        {

            rd->result_type[x]=1;
        }
        else if(result>max)
        {

            rd->result_type[x]=2;
        }
        else
        {
            rd->result_type[x]=0;
        }
    }
    else if(obj.type==2)
    {
        int row=x;
        double min=obj.min;
        double max=obj.max;
        double result=distance_pointtoline(obj.points[0],obj.points[1],obj.points[2]);
        QString strResult=QString::number(result, 10, 1);
        strResult+="mm";
        //QTableWidgetItem *newitem=new QTableWidgetItem(strResult);
        //newitem->setTextAlignment(Qt::AlignCenter);
        //ui->tableWidget->setItem(row,2,newitem);


        rd->results[x]=strResult;
        if(result<min)
        {

            rd->result_type[x]=1;
        }
        else if(result>max)
        {

            rd->result_type[x]=2;
        }
        else
        {
            rd->result_type[x]=0;
        }
    }
}

void MainWindow::getResults()
{

    length_10mm=distancep2p(ui->imageLabel->points[0],ui->imageLabel->points[1]);
    targetObj[0]=tclObj(86.8,68.8,1,ui->imageLabel->points[5],ui->imageLabel->points[6],ui->imageLabel->points[33],ui->imageLabel->points[6]);//SNA
    targetObj[1]=tclObj(84.0,76.2,1,ui->imageLabel->points[5],ui->imageLabel->points[6],ui->imageLabel->points[23],ui->imageLabel->points[6]);//SNB
    targetObj[2]=tclObj(4.7,0.7,1,ui->imageLabel->points[33],ui->imageLabel->points[6],ui->imageLabel->points[23],ui->imageLabel->points[6]);//ANB
    targetObj[3]=tclObj(89.1,81.7,1,ui->imageLabel->points[2],ui->imageLabel->points[3],ui->imageLabel->points[24],ui->imageLabel->points[6]);//NP-FH面角
    targetObj[4]=tclObj(73.4,59.2,1,ui->imageLabel->points[3],ui->imageLabel->points[2],ui->imageLabel->points[25],ui->imageLabel->points[5]);//Y轴角
    targetObj[5]=tclObj(36.7,25.5,1,ui->imageLabel->points[3],ui->imageLabel->points[2],ui->imageLabel->points[26],ui->imageLabel->points[27]);//MP-FH下颌平面角
    targetObj[6]=tclObj(10.4,1.6,1,ui->imageLabel->points[6],ui->imageLabel->points[33],ui->imageLabel->points[33],ui->imageLabel->points[24]);//NP-PA颌凸角
    targetObj[7]=tclObj(112.0,99.4,1,ui->imageLabel->points[5],ui->imageLabel->points[6],ui->imageLabel->points[47],ui->imageLabel->points[48]);//上1-SN角
    targetObj[8]=tclObj(7.5,2.7,2,ui->imageLabel->points[47],ui->imageLabel->points[6],ui->imageLabel->points[33],ui->imageLabel->points[0]);//上1-NA距
    targetObj[9]=tclObj(28.5,17.1,1,ui->imageLabel->points[48],ui->imageLabel->points[47],ui->imageLabel->points[6],ui->imageLabel->points[33]);//上1-NA角
    targetObj[10]=tclObj(100.1,87.7,1,ui->imageLabel->points[27],ui->imageLabel->points[26],ui->imageLabel->points[43],ui->imageLabel->points[44]);//下1-MP角
    targetObj[11]=tclObj(8.8,4.6,2,ui->imageLabel->points[43],ui->imageLabel->points[6],ui->imageLabel->points[23],ui->imageLabel->points[0]);//下1-NB距
    targetObj[12]=tclObj(36.1,24.5,1,ui->imageLabel->points[23],ui->imageLabel->points[6],ui->imageLabel->points[44],ui->imageLabel->points[43]);//下1-NB角
    targetObj[13]=tclObj(132.4,116.0,1,ui->imageLabel->points[48],ui->imageLabel->points[47],ui->imageLabel->points[44],ui->imageLabel->points[43]);//上1-下1角
    targetObj[14]=tclObj(110,80,1,ui->imageLabel->assistPoints[12][3],ui->imageLabel->points[12],ui->imageLabel->points[14],ui->imageLabel->points[12]);//NLA角

    for(int i=0;i<15;i++)
    {
        getObjResult(i);
    }

}

