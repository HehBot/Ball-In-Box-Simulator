#include <Game.hpp>
#include <Var.hpp>

Var::Var(Game const& game, double p_x_box, double p_y_box, double p_p, double p_o, double p_t, double p_VCx, double p_VCy):
	x_box(p_x_box), y_box(p_y_box),
	p(p_p),
	o(p_o),
	t(p_t),
	VCx(p_VCx), VCy(p_VCy)
{
    {   // to automatically delete temporary shapes below
        Rectangle temp_box(WINDOW_X / 2, WINDOW_Y / 2, game.l, game.b);
        Circle temp_box_top_left(WINDOW_X / 2 - game.l / 2, WINDOW_Y / 2 - game.b/2, 10);
        Circle temp_box_bottom_right(WINDOW_X / 2 + game.l/2, WINDOW_Y / 2 + game.b/2, 10);
        temp_box.setFill(false);
        temp_box.setColor(COLOR("green"));
        temp_box_top_left.setFill(true);
        temp_box_top_left.setColor(COLOR("green"));
        temp_box_bottom_right.setFill(false);
        temp_box_bottom_right.setColor(COLOR("green"));

        int click = getClick();
        x_ball = click / 65536, y_ball = click % 65536;

        while (abs(x_ball - x_box) >= game.l / 2 - game.r || abs(y_ball - y_box) >= game.b / 2) {                                                         
            std::cerr << "Starting position of ball should be inside box, select again!\n";
            click = getClick();
            x_ball = click / 65536, y_ball = click % 65536;
        }

        click = getClick();
        
        vx = game.f * (click / 65536 - x_ball), vy = game.f * (click % 65536 - y_ball);
        Vx = (VCx * (game.m + 1) - vx) / game.m, Vy = (VCy * (game.m + 1) - vy) / game.m;
        x_COM = (x_box * game.m + x_ball) / (game.m + 1), y_COM = (y_box * game.m + y_ball) / (game.m + 1);
        L = (x_ball * vy - y_ball * vx + game.m * (x_box * Vy - y_box * Vx)), E = 0.5 * (vx * vx + vy * vy + game.m * Vx * Vx + game.m * Vy * Vy);
    }
}

void Var::advance(double delta_t)
{
    x_ball += vx * delta_t;
    y_ball += vy * delta_t;
    x_box += Vx * delta_t;
    y_box += Vy * delta_t;
    p += o * delta_t;
    t += delta_t;

    if (p > 2 * PI || p < 0) {
        p = p - 2 * PI * floor(p/(2 * PI));
    }
}

double Var::collision_expression_for_upper_l_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return (y_ball - y_box) * c - (x_ball - x_box) * s - ((vy - Vy) * c - (vx - Vx) * s) * eta * game.dt + (game.b / 2 - game.r);
}

double Var::Dcollision_expression_for_upper_l_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return (y_ball - y_box) * s * o * game.dt + (x_ball - x_box) * c * o * game.dt - ((vy - Vy) * c - (vx - Vx) * s) * game.dt - ((vy - Vy) * s + (vx - Vx) * c) * o * eta * game.dt * game.dt;
}

double Var::collision_expression_for_lower_l_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return -(y_ball - y_box) * c + (x_ball - x_box) * s + ((vy - Vy) * c - (vx - Vx) * s) * eta * game.dt + (game.b / 2 - game.r);
}

double Var::Dcollision_expression_for_lower_l_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return -(y_ball - y_box) * s * o * game.dt - (x_ball - x_box) * c * o * game.dt + ((vy - Vy) * c - (vx - Vx) * s) * game.dt + ((vy - Vy) * s - (vx - Vx) * c) * o * eta * game.dt * game.dt;
}

double Var::collision_expression_for_left_b_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return (y_ball - y_box) * s + (x_ball - x_box) * c - ((vy - Vy) * s + (vx - Vx) * c) * eta * game.dt + (game.l / 2 - game.r);
}

double Var::Dcollision_expression_for_left_b_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return -(y_ball - y_box) * c * o * game.dt + (x_ball - x_box) * s * o * game.dt - ((vy - Vy) * s + (vx - Vx) * c) * game.dt + ((vy - Vy) * c - (vx - Vx) * s) * o * eta * game.dt * game.dt;
}

double Var::collision_expression_for_right_b_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return -(y_ball - y_box) * s - (x_ball - x_box) * c + ((vy - Vy) * s + (vx - Vx) * c) * eta * game.dt + (game.l / 2 - game.r);
}

double Var::Dcollision_expression_for_right_b_edge(Game const& game, double eta) const
{
    double c = cos(p - eta * o * game.dt), s = sin(p - eta * o * game.dt);
    return (y_ball - y_box) * c * o * game.dt - (x_ball - x_box) * s * o * game.dt + ((vy - Vy) * s + (vx - Vx) * c) * game.dt - ((vy - Vy) * c - (vx - Vx) * s) * o * eta * game.dt * game.dt;
}
