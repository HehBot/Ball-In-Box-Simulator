#include <ccd.hpp>

double root_Newton_Raphson(int n, Var const& var, Game const& game, double (Var::* pf)(Game const& game, double eta) const, double (Var::* pDf)(Game const& game, double eta) const)
{
    // Newton-Raphson method, not being used due to occasional hairy results
    double g = 0.5;
    for (int i = 0; i < n; i++) {
        g -= ((var.*pf)(game, g) / (var.*pDf)(game, g));
    }  
    return g;   
}

double root_bisection(int n, Var const& var, Game const& game, double (Var::* pf)(Game const& game, double eta) const)
{
    //Bisection method
    double gL = 0, gR = 1;                          // f(gL) < 0 and f(gR) > 0
    for(int i = 0; i < n; i++) {
        double f = (var.*pf)(game, (gL + gR) / 2);
        if (f > 0) {
            gR = (gL + gR) / 2;
        }
        else if (f < 0) {
            gL = (gL + gR) / 2;
        }
        else {
            return (gL + gR) / 2;
        }
    }

    double eta = (gL + gR) / 2;
    if (!(eta >= 0 && eta <= 1)) {
        std::cerr << eta << '\n';
        assert(false);
    }

    return eta; 
}

void collision_at_l_edge(Game const& game, Var& var, Scene& scene, double eta)
{	
	double s = sin(var.p), c = cos(var.p);

	var.advance(-eta * game.dt);
	scene.advance(game, var, (1 - eta) * game.dt);
	
	double i = (var.x_ball - var.x_box) * c + (var.y_ball - var.y_box) * s;
			
	double J = 2 * (var.vx * s - var.vy * c + var.Vy * c - var.Vx * s + i * var.o) / (1 + 1 / game.m + i * i / game.I);
	var.vx = var.vx - J * s;
	var.vy = var.vy + J * c;
	var.Vx = var.Vx + J * s / game.m;
	var.Vy = var.Vy - J * c / game.m;
	var.o = var.o - J * i / game.I;
	
	var.advance(eta * game.dt);
	scene.advance(game, var, eta * game.dt);
}

void collision_at_b_edge(Game const& game, Var& var, Scene& scene, double eta)
{
	double s = sin(var.p), c = cos(var.p);

	var.advance(-eta * game.dt);
	scene.advance(game, var, (1 - eta) * game.dt);
	
	double i = - (var.x_ball - var.x_box) * s + (var.y_ball - var.y_box) * c;
	
	double J = 2 * (var.vx * c + var.vy * s - var.Vy * s - var.Vx * c + i * var.o) / (1 + 1 / game.m + i * i / game.I);
	var.vx = var.vx - J * c;
	var.vy = var.vy - J * s;
	var.Vx = var.Vx + J * c / game.m;
	var.Vy = var.Vy + J * s / game.m;
	var.o = var.o - J * i / game.I;
	
	var.advance(eta * game.dt);
	scene.advance(game, var, eta * game.dt);
}
