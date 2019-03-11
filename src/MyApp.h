#ifndef MYAPP_H_
#define MYAPP_H_

#include "Aurora.h"

using namespace aurora;

class MyApp : public App3D
{
public:
	~MyApp();
private:
	bool OnCreate() override;
	void OnDestory() override;
	void OnUpdate() override;
};

#endif
