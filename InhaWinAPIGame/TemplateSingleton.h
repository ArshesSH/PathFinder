#pragma once

#include <memory>

template<typename T>
class TemplateSingleton
{
public:
	static std::shared_ptr<T> GetInstance()
	{
		if ( instance == nullptr )
		{
			instance = std::make_shared<T>();
		}
		return instance;
	}

private:
	static std::shared_ptr<T> instance;
};