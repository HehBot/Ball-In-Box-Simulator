/*
	Created by Arnav Aditya Singh
*/

#include <Game.hpp>
#include <Var.hpp>
#include <Scene.hpp>
#include <Display_var.hpp>

#include <ccd.hpp>

#define WINDOW_X 1200
#define WINDOW_Y 600


//void display_coordinates(Text &x_ball_disp, double x_ball, Text &y_ball_disp, double y_ball, Text &x_box_disp, double x_box, Text &y_box_disp, double y_box, Text &p_disp, double p, Text &x_COM_disp, double x_COM, Text &y_COM_disp, double y_COM, Text &t_disp, double t)
//{	
//	x_ball_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 100, "x_ball = " + to_string(x_ball));
//	y_ball_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 110, "y_ball = " + to_string(y_ball));
//	x_box_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 120, "x_box = " + to_string(x_box));
//	y_box_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 130, "y_box = " + to_string(y_box));
//	p_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 140, "p = " + to_string(p));
//	x_COM_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 150, "x_COM = " + to_string(x_COM));
//	y_COM_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 160, "y_COM = " + to_string(y_COM));
//	return;
//}

int main()
{
	Game game(500, 250, 15, 0.01, 1, 1);
	
	initCanvas("Bouncing ball", WINDOW_X, WINDOW_Y);
	
	Var var(game, WINDOW_X / 2, WINDOW_Y / 2, 0, 0, 0, 0, 0);
	
	Scene scene(game, var);
	Display_var display_var(game, var);	

//	Text x_ball_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 100, "x_ball = " + to_string(x_ball));
//	Text y_ball_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 110, "y_ball = " + to_string(y_ball));
//	Text x_box_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 120, "x_box = " + to_string(x_box));
//	Text y_box_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 130, "y_box = " + to_string(y_box));
//	Text p_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 140, "p = " + to_string(p));
//	Text x_COM_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 150, "x_COM = " + to_string(x_COM));
//	Text y_COM_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 160, "y_COM = " + to_string(y_COM));

    XEvent e;

	while (true) {
        if (checkEvent(e) && keyPressEvent(e) && charFromEvent(e) == 'q')
            break;

		var.advance(game.dt);
		double upper_l_edge = var.collision_expression_for_upper_l_edge(game, 0);
		double lower_l_edge = var.collision_expression_for_lower_l_edge(game, 0);
		double left_b_edge = var.collision_expression_for_left_b_edge(game, 0);
		double right_b_edge = var.collision_expression_for_right_b_edge(game, 0);
	
        double eta;
		if (upper_l_edge <= 0 || lower_l_edge <= 0 || left_b_edge <= 0 || right_b_edge <= 0) {
			if ((upper_l_edge <= 0 || lower_l_edge <= 0) && left_b_edge > 0 && right_b_edge > 0) {
				if (upper_l_edge <= 0) {
					eta = root_bisection(4, var, game, &Var::collision_expression_for_upper_l_edge);			
				}
				else {
					eta = root_bisection(4, var, game, &Var::collision_expression_for_lower_l_edge);		
				}
								
				collision_at_l_edge(game, var, scene, eta);		
			}
			else if ((left_b_edge <= 0 || right_b_edge <= 0) && upper_l_edge > 0 && lower_l_edge > 0) {
				if (left_b_edge <= 0) {
					eta = root_bisection(4, var, game, &Var::collision_expression_for_left_b_edge);
				}
				else {
					eta = root_bisection(4, var, game, &Var::collision_expression_for_right_b_edge);
				}
				
				collision_at_b_edge(game, var, scene, eta);
			}
		}
		else if (upper_l_edge <= 0 && left_b_edge <= 0) {
			if (upper_l_edge < left_b_edge) {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_upper_l_edge);
                collision_at_l_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_left_b_edge);
                collision_at_b_edge(game, var, scene, eta);
			}
			else {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_left_b_edge);
                collision_at_b_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_upper_l_edge);
                collision_at_l_edge(game, var, scene, eta);
			}
		}
		else if (upper_l_edge <= 0 && right_b_edge <= 0) {
			if (upper_l_edge < right_b_edge) {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_upper_l_edge);
                collision_at_l_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_right_b_edge);
                collision_at_b_edge(game, var, scene, eta);
			}
			else {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_right_b_edge);
                collision_at_b_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_upper_l_edge);
                collision_at_l_edge(game, var, scene, eta);
			}
		}
		else if (lower_l_edge <= 0 && left_b_edge <= 0) {
			if (lower_l_edge < left_b_edge) {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_lower_l_edge);
                collision_at_l_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_left_b_edge);
                collision_at_b_edge(game, var, scene, eta);
			}
			else {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_left_b_edge);
                collision_at_b_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_lower_l_edge);
                collision_at_l_edge(game, var, scene, eta);
			}
		}
		else if (lower_l_edge <= 0 && right_b_edge <= 0) {
			if (lower_l_edge < right_b_edge) {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_lower_l_edge);
                collision_at_l_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_right_b_edge);
                collision_at_b_edge(game, var, scene, eta);
			}
			else {
                eta = root_bisection(4, var, game, &Var::collision_expression_for_right_b_edge);
                collision_at_b_edge(game, var, scene, eta);
                eta = root_bisection(4, var, game, &Var::collision_expression_for_lower_l_edge);
                collision_at_l_edge(game, var, scene, eta);
			}
		}
		else {
			scene.advance(game, var, game.dt);
		}
			
        var.x_COM = (var.x_ball + game.m * var.x_box) / (game.m + 1), var.y_COM = (var.y_ball + game.m * var.y_box) / (game.m + 1);
        var.L = (var.x_ball * var.vy - var.y_ball * var.vx) + game.m * (var.x_box * var.Vy - var.y_box * var.Vx) + game.I * var.o;
        var.VCx = (var.vx + game.m * var.Vx) / (game.m + 1);
        var.VCy = (var.vy + game.m * var.Vy) / (game.m + 1);
        var.E = 0.5 * (var.vx * var.vx + var.vy * var.vy + game.m * var.Vx * var.Vx + game.m * var.Vy * var.Vy + game.I * var.o * var.o);
		
		display_var.update(var);
//		display_coordinates(x_ball_disp, x_ball, y_ball_disp, y_ball, x_box_disp, x_box, y_box_disp, y_box, p_disp, p, x_COM_disp, x_COM, y_COM_disp, y_COM);
	}
	
	return 0;
}
