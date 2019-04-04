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
			EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last)
			: m_firstItr(first), m_lastItr(last)
            {
                if (m_firstItr.get() == nullptr || (m_firstItr.get()->isPendingDestroy() && !m_firstItr.includePendingDestroy())
                    || !m_firstItr.get()->template has<Types...>())
                {
                    ++m_firstItr;
                }
            }

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