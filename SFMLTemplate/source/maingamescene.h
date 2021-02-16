#pragma once 

#include "sfml-engine/scene.h"
#include "followcameranode.h"

class MainGameScene : public gbh::Scene
{
protected:
	void onInitializeScene() override;
	void onUpdate(double deltaTime);

private:
	std::shared_ptr<gbh::SpriteNode>m_playerShip;
	std::shared_ptr<gbh::SpriteNode> m_asteroid01;
	std::shared_ptr<followCameraNode> m_followCamera;
	std::vector<std::shared_ptr<gbh::SpriteNode>> m_checkPoints;
	int m_currentCheckPoint = -1;
};