#pragma once

extern Carbon::Application* Carbon::CreateApplication();

int main(int argc, char** argv)
{
    LOG_INFO("Engine Start");
    auto app = Carbon::CreateApplication();
    app->run();
    delete app;
    LOG_INFO("Engine Stop");
}