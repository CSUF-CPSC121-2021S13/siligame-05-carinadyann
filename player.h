#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &image) override;

  void Move(const graphics::Image &foreground) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &image2) override;

  void Move(const graphics::Image &foreground) override;
};
#endif
