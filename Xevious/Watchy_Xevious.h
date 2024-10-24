#ifndef WATCHY_XEVIOUS_H
#define WATCHY_XEVIOUS_H

#ifdef WATCHY_SIM
#include "..\..\Watchy.h"
#else // WATCHY_SIM
#include <Watchy.h>
#endif // WATCHY_SIM

#define INDEX_SIZE 4

class WatchyXevious : public Watchy{
    public:
        using Watchy::Watchy;

        void drawWatchFace();
        void drawBackground();
        void drawBattery();
        void drawEnemy();
        void drawZapper();
        void drawSeg(const int& num, const int& index_x, const int& index_y, const bool& xevi_lang);
        void drawDate(const bool& xevi_lang);
        void drawSOL();

#ifndef WATCHY_SIM
        void handleButtonPress();
#endif
};

#endif