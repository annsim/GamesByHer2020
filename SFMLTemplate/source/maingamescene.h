#pragma once 

#include "sfml-engine/scene.h"

class MainGameScene : public gbh::Scene
{
protected:
	void onInitializeScene() override;
	void onUpdate(double deltaTime);

private:
	std::shared_ptr<gbh::SpriteNode>m_playerShip;
	std::shared_ptr < gbh::SpriteNode> m_asteroid01;
};