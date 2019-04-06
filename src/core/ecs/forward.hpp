#ifndef PLATCHAMER_CORE_ECS_FORWARD_HPP
#define PLATCHAMER_CORE_ECS_FORWARD_HPP

#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <type_traits>

#ifndef ECS_TICK_TYPE
#define ECS_TICK_TYPE ecs::DefaultTickData
#endif

#ifndef ECS_ALLOCATOR_TYPE
#define ECS_ALLOCATOR_TYPE std::allocator<ecs::Entity>
#endif


#ifndef ECS_NO_RTTI

#include <typeindex>
#include <typeinfo>
#define ECS_TYPE_IMPLEMENTATION

#else
#warning "RTTI Disabled"
#define ECS_TYPE_IMPLEMENTATION  \
	ecs::TypeIndex ecs::base::TypeRegistry::nextIndex = 1; \
	ECS_DEFINE_TYPE(ecs::events::OnEntityCreated); \
	ECS_DEFINE_TYPE(ecs::events::OnEntityDestroyed); \

#endif

namespace ecs
{

    #ifndef ECS_NO_RTTI
	typedef std::type_index TypeIndex;

#define ECS_DECLARE_TYPE
#define ECS_DEFINE_TYPE(name)

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return std::type_index(typeid(T));
	}

#else
	typedef uint32_t TypeIndex;

	namespace base
	{
		class TypeRegistry
		{
		public:
			TypeRegistry()
			{
				index = nextIndex;
				++nextIndex;
			}

			TypeIndex getIndex() const
			{
				return index;
			}

		private:
			static TypeIndex nextIndex;
			TypeIndex index;
		};
	}

#define ECS_DECLARE_TYPE public: static ecs::base::TypeRegistry __ecs_type_reg
#define ECS_DEFINE_TYPE(name) ecs::base::TypeRegistry name::__ecs_type_reg

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return T::__ecs_type_reg.getIndex();
    }
#endif

    class Registry;
    class Entity;

    typedef float DefaultTickData;
    typedef ECS_ALLOCATOR_TYPE Allocator;

	template<typename T>
	class ComponentHandle;

    template<typename T>
    class EventSubscriber;

    class EntitySystem;

    namespace base 
    {
        struct BaseComponentContainer;

        template<typename... Types>
		class EntityComponentView;

        class EntityView;
		
		class BaseEventSubscriber;

		template<typename... Types>
		class EntityComponentIterator;

		template<typename... Types>
		class EntityComponentView;

		class EntityIterator;

        template<typename T>
		struct ComponentContainer;

    }

	namespace events
	{
		struct OnEntityCreated;
		struct OnEntityDestroyed;

		template<typename T>
		struct OnComponentAssigned;
		template<typename T>
		struct OnComponentRemoved;

	} // events
	
}

#endif