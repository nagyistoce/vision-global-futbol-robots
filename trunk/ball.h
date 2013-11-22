/*
 * ball.h
 *
 *  Created on: 31/10/2011
 *      Author: willytell
 */

#ifndef BALL_H_
#define BALL_H_

#include "pattern.h"

class Ball {
public:
	bool enabled;
	int color_id;  	// color id used by a ball

	float area_min;
	float area_max;
	float area_mean;

	CvPoint center;		// central position of the patch
	CvPoint field_pos;	// translated center point to field position using an homography matrix.
	float height;		// height of cover above ground plane

	//float orientation;	// orientation between first and second marker
	//float speed;		// speed in x and y.

	Ball();
	virtual ~Ball();
};

#endif /* BALL_H_ */
