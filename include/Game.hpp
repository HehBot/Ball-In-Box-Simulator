#ifndef GAME_HPP
#define GAME_HPP

#define WINDOW_X 1200
#define WINDOW_Y 600

// class of loop constants
class Game {
public:
	double l;
	double b;
	double r;
	double dt;				// Time step of game loop
	double dilation;		// Rendering speed wrt simulation speed
	double f;				// Scaling factor for velocity input
	double m;				// Mass of box (relative to ball)
	double I;				// I_COM of box
	bool in_ground_frame;	// Frame of simulation

	Game(double p_l, double p_b, double p_r, double p_dt, double p_dilation, double p_f);
};

#endif
