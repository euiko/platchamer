#include "registers.hpp"

#include "../events/reset_player_state_event.hpp"
#include "../events/collide_event.hpp"
#include "../events/keyboard_event.hpp"
#include "../components/position_component.hpp"
#include "../components/camera_component.hpp"
#include "../components/polygon_component.hpp"
#include "../components/circle_component.hpp"
#include "../components/polygon_collider_component.hpp"
#include "../components/circle_collider_component.hpp"
#include "../components/rigid_body_component.hpp"
#include "../components/ui/game_ui_component.hpp"
#include "../components/ui/menu_ui_component.hpp"
#include "../tags/camera_tag.hpp"
#include "../tags/ground_tag.hpp"
#include "../tags/player_tag.hpp"
#include "../tags/enemy_tag.hpp"
#include "../tags/bullet_tag.hpp"
#include "../tags/thorn_tag.hpp"

ENTCOSY_INITIALIZATION;

RTTR_REGISTRATION {

    ENTCOSY_BEGIN_DEFINE;

    rttr::registration::class_<entcosy::core::BaseComponentContainer>("entcosy::core::BaseComponentContainer")
        .constructor<>() ( rttr::policy::ctor::as_std_shared_ptr );

    rttr::registration::class_<entcosy::Registry>("entcosy::Registry")
        .constructor<>() ( rttr::policy::ctor::as_std_shared_ptr );
        // .property_readonly("m_activeUiName", &entcosy::Registry::m_activeUiName, rttr::registration::private_access)

    ENTCOSY_DEFINE_TYPE(CameraComponent);
    ENTCOSY_DEFINE_TYPE(PolygonComponent);
    ENTCOSY_DEFINE_TYPE(CircleComponent);
    ENTCOSY_DEFINE_TYPE(CircleColliderComponent);
    ENTCOSY_DEFINE_TYPE(PositionComponent);
    ENTCOSY_DEFINE_TYPE(PolygonColliderComponent);
    ENTCOSY_DEFINE_TYPE(RigidBodyComponent);

    ENTCOSY_DEFINE_TYPE(CameraTag);
    ENTCOSY_DEFINE_TYPE(PlayerTag);
    ENTCOSY_DEFINE_TYPE(EnemyTag);
    ENTCOSY_DEFINE_TYPE(GroundTag);
    ENTCOSY_DEFINE_TYPE(BulletTag);
    ENTCOSY_DEFINE_TYPE(ThornTag);

    ENTCOSY_DEFINE_TYPE(GameUiComponent);
    ENTCOSY_DEFINE_TYPE(MenuUiComponent);


    rttr::registration::class_<Vect2>("Vect2")
        .constructor<>() ( rttr::policy::ctor::as_raw_ptr )
        .constructor<>() ( rttr::policy::ctor::as_object )
        .constructor<float, float>()
        .property("x", &Vect2::x) ( rttr::policy::prop::as_reference_wrapper )
        .property("y", &Vect2::y) ( rttr::policy::prop::as_reference_wrapper );

    rttr::registration::class_<MenuUiComponent>("MenuUiComponent")
        .constructor<>() ( rttr::policy::ctor::as_raw_ptr )
        .constructor<>() ( rttr::policy::ctor::as_object )
        .property("health", &MenuUiComponent::health)
        .property("color", &MenuUiComponent::color)
        .property("is_tool_active", &MenuUiComponent::is_tool_active);

    rttr::registration::class_<PositionComponent>("PositionComponent")
        .constructor<>() ( rttr::policy::ctor::as_raw_ptr )
        .constructor<>() ( rttr::policy::ctor::as_object )
        .constructor<float, float, float>() ( rttr::policy::ctor::as_object )
        .property("pos", &PositionComponent::pos)
        .property("rotation", &PositionComponent::rotation);

    rttr::registration::class_<RigidBodyComponent>("RigidBodyComponent")
        .constructor<>()
        .constructor<bool>() ( rttr::default_arguments(false) )
        .constructor<float, float, float, bool>() ( rttr::default_arguments(false) )
        .property("density", &RigidBodyComponent::density)
        .property("static_friction", &RigidBodyComponent::static_friction)
        .property("dynamic_friction", &RigidBodyComponent::dynamic_friction)
        .property("restitution", &RigidBodyComponent::restitution)
        .property("is_static", &RigidBodyComponent::is_static);

    // ENTCOSY_REGISTER_TYPE(KeyboardEvent);
    // ENTCOSY_REGISTER_TYPE(CollideEvent);
    // ENTCOSY_REGISTER_TYPE(ResetPlayerStateEvent);
} // END RTTR_REGISTRATION

ENTCOSY_SERIALIZATION_REGISTER(CameraComponent);
ENTCOSY_SERIALIZATION_REGISTER(PolygonComponent);
ENTCOSY_SERIALIZATION_REGISTER(CircleComponent);
ENTCOSY_SERIALIZATION_REGISTER(CircleColliderComponent);
ENTCOSY_SERIALIZATION_REGISTER(PositionComponent);
ENTCOSY_SERIALIZATION_REGISTER(PolygonColliderComponent);
ENTCOSY_SERIALIZATION_REGISTER(RigidBodyComponent);


ENTCOSY_SERIALIZATION_REGISTER(CameraTag);
ENTCOSY_SERIALIZATION_REGISTER(PlayerTag);
ENTCOSY_SERIALIZATION_REGISTER(EnemyTag);
ENTCOSY_SERIALIZATION_REGISTER(GroundTag);
ENTCOSY_SERIALIZATION_REGISTER(BulletTag);
ENTCOSY_SERIALIZATION_REGISTER(ThornTag);

ENTCOSY_SERIALIZATION_REGISTER(GameUiComponent);
ENTCOSY_SERIALIZATION_REGISTER(MenuUiComponent);
