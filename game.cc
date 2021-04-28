#include "game.h"
#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"
#include "player.h"

Player &Game::GetPlayer() { return player; }

std::vector<Opponent> &Game::GetOpponents() { return opponents; }

std::vector<OpponentProjectile> &Game::GetOpponentProjectiles() {
  return o_projectiles;
}

std::vector<PlayerProjectile> &Game::GetPlayerProjectiles() {
  return p_projectiles;
}

void Game::CreateOpponents() {
  Opponent opponent;
  int x = rand() % (game_screen.GetWidth() - opponent.GetWidth());
  int y = rand() % (game_screen.GetHeight() - opponent.GetHeight());
  opponent.SetX(x);
  opponent.SetY(y);
  opponents.push_back(opponent);
}

void Game::CreateOpponentProjectiles() {
  OpponentProjectile o_projectile;
  int x = rand() % (game_screen.GetWidth() - o_projectile.GetWidth());
  int y = rand() % (game_screen.GetHeight() - o_projectile.GetHeight());
  o_projectile.SetX(x);
  o_projectile.SetY(y);
  o_projectiles.push_back(o_projectile);
}

void Game::CreatePlayerProjectiles() {
  PlayerProjectile p_projectile;
  int x = rand() % (game_screen.GetWidth() - p_projectile.GetWidth());
  int y = rand() % (game_screen.GetHeight() - p_projectile.GetHeight());
  p_projectile.SetX(x);
  p_projectile.SetY(y);
  p_projectiles.push_back(p_projectile);
}

void Game::Init() {
  Player player;
  CreateOpponents();
  CreateOpponentProjectiles();
  CreatePlayerProjectiles();
  game_screen.AddMouseEventListener(*this);
  game_screen.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  // game_screen.DrawRectangle(0, 0, 800, 600, graphics::Color(255, 255, 255));
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i].GetIsActive() == true) {
      opponents[i].Draw(game_screen);
    }
  }

  for (int j = 0; j < o_projectiles.size(); j++) {
    if (o_projectiles[j].GetIsActive() == true) {
      o_projectiles[j].Draw(game_screen);
    }
  }

  for (int k = 0; k < p_projectiles.size(); k++) {
    if (p_projectiles[k].GetIsActive() == true) {
      p_projectiles[k].Draw(game_screen);
    }
  }

  if (player.GetIsActive() == true) {
    player.Draw(game_screen);
  }
}

graphics::Image &Game::GetGameScreen() { return game_screen; }

void Game::MoveGameElements() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i].GetIsActive() == true) {
      opponents[i].Move(game_screen);
    }
  }

  for (int i = 0; i < o_projectiles.size(); i++) {
    if (o_projectiles[i].GetIsActive() == true) {
      o_projectiles[i].Move(game_screen);
    }
  }

  for (int i = 0; i < p_projectiles.size(); i++) {
    if (p_projectiles[i].GetIsActive() == true) {
      p_projectiles[i].Move(game_screen);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i].IntersectsWith(player)) {
      opponents[i].SetIsActive(false);
      player.SetIsActive(false);
    }
  }

  for (int i = 0; i < p_projectiles.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (p_projectiles[i].IntersectsWith(opponents[j])) {
        p_projectiles[i].SetIsActive(false);
        opponents[j].SetIsActive(false);
      }
    }
  }

  for (int i = 0; i < o_projectiles.size(); i++) {
    if (o_projectiles[i].IntersectsWith(player)) {
      o_projectiles[i].SetIsActive(false);
      player.SetIsActive(false);
    }
  }
}

// void Game::AddMouseEventListener(graphics::MouseEventListener& listener) {}

// void Game::AddAnimationEventListener(graphics::AnimationEventListener&
// listener) {}

void Game::OnAnimationStep() {
  game_screen.DrawRectangle(0, 0, game_screen.GetWidth(), game_screen.GetHeight(), graphics::Color(255, 255, 255));
  MoveGameElements();
  FilterIntersections();
  UpdateScreen();
  game_screen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetX() <= game_screen.GetWidth() && event.GetX() >= 0 &&
      event.GetY() <= game_screen.GetHeight() && event.GetY() >= 0) {
    player.SetX(event.GetX() - (player.GetWidth() / 2));
    player.SetY(event.GetY() - (player.GetHeight() / 2));
  }
}

void Game::Start() { game_screen.ShowUntilClosed(); }
