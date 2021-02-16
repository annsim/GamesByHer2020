#pragma once 

#include "sfml-engine/scene.h"
#include "sfml-engine/cameranode.h"

class followCameraNode : public gbh::CameraNode
{
public:
	
	void setTarget(std::shared_ptr<gbh::Node>target);

protected: void onUpdate(double deltaTime) override;

private:

	std::shared_ptr<gbh::Node>m_target;

};

