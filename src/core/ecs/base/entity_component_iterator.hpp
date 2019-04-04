#ifndef PLATCHAMER_CORE_ECS_BASE_ENTITYCOMPONENTITERATOR_HPP
#define PLATCHAMER_CORE_ECS_BASE_ENTITYCOMPONENTITERATOR_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace base
    {
        template<typename... Types>
		class EntityComponentIterator
		{
		public:
            EntityComponentIterator(Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy)
                : m_bIsEnd(bIsEnd), m_index(index), m_registry(registry), m_bIncludePendingDestroy(bIncludePendingDestroy)
            {
                if (m_index >= m_registry->getCount())
                    this->m_bIsEnd = true;
            }

			size_t getIndex() const
			{
				return m_index;
			}

			bool isEnd() const
            {
                return m_bIsEnd || m_index >= m_registry->getCount();
            }

			bool includePendingDestroy() const
			{
				return m_bIncludePendingDestroy;
			}

			Registry* getRegistry() const
			{
				return m_registry;
			}

			Entity* get() const
            {
                if (isEnd())
                    return nullptr;

                return m_registry->getByIndex(m_index);
            }

			Entity* operator*() const
			{
				return get();
			}

			bool operator==(const EntityComponentIterator<Types...>& other) const
			{
				if (m_registry != other.m_registry)
					return false;

				if (isEnd())
					return other.isEnd();

				return m_index == other.m_index;
			}

			bool operator!=(const EntityComponentIterator<Types...>& other) const
			{
				if (m_registry != other.m_registry)
					return true;

				if (isEnd())
					return !other.isEnd();

				return m_index != other.m_index;
			}

			EntityComponentIterator<Types...>& operator++()
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

			EntityComponentIterator<Types...>& operator+(size_t v)
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

		private:
			bool m_bIsEnd = false;
			size_t m_index;
			class ecs::Registry* m_registry;
			bool m_bIncludePendingDestroy;
        };
    }
}

#endif