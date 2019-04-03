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
			EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last); // Inline

			const EntityComponentIterator<Types...>& begin() const
			{
				return m_firstItr;
			}

			EntityComponentIterator<Types...>& begin()
			{
				return m_firstItr;
			}

			const EntityComponentIterator<Types...>& end() const
			{
				return m_lastItr;
			}

			EntityComponentIterator<Types...>& end()
			{
				return m_lastItr;
			}

		private:
			EntityComponentIterator<Types...> m_firstItr;
			EntityComponentIterator<Types...> m_lastItr;
        };
    }
}

#endif