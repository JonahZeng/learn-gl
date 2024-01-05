# learn OpenGL
----
## note
代码已在windows11(MSVC v143)和ubuntu22.04(GCC 11.3.0)上通过测试，我的显卡驱动支持的OpenGL版本为4.6;
ubuntu上需要安装glfw3：
```bash
sudo apt install libglfw3-dev
# 查看OpenGL版本
sudo apt install mesa-utils
DISPLAY=:0 glxgears -info | grep GL_VERSION # 查看显卡对应的 opengl 版本
```
如果你的OpenGL版本不是4.6，请前往[这里下载glad](https://glad.dav1d.de)，然后替换掉third-party/glad目录下的文件；
## Qt
chapter[x]-Qt与chatper[x]的程序功能是类似的，只是没有使用glad和glfw库，而是使用Qt框架自带的OpenGL4.5环境；
我使用的Qt版本是6.4.3，搭配vscode开发，为了使cmake找到Qt，应修改.vscode目录下的setting.json文件中的CMAKE_PREFIX_PATH路径：
```json
"cmake.configureArgs": ["-DCMAKE_PREFIX_PATH=D:/qt643/qtbase", "-DUSE_QT=TRUE"],
```
如果你不想使用Qt，则令USE_QT=FALSE即可；
编译后的程序运行依赖Qt动态链接库，所以在运行之前你应当使用Qt自带的deployqt工具，复制动态链接库到你的程序目录下：
```bat
D:/your-qtbase-dir/bin/windeployqt.exe ./chapter1-Qt.exe
```

## 构建
在当前项目根目录下，新建build文件夹，然后切换到build目录下，执行
```bat
cmake ..
cmake --build . --config Release --target ALL_BUILD
```
当然更好的办法是vscode+cmake tools插件，直接打开项目目录即可自动配置；
## chapter1
第一个三角形，以及两个三角形组成一个矩形

## chapter2
GLSL规则，uniform变量

## chapter3
多vertex，输入三角形顶点坐标+顶点颜色；

## chapter4
做一个三角形着色器类

## chapter5
实现贴图纹理

## chapter6
实现贴图纹理并偏移旋转

## chapter7
实现纹理贴图，呈现3D立体效果

## chapter8
实现纹理贴图，呈现动态3D BOX效果

## chapter9
多个3D BOX