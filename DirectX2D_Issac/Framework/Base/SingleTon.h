#pragma once
template  <typename T>
class SingleTon
{
protected:
	SingleTon() {};
public:
	virtual ~SingleTon() {};
public:
	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}
};