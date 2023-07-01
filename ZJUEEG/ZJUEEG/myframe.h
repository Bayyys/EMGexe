#ifndef MYFRAME_H
#define MYFRAME_H

#include <QMainWindow>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <qdebug.h>
#include <QStylePainter>
#include <QResizeEvent>

class myframe: public QWidget
{
public:
    explicit myframe(QWidget *parent = 0);
    ~myframe();

    int hasDataToDraw(double sample_rate, QVector<double>& singlechannel_data,
                      Qt::GlobalColor lineColor,
                      double min, double max, double rms,
                      QVector<qint8>& mark,int rms_w_count,int rms_w_length,
                      bool leadoff_p = false, bool leadoff_n = false,bool singleElectMode = false,int channel=0);
    void refreshPixmap();
    void refreshScale();
    void setRMS(bool rmsenable);
    void setXscale(int t_scale);
    void setYscale(int ampli_scale);
protected:
    /*      重载
     *    重载resizeEvent，窗口变化时执行操作
     *    重载paintEvent，自定义器件绘图事件重载，所以绘图须在该函数中实现，采用双缓冲，将绘图内容存入PIXMAP，再在该事件函数中绘制PIXMAP
     *    重载mousePressEvent，保留待用。
     */
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
private:
    void clearParameter();//窗口大小变化时初始化绘图参数

    QPixmap *pixmap=nullptr;
    QPointF* polyline;
    QPointF* polyline_2;
    QPointF polyline_first;
    bool mark0;//存储上一次绘图终点mark值
    bool has_data_to_draw;
    double x_interval;//ms  每两个点的间距
    double y_scale;//uV
    double x_scale;//ms
    double pen_pos_x;//画笔当前位置
    double pen_pos_y;
    int height;
    int width;
    bool rms_enable;
    int amplititude_scale;
    int time_scale;
};

#endif // MYFRAME_H
