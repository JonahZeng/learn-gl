#include "myWidget.hpp"
#include <QScreen>
#include <QApplication>
#include <QTime>
#include <QTimer>

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f, 
    0.0f, 0.5f, 0.0f
};

static const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

static const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"    FragColor = ourColor;\n"
	"}\0";

MyGlWidget::MyGlWidget(QWidget *parent, Qt::WindowFlags f): QOpenGLWidget(parent, f)
{
}

MyGlWidget::~MyGlWidget()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

	QTime currentTime = QTime::currentTime();

	float timeValue = currentTime.second() + currentTime.msec() / 1000.0f;
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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