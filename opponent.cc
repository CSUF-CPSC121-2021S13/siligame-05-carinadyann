#include "opponent.h"
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image &image3) {
  // cat
  // body
  image3.DrawRectangle(GetX() + 10, GetY() + 20, 30, 25,
                       graphics::Color(253, 182, 88));
  // ears
  image3.DrawPolygon({GetX() + 30, GetY() + 2, GetX() + 40, GetY() + 0,
                      GetX() + 40, GetY() + 10},
                     graphics::Color(253, 182, 88));
  image3.DrawPolygon({GetX() + 10, GetY() + 10, GetX() + 10, GetY() + 0,
                      GetX() + 20, GetY() + 2},
                     graphics::Color(253, 182, 88));
  // head
  image3.DrawCircle(GetX() + 25, GetY() + 15, 15,
                    graphics::Color(253, 170, 66));
  // face
  image3.DrawLine(GetX() + 25, GetY() + 24, GetX() + 22, GetY() + 25,
                  graphics::Color(0, 0, 0), 1);
  image3.DrawLine(GetX() + 25, GetY() + 24, GetX() + 28, GetY() + 25,
                  graphics::Color(0, 0, 0), 1);
  image3.DrawPolygon({GetX() + 22, GetY() + 23, GetX() + 25, GetY() + 20,
                      GetX() + 28, GetY() + 23},
                     graphics::Color(0, 0, 0));
  image3.DrawCircle(GetX() + 16, GetY() + 18, 4,
                    graphics::Color(255, 255, 255));
  image3.DrawCircle(GetX() + 34, GetY() + 18, 4,
                    graphics::Color(255, 255, 255));
  image3.DrawCircle(GetX() + 16, GetY() + 19, 3, graphics::Color(0, 0, 0));
  image3.DrawCircle(GetX() + 34, GetY() + 19, 3, graphics::Color(0, 0, 0));
  // paws
  image3.DrawCircle(GetX() + 15, GetY() + 32, 8, graphics::Color(253, 154, 66));
  image3.DrawCircle(GetX() + 35, GetY() + 32, 8, graphics::Color(253, 154, 66));
  image3.DrawRectangle(GetX() + 5, GetY() + 35, 40, 10,
                       graphics::Color(255, 255, 255));
}

void Opponent::Move(const graphics::Image &foreground) {
  // checks if the object is out of bounds in the beginning
  if (IsOutOfBounds(foreground) == true) {
    // if it is out of bounds, set the is_active variable to false
    SetIsActive(false);
  } else {
    // if it's not out of bounds, increment the y (the enemy keeps moving up)
    x_ += 1;
    y_ += 1;
  }
}

void OpponentProjectile::Draw(graphics::Image &image4) {
  // fish
  // body
  image4.DrawPolygon({GetX() + 34, GetY() + 36, GetX() + 15, GetY() + 25,
                      GetX() + 34, GetY() + 14},
                     graphics::Color(136, 199, 255));
  // tail
  image4.DrawPolygon({GetX() + 5, GetY() + 10, GetX() + 15, GetY() + 25,
                      GetX() + 20, GetY() + 23},
                     graphics::Color(183, 199, 255));
  image4.DrawPolygon({GetX() + 5, GetY() + 40, GetX() + 15, GetY() + 25,
                      GetX() + 20, GetY() + 27},
                     graphics::Color(183, 199, 255));
  // head
  image4.DrawCircle(GetX() + 35, GetY() + 25, 10,
                    graphics::Color(136, 199, 255));
  // eye
  image4.DrawCircle(GetX() + 40, GetY() + 25, 4,
                    graphics::Color(255, 255, 255));
  image4.DrawCircle(GetX() + 42, GetY() + 25, 2, graphics::Color(0, 0, 0));
}

void OpponentProjectile::Move(const graphics::Image &foreground) {
  // checks if the object is out of bounds in the beginning
  if (IsOutOfBounds(foreground) == true) {
    // if it is out of bounds, set the is_active variable to false
    SetIsActive(false);
  } else {
    // if it's not out of bounds, increment the y (the enemy keeps moving up)
    // x_ += 1;
    y_ += 1;
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (count == 20) {
    std::unique_ptr<OpponentProjectile> o_project =
    std::make_unique<OpponentProjectile>(Opponent::GetX(), Opponent::GetY());
    count = 0;
    return std::move(o_project);
  } else {
    count++;
    return nullptr;
  }
}
