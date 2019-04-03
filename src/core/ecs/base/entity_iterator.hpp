#ifndef PLATCHAMER_CORE_ECS_BASE_ENTITYITERATOR_HPP
#define PLATCHAMER_CORE_ECS_BASE_ENTITYITERATOR_HPP

#include "../forward.hpp"

namespace ecs
{
    namespace base
    {
        class EntityIterator
		{
		public:
			EntityIterator(Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy); //Inline

			size_t getIndex() const
			{
				return m_index;
			}

			bool isEnd() const; // Inline

			bool includePendingDestroy() const
			{
				return m_bIncludePendingDestroy;
			}

			Registry* getRegistry() const
			{
				return m_registry;
			}

			Entity* get() const;

			Entity* operator*() const
			{
				return get();
			}

			bool operator==(const EntityIterator& other) const
			{
				if (m_registry != other.m_registry)
					return false;

				if (isEnd())
					return other.isEnd();

				return m_index == other.m_index;
			}

			bool operator!=(const EntityIterator& other) const
			{
				if (m_registry != other.m_registry)
					return true;

				if (isEnd())
					return !other.isEnd();

				return m_index != other.m_index;
			}

			EntityIterator& operator++();

		private:
			bool m_bIsEnd = false;
			size_t m_index;
			class ecs::Registry* m_registry;
			bool m_bIncludePendingDestroy;
		};
    } // base
} // ecs


#endif