#include "Magenta.h"
#include "EntryPoint.h"

#include <glm/glm.hpp>
#include <memory>

class SandBox : public Magenta::Application
{
public:
    SandBox() { }

    ~SandBox() { }
};

class SandBoxLayer : public Magenta::MagentaLayer
{
public:
    using MagentaLayer::MagentaLayer; 

    void OnAttach() override { }

    void OnDetach() override { }

    void OnUpdate() override 
    {
        if(m_InputManager->IsKeyDown(Magenta::KeyCode::Escape))
        {
            m_Application->CloseWindow();
        }

        std::vector<uint32_t> imageData(m_Application->GetWidth() * m_Application->GetHeight());

        for (size_t i = 0; i < imageData.size(); i++)
        {
            imageData[i] = 0xFFA5A6F1;
        }
        
        m_Image = std::make_unique<Magenta::Image>(imageData.data(), glm::vec2(m_Application->GetWidth(), m_Application->GetHeight()), GL_RGBA);
    }

    void OnUIRender() override
    {
        ImGui::Begin("ViewPort");

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(0.0f, 0.0f); 

        ImGui::Image((void*)m_Image->GetTextureID(), ImGui::GetContentRegionAvail());
        ImGui::Text("deltaTime: %fms", m_Application->GetDeltaTime());

        ImGui::End();
    }

private:
    std::shared_ptr<Magenta::InputManager> m_InputManager = m_Application->GetInputManager();
    std::unique_ptr<Magenta::Image> m_Image;
};

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();

    app->InitWindow(1280, 720, "SandBox");
    app->PushMagentaLayer(std::make_shared<SandBoxLayer>(app));

    return app;
}