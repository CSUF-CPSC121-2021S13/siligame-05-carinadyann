#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"
#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : game_screen(800, 600) {}
  Game(int width, int height) : game_screen(width, height) {
    // game_screen.Initialize(width, height);
    // player->SetX(10);
    // player->SetY(10);
  }
  int GetScore() const;

  bool HasLost() const;

  Player &GetPlayer();

  std::vector<std::unique_ptr<Opponent>> &GetOpponents();

  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles();

  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles();

  void CreateOpponents();

  void CreateOpponentProjectiles();

  void CreatePlayerProjectiles();

  void Init();

  void UpdateScreen();

  graphics::Image &GetGameScreen();

  void AddMouseEventListener(graphics::MouseEventListener &listener);

  void AddAnimationEventListener(graphics::AnimationEventListener &listener);

  void MoveGameElements();

  void FilterIntersections();

  void OnAnimationStep() override;

  void OnMouseEvent(const graphics::MouseEvent &event) override;

  void Start();

  void LaunchProjectiles();

  void RemoveInactive();

 private:
  std::string scoreboard = "";
  int score = 0;
  std::vector<std::unique_ptr<PlayerProjectile>> p_projectiles;
  std::vector<std::unique_ptr<OpponentProjectile>> o_projectiles;
  std::vector<std::unique_ptr<Opponent>> opponents;
  graphics::Image game_screen;
  Player player;
  bool has_lost = false;
};

#endif
