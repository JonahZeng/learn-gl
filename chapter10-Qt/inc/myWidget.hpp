#include "shader.h"
#include <QOpenGLWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QOpenGLFunctions_4_5_Core>

class MyGlWidget final: public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
public:
    MyGlWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~MyGlWidget();
    //-------gl object
    GLuint VAO;
    GLuint VBO;
    // GLuint EBO;
    GLuint texture0;
    GLuint texture1;
    Shader* myShader;
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
};

class MyWidget final: public QWidget
{
public:
    MyWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~MyWidget();
    MyGlWidget* glWidget;
    QHBoxLayout* mainLayout;
protected:
    void keyPressEvent(QKeyEvent* event) override;
};
