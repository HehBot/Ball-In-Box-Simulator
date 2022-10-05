#ifndef DISPLAY_VAR_HPP
#define DISPLAY_VAR_HPP

#include <simplecpp>

#include <Game.hpp>
#include <Var.hpp>

class Display_var{
	Text m_disp;
	Text t_disp;
	Text vx_disp;
	Text vy_disp;
	Text Vx_disp;
	Text Vy_disp;
	Text o_disp;
	Text VCx_disp;
	Text VCy_disp;
	Text L_disp;
	Text E_disp;
public:
	Display_var(Game const& game, Var const& var);
    void update(Var const& var);
};

#endif
