#ifndef App_hpp
#define App_hpp

#include <vector>
#include "GlutApp.h"
#include "Rect.h"



class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;

    // Keep track of players turn
    char turn;

    bool isNewGame;

    bool menuOpen;

    bool ai;

    // Winner identifier
    char winner;

    // BG Color
    float rcolor; // 0.22 on r turn or 0
    float bcolor; // 0.22 on b turn or 0
    float gcolor; // 0.22 on win

    // Rectangles to be selected
    vector<Rect*> *rectangles;
    vector<Rect*> *options;

    // Int Array to player locations
    // 0 means no play, -1 means O and 1 means X
    int loc [9];


public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);

    // These are the events we want to handle
    void draw();
    void delay(float seconds);
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
    void checkWin();
    void drawMenu(string message);
};

#endif
