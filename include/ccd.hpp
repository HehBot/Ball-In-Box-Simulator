#ifndef CCD_HPP
#define CCD_HPP

#include <cassert>

#include <Game.hpp>
#include <Var.hpp>
#include <Scene.hpp>

double root_Newton_Raphson(int n, Var const& var, Game const& game, double (Var::* pf)(Game &game, double eta) const, double (Var::* pDf)(Game const& game, double eta) const);

double root_bisection(int n, Var const& var, Game const& game, double (Var::* pf)(Game const& game, double eta) const);

void collision_at_l_edge(Game const& game, Var& var, Scene& scene, double eta);
void collision_at_b_edge(Game const& game, Var& var, Scene& scene, double eta);

#endif
