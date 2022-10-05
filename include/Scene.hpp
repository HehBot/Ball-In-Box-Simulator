#ifndef SCENE_HPP
#define SCENE_HPP

#include <simplecpp>
#include <Game.hpp>
#include <Var.hpp>

class Scene {
	Rectangle box;
	Circle box_top_left;
	Circle box_bottom_right;
	Circle ball;

  public:
	Scene(Game const& game, Var const& var);
    void advance(Game const& game, Var const& var, double wait_time);
};

#endif
