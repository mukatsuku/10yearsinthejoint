#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("10 years in the joint made you a fucking pussy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    if (window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load the image
    SDL_Surface* imageSurface = IMG_Load("t.png");
    if (imageSurface == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture from the image
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the texture
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a font
    TTF_Font* font = TTF_OpenFont("test.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a surface with the text
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "10 years in the joint made you a fucking pussy", textColor);
    if (textSurface == nullptr) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture from the text surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set the position and size of the text
    SDL_Rect textRect;
    textRect.x = 10;
    textRect.y = 10;
    textRect.w = 100;
    textRect.h = 30;

    // Render the text texture
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Play the MP3 file
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    Mix_Music* music = Mix_LoadMUS("c.wav");
    if (music == nullptr) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
    }
    else {
        Mix_PlayMusic(music, -1); // -1 means loop the music
    }

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for the window to be closed
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Cleanup
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
