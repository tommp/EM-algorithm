
#ifndef MAIN_HPP
#define MAIN_HPP


/*Included headers*/
/*---------------------------------------------*/
#include "errorlogger.hpp"
#include "alg.hpp"
/*---------------------------------------------*/

/*Included dependencies*/
/*---------------------------------------------*/
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <unistd.h>
/*---------------------------------------------*/

/*Header content*/
/*=============================================*/
void pollevent(bool& var);

void waitForEvent();
/*=============================================*/

#endif