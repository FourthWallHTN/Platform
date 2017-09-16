// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "TestActor.h"

/**
 * 
 */
class FOURTHWALL_API Worker : public FRunnable
{
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  Worker* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** The Data Ptr */
	TArray<uint32>* PrimeNumbers;
	ATestActor* ThePC;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	//The actual finding of prime numbers
	int32 FindNextPrimeNumber();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

private:
	int32 PrimesFoundCount;
public:
	void EnsureCompletion();
	static Worker* JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, ATestActor* IN_PC);


	int32 TotalPrimesToFind;
	Worker(TArray<uint32>& TheArray, const int32 IN_PrimesToFindPerTick, ATestActor * IN_PC);
	~Worker();

	bool IsFinished() const
	{
		return PrimesFoundCount >= TotalPrimesToFind;
	}

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();
	static bool IsThreadFinished();
};