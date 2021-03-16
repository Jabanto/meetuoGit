#pragma once

#define WORKING 0
#define FAILED 1
#define FREEZED 2

typedef enum Day {Monday, Tuesday, Wednesday,Thursday,Friday, Saturday, Sonday};

typedef enum LM_wait_reason_t {

	apWaitNormal,

	apWaitPhysDBerr = 1,
	apWaitMssLoopDetected = 2,
	
	apWaitUserAction = 10,
	apWaitLoadCrane = 12,

	apWaitPrepare = 20,
	apWitRouting = 30,
	apWaitGroupJump = 31,

	apWaitJam = 40,
	apWaitUserStop = 41,
	apWaitNextNdllSegFree = 43,
	apWaitJamToDest = 44,
	apWaitFillRate = 45,
	apWaitFreeInput = 46,
	apWaitConveyDir =47


} LM_wait_reason_t;

class lm_emun_test
{
public:
	lm_emun_test();
	~lm_emun_test();
};

