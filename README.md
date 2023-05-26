# Magenta

<p align="center"> A low-level C++ graphics library with ImGui support out of the box. <p>
 
## Getting started
  - The easiest way to get started is to clone the repo and start writing your code in the SandBox project. The project can be renamed but it also needs to be changed in the premake file
  
## Example

- The First thing you need to do is to Create an Application class. This can be done by inheriting from the Application class

```cpp
class SandBox : public Magenta::Application
{
public:
    SandBox() { }

    ~SandBox() { }
};
```
 - After this, we need to create a layer. A layer can be created by inheriting from the MagentaLayer class. A layer has the following part:
    * OnAttach method that runs once at the beginning of the program
    * OnDettach method that runs once at the end of the program
    * OnUpdate method that runs periodically until the program is closed
    * OnUIRender method that is responsible for rendering the ImGui UI

```cpp
  class SandBoxLayer : public Magenta::MagentaLayer
  {
  public:
    using MagentaLayer::MagentaLayer; 

    void OnAttach() override { }

    void OnDetach() override { }

    void OnUpdate() override { }

    void OnUIRender() override { }
};
```
- A layer must inherit the constructor from the class MagentaLayer.
- And the last step is to implement the CreaetApplication function
```cpp
Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();

    app->InitWindow(1280, 720, "SandBox");
    app->PushMagentaLayer(std::make_shared<SandBoxLayer>(app));

    return app;
}
```
- In the CreateApplication function, we must create an instance on the SandBox class, initialize our window, push the layer we created, and return an instance of the SandBox class
 
## 3rd party libaries & Tools
- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)
- [GLM](https://github.com/g-truc/glm)
- [Premake](https://github.com/premake/premake-core)
- [GLEW](https://github.com/nigels-com/glew)
