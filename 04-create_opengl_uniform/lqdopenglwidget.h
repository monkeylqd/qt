#ifndef LQDOPENGLWIDGET_H
#define LQDOPENGLWIDGET_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QTimer>
class LqdOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit LqdOpenGLWidget(QWidget *parent = nullptr);
    ~LqdOpenGLWidget();

public slots:
    void on_timeout();
signals:

private:
    QOpenGLVertexArrayObject m_VAO;
    QOpenGLBuffer m_VBO;
    QOpenGLShaderProgram m_OpenGLShader_1;
    int m_attr;
    int m_color;
    QTimer m_timer;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

};

#endif // LQDOPENGLWIDGET_H
