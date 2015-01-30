#include "glwidget.h"
#include <QMouseEvent>
#include "stdio.h"
#include "GL/glu.h"
#include <iostream>
#include "mainwindow.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    setMouseTracking(true);
}

void GLWidget::initializeGL() {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0,640,480,0,0,1); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT);
    float x1 = -1.25/2;
    float x2 = -0.75/2;
    float y1 = -0.75;
    float y2 = -1.0;
    int count=0;
    for(int drawRow = 0;drawRow<9;drawRow++){
        for(int drawCol = 0;drawCol<6;drawCol++){

            // drawRow){
            if(drawRow==0&& drawCol==3){
                glBegin(GL_POLYGON);
                if(counter!=0){
                glColor3f(0,1,0);
                }else{
                glColor3f(1,0,0);
                }
                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);



                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();
                //count++;
            }
            else if((drawRow ==1||drawRow==3) &&drawCol!=0){
                glBegin(GL_POLYGON);

                if(counter==1&&drawRow==1&&drawCol==1&&counter1==1){
                 glColor3f(1,0,0);
                }else if(counter==1&&drawRow==1&&drawCol==2&&counter1==2){
                    glColor3f(1,0,0);
                }else if(counter==1&&drawRow==1&&drawCol==3&&counter1==3){
                    glColor3f(1,0,0);
                }else if(counter==1&&drawRow==1&&drawCol==4&&counter1==4){
                    glColor3f(1,0,0);
                }else if(counter==1&&drawRow==1&&drawCol==5&&counter1==5){
                    glColor3f(1,0,0);

                }else if(counter==3&&drawRow==3&&drawCol==1&&counter1==1){
                    glColor3f(1,0,0);
                }else if(counter==3&&drawRow==3&&drawCol==2&&counter1==2){
                       glColor3f(1,0,0);
                }else if(counter==3&&drawRow==3&&drawCol==3&&counter1==3){
                       glColor3f(1,0,0);
                }else if(counter==3&&drawRow==3&&drawCol==4&&counter1==4){
                       glColor3f(1,0,0);
                }else if(counter==3&&drawRow==3&&drawCol==5&&counter1==5){
                       glColor3f(1,0,0);

                //}else if(counter==3&&drawRow==3){
                // glColor3f(1,0,0);
                } else if(drawRow==3&&drawCol==3){
                glColor3f(1,0.5,0.75);
                }
                else{
                    glColor3f(0,1,0);
                }
                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);


                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();
                //count++;
            }
            else if(drawRow ==2 &&(drawCol==0||drawCol==1||drawCol==5)){
                glBegin(GL_POLYGON);
                if(counter==2&&drawRow==2&&counter1==0&&drawCol==0){
                 glColor3f(1,0,0);
                }else if(counter==2&&drawRow==2&&counter1==1&&drawCol==1){
                    glColor3f(1,0,0);
                }else if(counter==2&&drawRow==2&&counter1==5&&drawCol==5){
                glColor3f(1,0,0);
                }else if(drawRow==2&&drawCol==0){
                    glColor3f(1,0.5,0.75);
                }else{
                    glColor3f(0,1,0);
                }


                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();

            }
            else if(drawRow ==4 &&(drawCol==3||drawCol==5)){
                glBegin(GL_POLYGON);
                //if(counter==4&&drawRow==4){
                 //glColor3f(1,0,0);
                if(counter==4&&drawRow==4&&counter1==3&&drawCol==3){
                    glColor3f(1,0,0);
                }else if(counter==4&&drawRow==4&&counter1==5&&drawCol==5){
                    glColor3f(1,0,0);
                }else{
                    glColor3f(0,1,0);
                }

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();
                //count++;
            }
            else if(drawRow ==5 &&(drawCol==2||drawCol==3||drawCol==5)){
                glBegin(GL_POLYGON);
                if(counter==5&&drawRow==5&&counter1==2&&drawCol==2){
                    glColor3f(1,0,0);
                }else if(counter==5&&drawRow==5&&counter1==3&&drawCol==3){
                    glColor3f(1,0,0);
                }else if(counter==5&&drawRow==5&&counter1==5&&drawCol==5){
                    glColor3f(1,0,0);
                }else if(drawRow==5&&drawCol==5){
                glColor3f(1,0.5,0.75);
                } else{
                    glColor3f(0,1,0);
                }

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();
                //count++;
            }
            else if(drawRow ==6 &&drawCol<3){
                glBegin(GL_POLYGON);

               if(counter==6&&drawRow==6&&counter1==0&&drawCol==0){
                    glColor3f(1,0,0);
                }else if(counter==6&&drawRow==6&&counter1==1&&drawCol==1){
                    glColor3f(1,0,0);
                }else if(counter==6&&drawRow==6&&counter1==2&&drawCol==2){
                    glColor3f(1,0,0);
                }else if (drawCol==0){
                    glColor3f(0,0,1);
                }else if(drawRow==6&&drawCol==2){
                glColor3f(1,0.5,0.75);
                }else {
                glColor3f(0,1,0);
                }

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();
                //count++;
            }
            else if(drawRow ==7 &&drawCol==2){

                glBegin(GL_POLYGON);

                if(counter==7&&drawRow==7){
                 glColor3f(1,0,0);
                } else{
                    glColor3f(0,0,1);
                }

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();
                glBegin(GL_LINES);
                glColor3f(0,0,0);

                glVertex2f(x2,y1);
                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y2);

                glEnd();

                glBegin(GL_LINES);
                glColor3f(0,0,0);


                glVertex2f(x1,y1);
                glVertex2f(x1,y2);
                glVertex2f(x2,y1);
                glVertex2f(x2,y2);

                glEnd();
                //count++;
            }
            count++;
            if(count < 6){
                x1=(x1+0.50/2);
                x2=(x2+0.50/2);
            }else{
                x1 = -1.25/2;
                x2 = -0.75/2;
                count =0;
            }


        }
        y1=(y1+0.25);
        y2=(y2+0.25);
    }


    /* }else{

            glBegin(GL_POLYGON);
            glColor3f(1,0,0);

            glVertex2f(-0.25/2,x);
            glVertex2f(0.25/2,x);
            glVertex2f(0.25/2,z);
            glVertex2f(-0.25/2,z);
            //setI(0);
             glEnd();

              z=(z+0.5/2);
              x=(x+0.5/2);
        }*/


}


void GLWidget::setCount(int setCount)
{

    counter = setCount;
}

int GLWidget::getCount()
{
    return counter;
}

void GLWidget::setCount1(int setCount)
{

    counter1 = setCount;
}

int GLWidget::getCount1()
{
    return counter1;
}

