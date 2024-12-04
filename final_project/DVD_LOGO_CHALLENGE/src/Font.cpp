#include "Font.hpp"

Font::Font(void* fontType) {
	font = fontType;
}

int Font::calculateTextWidth(const char* str) {
	int currentLineWidth = 0;

	int i = 0;
	while (str[i]) {
		// Update current line width size
		currentLineWidth += glutBitmapWidth(font, str[i]);
		i++;
	}

	return currentLineWidth;
}

int Font::calculateTextMaxWidth(const char* str) {
	int maxWidth = 0;
	int currentLineWidth = 0;

	int i = 0;
	while (str[i]) {
		if (str[i] == '\n') {
			// end of line: update maxWidth and reset line width
			maxWidth = std::max(maxWidth, currentLineWidth);
			currentLineWidth = 0;
		} else {
			// Update current line width size
			currentLineWidth += glutBitmapWidth(font, str[i]);
		}

		i++;
	}

	maxWidth = std::max(maxWidth, currentLineWidth);

	return maxWidth;
}

void Font::renderText(char str[], GLfloat startX, GLfloat startY,
		GLfloat lineHeight) {
	glRasterPos2f(startX, startY);

	int i = 0;
	GLfloat currentX = startX, currentY = startY;

	while (str[i]) {
		if (str[i] == '\n') {
			currentY -= lineHeight; // Decrease Y to move downward (assume position Y is up)
			currentX = startX;  // Reset X to start of the line
			glRasterPos2f(currentX, currentY);  // Update raster position
		} else {
			glutBitmapCharacter(font, str[i]);  // Draw each character
		}
		i++;
	}
}

// Function to render the text center horizontally within its own box
void Font::renderTextCenter(char str[], GLfloat startX, GLfloat startY,
		GLfloat lineHeight) {
	// Calculate the maximum width of any line in the multiline string
	int lineMaxWidth = calculateTextMaxWidth(str);

	// Make a copy of the string to prevent modification by strtok
	char strCopy[200];
	strncpy(strCopy, str, sizeof(strCopy));

	char* line = strtok(strCopy, "\n");
	int lineCount = 0;
	GLfloat lineStartX[10]; // Store the x position for each line

	// Calculate the starting X position for each line
	while (line != NULL) {
		int lineWidth = calculateTextWidth(line);
		lineStartX[lineCount] = (GLfloat) (lineMaxWidth - lineWidth) / 2; // center the text

		line = strtok(NULL, "\n");
		lineCount++;
	}

	// Use a copy of the original string for rendering
	char strRenderCopy[200];
	strncpy(strRenderCopy, str, sizeof(strRenderCopy));

	// Render the text
	line = strtok(strRenderCopy, "\n");  // Re-tokenize the string
	GLfloat currentX, currentY = startY;
	int i = 0;

	while (line != NULL) {
		currentX = startX + lineStartX[i]; // Center each line based on its width

		glRasterPos2f(currentX, currentY);  // Set position for this line
		for (int j = 0; line[j] != '\0'; j++) {
			glutBitmapCharacter(font, line[j]); // Render each character of the line
		}

		currentY -= lineHeight;  // Move to the next line
		line = strtok(NULL, "\n");  // Move to the next line
		i++;
	}
}

