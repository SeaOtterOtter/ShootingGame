#pragma once

#include <functional>
#include <vector>

template<typename TReturn , typename... TArgs>
class Delegate
{
public:
	using FunctionType = std::function<TReturn(TArgs...)>;

	Delegate() = default;
	Delegate(const Delegate& rhs) = delete;

	void operator() (const TArgs... args)
	{
		for (auto& func : m_handlers)
		{
			func(args...);
		}
	}

	void operator +=(const FunctionType& listener)
	{
		m_handlers.push_back(listener);
	}
	void operator-=(const FunctionType& listener)
	{
		TReturn(* const* func_ptr)(TArgs...) = listener.template target<TReturn(*)(TArgs...)>();
		size_t func_hash = listener.target_type().hash_code();
		
		//클래스 멤버함수나 람다의 경우 target을 이용해 함수 포인터 얻어 오려고 하면 nullptr 리턴
		//따라서 멤버함수,람다는 여기서 처리
		if (nullptr == func_ptr)
		{
			for (auto iter = m_handlers.begin(); iter != m_handlers.end(); iter++)
			{
				if (func_hash == iter->target_type().hash_code())
				{
					m_handlers.erase(iter);
					return;
				}
			}
		}
		//일반 전역함수의 경우 여기서 처리
		else
		{
			for (auto iter = m_handlers.begin(); iter != m_handlers.end(); iter++)
			{
				TReturn(* const* delegate_ptr)(TArgs...) = (*iter).template target<TReturn(*)(TArgs...)>();
				if (nullptr != delegate_ptr && *func_ptr == *delegate_ptr)
				{
					m_handlers.erase(iter);
					return;

				}

			}
		}

	}

private:
	std::vector<FunctionType> m_handlers;
};