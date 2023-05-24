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
        m_Renderer2D->DrawBox({m_Application->GetWidth() / 2 - 200.0f, m_Application->GetHeight() / 2 - 100.0f}, {200.0f, 200.0f}, {0.3f, 0.8f, 0.2f, 1.0f});

        m_Renderer2D->DrawBox({m_Application->GetWidth() / 2, m_Application->GetHeight() / 2 - 100.0f}, {200.0f, 200.0f}, {0.3f, 0.2f, 0.8f, 1.0f});

        m_Renderer2D->ClearColor(0.22f, 0.22f, 0.22f, 1.0f);
    }

    void OnUIRender() override
    {
        ImGui::Begin("ViewPort");

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(0.0f, 0.0f); 

        ImGui::Image((void*)m_FrameBuffer->GetColorAttachment(), ImGui::GetContentRegionAvail());

        ImGui::End();
    }

private:
    std::shared_ptr<Magenta::Renderer2D> m_Renderer2D = m_Application->GetRenderer2D();
    std::shared_ptr<Magenta::FrameBuffer> m_FrameBuffer = m_Application->GetFrameBuffer();
};

Magenta::Application* Magenta::CreateApplication()
{
    SandBox* app = new SandBox();

    app->InitWindow(1280, 720, "SandBox");
    app->PushMagentaLayer(std::make_shared<SandBoxLayer>(app));

    return app;
}