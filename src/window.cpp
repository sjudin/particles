#include "window.h"

Window::Window(const std::string &title, int width, int height):
    _title(title), _width(width), _height(height)
{
    _closed = !init();
}

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Window::pollEvents()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
              _closed = true;
              break;

            default:
              break;
        }
    }
}

bool Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to initialize SDL" << std::endl;

        return false;
    }

    _window = SDL_CreateWindow(
                  _title.c_str(),
                  SDL_WINDOWPOS_CENTERED,
                  SDL_WINDOWPOS_CENTERED,
                  _width, _height,
                  0
              );

    if (_window == nullptr)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == nullptr)
    {
        std::cerr << "Failed to create renderer!" << std::endl;
        return false;
    }

    return true;
}

SDL_Renderer* Window::getRenderer()
{
    return _renderer;
}

void Window::clear() const
{
    SDL_RenderPresent(_renderer);
    SDL_SetRenderDrawColor(_renderer, 205, 207, 190, 10);
    SDL_RenderClear(_renderer);
}
