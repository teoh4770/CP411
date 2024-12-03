#include "Score.hpp"

Score::Score() {
	points = 0;
}

int Score::getPoints() const {
    return points;
}

void Score::increment() {
	points += 1;
}

void Score::reset() {
	points = 0;
}
