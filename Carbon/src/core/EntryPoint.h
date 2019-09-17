#pragma once

extern Carbon::Application* Carbon::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Carbon::CreateApplication();
    app->run();
    delete app;
}