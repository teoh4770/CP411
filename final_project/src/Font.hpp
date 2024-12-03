#ifndef FONT_H
#define FONT_H

#include <windows.h>
#include <GL/glut.h>
#include <cstring>
#include <algorithm> // For std::max

class Font {
private:
	void* font; // Font type (e.g., GLUT_BITMAP_HELVETICA_18)

public:
	// Constructor to initialize the font
	    Font(void* fontType);

	    // Function to calculate the width of the text
	    int calculateTextWidth(const char* str);

	    // Function to calculate the max width of multiline text
	    int calculateTextMaxWidth(const char* str);

	    // Function to render the text at a specific position
	    void renderText(char str[], GLfloat startX, GLfloat startY, GLfloat lineHeight);

	    // Function to render the text center horizontally within its own box
	    void renderTextCenter(char str[], GLfloat startX, GLfloat startY, GLfloat lineHeight);
};


#endif
