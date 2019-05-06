#ifndef PLATCHAMER_SYSTEMS_CAMERA_HPP
#define PLATCHAMER_SYSTEMS_CAMERA_HPP

#include "../libs/entcosy/src/entcosy/registry.hpp"

class CameraSystem : public entcosy::System
{
public:
    CameraSystem();

	virtual ~CameraSystem();

	virtual void configure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void unconfigure(std::shared_ptr<entcosy::Registry> registry) override;

	virtual void update(std::shared_ptr<entcosy::Registry> registry, float deltaTime) override;
};

#endif
