#pragma once

#include <string>
#include "SDL2/SDL.h"
#include <iostream>

class Window {
    
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    inline bool isClosed() const { return _closed; }

    void pollEvents();
    void clear() const;

    SDL_Renderer* getRenderer();

private:
    bool init();

private:
    std::string _title;
    int _width = 800;
    int _height = 600;

    bool _closed = false;

    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;

};

