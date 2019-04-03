#ifndef PLATCHAMER_CORE_ECS_BASE_ENTITYVIEW_HPP
#define PLATCHAMER_CORE_ECS_BASE_ENTITYVIEW_HPP

#include "../forward.hpp"
#include "entity_iterator.hpp"

namespace ecs
{
    namespace base
    {
        class EntityView
		{
		public:
			EntityView(const EntityIterator& first, const EntityIterator& last)
				: m_firstItr(first), m_lastItr(last)
			{
				if (m_firstItr.get() == nullptr || (m_firstItr.get()->isPendingDestroy() && !m_firstItr.includePendingDestroy()))
				{
					++m_firstItr;
				}
			}

			const EntityIterator& begin() const
			{
				return m_firstItr;
			}

			const EntityIterator& end() const
			{
				return m_lastItr;
			}

		private:
			EntityIterator m_firstItr;
			EntityIterator m_lastItr;
		};
    } // base
} // ecs


#endif