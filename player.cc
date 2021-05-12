#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image &image) {
  // dog
  // body
  image.DrawRectangle(GetX() + 10, GetY() + 20, 30, 25,
                      graphics::Color(195, 115, 0));
  // ears
  image.DrawCircle(GetX() + 12, GetY() + 16, 5, graphics::Color(195, 115, 0));
  image.DrawCircle(GetX() + 38, GetY() + 16, 5, graphics::Color(195, 115, 0));
  image.DrawCircle(GetX() + 10, GetY() + 25, 5, graphics::Color(195, 115, 0));
  image.DrawCircle(GetX() + 40, GetY() + 25, 5, graphics::Color(195, 115, 0));
  // head
  image.DrawCircle(GetX() + 25, GetY() + 15, 15, graphics::Color(195, 135, 0));
  // face
  image.DrawLine(GetX() + 25, GetY() + 24, GetX() + 22, GetY() + 25,
                 graphics::Color(0, 0, 0), 1);
  image.DrawLine(GetX() + 25, GetY() + 24, GetX() + 28, GetY() + 25,
                 graphics::Color(0, 0, 0), 1);
  image.DrawPolygon({GetX() + 22, GetY() + 23, GetX() + 25, GetY() + 20,
                     GetX() + 28, GetY() + 23},
                    graphics::Color(0, 0, 0));
  image.DrawCircle(GetX() + 16, GetY() + 18, 4, graphics::Color(255, 255, 255));
  image.DrawCircle(GetX() + 34, GetY() + 18, 4, graphics::Color(255, 255, 255));
  image.DrawCircle(GetX() + 16, GetY() + 19, 3, graphics::Color(0, 0, 0));
  image.DrawCircle(GetX() + 34, GetY() + 19, 3, graphics::Color(0, 0, 0));
  // paws
  image.DrawCircle(GetX() + 15, GetY() + 32, 8, graphics::Color(205, 148, 0));
  image.DrawCircle(GetX() + 35, GetY() + 32, 8, graphics::Color(205, 148, 0));
  image.DrawRectangle(GetX() + 5, GetY() + 35, 40, 10,
                      graphics::Color(255, 255, 255));
}

void Player::Move(const graphics::Image &foreground) {}

void PlayerProjectile::Draw(graphics::Image &image2) {
  image2.DrawCircle(GetX() + 10, GetY() + 30, 8,
                    graphics::Color(200, 204, 205));
  image2.DrawCircle(GetX() + 10, GetY() + 15, 8,
                    graphics::Color(200, 204, 205));
  image2.DrawRectangle(GetX() + 10, GetY() + 13, 35, 20,
                       graphics::Color(200, 204, 205));
  image2.DrawCircle(GetX() + 40, GetY() + 30, 8,
                    graphics::Color(200, 204, 205));
  image2.DrawCircle(GetX() + 40, GetY() + 15, 8,
                    graphics::Color(200, 204, 205));
}

void PlayerProjectile::Move(const graphics::Image &foreground) {
  // checks if the object is out of bounds in the beginning
  if (IsOutOfBounds(foreground) == true) {
    // if it is out of bounds, set the is_active variable to false
    SetIsActive(false);
  } else {
    // if it's not out of bounds, increment the y (the enemy keeps moving up)
    x_ -= 1;
    y_ -= 1;
  }
}
