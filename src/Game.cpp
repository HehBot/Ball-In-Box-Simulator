#include <simplecpp>

#include <Game.hpp>

Game::Game(double p_l, double p_b, double p_r, double p_dt, double p_dilation, double p_f):
	l(p_l), b(p_b),
	r(p_r),
	dt(p_dt),
	dilation(p_dilation),
	f(p_f)
{
    std::cout << "Enter mass of box relative to ball: " ;
    std::cin >> m;
	I = m * (l + b) * (l + b) / 12;
    std::cout << "Render in ground frame ('1') or box frame ('0')? ";
    std::cin >> in_ground_frame;
    std::cout << "Click at the starting position of the ball\n";
    std::cout << "Click again to indicate initial velocity\n";
    std::cout << "Press 'q' to quit\n";
    wait(0.5);
}
