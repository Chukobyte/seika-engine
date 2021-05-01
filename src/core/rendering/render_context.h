#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../utils/logger.h"

class RenderContext {
  public:
    RenderContext() = default;

    ~RenderContext() {
        FT_Done_FreeType(freeTypeLibrary);
    }

    SDL_Window *window = nullptr;
    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
                                      SDL_WINDOW_OPENGL
                                      | SDL_WINDOW_RESIZABLE
                                      | SDL_WINDOW_ALLOW_HIGHDPI
                                  );
    SDL_GLContext gl_context;
    FT_Library freeTypeLibrary;

    void InitializeFont() {
        if(FT_Init_FreeType(&freeTypeLibrary)) {
            Logger::GetInstance()->Error("Could not initialize FreeType Library!");
        }
    }
};

#endif //RENDER_CONTEXT_H
