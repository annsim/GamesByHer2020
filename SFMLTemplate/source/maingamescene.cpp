#include "maingamescene.h"
#include "sfml-engine/mathutils.h"

#include <iostream>

const std::string kStarField = "../assets/gfx/starfield-01.png";
const std::string kPlayerShip = "../assets/gfx/player-ship.png";
const std::string kCheckPointSprite = "../assets/gfx/checkpoint.png";

void MainGameScene::onInitializeScene()
{
	//add physics debug
	setDrawPhysicsDebug(true);

	//add background first
	createPhysicsWorld(sf::Vector2f(0.0f, 0.0f));
	std::shared_ptr<gbh::SpriteNode>background = std::make_shared<gbh::SpriteNode>(kStarField);
	background->setName("background");
	addChild(background);

	// Add a boundary that is almost as big as the screen (1270, 710) and centered.
	std::shared_ptr<gbh::Node> boundary = std::make_shared<gbh::Node>();
	boundary->setPhysicsBody(getPhysicsWorld()->createEdgeBox(sf::Vector2f(1270, 710)));
	boundary->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	boundary->setPosition(1280.0f / 2.0f, 720.0f / 2.0f);
	addChild(boundary);


	//add player spaceship
	const sf::Vector2f shipSize = sf::Vector2f(80.0f, 120.0f);
	m_playerShip = std::make_shared<gbh::SpriteNode>(kPlayerShip);
	m_playerShip->setPosition(640, 360);
	m_playerShip->setScale(0.5f, 0.5f);
	m_playerShip->setPhysicsBody(getPhysicsWorld()->createBox(shipSize * 0.5f));
	m_playerShip->getPhysicsBody()->setLinearDamping(2.0f);
	m_playerShip->getPhysicsBody()->setFixedRotation(true);
	addChild(m_playerShip);

	//add camera 
	m_followCamera = std::make_shared<followCameraNode>();
	m_followCamera->setTarget(m_playerShip);
	m_followCamera->setPosition(640, 360);
	addChild(m_followCamera);
	setCamera(m_followCamera);

	//add checkpoints
	std::vector<sf::Vector2f> checkPointPositions = {
		sf::Vector2f(640.0f, 720.0f),
		sf::Vector2f(1240.0f, 200.0f),
		sf::Vector2f(80.0f, 400.0f),
	};

	for (int i = 0; i < checkPointPositions.size(); ++i) {
		sf::Vector2f position = checkPointPositions[i];

		std::shared_ptr<gbh::SpriteNode> node = std::make_shared<gbh::SpriteNode>(kCheckPointSprite);
		node->setColor(kInactiveCheckpoint);
		node->setPhysicsBody(getPhysicsWorld()->createCircle(50));
		node->getPhysicsBody()->makeSensor();
		node->getPhysicsBody()->setEnabled(false);
		node->setPosition(checkpoints[i]);
		node->setName("checkpoint");

		m_checkPoints.push_back(node);
		addChild(node);

	}
	//add asteroids
	//const sf::Vector2f asteroidRadius = sf::Vector2f(40.0f, 60.0f);
	m_asteroid01 = std::make_shared<gbh::SpriteNode>("../assets/gfx/asteroid-small-01.png");
	m_asteroid01->setPosition(800, 400);
	m_asteroid01->setScale(0.5f, 0.5f);
	m_asteroid01->setOrigin(0.5f, 0.5f);
	m_asteroid01->setPhysicsBody(getPhysicsWorld()->createCircle(10.0f));
	m_asteroid01->getPhysicsBody()->setLinearDamping(20.0f);
	m_asteroid01->getPhysicsBody()->setFixedRotation(true);
	addChild(m_asteroid01);

	//add debugg rectagnle
	sf::RectangleShape rectangle{ sf::Vector2f(50, 50) };

	std::shared_ptr<gbh::ShapeNode> shapeNode = std::make_shared<gbh::ShapeNode>(rectangle);
	shapeNode->setPosition(100, 100);
	shapeNode->getShape()->setFillColor(sf::Color(0, 255, 0, 64));
	shapeNode->setName("Rectangle");
	addChild(shapeNode);
}

void MainGameScene::onUpdate(double deltaTime)
{
	static const float acceleration = 2000.0f;

	sf::Vector2f moveDirection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveDirection.y -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveDirection.y += 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveDirection.x -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveDirection.x += 1.0f;
	}

	moveDirection = gbh::math::normalize(moveDirection);
	m_playerShip->getPhysicsBody()->applyForceToCenter(moveDirection * acceleration);
}



