#include "Logo.hpp"
#include <cstdlib>

Logo::Logo() {
	// Initialize the logo properties
	position.x = 100.0f;
	position.y = 100.0f;

	velocity.x = 1.0f;
	velocity.y = 1.0f;

	size.width = 100.0f;
	size.height = 100.0f;

	bgColor.r = 0.0f;
	bgColor.g = 7.0f;
	bgColor.b = 1.0f;
}

void Logo::draw() {
	glColor3f(bgColor.r, bgColor.g, bgColor.b);
	glBegin(GL_POLYGON);
	glVertex2f(position.x, position.y);
	glVertex2f(position.x + size.width, position.y);
	glVertex2f(position.x + size.width, position.y + size.height);
	glVertex2f(position.x, position.y + size.height);
	glEnd();
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

void Logo::detectCollision(GLsizei windowWidth, GLsizei windowHeight, Score &score) {
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
