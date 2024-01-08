#include "myWidget.hpp"
#include <QScreen>
#include <QApplication>
#include <QTimer>
#include <QKeyEvent>
#include <QImage>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// unsigned int indices[] = {
//     0, 1, 2,
//     1, 2, 3
// };

static glm::vec3 cubePositions[10] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
};

static glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,  -1.0f);
static glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

MyGlWidget::MyGlWidget(QWidget *parent, Qt::WindowFlags f): QOpenGLWidget(parent, f), myShader(nullptr)
{
}

MyGlWidget::~MyGlWidget()
{
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture0);
    glDeleteTextures(1, &texture1);
    myShader->del();
    doneCurrent();
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
    // glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#ifdef _MSC_VER
    myShader = new Shader("../../chapter10-Qt/src/shader.vs", "../../chapter10-Qt/src/shader.fs", QOpenGLContext::currentContext()->functions());
#else
	myShader = new Shader("../chapter10-Qt/src/shader.vs", "../chapter10-Qt/src/shader.fs", QOpenGLContext::currentContext()->functions());
#endif
    glEnable(GL_DEPTH_TEST);
}

void MyGlWidget::paintGL()
{
    QRect clientArea = geometry();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    myShader->use();
    myShader->setInt("texture0", 0);
    myShader->setInt("texture1", 1);


    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)clientArea.width() / clientArea.height(), 0.1f, 100.0f);
    myShader->setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
    myShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);

	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model;
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        myShader->setMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

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

void MyWidget::keyPressEvent(QKeyEvent* event)
{
    float cameraSpeed = 0.05f;
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
    else if(event->key() == Qt::Key_W)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    else if(event->key() == Qt::Key_S)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    else if(event->key() == Qt::Key_A)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    else if(event->key() == Qt::Key_D)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    else
    {
        event->ignore();
    }
}