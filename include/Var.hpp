#ifndef VAR_HPP
#define VAR_HPP

#include <Game.hpp>
#include <simplecpp>

// class of loop variables
class Var {
public:
	double x_box;
	double y_box;
	double p;				// Angle of rotation of box (in rad wrt +x axis) measured clockwise
	double o;				// Angular velocity of box (in rad/s) measured clockwise
	double t;
	double VCx;
	double VCy;
	
	double x_ball;
	double y_ball;
	double vx;
	double vy;
	double Vx;
	double Vy;
	double x_COM;
	double y_COM;
	double L;				// Angular momentum about origin
	double E;				// Kinetic energy of system

	Var(Game const& game, double p_x_box, double p_y_box, double p_p, double p_o, double p_t, double p_VCx, double p_VCy);
    void advance(double delta_t);

    double collision_expression_for_upper_l_edge(Game const& game, double eta) const;
    double Dcollision_expression_for_upper_l_edge(Game const& game, double eta) const;
    double collision_expression_for_lower_l_edge(Game const& game, double eta) const;
    double Dcollision_expression_for_lower_l_edge(Game const& game, double eta) const;
    double collision_expression_for_left_b_edge(Game const& game, double eta) const;
    double Dcollision_expression_for_left_b_edge(Game const& game, double eta) const;
    double collision_expression_for_right_b_edge(Game const& game, double eta) const;
    double Dcollision_expression_for_right_b_edge(Game const& game, double eta) const;
};

#endif
