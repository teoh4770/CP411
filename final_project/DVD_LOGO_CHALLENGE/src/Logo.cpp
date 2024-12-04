#include "Logo.hpp"
#include <cstdlib>
#include <cmath>

// Image
struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};

// Loading Texture
// Reads a BMP file and loads its data into an Image structure.
// Convert img for BGR (BMP format) to RGB for OpenGL compatibility
int ImageLoad(const char *filename, Image *image) {
	FILE *file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)

	char temp; // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}

	// read the height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}

	size = image->sizeX * image->sizeY * 3;

	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bpp (bits per pixel)
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	return 1;
}

// Function to load the BMP texture into the Image structure
Image* loadTextureData(const char *filename) {
	Image *image = (Image *) malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating space for image");
	}
	if (!ImageLoad(filename, image)) {
		printf("Error allocating space for image");
	}
	return image;
}

Logo::Logo() {
	// Initialize the logo properties
	position.x = 100.0f;
	position.y = 100.0f;

	velocity.x = 1.0f;
	velocity.y = 1.0f;

	size.width = 180.0f;
	size.height = size.width / 2;

	bgColor.r = 0.0f;
	bgColor.g = 7.0f;
	bgColor.b = 1.0f;

	textureID = -1;
}

void Logo::loadTexture(const char *filename) {
	Image *image = loadTextureData(filename);  // Load texture from file
	glGenTextures(1, &textureID);          // Generate a texture ID
	glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture to OpenGL

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Scale linearly when the image is bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Scale linearly when the image is smaller
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND); // Set texture environment mode

	// Create the texture from the image data
	if (image->data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image->data);
	}

	free(image->data);  // Clean up the image data after loading it into OpenGL
	free(image);
}

void Logo::draw() {
	glEnable(GL_TEXTURE_2D);  // Enable 2D textures
	glBindTexture(GL_TEXTURE_2D, textureID);  // Bind the logo texture

	glColor4f(bgColor.r, bgColor.g, bgColor.b, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  // Texture coordinates for the bottom-left corner
	glVertex2f(position.x, position.y);

	glTexCoord2f(1.0f, 0.0f); // Texture coordinates for the bottom-right corner
	glVertex2f(position.x + size.width, position.y);

	glTexCoord2f(1.0f, 1.0f);  // Texture coordinates for the top-right corner
	glVertex2f(position.x + size.width, position.y + size.height);

	glTexCoord2f(0.0f, 1.0f);  // Texture coordinates for the top-left corner
	glVertex2f(position.x, position.y + size.height);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Logo::move() {
	position.x += velocity.x;
	position.y += velocity.y;
}

void Logo::moveUp() {
	velocity.y = 1;
}

void Logo::moveDown() {
	velocity.y = -1;
}

void Logo::moveLeft() {
	velocity.x = -1;
}

void Logo::moveRight() {
	velocity.x = 1;
}

void Logo::detectCollision(GLsizei windowWidth, GLsizei windowHeight,
		Score &score) {
	bool cornerHit = false;

	bool leftBoundary = position.x <= 0;
	bool rightBoundary = position.x + size.width >= windowWidth;
	bool topBoundary = position.y + size.height >= windowHeight;
	bool bottomBoundary = position.y <= 0;

	if (leftBoundary) {
		position.x = 0;
		velocity.x = -velocity.x;
	}

	if (rightBoundary) {
		position.x = windowWidth - size.width;
		velocity.x = -velocity.x;
	}

	if (bottomBoundary) {
		position.y = 0;
		velocity.y = -velocity.y;
	}

	if (topBoundary) {
		position.y = windowHeight - size.height;
		velocity.y = -velocity.y;
	}

	if (leftBoundary || rightBoundary || bottomBoundary || topBoundary) {
		changeRandomColor();
	}

	if (leftBoundary || rightBoundary) {
		if (bottomBoundary || topBoundary) {
			cornerHit = true;
		}
	}

	if (cornerHit) {
		// increment the score
		score.increment();
	}
}

void Logo::changeRandomColor() {
	float newR, newG, newB;

    // Generate new random RGB values ensuring significant difference from the current color
	do {
		newR = static_cast<float>(rand()) / RAND_MAX;
		newG = static_cast<float>(rand()) / RAND_MAX;
		newB = static_cast<float>(rand()) / RAND_MAX;
	} while (fabs(newR - bgColor.r) < 0.2f && fabs(newG - bgColor.g) < 0.2f
			&& fabs(newB - bgColor.b) < 0.2f);

	bgColor.r = newR;
	bgColor.g = newG;
	bgColor.b = newB;
}
