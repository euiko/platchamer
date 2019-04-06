#include "entity_iterator.hpp"
#include "../registry.hpp"
#include "../entity.hpp"

namespace ecs
{
    namespace base
    {

        EntityIterator::EntityIterator(class Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy)
            : m_bIsEnd(bIsEnd), m_index(index), m_registry(registry), m_bIncludePendingDestroy(bIncludePendingDestroy)
        {
            if (index >= m_registry->getCount())
                this->m_bIsEnd = true;
        } //Inline

        size_t EntityIterator::getIndex() const
        {
            return m_index;
        }

        bool EntityIterator::isEnd() const
        {
            return m_bIsEnd || m_index >= m_registry->getCount();
        } // Inline

        bool EntityIterator::includePendingDestroy() const
        {
            return m_bIncludePendingDestroy;
        }

        Registry* EntityIterator::getRegistry() const
        {
            return m_registry;
        }

        Entity* EntityIterator::get() const
        {
            if (isEnd())
                return nullptr;

            return m_registry->getByIndex(m_index);
        }

        Entity* EntityIterator::operator*() const
        {
            return get();
        }

        bool EntityIterator::operator==(const EntityIterator& other) const
        {
            if (m_registry != other.m_registry)
                return false;

            if (isEnd())
                return other.isEnd();

            return m_index == other.m_index;
        }

        bool EntityIterator::operator!=(const EntityIterator& other) const
        {
            if (m_registry != other.m_registry)
                return true;

            if (isEnd())
                return !other.isEnd();

            return m_index != other.m_index;
        }

        EntityIterator& EntityIterator::operator++()
        {
            ++m_index;
            while (m_index < m_registry->getCount() && (get() == nullptr || (get()->isPendingDestroy() && !m_bIncludePendingDestroy)))
            {
                ++m_index;
            }

            if (m_index >= m_registry->getCount())
                m_bIsEnd = true;

            return *this;
        }
    } // base
} // ecs
