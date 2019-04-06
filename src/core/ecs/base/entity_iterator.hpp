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
			EntityIterator(class Registry* registry, size_t index, bool bIsEnd, bool bIncludePendingDestroy);

			size_t getIndex() const;

			bool isEnd() const;

			bool includePendingDestroy() const;

			Registry* getRegistry() const;

			Entity* get() const;

			Entity* operator*() const;

			bool operator==(const EntityIterator& other) const;

			bool operator!=(const EntityIterator& other) const;

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