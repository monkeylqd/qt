#ifndef LQDOPENGLWIDGET_H
#define LQDOPENGLWIDGET_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QVector>
#include <QTimer>
class LqdOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit LqdOpenGLWidget(QWidget *parent = nullptr);
    ~LqdOpenGLWidget();

public slots:
    void on_timeout();
    void rotateBy(int xAngle, int yAngle, int zAngle);
signals:
    void clicked();

private:
    QOpenGLVertexArrayObject m_VAO;
    QOpenGLBuffer m_VBO;
    QOpenGLShaderProgram m_OpenGLShader_1;
    int m_attr;
    int m_color;
    QVector<float> m_PointsVertex;
    float *m_buff;
    int m_buff_size;
    QTimer m_timer;


    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif // LQDOPENGLWIDGET_H
