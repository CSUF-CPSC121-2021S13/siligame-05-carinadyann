#include <iostream>
#include <string>
#include "cpputils/graphics/image.h"
#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  GameElement(int x, int y, int height, int width)
      : x_(x), y_(y), height_(height), width_(width) {}

  GameElement() {
    x_ = 0;
    y_ = 0;
    height_ = 50;
    width_ = 50;
  }

  void SetX(int x);

  void SetY(int y);

  int GetX() const;

  int GetY() const;

  int GetWidth() const;

  int GetHeight() const;

  virtual void Draw(graphics::Image &picture) = 0;

  void SetIsActive(bool is_active);

  bool GetIsActive() const;

  virtual void Move(const graphics::Image &foreground) = 0;

  bool IntersectsWith(GameElement* game);

  bool IsOutOfBounds(const graphics::Image &image);

 protected:
  bool is_active_ = true;
  int x_, y_, width_, height_;
};

#endif
