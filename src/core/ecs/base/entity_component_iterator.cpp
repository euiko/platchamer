#include "entity_component_iterator.hpp"
#include "../registry.hpp"

namespace ecs
{
    namespace base
    {
        template<typename... Types>
        EntityComponentIterator<Types...>::EntityComponentIterator(Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy)
            : m_bIsEnd(bIsEnd), m_index(index), m_registry(registry), m_bIncludePendingDestroy(bIncludePendingDestroy)
        {
            if (m_index >= m_registry->getCount())
                this->m_bIsEnd = true;
        }

        template<typename... Types>
        size_t EntityComponentIterator<Types...>::getIndex() const
        {
            return m_index;
        }

        template<typename... Types>
        bool EntityComponentIterator<Types...>::isEnd() const
        {
            return m_bIsEnd || m_index >= m_registry->getCount();
        }

        template<typename... Types>
        bool EntityComponentIterator<Types...>::includePendingDestroy() const
        {
            return m_bIncludePendingDestroy;
        }

        template<typename... Types>
        Registry* EntityComponentIterator<Types...>::getRegistry() const
        {
            return m_registry;
        }

        template<typename... Types>
        Entity* EntityComponentIterator<Types...>::get() const
        {
            if (isEnd())
                return nullptr;

            return m_registry->getByIndex(m_index);
        }

        template<typename... Types>
        Entity* EntityComponentIterator<Types...>::operator*() const
        {
            return get();
        }

        template<typename... Types>
        bool EntityComponentIterator<Types...>::operator==(const EntityComponentIterator<Types...>& other) const
        {
            if (m_registry != other.m_registry)
                return false;

            if (isEnd())
                return other.isEnd();

            return m_index == other.m_index;
        }

        template<typename... Types>
        bool EntityComponentIterator<Types...>::operator!=(const EntityComponentIterator<Types...>& other) const
        {
            if (m_registry != other.m_registry)
                return true;

            if (isEnd())
                return !other.isEnd();

            return m_index != other.m_index;
        }

        template<typename... Types>
        EntityComponentIterator<Types...>& EntityComponentIterator<Types...>::operator++()
        {
            ++m_index;
            while (m_index < m_registry->getCount() && (get() == nullptr || !get()->template has<Types...>() || (get()->isPendingDestroy() && !m_bIncludePendingDestroy)))
            {
                ++m_index;
            }

            if (m_index >= m_registry->getCount())
                m_bIsEnd = true;

            return *this;
        }

        template<typename... Types>
        EntityComponentIterator<Types...>& EntityComponentIterator<Types...>::operator+(size_t v)
        {
            m_index += v;
            while (m_index < m_registry->getCount() && (get() == nullptr || !get()->template has<Types...>() || (get()->isPendingDestroy() && !m_bIncludePendingDestroy)))
            {
                ++m_index;
            }

            if (m_index >= m_registry->getCount())
                m_bIsEnd = true;

            return *this;
        }
    } // base
} // ecs
