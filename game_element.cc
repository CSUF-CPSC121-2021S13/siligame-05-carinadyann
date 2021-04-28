#include "game_element.h"
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game.h"

void GameElement::SetX(int x) { x_ = x; }

void GameElement::SetY(int y) { y_ = y; }

int GameElement::GetX() const { return x_; }

int GameElement::GetY() const { return y_; }

int GameElement::GetWidth() const { return width_; }

int GameElement::GetHeight() const { return height_; }

void GameElement::SetIsActive(bool is_active) { is_active_ = is_active; }

bool GameElement::GetIsActive() const { return is_active_; }

bool GameElement::IntersectsWith(GameElement &game) {
  return !(x_ > game.GetX() + game.GetWidth() ||
           game.GetX() > GetX() + GetWidth() ||
           y_ > game.GetY() + game.GetHeight() ||
           game.GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image &image) {
  if (x_ < 0 || x_ + width_ > image.GetWidth() || y_ < 0 ||
      y_ + height_ > image.GetHeight()) {
    return true;
  }
  return false;
}
