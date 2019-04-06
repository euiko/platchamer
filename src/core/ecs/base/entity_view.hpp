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
			EntityView(const EntityIterator& first, const EntityIterator& last);

			const EntityIterator& begin() const;

			const EntityIterator& end() const;

		private:
			EntityIterator m_firstItr;
			EntityIterator m_lastItr;
		};
    } // base
} // ecs


#endif