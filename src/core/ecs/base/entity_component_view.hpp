#ifndef PLATCHAMER_CORE_ECS_BASE_ENTITYCOMPONENTVIEW_HPP
#define PLATCHAMER_CORE_ECS_BASE_ENTITYCOMPONENTVIEW_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace base
    {
        template<typename... Types>
		class EntityComponentView
		{
		public:
			EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last);

			const EntityComponentIterator<Types...>& begin() const;

			EntityComponentIterator<Types...>& begin();

			const EntityComponentIterator<Types...>& end() const;

			EntityComponentIterator<Types...>& end();

		private:
			EntityComponentIterator<Types...> m_firstItr;
			EntityComponentIterator<Types...> m_lastItr;
        };
    }
}

#endif