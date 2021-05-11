#include "game.h"
#include "opponent.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "cpputils/graphics/image.h"
#include "player.h"

int Game::GetScore() const { return score; }

bool Game::HasLost() const { return has_lost; }

Player& Game::GetPlayer() { return player; }

std::vector<std::unique_ptr<Opponent>> &Game::GetOpponents() { return opponents; }

std::vector<std::unique_ptr<OpponentProjectile>> &Game::GetOpponentProjectiles() {
  return o_projectiles;
}

std::vector<std::unique_ptr<PlayerProjectile>> &Game::GetPlayerProjectiles() {
  return p_projectiles;
}

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>();
  // Opponent* opponent;
  int x = rand() % (game_screen.GetWidth() - opponent->GetWidth());
  int y = rand() % (game_screen.GetHeight() - opponent->GetHeight());
  opponent->SetX(x);
  opponent->SetY(y);
  opponents.push_back(std::move(opponent));
}

void Game::CreateOpponentProjectiles() {
  std::unique_ptr<OpponentProjectile> o_projectile = std::make_unique<OpponentProjectile>();
  // OpponentProjectile* o_projectile;
  int x = rand() % (game_screen.GetWidth() - o_projectile->GetWidth());
  int y = rand() % (game_screen.GetHeight() - o_projectile->GetHeight());
  o_projectile->SetX(x);
  o_projectile->SetY(y);
  o_projectiles.push_back(std::move(o_projectile));
}

void Game::CreatePlayerProjectiles() {
  std::unique_ptr<PlayerProjectile> p_projectile = std::make_unique<PlayerProjectile>();
  // PlayerProjectile* p_projectile;
  int x = rand() % (game_screen.GetWidth() - p_projectile->GetWidth());
  int y = rand() % (game_screen.GetHeight() - p_projectile->GetHeight());
  p_projectile->SetX(x);
  p_projectile->SetY(y);
  p_projectiles.push_back(std::move(p_projectile));
}

void Game::Init() {
  Player(10, 10);
  // CreateOpponents();
  // CreateOpponentProjectiles();
  // CreatePlayerProjectiles();
  game_screen.AddMouseEventListener(*this);
  game_screen.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  game_screen.DrawRectangle(0, 0, 800, 600, graphics::Color(255, 255, 255));
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive() == true) {
      opponents[i]->Draw(game_screen);
      std::string s_score = std::to_string(score);
      scoreboard = "Score: " + s_score;
      game_screen.DrawText(400, 300, scoreboard, 20, graphics::Color(255, 0, 0));
    }
  }

  for (int j = 0; j < o_projectiles.size(); j++) {
    if (o_projectiles[j]->GetIsActive() == true) {
      o_projectiles[j]->Draw(game_screen);
      std::string s_score = std::to_string(score);
      scoreboard = "Score: " + s_score;
      game_screen.DrawText(400, 300, scoreboard, 20, graphics::Color(255, 0, 0));
    }
  }

  for (int k = 0; k < p_projectiles.size(); k++) {
    if (p_projectiles[k]->GetIsActive() == true) {
      p_projectiles[k]->Draw(game_screen);
      std::string s_score = std::to_string(score);
      scoreboard = "Score: " + s_score;
      game_screen.DrawText(400, 300, scoreboard, 20, graphics::Color(255, 0, 0));
    }
  }

  if (player.GetIsActive() == true) {
    player.Draw(game_screen);
  } else {
    game_screen.DrawText(400, 300, "Game Over", 20, graphics::Color(255, 0, 0));
  }
}

graphics::Image &Game::GetGameScreen() { return game_screen; }

void Game::MoveGameElements() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive() == true) {
      opponents[i]->Move(game_screen);
    }
  }

  for (int i = 0; i < o_projectiles.size(); i++) {
    if (o_projectiles[i]->GetIsActive() == true) {
      o_projectiles[i]->Move(game_screen);
    }
  }

  for (int i = 0; i < p_projectiles.size(); i++) {
    if (p_projectiles[i]->GetIsActive() == true) {
      p_projectiles[i]->Move(game_screen);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->IntersectsWith(&player)) {
      opponents[i]->SetIsActive(false);
      player.SetIsActive(false);
      has_lost = true;
    }
  }

  for (int i = 0; i < p_projectiles.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (p_projectiles[i]->IntersectsWith(opponents[j].get())) {
        p_projectiles[i]->SetIsActive(false);
        opponents[j]->SetIsActive(false);
        score++;
      }
    }
  }

  for (int i = 0; i < o_projectiles.size(); i++) {
    if (o_projectiles[i]->IntersectsWith(&player)) {
      o_projectiles[i]->SetIsActive(false);
      player.SetIsActive(false);
      has_lost = true;
    }
  }
}

// void Game::AddMouseEventListener(graphics::MouseEventListener& listener) {}

// void Game::AddAnimationEventListener(graphics::AnimationEventListener&
// listener) {}

void Game::OnAnimationStep() {
  game_screen.DrawRectangle(0, 0, game_screen.GetWidth(), game_screen.GetHeight(), graphics::Color(255, 255, 255));
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetX() <= game_screen.GetWidth() && event.GetX() >= 0 &&
      event.GetY() <= game_screen.GetHeight() && event.GetY() >= 0) {
    player.SetX(event.GetX() - (player.GetWidth() / 2));
    player.SetY(event.GetY() - (player.GetHeight() / 2));
    if (event.GetMouseAction() == graphics::MouseAction::kPressed || event.GetMouseAction() == graphics::MouseAction::kDragged) {
      std::unique_ptr<PlayerProjectile> play_pro = std::make_unique<PlayerProjectile>();
      p_projectiles.push_back(std::move(play_pro));
    }
  }
}

void Game::Start() { game_screen.ShowUntilClosed(); }

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents.size(); i++) {
    std::unique_ptr<OpponentProjectile> result = opponents[i]->LaunchProjectile();
    if (result != nullptr) {
      o_projectiles.push_back(std::move(result));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = 0; i < opponents.size(); i++) {
    if (!opponents[i]->GetIsActive()) {
      opponents.erase(opponents.begin() + i);
    }
  }

  for (int i = 0; i < o_projectiles.size(); i++) {
    if (!o_projectiles[i]->GetIsActive()) {
      o_projectiles.erase(o_projectiles.begin() + i);
    }
  }

  for (int i = 0; i < p_projectiles.size(); i++) {
    if (!p_projectiles[i]->GetIsActive()) {
      p_projectiles.erase(p_projectiles.begin() + i);
    }
  }
}
