#ifndef SETLIGHT_H_INCLUDED
#define SETLIGHT_H_INCLUDED



typedef enum{
                GREEN  = 5,
                RED = 2,
                YELLOW = 4,
                WAIT = 27
            }LED;




int setLight( LED in_whichLED, int in_newState );     //returns '1' if succesfull


int initOutput();                                      //returns '1' if succesfull
























#endif // SETLIGHT_H_INCLUDED
