#ifndef ISYSTEM_SHARDLITE
#define ISYSTEM_SHARDLITE

class ISystem
{
public:
	virtual int StartUp() = 0;
	virtual int ShutDown() = 0;

	const int SETUP_SUCCESS = 2;
};

#endif