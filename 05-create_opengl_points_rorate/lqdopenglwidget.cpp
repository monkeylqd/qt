#include "lqdopenglwidget.h"
#include <QFile>
#include <QMouseEvent>


static GLfloat m_vertices[] = {
    -0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
    0.0f,   -0.8f,   0.0f,   0.0f, 0.0f, 1.0f,
    0.5f,   -0.5f,  -0.5f,   0.0f, 1.0f, 0.0f,
    0.0f,   0.5f,   0.0f,   0.0f, 0.0f, 1.0f,
};

LqdOpenGLWidget::LqdOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
//    m_timer.start(100);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    m_buff_size = 40000;
    m_buff = (float *)malloc(sizeof(float)*m_buff_size);
    memset(m_buff, 0, m_buff_size);


    QFile file(":/srcfile/asc");
    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        qDebug() << "There is no asc file" ;
    }
    QTextStream in(&file);
    QString ramData = in.readAll();
    QStringList list = ramData.split("\n");
    QStringList listline;

    m_PointsVertex.resize(3*list.count());
    for (int i = 0; i < list.count() - 1; i++)
    {
        listline = list.at(i).split(" ");
        if(listline.size()>=3)
        {
//            if(i%2 == 0)
            {
                m_buff[i*3] = listline.at(0).toFloat()-0.5;
                m_buff[i*3+1] = listline.at(1).toFloat()-0.5;
                m_buff[i*3+2] = listline.at(2).toFloat()-0.5;
            }
//            else
//            {
//                m_buff[i*3] = listline.at(0).toFloat();
//                m_buff[i*3+1] = listline.at(1).toFloat();
//                m_buff[i*3+2] = listline.at(2).toFloat();
//            }

//            qDebug("%f %f %f\n", m_buff[i*3], m_buff[i*3+1], m_buff[i*3+2]);
//            m_PointsVertex.replace(i*3, listline.at(0).toFloat());
//            m_PointsVertex.replace(i*3+1, listline.at(1).toFloat());
//            m_PointsVertex.replace(i*3+2, listline.at(2).toFloat());
        }
    }
}

LqdOpenGLWidget::~LqdOpenGLWidget()
{
    makeCurrent();
    m_VAO.destroy();
    m_VBO.destroy();
    doneCurrent();
}

void LqdOpenGLWidget::on_timeout()
{
    static float point_size = 0.1;
    point_size += 0.1;
    if(point_size > 5.0)
    {
        point_size = 0.1;
    }
    makeCurrent();
    m_OpenGLShader_1.bind();
    m_OpenGLShader_1.setUniformValue("point_size", point_size);
    doneCurrent();
    update();
}

void LqdOpenGLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    update();
}

void LqdOpenGLWidget::initializeGL()
{
    qDebug("start initializeGL\n");



    qDebug("m_PointsVertex.size:%d", m_PointsVertex.size()/6);


    initializeOpenGLFunctions();
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);// 开启点大小调节功能。同时在定点着色器里面设置gl_PointSize的值
//    glShadeModel(GL_FLAT);
    m_OpenGLShader_1.bind();
    if(!m_OpenGLShader_1.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/shader.vert"))
    {
        qDebug("shader.vert fail.\n");
    }
    if(!m_OpenGLShader_1.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/shader.frag"))
    {
        qDebug("shader.frag fail.\n");
    }
    if(!m_OpenGLShader_1.link())
    {
        qDebug("link fail.\n");
    }

    m_VAO.create();
    m_VAO.bind();

    m_VBO.create();
    m_VBO.bind();
//    m_VBO.allocate(m_vertices, sizeof (m_vertices));
    m_VBO.allocate(m_buff, m_buff_size);

    m_attr = m_OpenGLShader_1.attributeLocation("aPos");
    m_OpenGLShader_1.setAttributeBuffer(m_attr, GL_FLOAT, 0, 3, 3*sizeof (GLfloat));
//    m_OpenGLShader_1.setAttributeBuffer(m_attr, GL_FLOAT, 0, 1000, 6*sizeof (GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_attr);

//    m_color = m_OpenGLShader_1.attributeLocation("aColor");
//    m_OpenGLShader_1.setAttributeBuffer(m_color, GL_FLOAT, 3*sizeof (GLfloat), 3, 6*sizeof(GLfloat));
//    m_OpenGLShader_1.setAttributeBuffer(m_color, GL_FLOAT, 3*sizeof (GLfloat), 1000, 6*sizeof(GLfloat));
//    m_OpenGLShader_1.enableAttributeArray(m_color);
    m_OpenGLShader_1.release();


}

void LqdOpenGLWidget::resizeGL(int w, int h)
{

}

void LqdOpenGLWidget::paintGL()
{
    qDebug("start paintGL\n");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    QMatrix4x4 m;
    m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
    m.translate(0.0f, 0.0f, -10.0f);
    m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    m_OpenGLShader_1.bind();
    m_OpenGLShader_1.setUniformValue("matrix", m);
    m_VAO.bind();
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
    //    glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glDrawArrays(GL_QUADS, 0, m_PointsVertex.size()/6);
    glDrawArrays(GL_POINTS, 0, m_buff_size);
//    glDrawArrays(GL_POINTS, 0, 1000);
    m_VAO.release();
    m_OpenGLShader_1.release();
}

void LqdOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void LqdOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotateBy(8 * dy, 8 * dx, 0);
    } else if (event->buttons() & Qt::RightButton) {
        rotateBy(8 * dy, 0, 8 * dx);
    }
    lastPos = event->pos();
}

void LqdOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked();
}

