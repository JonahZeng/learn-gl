#include "myWidget.hpp"
#include <QScreen>
#include <QApplication>
#include <QTimer>

static float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

MyGlWidget::MyGlWidget(QWidget *parent, Qt::WindowFlags f): QOpenGLWidget(parent, f), myShader(nullptr)
{
}

MyGlWidget::~MyGlWidget()
{
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    myShader->del();
    doneCurrent();
    delete myShader;
}

void MyGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

#ifdef _MSC_VER
    myShader = new Shader("../../chapter4-Qt/src/shader.vs", "../../chapter4-Qt/src/shader.fs", QOpenGLContext::currentContext()->functions());
#else
	myShader = new Shader("../chapter4-Qt/src/shader.vs", "../chapter4-Qt/src/shader.fs", QOpenGLContext::currentContext()->functions());
#endif
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    myShader->use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void MyGlWidget::resizeGL(int w, int h)
{
}

MyWidget::MyWidget(QWidget *parent, Qt::WindowFlags f): QWidget(parent, f), 
    glWidget(nullptr), mainLayout(nullptr)
{
    QList<QScreen*> screenInfoList = QApplication::screens();
    QRect screenRect = screenInfoList.at(0)->geometry();
    setGeometry(screenRect.width() / 6, screenRect.height() / 6, screenRect.width() * 2 / 3, screenRect.height() * 2 / 3);
    glWidget = new MyGlWidget();
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(glWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
    setWindowTitle("learnOpenGL-Qt");

	QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, glWidget, QOverload<>::of(&MyGlWidget::update));
    timer->start(33);
}

MyWidget::~MyWidget()
{

}