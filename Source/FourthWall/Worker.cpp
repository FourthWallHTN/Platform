#include "Worker.h"

//***********************************************************
//Thread Worker Starts as NULL, prior to being instanced
//		This line is essential! Compiler error without it
Worker* Worker::Runnable = NULL;
//***********************************************************

/*
Worker::Worker(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, ATestActor * IN_PC) : ThePC(IN_PC)
	, TotalPrimesToFind(IN_TotalPrimesToFind)
	, StopTaskCounter(0)
	, PrimesFoundCount(0)
{
	//Link to where data should be stored
	PrimeNumbers = &TheArray;

	Thread = FRunnableThread::Create(this, TEXT("FPrimeNumberWorker"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}*/

Worker::~Worker()
{
	delete Thread;
	Thread = NULL;
}

//Init
bool Worker::Init()
{
	//Init the Data 
	PrimeNumbers->Empty();
	PrimeNumbers->Add(2);
	PrimeNumbers->Add(3);
	return true;
}

//Run
uint32 Worker::Run()
{
	//Initial wait before starting
	FPlatformProcess::Sleep(0.03);

	//While not told to stop this thread 
	//		and not yet finished finding Prime Numbers
	while (StopTaskCounter.GetValue() == 0 && !IsFinished())
	{
		PrimeNumbers->Add(FindNextPrimeNumber());
		PrimesFoundCount++;

		UE_LOG(LogTemp, Warning, TEXT("test"));

		FPlatformProcess::Sleep(0.01);
	}

	//Run FPrimeNumberWorker::Shutdown() from the timer in Game Thread that is watching
	//to see when FPrimeNumberWorker::IsThreadFinished()

	return 0;
}

//stop
void Worker::Stop()
{
	StopTaskCounter.Increment();
}

/*
Worker* Worker::JoyInit(TArray<uint32>& TheArray, const int32 IN_TotalPrimesToFind, ATestActor * IN_PC)
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		UE_LOG(LogTemp, Warning, TEXT("creating worker"));
		Runnable = new Worker(TheArray, IN_TotalPrimesToFind, IN_PC);
	}
	return Runnable;
}*/

void Worker::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void Worker::Shutdown()
{
	if (Runnable)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;
	}
}

bool Worker::IsThreadFinished()
{
	if (Runnable) return Runnable->IsFinished();
	return true;
}
int32 Worker::FindNextPrimeNumber()
{
	//Last known prime number  + 1
	int32 TestPrime = PrimeNumbers->Last();

	bool NumIsPrime = false;
	while (!NumIsPrime)
	{
		NumIsPrime = true;

		//Try Next Number
		TestPrime++;

		//Modulus from 2 to current number - 1 
		for (int32 b = 2; b < TestPrime; b++)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//prevent thread from using too many resources
			//FPlatformProcess::Sleep(0.01);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			if (TestPrime % b == 0)
			{
				NumIsPrime = false;
				break;
				//~~~
			}
		}
	}

	//Success!
	return TestPrime;
}