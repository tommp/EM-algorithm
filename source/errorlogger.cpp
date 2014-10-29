#include "./headers/errorlogger.hpp"

void SDLerrorLogger(const char *msg){
	time_t current = time(0);
	tm *date_raw = gmtime(&current);
	char *date = asctime(date_raw);

	std::ofstream errors; 
	errors.open("ErrorLog.txt", std::ofstream::app);
	if(errors.is_open()){
		errors << "Date: "<< date << msg << " Error: "<< SDL_GetError() << "\n" << std::endl;
		errors.close();
	}/*IF*/
	else{
		printf("Error opening external file Errorlog.txt\n");
		printf("%s", msg);
		printf(" Error: %s\n Date: %s\n", SDL_GetError(), date );
	}/*ELSE*/
}/*SDLerrorLogger*/

void errorlogger(const char *errormsg){
	time_t current = time(0);
	tm *date_raw = gmtime(&current);
	char *date = asctime(date_raw);

	std::ofstream errors; 
	errors.open("ErrorLog.txt", std::ofstream::app);
	if(errors.is_open()){
		errors << "Date: "<< date << "Error: " << errormsg << "\n" << std::endl;
		errors.close();
	}/*IF*/
	else{
		printf("Error opening external file Errorlog.txt\n");
		printf(" Error: %s\n Date: %s\n", errormsg, date );
	}/*ELSE*/
}/*errorLogger*/
