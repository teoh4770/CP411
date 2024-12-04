#ifndef CSCORE_H
#define CSCORE_H

class Score {
private:
	int points;

public:
	Score();

	int getPoints() const;

	void increment();
	void reset();
};

#endif
