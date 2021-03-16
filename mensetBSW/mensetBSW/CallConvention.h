#pragma once

#define CALLCONVENTION_A _stdcall
#define CALLCONVENTION_B _declspec(dllexport)

class CallConvention
{
public:
	CallConvention();
	~CallConvention();
};

