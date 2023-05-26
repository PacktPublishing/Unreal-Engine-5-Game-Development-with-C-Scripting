// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"




template<class T>
class UActorPool
{
protected:

	TQueue<T*> _ActorPool;
public:
	UActorPool()
	{

	}
	~UActorPool()
	{

	}

	void Initialize(int poolSize)
	{
		
	}

	T* GetActor()
	{

	}

	void ReturnActor(T* actor)
	{
		return nullptr;
	}
};
