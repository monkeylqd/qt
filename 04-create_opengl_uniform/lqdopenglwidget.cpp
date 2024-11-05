#include "lqdopenglwidget.h"
#include <QTime>

//static GLfloat m_vertices[] = {
//    -0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
//    0.0f,   -0.8f,   0.0f,   0.0f, 0.0f, 1.0f,
//    0.5f,   -0.5f,  -0.5f,   0.0f, 1.0f, 0.0f,
//    0.0f,   0.5f,   0.0f,   0.0f, 0.0f, 1.0f,
//};

static GLfloat m_vertices[] = {
    -0.5f,  -0.5f,  0.5f,
    0.0f,   -0.8f,   0.0f,
    0.5f,   -0.5f,  -0.5f,
    0.0f,   0.5f,   0.0f,
};

LqdOpenGLWidget::LqdOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_timer.start(1000);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
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
    static int count = 0;
    count++;
    makeCurrent();
    m_OpenGLShader_1.bind();
    int time = QTime::currentTime().second();
//    float uniformVale = (sin(time)/2.0f)+0.5f;
//    m_OpenGLShader_1.setUniformValue("uniform_ourColor", 0.0, uniformVale, 0.0, 1.0);

    if(count%4 == 0)
    {
        m_OpenGLShader_1.setUniformValue("uniform_ourColor", 1.0, 0.0, 0.0, 1.0);
    }
    else if(count%4 == 1)
    {
        m_OpenGLShader_1.setUniformValue("uniform_ourColor", 0.0, 1.0, 0.0, 1.0);
    }
    else if(count%4 == 2)
    {
        m_OpenGLShader_1.setUniformValue("uniform_ourColor", 0.0, 0.0, 1.0, 1.0);
    }
    else if(count%4 == 3)
    {
        m_OpenGLShader_1.setUniformValue("uniform_ourColor", 0.0, 0.0, 0.0, 1.0);
    }
    m_OpenGLShader_1.release();
    doneCurrent();
    update();
}

void LqdOpenGLWidget::initializeGL()
{
    qDebug("start initializeGL\n");
    initializeOpenGLFunctions();
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
    m_VBO.allocate(m_vertices, sizeof (m_vertices));

    m_attr = m_OpenGLShader_1.attributeLocation("aPos");
    m_OpenGLShader_1.setAttributeBuffer(m_attr, GL_FLOAT, 0, 3, 3*sizeof (GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_attr);

//    m_color = m_OpenGLShader_1.attributeLocation("aColor");
//    m_OpenGLShader_1.setAttributeBuffer(m_color, GL_FLOAT, 3*sizeof (GLfloat), 4, 6*sizeof(GLfloat));
//    m_OpenGLShader_1.enableAttributeArray(m_color);
    m_OpenGLShader_1.release();


}

void LqdOpenGLWidget::resizeGL(int w, int h)
{

}

void LqdOpenGLWidget::paintGL()
{
    qDebug("start paintGL\n");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    m_OpenGLShader_1.bind();
    m_VAO.bind();
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glDrawArrays(GL_QUADS, 0, 4);
//    glDrawArrays(GL_POINTS, 0, 4);
    m_VAO.release();
    m_OpenGLShader_1.release();
}

