#ifndef MOPENGLWIDGET_H
#define MOPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QVector>
#include <QDebug>

typedef struct
{
    GLfloat posX,posY,posZ;
    GLfloat rotX,rotY,rotZ;
    QPoint  lastPos;
}
Camera;

class MOpenGLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MOpenGLWidget(QWidget *parent=0);

protected:

    void initializeGL();
    void resizeGL(int width,int height);
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:

    void drawFloorGrid(GLfloat size);
    void drawXYZ(GLfloat axisLength);
    Camera cam;

signals:

public slots:

void setCameraFront();
void setCameraBack();
void setCameraTop();
void setCameraBottom();
void setCameraDefault();

};

#endif // MOPENGLWIDGET_H
