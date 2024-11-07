#include "lqdopenglwidget.h"


//static GLfloat m_vertices[] = {
//    -0.5f,  -0.5f,  0.5f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//    0.0f,   -0.8f,   0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//    0.5f,   -0.5f,  -0.5f,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//    0.0f,   0.5f,   0.0f,   0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//};

//static GLfloat m_vertices[]={
//    // 位置              // 颜色               //纹理坐标
//    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    0.2f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f,    0.0f, 0.2f,   // 左下
//    0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    0.2f, 0.2f,   // 右上
//};

//static GLfloat m_vertices[]={
//    // 位置              // 颜色               //纹理坐标
//    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    1.5f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f,    0.0f, 1.5f,   // 左下
//    0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    1.5f, 1.5f,   // 右上
//};

//static GLfloat m_vertices[]={
//    // 位置              // 颜色               //纹理坐标
//    1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,    1.0f, 0.0f,   // 右下
//    -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f,   // 左下
//    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,    0.0f, 1.0f,   // 左下
//    1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,    1.0f, 1.0f,   // 右上
//};

//static GLfloat m_vertices[]={
//    // 位置              // 颜色               //纹理坐标
//    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    1.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f,   // 左下
//    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f,    0.0f, 1.0f,   // 左下
//    0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    1.0f, 1.0f,   // 右上
//};

static GLfloat m_vertices[]={
    // 位置              // 颜色               //纹理坐标
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    3.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f,    0.0f, 3.0f,   // 左下
    0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    3.0f, 3.0f,   // 右上
};

LqdOpenGLWidget::LqdOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent), m_texture(QOpenGLTexture::Target2D), m_cstexture(QOpenGLTexture::Target2D)
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
    initializeOpenGLFunctions();
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

    // 纹理的相关配置必须在initializeGL里面
    m_texture.create();
    m_texture.setData(QImage(":/image/wall.jpg").mirrored());
//    m_texture.setData(QImage(":/image/cs.png").mirrored());
        m_texture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
        m_texture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
    //    m_texture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::MirroredRepeat);
    //    m_texture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::MirroredRepeat);
    //    m_texture.setBorderColor(QColor(1.0f,1.0f,1.0f,1.0f));
    //    m_texture.setMinMagFilters(QOpenGLTexture::Nearest,QOpenGLTexture::Linear);
        m_texture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);

        float borderColor[] = {1.0, 1.0, 0.0, 1.0};
    m_cstexture.create();
    m_cstexture.setData(QImage(":/image/cs.png").mirrored());
//        m_cstexture.setData(QImage(":/image/wall.jpg").mirrored());
//    m_cstexture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
//    m_cstexture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
    m_cstexture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::ClampToBorder);
    m_cstexture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::ClampToBorder);
    m_cstexture.setBorderColor(1.0f, 1.0f, 0.0f, 1.0f);
    //    m_cstexture.setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::MirroredRepeat);
    //    m_cstexture.setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::MirroredRepeat);
    //    m_cstexture.setBorderColor(QColor(1.0f,1.0f,1.0f,1.0f));
    //    m_cstexture.setMinMagFilters(QOpenGLTexture::Nearest,QOpenGLTexture::Linear);
        m_cstexture.setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);

    //    glShadeModel(GL_FLAT);

    m_VAO.create();
    m_VAO.bind();

    m_VBO.create();
    m_VBO.bind();
    m_VBO.allocate(m_vertices, sizeof (m_vertices));

    m_attr = m_OpenGLShader_1.attributeLocation("aPos");
    m_OpenGLShader_1.setAttributeBuffer(m_attr, GL_FLOAT, 0, 3, 8*sizeof (GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_attr);

    m_color = m_OpenGLShader_1.attributeLocation("aColor");
    m_OpenGLShader_1.setAttributeBuffer(m_color, GL_FLOAT, 3*sizeof (GLfloat), 3, 8*sizeof(GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_color);

    m_textureID = m_OpenGLShader_1.attributeLocation("aTexcoord");
    m_OpenGLShader_1.setAttributeBuffer(m_textureID, GL_FLOAT, 6*sizeof (GLfloat), 2, 8*sizeof(GLfloat));
    m_OpenGLShader_1.enableAttributeArray(m_textureID);



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
//    m_VAO.bind();
    m_texture.bind(0);
    m_cstexture.bind(1);

    m_OpenGLShader_1.setUniformValue("ourTexture", 0);  // 纹理单元绑定必须在paintGL里面
    m_OpenGLShader_1.setUniformValue("csTexture", 1);  // 纹理单元绑定必须在paintGL里面
    glDrawArrays(GL_QUADS, 0, 4);
    //    glDrawArrays(GL_POLYGON, 0, 4);
    //    glDrawArrays(GL_POINTS, 0, 4);
    m_VAO.release();
    m_OpenGLShader_1.release();
}

