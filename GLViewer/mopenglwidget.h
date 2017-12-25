#ifndef MOPENGLWIDGET_H
#define MOPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QVector>

typedef struct
{
    GLfloat posX,posY,posZ;
    GLfloat rotX,rotY,rotZ;
    QPoint  lastPos;
}
Camera_t;

class MOpenGLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MOpenGLWidget(QWidget *parent = nullptr);

signals:
    void updateCameraLocationStatus(QString);

protected:

    void initializeGL();
    void resizeGL(int width,int height);
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    void setFrustum(GLdouble fovY,GLdouble aspect, GLdouble zNear, GLdouble zFar);

    void drawFloorGrid(float size, float step);
    void drawAxis(GLfloat axisLength);
    void drawBox(GLfloat size);

private:
    Camera_t m_camera;
};

#endif // MOPENGLWIDGET_H
