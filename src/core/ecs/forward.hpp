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
	ecs::TypeIndex ecs::core::TypeRegistry::nextIndex = 1; \
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

	namespace core
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

#define ECS_DECLARE_TYPE public: static ecs::core::TypeRegistry __ecs_type_reg
#define ECS_DEFINE_TYPE(name) ecs::core::TypeRegistry name::__ecs_type_reg

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


    namespace base 
    {
        struct BaseComponentContainer;
    }
}

#endif