#include <math.h>
#include <time.h>
#include <string>

#include "App.h"
#include "Rect.h"


App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;

    // BG Color
    rcolor = 0.0;
    bcolor = 0.0;
    gcolor = 0.0;

    isNewGame = true;

    menuOpen = true;

    ai = false;

    // Rectangles
    rectangles = new vector<Rect*>;
    rectangles->push_back(new Rect(-0.9, 0.6, 0.6, 0.5));
    rectangles->push_back(new Rect(-0.3, 0.6, 0.6, 0.5));
    rectangles->push_back(new Rect(0.3, 0.6, 0.6, 0.5));

    rectangles->push_back(new Rect(-0.9, 0.1, 0.6, 0.5));
    rectangles->push_back(new Rect(-0.3, 0.1, 0.6, 0.5));
    rectangles->push_back(new Rect(0.3, 0.1, 0.6, 0.5));

    rectangles->push_back(new Rect(-0.9, -0.4, 0.6, 0.5));
    rectangles->push_back(new Rect(-0.3, -0.4, 0.6, 0.5));
    rectangles->push_back(new Rect(0.3, -0.4, 0.6, 0.5));

    // Options
    options = new vector<Rect*>;
    options->push_back(new Rect(-0.6, 0.0, 1.2, 0.3));
    options->push_back(new Rect(-0.6, -0.35, 1.2, 0.3));

    // Initialize all square values to be empty
    for(int i = 0; i<9; i++){ loc[i] = 0; }

    // first turn is x, then the winner goes first next round
    turn = 'x';

    // Winner will eventually be 'x' or 'o' or 'd' for draw
    winner = 'n';

}

//=======================================================================================

	// drawDiggie(start X, start Y, Scalar x, Scalar y)
	float drawDiggie(float X, float Y, float x, float y, bool one, bool two, bool three, bool four, bool five, bool six, bool seven){
		if (one){ //Vertical
			glBegin(GL_POLYGON);
				glVertex2f(.2f*x+X, .9f*y+Y);
				glVertex2f(.3f*x+X, 1.0f*y+Y);
				glVertex2f(.4f*x+X, .9f*y+Y);
				glVertex2f(.4f*x+X, .6f*y+Y);
				glVertex2f(.3f*x+X, .5f*y+Y);
				glVertex2f(.2f*x+X, .6f*y+Y);
			glEnd();
		}
		if (two){ //Horizontal 1
			glBegin(GL_POLYGON);
				glVertex2f(.4f*x+X, 1.1f*y+Y);//top left - left top
				glVertex2f(.3f*x+X, 1.0f*y+Y); //ctr - left
				glVertex2f(.4f*x+X, .9f*y+Y);//top right - left bottom
				glVertex2f(.7f*x+X, .9f*y+Y);// bottom right - bottom right
				glVertex2f(.8f*x+X, 1.0f*y+Y);// bottom - right
				glVertex2f(.7f*x+X, 1.1f*y+Y);// bottom left - right top
			glEnd();
		}
		if (three){ //vertical
			glBegin(GL_POLYGON);
				glVertex2f(.2f*x+X + x*.5, .9f*y+Y);
				glVertex2f(.3f*x+X + x*.5, 1.0f*y+Y);
				glVertex2f(.4f*x+X + x*.5, .9f*y+Y);
				glVertex2f(.4f*x+X + x*.5, .6f*y+Y);
				glVertex2f(.3f*x+X + x*.5, .5f*y+Y);
				glVertex2f(.2f*x+X + x*.5, .6f*y+Y);
			glEnd();
		}
		if (four){ //Horizontal 2
			glBegin(GL_POLYGON);
				glVertex2f(.4f*x+X, 1.1f*y+Y - y*.5);//top left - left top
				glVertex2f(.3f*x+X, 1.0f*y+Y - y*.5); //ctr - left
				glVertex2f(.4f*x+X, .9f*y+Y - y*.5);//top right - left bottom
				glVertex2f(.7f*x+X, .9f*y+Y - y*.5);// bottom right - bottom right
				glVertex2f(.8f*x+X, 1.0f*y+Y - y*.5);// bottom - right
				glVertex2f(.7f*x+X, 1.1f*y+Y - y*.5);// bottom left - right top
			glEnd();
		}
		if (five){ //vertical
			glBegin(GL_POLYGON);
				glVertex2f(.2f*x+X, .9f*y+Y - y*.5);
				glVertex2f(.3f*x+X, 1.0f*y+Y - y*.5);
				glVertex2f(.4f*x+X, .9f*y+Y - y*.5);
				glVertex2f(.4f*x+X, .6f*y+Y - y*.5);
				glVertex2f(.3f*x+X, .5f*y+Y - y*.5);
				glVertex2f(.2f*x+X, .6f*y+Y - y*.5);
			glEnd();
		}
		if (six){ //vertical
			glBegin(GL_POLYGON);
				glVertex2f(.2f*x+X + x*.5, .9f*y+Y - y*.5);
				glVertex2f(.3f*x+X + x*.5, 1.0f*y+Y - y*.5);
				glVertex2f(.4f*x+X + x*.5, .9f*y+Y - y*.5);
				glVertex2f(.4f*x+X + x*.5, .6f*y+Y - y*.5);
				glVertex2f(.3f*x+X + x*.5, .5f*y+Y - y*.5);
				glVertex2f(.2f*x+X + x*.5, .6f*y+Y - y*.5);
			glEnd();
		}
		if (seven){ //Horizontal 3
			glBegin(GL_POLYGON);
				glVertex2f(.4f*x+X, 1.1f*y+Y - y*1);//top left - left top
				glVertex2f(.3f*x+X, 1.0f*y+Y - y*1); //ctr - left
				glVertex2f(.4f*x+X, .9f*y+Y - y*1);//top right - left bottom
				glVertex2f(.7f*x+X, .9f*y+Y - y*1);// bottom right - bottom right
				glVertex2f(.8f*x+X, 1.0f*y+Y - y*1);// bottom - right
				glVertex2f(.7f*x+X, 1.1f*y+Y - y*1);// bottom left - right top
			glEnd();
		}
		return x*.8;
	}


//--------------(char c, start X, start Y, Scalar x, Scalar y)
//====================================================
float drawletter(char c, float X, float Y, float x, float y){
	float scoot = 0;
	if(c == 'X' || c == 'x'){
		scoot = drawDiggie(X, Y, x, y, true, false, true, true, true, true, false);
	}
	else if(c == 'A' || c == 'a'){
		scoot = drawDiggie(X, Y, x, y, true, true, true, true, true, true, false);
	}
	else if(c == 'I' || c == 'i'){
		scoot = drawDiggie(X, Y, x, y, true, false, false, false, true, false, false);
	}
	else if(c == 'E' || c == 'e'){
		scoot = drawDiggie(X, Y, x, y, true, true, false, true, true, false, true);
  }
	else if(c == 'R' || c == 'r'){
		scoot = drawDiggie(X, Y, x, y, true, true, true, true, true, true, false);
	}
	else if(c == 'n' || c == 'N'){
		scoot = drawDiggie(X, Y, x, y, true, true, true, false, true, true, false);
	}
  else if(c == 'P' || c == 'p'){
    scoot = drawDiggie(X, Y, x, y, true, true, true, true, true, false, false);
  }
  else if(c == 'l' || c == 'L'){
    scoot = drawDiggie(X, Y, x, y, true, false, false, false, true, false, true);
  }
  else if(c == 'y' || c == 'Y'){
    scoot = drawDiggie(X, Y, x, y, true, false, true, true, false, true, true);
  }
  else if(c == '1'){
    scoot = drawDiggie(X, Y, x, y, true, false, false, false, true, false, false);
  }
  else if(c == ' '){
    scoot = drawDiggie(X, Y, x, y, false, false, false, false, false, false, false);
  }
  else if(c == '2'){
    scoot = drawDiggie(X, Y, x, y, false, true, true, true, true, false, true);
  }
  else if(c == 'c' || c == 'C'){
    scoot = drawDiggie(X, Y, x, y, true, true, false, false, true, false, true);
  }
  else if(c == 'h' || c == 'H'){
    scoot = drawDiggie(X, Y, x, y, true, false, true, true, true, true, false);
  }
  else if(c == 'o' || c == 'O'){
    scoot = drawDiggie(X, Y, x, y, true, true, true, false, true, true, true);
  }
  else if(c == 's' || c == 'S'){
    scoot = drawDiggie(X, Y, x, y, true, true, false, true, false, true, true);
  }
  else if (c == '-'){
    scoot = drawDiggie(X, Y, x, y, false, false, false, true, false, false, false);
  }
	return scoot;
}

//----------(string name, start X, start Y, Scalar x, Scalar y)
void drawname(string name, float X, float Y, float x, float y) {

	// for each letter print char
	float scoot = 0;
	float tmp = X;
	for (size_t i = 0; i < name.length(); i++){
		tmp = tmp + scoot;
		scoot = drawletter(name[i], tmp, Y, x, y);
	}
}
//============end of mods

// This checks for a winner and changes char winner = 'x' or 'o'
// This function is called every turn, so it is used for debugging.
void App::checkWin() {

  //TODO: automatically assign last spot in rect to 'turn'
  // First, see if the array is full
  bool full = true;
  for (int i = 0; i < 9; i++){
    if (loc[i] == 0){
      full = false;
      break;
    }
  }

  // Check for a winner in the columns
  for(int i = 0; i < 3; i++) {
    if ( (loc[i] != 0) && ((loc[i] == loc[i+3]) && (loc[i] == loc[i+6])) ) {
      if (loc[i] == 1) {
        winner = 'x';
      }
      else {
        winner = 'o';
      }
      menuOpen = true;
    }
  }

  // Check for a winner in the rows
  for(int i = 0; i < 7; i+=3) {
    if ( (loc[i] != 0) && ((loc[i] == loc[i+1]) && (loc[i] == loc[i+2])) ) {
      if (loc[i] == 1) {
        winner = 'x';
      }
      else {
        winner = 'o';
      }
      menuOpen = true;
    }
  }

  // Check for a winner in the diagonals
  if ( (loc[0] != 0) && ((loc[0] == loc[4]) && (loc[0] == loc[8])) ) {
    if (loc[0] == 1) {
      winner = 'x';
    }
    else {
      winner = 'o';
    }
    menuOpen = true;
  }
  else if ( (loc[2] != 0) && ((loc[2] == loc[4]) && (loc[2] == loc[6])) ) {
    if (loc[0] == 1) {
      winner = 'x';
    }
    else {
      winner = 'o';
    }
    menuOpen = true;
  }

  // Check if all boxes are full.
  if ((full == true) && (winner == 'n')){
    winner = 'd';
    menuOpen = true;
  }

  glFlush();
  glutSwapBuffers();

}

void App::delay(float secs){
  float end = clock()/CLOCKS_PER_SEC + secs;
  while((clock()/CLOCKS_PER_SEC) < end);
}

// Main Draw function
void App::draw() {

      // Clear the screen and set BG color (for unknown reasons, it wont work doing this once.)
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // Set background color
      if(turn == 'x') { rcolor = 0.22; gcolor = 0.0; bcolor = 0.0; }
      else if(turn == 'o') { rcolor = 0.0; gcolor = 0.0; bcolor = 0.22; }
      else if(turn == 'd') { rcolor = 0.22; gcolor = 0.0; bcolor = 0.22; }
      else { rcolor = 0.22; gcolor = 0.22; bcolor = 0.0; }
      glClearColor(rcolor/0.2, gcolor/0.2, bcolor/0.2, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // Set background color
      if(turn == 'x') { rcolor = 0.22; gcolor = 0.0; bcolor = 0.0; }
      else if(turn == 'o') { rcolor = 0.0; gcolor = 0.0; bcolor = 0.22; }
      else if(turn == 'd') { rcolor = 0.22; gcolor = 0.0; bcolor = 0.22; }
      else { rcolor = 0.22; gcolor = 0.22; bcolor = 0.0; }
      glClearColor(rcolor/0.2, gcolor/0.2, bcolor/0.2, 1.0);

      // Set up the transformations stack
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      // Set Color
      glColor3f(1.0, 1.0, 1.0);

      // Draw the team on top to indicate player's turn X/O
      if (turn == 'x') {
        glBegin(GL_LINES);
        glVertex2f(0.0f - 0.1f, 0.8f - 0.1f);
        glVertex2f(0.0f + 0.1f, 0.8f + 0.1f);
        glVertex2f(0.0f + 0.1f, 0.8f - 0.1f);
        glVertex2f(0.0f - 0.1f, 0.8f + 0.1f);
        glEnd();
      }
      else {
        float DEG2RAD = 3.14159/180;
        glBegin(GL_LINE_LOOP);
        for (int i=0; i < 360; i++) {
          float degInRad = i*DEG2RAD;
          glVertex2f(cos(degInRad)*0.1 + 0.0f, sin(degInRad)*0.1 + 0.8f);
        }
        glEnd();
      }

      // Draw player's moves
      // Temp vars to shift the X axis of token
      for (int i = 0; i<9; i++){
        // Use this as your center cordinate for X and Os
        float xshift = -0.6;
        float yshift = 0.35;

        // Temp variables for shifting X token
        int column = i%3;
        if(column == 1) { xshift = 0; }
        else if(column == 2) { xshift = 0.6; }

        // Temp vars for shifting Y for token
        if(i >=3 && i < 6) { yshift = -.15; }
        else if (i >= 6) { yshift = -.65; }

        // Draw X
        if (loc[i] == 1){
          glBegin(GL_LINES);
          glVertex2f(xshift - 0.2f, yshift - 0.2f);
          glVertex2f(xshift + 0.2f, yshift + 0.2f);
          glVertex2f(xshift + 0.2f, yshift - 0.2f);
          glVertex2f(xshift - 0.2f, yshift + 0.2f);
          glEnd();
        }

        // Draw O
        else if (loc[i] == -1){
          // Draw O
          float DEG2RAD = 3.14159/180;
          glBegin(GL_LINE_LOOP);
          for (int i=0; i < 360; i++) {
            float degInRad = i*DEG2RAD;
            glVertex2f(cos(degInRad)*0.2 + xshift, sin(degInRad)*0.2 + yshift);
          }
          glEnd();
        }
      }

      // Draw Grid
      glBegin(GL_LINES);
      // vertical top
      glVertex2f(-0.3f, -0.9f);
      glVertex2f(-0.3f, 0.6f);
      // vertical bottom
      glVertex2f(0.3f, -0.9f);
      glVertex2f(0.3f, 0.6f);
      // horizontal top
      glVertex2f(-0.9f, 0.1f);
      glVertex2f(0.9f, 0.1f);
      // horizontal bottom
      glVertex2f(-0.9f, -0.4f);
      glVertex2f(0.9f, -0.4f);
      glEnd();

      //Draw rectangles to make sure that we did it right
      for(auto it = rectangles->cbegin(); it != rectangles->cend(); it++){
        glColor3d(rcolor/0.5, gcolor/0.5, bcolor/0.5);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        glVertex2f((*it)->getX(),                   (*it)->getY());
        glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY());
        glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY()-(*it)->getH());
        glVertex2f((*it)->getX(),                   (*it)->getY()-(*it)->getH());
        glEnd();

        glColor3d(rcolor/0.5, gcolor/0.5, bcolor/0.5);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
        glVertex2f((*it)->getX(),                   (*it)->getY());
        glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY());
        glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY()-(*it)->getH());
        glVertex2f((*it)->getX(),                   (*it)->getY()-(*it)->getH());
        glEnd();
      }

      // We have been drawing everything to the back buffer
      // Swap the buffers to see the result of what we drew
      glFlush();
      glutSwapBuffers();


          if(menuOpen){
            if (winner != 'n'){
              delay(2);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // This game has started, so it is no longer new
            isNewGame = false;

            //Set background color
            if(winner == 'x') { rcolor = 0.22; gcolor = 0.0; bcolor = 0.0; }
            else if(winner == 'o') { rcolor = 0.0; gcolor = 0.0; bcolor = 0.22; }
            else if(winner == 'd') { rcolor = 0.22; gcolor = 0.0; bcolor = 0.22; }
            else { rcolor = 0.22; gcolor = 0.22; bcolor = 0.0; }
            glClearColor(rcolor/0.2, gcolor/0.2, bcolor/0.2, 1.0);

          //==============================================================
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //glClearColor(rcolor/0.2, gcolor/0.2, bcolor/0.2, 1.0);

            // Clear the screen
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Clear the screen
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Set up the transformations stack
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            // Set Color
            glColor3d(0.0, 0.0, 0.0);

            //Draw font for  buttons
            //=======================FONT============================



            //========================END============================

            drawname("choose one", -0.61f, .2f, .15f, .15f);

            drawname("1 PLAYER", -0.5f, -.23f, .15f, .15f);

            drawname("2 PLAYER", -0.5f, -.58f, .15f, .15f);

            //Draw rectangles for our menu buttons
            for(auto it = options->cbegin(); it != options->cend(); it++){
              glColor3d(0.0f, 0.0f, 0.0f);

              glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
              glBegin(GL_POLYGON);
              glVertex2f((*it)->getX(),                   (*it)->getY());
              glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY());
              glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY()-(*it)->getH());
              glVertex2f((*it)->getX(),                   (*it)->getY()-(*it)->getH());
              glEnd();

              glColor3d(rcolor/0.5, gcolor/0.5, bcolor/0.5);

              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
              glBegin(GL_POLYGON);
              glVertex2f((*it)->getX(),                   (*it)->getY());
              glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY());
              glVertex2f((*it)->getX()+(*it)->getW(),     (*it)->getY()-(*it)->getH());
              glVertex2f((*it)->getX(),                   (*it)->getY()-(*it)->getH());
              glEnd();
            }

            glColor3d(rcolor/0.3, gcolor/0.3, bcolor/0.3);
            drawname("xoxoxoxo", -1.18f, -1.0f, 0.4f, 1.0f);
            // We have been drawing everything to the back buffer
            // Swap the buffers to see the result of what we drew
            glFlush();
            glutSwapBuffers(); //==========================================================

            // Initialize all squares to empty
            for(int i = 0; i<9; i++){ loc[i] = 0; }

            // Winner is first on restart
            if (winner != 'n' && winner != 'd'){
                turn = winner;
            }
            else {
              turn = 'x';
            }

            // Winner will eventually be 'x' or 'o' or 'd' for draw
            winner = 'n';
            }

}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

    // Set clickable rectangles only if the menu is open
    if(menuOpen){
      // Iterate through the option buttons and check if any contain the click event
      int i = 0;
      for(auto it = options->cbegin(); it != options->cend(); it++){
        if ((*it)->contains(mx, my)){
          if (i == 0) { // First Menu button
            ai = true;
            menuOpen = false;
            if(winner == 'o' || turn == 'o'){
              int pick = (int)rand()%9;
              if (loc[pick] == 0){
                loc[pick] = -1;
                turn = 'x';
              }
            }
          }
          if (i == 1) {
            ai = false;
            menuOpen = false;
          }
        }
        i++;
      }
    }
    else{
      // Iterate through the squares and check if any contain the click event

      // one player
      if (ai && turn=='x') {
        int i = 0;
        for(auto it = rectangles->cbegin(); it != rectangles->cend(); it++){
          if ((*it)->contains(mx, my)){
            // Make sure this rectangle is empty before doing anything
            if (loc[i]!=0) { break; }
            // if 'it' is clicked, add the corresponding player's decision to the array
            if(turn == 'x'){
              loc[i] = 1;
              turn = 'o';
            }
            else{
              loc[i] = -1;
              turn = 'x';
            }
            draw();
            // Now check for a winner-=======================================================
            checkWin();
            // Here we start our AI response
            // Delay makes it seem like AI is thinking
            delay((rand()%4));
            if (menuOpen == true) {
              break;
            }
            else if (ai && turn =='o'){
              int pick;
              while (true){
                pick = (int)rand()%9;
                if (loc[pick] == 0){
                  loc[pick] = -1;
                  turn = 'x';
                  checkWin();
                  redraw();
                  break;
                }
              }
            }
          }
          i++;
        }
      }


      // 2 Player Mode.
      else{
        int i = 0;
        for(auto it = rectangles->cbegin(); it != rectangles->cend(); it++){
          if ((*it)->contains(mx, my)){
            // Make sure this rectangle is empty before doing anything
            if (loc[i]!=0) { break; }
            // if 'it' is clicked, add the corresponding player's decision to the array
            if(turn == 'x'){
              loc[i] = 1;
              turn = 'o';
            }
            else{
              loc[i] = -1;
              turn = 'x';
            }

            // Now check for a winner
            checkWin();

            break;
          }
          i++;
        }

      }
    }

    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;

    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27 || key == 3){
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
