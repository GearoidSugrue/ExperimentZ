#ifndef QGLWIDGET_H
#define QGLWIDGET_H



//#include <qglwidget>
#include <QGLWidget>

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(QWidget *parent = NULL);
    //void setI(int);
    //void setK(int);
    int l = 0.25;
    int l1 = -0.25;
    int getCount();
    void setCount(int);
    int getCount1();
    void setCount1(int);


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    //int i = 1;
    //float k = 0.5;
     int counter = 0;
     int counter1 = 3;

};
#endif



