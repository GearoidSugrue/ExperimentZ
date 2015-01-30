#include "glwidget2.h"
#include <QMouseEvent>
#include "stdio.h"
#include "GL/glu.h"
#include <iostream>
#include "mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <GL/gl.h>


GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 100.0f, 0.0f, -10.0f, 1.0f };

GLfloat mat_ambient[]= { 0.5f, 0.5f, 0.5f, 0.5f};
GLfloat mat_shininess[]= { 1.0f };


GLWidget2::GLWidget2(QWidget *parent) : QGLWidget(parent) {
     rotValue_ = 0;

         load("M16[1].obj");



}


GLWidget2::~GLWidget2()
{
}

void GLWidget2::initializeGL() {
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    refreshTimer_ = new QTimer(this);
    connect(refreshTimer_, SIGNAL(timeout()), this, SLOT(update()));
    refreshTimer_->start(10);

 }

void GLWidget2::resizeGL(int w, int h) {

           float ratio = 1.0*(w/h);
           glViewport( 0,0,w,h );
           glMatrixMode( GL_PROJECTION );
           glLoadIdentity();
           glOrtho(-25, 25, -15, 15, -30, 30);
           gluPerspective(45,ratio,1,1000);


           glMatrixMode( GL_MODELVIEW );
           //gluLookAt(0.0,0.0,5.0,0.0,0.0,-1.0,0.0f,1.0f,0.0f);
           glLoadIdentity();
  }

void GLWidget2::paintGL()
{
    if(temp!=imageCounter){
    vertices = {};
    normals = {};
    faces = {};
    if(imageCounter ==0){
    load("M16[1].obj");
    }else if(imageCounter==1){
    load("Kabar_lowPoly.obj");
    }else{
     load("Krug.obj");

    }
    temp = imageCounter;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(angle,0.0, angle, 0.0);
    if(imageCounter==1){

        glScalef(0.5,0.5,0.5);
     }else if(imageCounter==2){

         glScalef(50,50,50);
     }else{
        glScalef(1.5,1.5,1.5);

    }

    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);


    glColor3f(1,1,1);





    glBegin(GL_TRIANGLES);




        for(int f = 0; f < faces.size(); f++)
        {
            glNormal3f(normals[faces[f].vn1 - 1].x, normals[faces[f].vn1 - 1].y, normals[faces[f].vn1 - 1].z);
            glVertex3f(vertices[faces[f].v1 - 1].x, vertices[faces[f].v1 - 1].y, vertices[faces[f].v1 - 1].z);

            glNormal3f(normals[faces[f].vn2 - 1].x, normals[faces[f].vn2 - 1].y, normals[faces[f].vn2 - 1].z);
            glVertex3f(vertices[faces[f].v2 - 1].x, vertices[faces[f].v2 - 1].y, vertices[faces[f].v2 - 1].z);

            glNormal3f(normals[faces[f].vn3 - 1].x, normals[faces[f].vn3 - 1].y, normals[faces[f].vn3 - 1].z);
            glVertex3f(vertices[faces[f].v3 - 1].x, vertices[faces[f].v3 - 1].y, vertices[faces[f].v3 - 1].z);

        }

        glEnd();
        angle += 0.2f;

}


int GLWidget2::load(char *filename)
{

    fstream objFile;
    objFile.open(filename);

    if(objFile.is_open())
    {
        char line[255];

        // Parse object file line by line
        while(objFile.good())
        {

            objFile.getline(line, 255);
            parseLine(line);
        }

        objFile.close();
    }
    else
    {
        cout << "Could not open WFObject file '" << filename << "'\n";
        return false;
    }

    return true;
}

void GLWidget2::parseLine(char *line)
{
    if(!strlen(line))
    {
        return;
    }

    char *lineType;
    lineType = strtok(strdup(line), " ");

    // Decide what to do
    if(!strcmp(lineType, "v"))      // Vertex
    {
        parseVertex(line);
    }
    else if(!strcmp(lineType, "vn"))    // Normal
    {
        parseNormal(line);
    }
    else if(!strcmp(lineType, "f")) // Face
    {
        parseFace(line);
    }

    return;
}


// Parse a "v" vertex line of the file into our vertices array
void GLWidget2::parseVertex(char *line)
{
    vertices.push_back(Vector());       // Add a new element to the vertices array

    sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);



    return;
}

// Parse a "vn" normal line of the file into the normals array
void GLWidget2::parseNormal(char *line)
{
    normals.push_back(Vector());

    sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z);


    return;
}

// Parse a "f" face line into the faces array. This gets complex due to there being different line formats.
void GLWidget2::parseFace(char *line)
{
    int fill = 0;

    faces.push_back(Face());

    // Read face line. If texture indicies aren't present, don't read them.
    if(sscanf(line, "f %d//%d %d//%d %d//%d", &faces.back().v1,
                                              &faces.back().vn1,
                                              &faces.back().v2,
                                              &faces.back().vn2,
                                              &faces.back().v3,
                                              &faces.back().vn3) <= 1)
    {
        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces.back().v1,
                                                     &fill,
                                                     &faces.back().vn1,
                                                     &faces.back().v2,
                                                     &fill,
                                                     &faces.back().vn2,
                                                     &faces.back().v3,
                                                     &fill,
                                                     &faces.back().vn3);
    }




    return;
}





void GLWidget2::setImageCounter(int setCount)
{

    imageCounter = setCount;
}

int GLWidget2::getImageCounter()
{
    return imageCounter;
}


void GLWidget2::reload(int image)
{

    if(image = 0)
        return;

}
