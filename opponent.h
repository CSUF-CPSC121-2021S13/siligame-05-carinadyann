#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#ifndef OPPONENT_H
#define OPPONENT_H

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image &image4) override;
  void Move(const graphics::Image &foreground) override;
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image &image3) override;
  void Move(const graphics::Image &foreground) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();
 private:
  int count = 0;
};

#endif
