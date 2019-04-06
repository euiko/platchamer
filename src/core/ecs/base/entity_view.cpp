#include "entity_view.hpp"
#include "../entity.hpp"

namespace ecs
{
    namespace base
    {
    
        EntityView::EntityView(const EntityIterator& first, const EntityIterator& last)
            : m_firstItr(first), m_lastItr(last)
        {
            if (m_firstItr.get() == nullptr || (m_firstItr.get()->isPendingDestroy() && !m_firstItr.includePendingDestroy()))
            {
                ++m_firstItr;
            }
        }

        const EntityIterator& EntityView::begin() const
        {
            return m_firstItr;
        }

        const EntityIterator& EntityView::end() const
        {
            return m_lastItr;
        }
    } // base
} // ecs
