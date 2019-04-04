#ifndef PLATCHAMER_SYSTEMS_CAMERA_HPP
#define PLATCHAMER_SYSTEMS_CAMERA_HPP

#include "../core/ecs/registry.hpp"

using namespace ecs;
class CameraSystem : public EntitySystem 
{
public:
    CameraSystem();

	virtual ~CameraSystem();

	virtual void configure(Registry* registry) override;

	virtual void unconfigure(Registry* registry) override;

	virtual void tick(Registry* registry, float deltaTime) override;
};

#endif