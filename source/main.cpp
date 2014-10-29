#include "./headers/main.hpp"

int main(int argc, char** argv){
	/*Initializes SDL for graphical display*/
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		SDLerrorLogger("SDL initialization");
		std::cout<<"Failed to initialize SDL, see errorlog for details."<<std::endl;
		return 1;
	}

	/*Disables pesky screensavers while our wonderful graphics are beeing displayed*/
	SDL_DisableScreenSaver();

	/*Initializes a window to render graphics in*/
	SDL_Window *win = SDL_CreateWindow("SA", 0, 0, EMconsts::windowlength, EMconsts::windowheight, 0);
	if (win == nullptr){
		SDLerrorLogger("SDL_CreateWindow");
		std::cout<<"Failed to create SDL window, see errorlog for details."<<std::endl;
		return 1;
	}

	/*Initializes the renderer to draw in*/
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDLerrorLogger("SDL_CreateRenderer");
		std::cout<<"Failed to create SDL renderer, see errorlog for details."<<std::endl;
		return 1;
	}

	Means initmeans(1.9,6.2);
	Mixture_of_gaussian emalg(initmeans, "../data/sample_data.txt");
	bool done = false;

	for(int i = 0; i < EMconsts::iterations; i++){
		emalg.run_algorithm(EMconsts::algiterations);
		std::cout << "Iteration: " << i+1 << " ======================================\n";
		emalg.present_state(ren);
		std::cout << std::endl;

		pollevent(done);

		SDL_RenderPresent(ren);
		if(done){
			break;
		}
		usleep(EMconsts::iterationdelay);
	}

	waitForEvent();
	
}

void pollevent(bool& var){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				var = true;
				break;
			default:
				break;
		}
	}
}


void waitForEvent(){
	SDL_Event event;
	bool done = false;
	while((!done) && (SDL_WaitEvent(&event))) {
        switch(event.type) {
    
            case SDL_KEYDOWN:
                done = true;
                break;


            case SDL_QUIT:
                done = true;
                exit(0);
                break;
                
            default:
                break;
        } 
            
    }
}