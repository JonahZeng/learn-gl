#include "myWidget.hpp"
#include <QScreen>
#include <QApplication>
#include <QTimer>
#include <QKeyEvent>
#include <QImage>

static float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
};

static float faceMixWeight = 0.5f;

MyGlWidget::MyGlWidget(QWidget *parent, Qt::WindowFlags f): QOpenGLWidget(parent, f), myShader(nullptr)
{
}

MyGlWidget::~MyGlWidget()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture0);
    glDeleteTextures(1, &texture1);
    myShader->del();
    delete myShader;
}

void MyGlWidget::initializeGL()
{
#ifdef _MSC_VER
    QImage data0("../../image/container.jpg");
    QImage data1("../../image/awesomeface.png");
#else
    QImage data0("../image/container.jpg");
    QImage data1("../image/awesomeface.png");
#endif

    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(!data0.isNull())
    {
        data0.convertTo(QImage::Format_RGB888);
        data0.mirror(false, true);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data0.width(), data0.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, data0.constBits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        qDebug() << "Failed to load texture";
    }

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(!data1.isNull())
    {
        data1.convertTo(QImage::Format_RGBA8888);
        data1.mirror(false, true);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data1.width(), data1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data1.constBits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        qDebug() << "Failed to load texture";
    }

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

	glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#ifdef _MSC_VER
    myShader = new Shader("../../chapter5-Qt/src/shader.vs", "../../chapter5-Qt/src/shader.fs", QOpenGLContext::currentContext()->functions());
#else
	myShader = new Shader("../chapter5-Qt/src/shader.vs", "../chapter5-Qt/src/shader.fs", QOpenGLContext::currentContext()->functions());
#endif
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    myShader->use();
    myShader->setInt("texture0", 0);
    myShader->setInt("texture1", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    myShader->setFloat("mixWeight", faceMixWeight);

	glBindVertexArray(VAO);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        faceMixWeight += 0.1f;
        faceMixWeight = faceMixWeight > 1.0f ? 1.0f:faceMixWeight;
    }
    else if(event->key() == Qt::Key_Down)
    {
        faceMixWeight -= 0.1f;
        faceMixWeight = faceMixWeight < 0.0f ? 0.0f:faceMixWeight;
    }
    else{
        event->ignore();
    }
}