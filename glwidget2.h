#ifndef QGLWIDGET2_H
#define QGLWIDGET2_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <QGLWidget>
#include <GL/gl.h>
using namespace std;
typedef struct
{
    float x;
    float y;
    float z;
}
Vector;

typedef struct
{
    int v1, v2, v3;
    int vn1, vn2, vn3;
}
Face;

typedef struct
{
    float Ka[3];    // Ambient colour
    float Kd[3];    // Diffuse colour
    float Ks[3];    // Specular colour
    float Ns;       // Specular (coeff)
}
Material;


class QTimer;
class GLWidget2 : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget2(QWidget *parent = NULL);
    ~GLWidget2();
    int load(char *filename);
    void draw();
    void update();
    GLfloat angle =3.00;
    void setImageCounter(int);
    int getImageCounter();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QTimer *refreshTimer_;
    GLfloat rotValue_;
    int imageCounter = 0;
    int temp = 0;
    vector<Vector> vertices;
    vector<Vector> normals;
    vector<Face> faces;
    vector<Material> materials;
    void reload(int);
    void parseLine(char *line);

    void parseVertex(char *line);
    void parseNormal(char *line);
    void parseFace(char *line);
    int loadMaterials(char *filename);
    void parseMaterial(string line);
};
#endif
