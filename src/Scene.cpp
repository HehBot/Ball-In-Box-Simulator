#include "Scene.hpp"

// class of rendered scene
Scene::Scene(Game const &game, Var const &var):
	box(var.x_box, var.y_box, game.l, game.b),
	box_top_left(var.x_box - game.l / 2, var.y_box - game.b/2, 10),
	box_bottom_right(var.x_box + game.l/2, var.y_box + game.b/2, 10),
	ball(var.x_ball, var.y_ball, game.r)
{
	box.setFill(false);
	box.setColor(COLOR("green"));

	box_top_left.setFill(true);
	box_top_left.setColor(COLOR("green"));
	
	box_bottom_right.setFill(false);
	box_bottom_right.setColor(COLOR("green"));
	
	ball.setFill(true);
	ball.setColor(COLOR("blue"));
}

void Scene::advance(Game const& game, Var const& var, double wait_time)
{
    double s = sin(var.p), c = cos(var.p);
    if (game.in_ground_frame){
        ball.moveTo(var.x_ball, var.y_ball);

        box.moveTo(var.x_box, var.y_box);
        box.rotate(var.p - box.getOrientation());

        box_top_left.moveTo(var.x_box - game.l * c / 2 + game.b * s / 2, var.y_box - game.l * s / 2 - game.b * c /2);
        box_bottom_right.moveTo(var.x_box + game.l * c / 2 - game.b * s / 2, var.y_box + game.l * s / 2 + game.b * c /2);
    }
    else {
        double x_ball_in_box_frame, y_ball_in_box_frame;
        x_ball_in_box_frame = WINDOW_X / 2 + (var.x_ball - var.x_box) * c + (var.y_ball - var.y_box) * s;
        y_ball_in_box_frame = WINDOW_Y / 2 + (var.y_ball - var.y_box) * c - (var.x_ball - var.x_box) * s;
        ball.moveTo(x_ball_in_box_frame, y_ball_in_box_frame);
    }

    wait(wait_time * game.dilation);
}
