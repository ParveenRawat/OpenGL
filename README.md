# OpenGL Lighting Engine

A modern OpenGL rendering project written in C++ using GLFW, GLEW, and GLM.
Implements textured meshes, lighting, camera movement, and shader-based rendering.


## Features

- OpenGL 3.3 Core Profile
- Phong lighting
- Diffuse + specular textures
- Camera movement
- Shader abstraction
- Mesh abstraction
- Depth testing
- Texture loading


## Dependencies

- OpenGL
- GLFW
- GLEW
- GLM


```bash
sudo pacman -S glfw-x11 glew glm mesa
```

## Screenshots

![image](./Screenshots/Screenshot_2025-10-05-18-28-21_1366x768.png)
![image](./Screenshots/Screenshot_2025-10-05-21-06-45_1366x768.png)
![image](./screenshots/screenshot_2025-10-05-21-06-45_1366x768.png)
![image](./Screenshots/Screenshot_2025-10-09-13-28-01_1366x768.png)
![image](./Screenshots/Screenshot_2025-10-10-00-21-35_1366x768.png)
![image](./Screenshots/Screenshot_2025-10-10-01-07-15_1366x768.png)



## 6. Build Instructions

```bash
g++ -std=c++17 \
    main.cpp src/*.cpp \
    -Iinclude \
    -lglfw -lGLEW -lGL \
    -o app
```


## Controls

| Key | Action |
|-----|--------|
| W A S D | Move camera |
| Mouse | Look around |
| Scroll | Zoom |
| ESC | Exit |
