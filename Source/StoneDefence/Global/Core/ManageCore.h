// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//当前模板只适合在有World 对象的身上 
template<class T>
struct FManagementCore
{
	FManagementCore()
		:Management(nullptr)
	{}

	T *Get(UWorld *InWorld);
	void Destory();
private:
	T *Management;
};

template<class T>
void FManagementCore<T>::Destory()
{
	if (Management)
	{
		Management->Destructural();
		delete Management;
	}

	Management = nullptr;
}

template<class T>
T * FManagementCore<T>::Get(UWorld *InWorld)
{
	if (InWorld)
	{
		if (!Management)
		{
			Management = new T();
			Management->Constructor(InWorld);
		}

		return Management;
	}
	
	return nullptr;
}
