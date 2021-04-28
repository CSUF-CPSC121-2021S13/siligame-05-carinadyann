#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"
#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(int width, int height) {
    game_screen.Initialize(width, height);
    player->SetX(10);
    player->SetY(10);
  }
  Player* GetPlayer();

  std::vector<Opponent*> &GetOpponents();

  std::vector<OpponentProjectile*> &GetOpponentProjectiles();

  std::vector<PlayerProjectile*> &GetPlayerProjectiles();

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

 private:
  std::vector<PlayerProjectile*> p_projectiles;
  std::vector<OpponentProjectile*> o_projectiles;
  std::vector<Opponent*> opponents;
  graphics::Image game_screen;
  Player* player;
};

#endif
