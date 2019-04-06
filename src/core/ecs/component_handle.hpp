#ifndef PLATCHAMER_CORE_ECS_COMPONENTHANDLE_HPP
#define PLATCHAMER_CORE_ECS_COMPONENTHANDLE_HPP

namespace ecs
{
    template<typename T>
	class ComponentHandle
	{
	public:
		ComponentHandle()
			: m_component(nullptr)
		{
		}

		ComponentHandle(T* component)
			: m_component(component)
		{
		}

		T* operator->() const
		{
			return m_component;
		}

		operator bool() const
		{
			return isValid();
		}

		T& get()
		{
			return *m_component;
		}

		bool isValid() const
		{
			return m_component != nullptr;
		}

	private:
		T* m_component;
    };
}

#endif