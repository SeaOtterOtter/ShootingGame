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
		
		//Ŭ���� ����Լ��� ������ ��� target�� �̿��� �Լ� ������ ��� ������ �ϸ� nullptr ����
		//���� ����Լ�,���ٴ� ���⼭ ó��
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
		//�Ϲ� �����Լ��� ��� ���⼭ ó��
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