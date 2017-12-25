#include "mopenglwidget.h"

MOpenGLWidget::MOpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    m_camera.rotX=18.50;
    m_camera.rotY=-45.0;
    m_camera.rotZ=  0.0;
    m_camera.posZ=-7.0;
}

void MOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    qglClearColor(QColor(32,32,32));

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    //glEnable(GL_SCISSOR_TEST);
    //glClearStencil(0);
    //glClearDepth(1.0f);
    //glDepthFunc(GL_LEQUAL);
}

void MOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = (float)width / (float)height;
    setFrustum(45,aspectRatio,0.5,50.0);
    glMatrixMode(GL_MODELVIEW);
}

void MOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera
    glTranslatef(0.0, 0.0, m_camera.posZ);
    glRotatef(m_camera.rotX, 1.0, 0.0, 0.0);
    glRotatef(m_camera.rotY, 0.0, 1.0, 0.0);
    glRotatef(m_camera.rotZ, 0.0, 0.0, 1.0);

    // Flor and axis
    drawFloorGrid(4.0,0.5);
    drawAxis(1.0);

    // Box
    glPushMatrix();
    glTranslatef(0.5,0.0,0.0);
    drawBox(0.5);
    glPopMatrix();
}

void MOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_camera.lastPos = event->pos();
}

void MOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - m_camera.lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - m_camera.lastPos.y()) / height();

    if(event->buttons() & Qt::LeftButton) {
        m_camera.rotX += 180 * dy;
        m_camera.rotY += 180 * dx;
        updateGL();
    } else if(event->buttons() & Qt::RightButton) {
        m_camera.rotX += 180 * dy;
        m_camera.rotZ += 180 * dx;
        updateGL();
    }

    m_camera.lastPos = event->pos();


    // Send camera info
    QString info = "Camera: {"+QString::number(m_camera.posX)+","+QString::number(m_camera.posY)+","+QString::number(m_camera.posZ)+
            "} {"+QString::number(m_camera.rotX)+","+QString::number(m_camera.rotY)+","+QString::number(m_camera.rotZ)+"}";


    emit updateCameraLocationStatus(info);
}

void MOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    m_camera.posZ+=((float)event->delta())*0.01;
    updateGL();
    event->accept();

    // Send camera info
    QString info = "Camera: {"+QString::number(m_camera.posX)+","+QString::number(m_camera.posY)+","+QString::number(m_camera.posZ)+
            "} {"+QString::number(m_camera.rotX)+","+QString::number(m_camera.rotY)+","+QString::number(m_camera.rotZ)+"}";


    emit updateCameraLocationStatus(info);
}

void MOpenGLWidget::setFrustum(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void MOpenGLWidget::drawFloorGrid(float size, float step)
{
    glBegin(GL_LINES);

    glColor3f(0.3f, 0.3f, 0.3f);
    for(float i=step; i <= size; i+= step)
    {
        glVertex3f(-size, 0,  i);   // lines parallel to X-axis
        glVertex3f( size, 0,  i);
        glVertex3f(-size, 0, -i);   // lines parallel to X-axis
        glVertex3f( size, 0, -i);

        glVertex3f( i, 0, -size);   // lines parallel to Z-axis
        glVertex3f( i, 0,  size);
        glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(-i, 0,  size);
    }

    // x-axis
    glColor3f(0.5f, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f( size, 0, 0);

    // z-axis
    glColor3f(0,0,0.5f);
    glVertex3f(0, 0, -size);
    glVertex3f(0, 0,  size);

    glEnd();
}

void MOpenGLWidget::drawAxis(GLfloat axisLength)
{
    GLfloat offset=0;

    glLineWidth(3.0);

    glBegin(GL_LINES);
    qglColor(Qt::red);
    glVertex3f(offset,offset,offset);
    glVertex3f(axisLength,offset,offset);
    glEnd();

    glBegin(GL_LINES);
    qglColor(Qt::green);
    glVertex3f(offset,offset,offset);
    glVertex3f(offset,axisLength,offset);
    glEnd();

    glBegin(GL_LINES);
    qglColor(Qt::blue);
    glVertex3f(offset,offset,offset);
    glVertex3f(offset,offset,axisLength);
    glEnd();

    glLineWidth(1.0);
}

void MOpenGLWidget::drawBox(GLfloat size)
{
    // Front
    glBegin(GL_QUADS);
    qglColor(Qt::red);
    glVertex3f(-size/2.0,-size/2.0,size/2.0);
    glVertex3f(size/2.0,-size/2.0,size/2.0);
    glVertex3f(size/2.0,size/2.0,size/2.0);
    glVertex3f(-size/2.0,size/2.0,size/2.0);
    glEnd();

    // Top
    glBegin(GL_QUADS);
    qglColor(Qt::blue);
    glVertex3f(size/2.0,size/2.0,-size/2.0);
    glVertex3f(-size/2.0,size/2.0,-size/2.0);
    glVertex3f(-size/2.0,size/2.0,size/2.0);
    glVertex3f(size/2.0,size/2.0,size/2.0);
    glEnd();

    // Back
    glBegin(GL_QUADS);
    qglColor(Qt::magenta);
    glVertex3f(size/2.0,-size/2.0,-size/2.0);
    glVertex3f(-size/2.0,-size/2.0,-size/2.0);
    glVertex3f(-size/2.0,size/2.0,-size/2.0);
    glVertex3f(size/2.0,size/2.0,-size/2.0);

    // Bottom
    glBegin(GL_QUADS);
    qglColor(Qt::white);
    glVertex3f(-size/2.0,-size/2.0,-size/2.0);
    glVertex3f(size/2.0,-size/2.0,-size/2.0);
    glVertex3f(size/2.0,-size/2.0,size/2.0);
    glVertex3f(-size/2.0,-size/2.0,size/2.0);
    glEnd();

    // Left
    glBegin(GL_QUADS);
    qglColor(Qt::green);
    glVertex3f(-size/2.0,size/2.0,-size/2.0);
    glVertex3f(-size/2.0,-size/2.0,-size/2.0);
    glVertex3f(-size/2.0,-size/2.0,size/2.0);
    glVertex3f(-size/2.0,size/2.0,size/2.0);
    glEnd();

    // Right
    glBegin(GL_QUADS);
    qglColor(Qt::yellow);
    glVertex3f(size/2.0,-size/2.0,-size/2.0);
    glVertex3f(size/2.0,size/2.0,-size/2.0);
    glVertex3f(size/2.0,size/2.0,size/2.0);
    glVertex3f(size/2.0,-size/2.0,size/2.0);
    glEnd();
}
