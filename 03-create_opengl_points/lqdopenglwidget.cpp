#include "lqdopenglwidget.h"
#include <QFile>


static GLfloat m_vertices[] = {
    -0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
    0.0f,   -0.8f,   0.0f,   0.0f, 0.0f, 1.0f,
    0.5f,   -0.5f,  -0.5f,   0.0f, 1.0f, 0.0f,
    0.0f,   0.5f,   0.0f,   0.0f, 0.0f, 1.0f,
};

LqdOpenGLWidget::LqdOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

LqdOpenGLWidget::~LqdOpenGLWidget()
{
    makeCurrent();
    m_VAO.destroy();
    m_VBO.destroy();
    doneCurrent();
}

void LqdOpenGLWidget::initializeGL()
{
    qDebug("start initializeGL\n");


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
            m_PointsVertex.replace(i*3, listline.at(0).toFloat());
            m_PointsVertex.replace(i*3+1, listline.at(1).toFloat());
            m_PointsVertex.replace(i*3+2, listline.at(2).toFloat());
        }
    }

    qDebug("m_PointsVertex.size:%d", m_PointsVertex.size()/6);


    initializeOpenGLFunctions();
    glShadeModel(GL_FLAT);
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
    m_VBO.allocate(m_PointsVertex.data(), m_PointsVertex.size());

    m_attr = m_OpenGLShader_1.attributeLocation("aPos");
    m_OpenGLShader_1.setAttributeBuffer(m_attr, GL_FLOAT, 0, m_PointsVertex.size()/6, 6*sizeof (GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_attr);

    m_color = m_OpenGLShader_1.attributeLocation("aColor");
    m_OpenGLShader_1.setAttributeBuffer(m_color, GL_FLOAT, 3*sizeof (GLfloat), m_PointsVertex.size()/6, 6*sizeof(GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_color);
    m_OpenGLShader_1.release();


}

void LqdOpenGLWidget::resizeGL(int w, int h)
{

}

void LqdOpenGLWidget::paintGL()
{
    qDebug("start paintGL\n");
    //    glClearColor(1.0, 1.0, 0.0, 0.0);
    //    glClear(GL_COLOR_BUFFER_BIT);
    m_OpenGLShader_1.bind();
    m_VAO.bind();
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
    //    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDrawArrays(GL_QUADS, 0, m_PointsVertex.size()/6);
//    glDrawArrays(GL_POINTS, 0, 4);
    m_VAO.release();
    m_OpenGLShader_1.release();
}

