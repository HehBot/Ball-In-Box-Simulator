#include <Display_var.hpp>

Display_var::Display_var(Game const& game, Var const& var):
	m_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y - 20, "m = " + to_string(game.m)),
	t_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y - 10, "t = " + to_string(var.t)),
	vx_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y, "vx = " + to_string(var.vx)),
	vy_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 10, "vy = " + to_string(var.vy)),
	Vx_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 20, "Vx = " + to_string(var.Vx)),
	Vy_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 30, "Vy = " + to_string(var.Vy)),
	o_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 40, "o = " + to_string(var.o)),
	VCx_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 50, "VCx = " + to_string(var.VCx)),
	VCy_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 60, "VCy = " + to_string(var.VCy)),
	L_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 70, "L = " + to_string(var.L)),
	E_disp(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 80, "E = " + to_string(var.E))
{}

void Display_var::update(Var const& var)
{
	t_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y - 10, "t = " + to_string(var.t));
	vx_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y, "vx = " + to_string(var.vx));
	vy_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 10, "vy = " + to_string(var.vy));
	Vx_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 20, "Vx = " + to_string(var.Vx));
	Vy_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 30, "Vy = " + to_string(var.Vy));
	o_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 40, "o = " + to_string(var.o));
	VCx_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 50, "VCx = " + to_string(var.VCx));
	VCy_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 60, "VCy = " + to_string(var.VCy));
	L_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 70, "L = " + to_string(var.L));
	E_disp.reset(0.9 * WINDOW_X, 0.1 * WINDOW_Y + 80, "E = " + to_string(var.E));
	return;
}

