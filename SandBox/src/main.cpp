#include "Magenta.h"
#include <glm/glm.hpp>
#include <memory>
#include "iostream"

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
        m_Renderer2D->DrawBox2D(glm::vec2(m_Application->GetWidth() / 2 - 200.0f, m_Application->GetHeight() / 2 - 100.0f), glm::vec2(200.0f, 200.0f), glm::vec4(0.3f, 0.8f, 0.2f, 1.0f));

        m_Renderer2D->DrawBox2D(glm::vec2(m_Application->GetWidth() / 2, m_Application->GetHeight() / 2 - 100.0f), glm::vec2(200.0f, 200.0f), glm::vec4(0.3f, 0.2f, 0.8f, 1.0f));

        m_Renderer2D->ClearColor(0.22f, 0.22f, 0.22f, 1.0f);
    }

    void OnUIRender() override
    {
        ImGui::Begin("ViewPort");

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(0.0f, 0.0f);

        for(size_t i = 0; i < 1280 * 720; i++)
        {
            m_ImageData[i] = 0xFFA3A2FF;
        } 

        m_Image = std::make_shared<Magenta::Image>(m_ImageData, glm::vec2(1280, 720), GL_RGBA);

        ImGui::Image((void*)m_Image->GetTextureID(), ImGui::GetContentRegionAvail());

        ImGui::End();
    }

private:
    std::shared_ptr<Magenta::Renderer2D> m_Renderer2D = m_Application->GetRenderer2D();
    std::shared_ptr<Magenta::Image> m_Image;
    uint32_t* m_ImageData = new uint32_t[m_Application->GetWidth() * m_Application->GetHeight()];
};

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();

    app->InitWindow(1280, 720, "SandBox");
    app->PushMagentaLayer(std::make_shared<SandBoxLayer>(app));

    return app;
}