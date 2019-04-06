#include "entity_component_view.hpp"
#include "entity_component_iterator.hpp"

namespace ecs
{
    namespace base
    {

        template<typename... Types>
        EntityComponentView<Types...>::EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last)
            : m_firstItr(first), m_lastItr(last)
        {
            if (m_firstItr.get() == nullptr || (m_firstItr.get()->isPendingDestroy() && !m_firstItr.includePendingDestroy())
                || !m_firstItr.get()->template has<Types...>())
            {
                ++m_firstItr;
            }
        }

        template<typename... Types>
        const EntityComponentIterator<Types...>& EntityComponentView<Types...>::begin() const
        {
            return m_firstItr;
        }

        template<typename... Types>
        EntityComponentIterator<Types...>& EntityComponentView<Types...>::begin()
        {
            return m_firstItr;
        }

        template<typename... Types>
        const EntityComponentIterator<Types...>& EntityComponentView<Types...>::end() const
        {
            return m_lastItr;
        }

        template<typename... Types>
        EntityComponentIterator<Types...>& EntityComponentView<Types...>::end()
        {
            return m_lastItr;
        }

    } // base
} // ecs
