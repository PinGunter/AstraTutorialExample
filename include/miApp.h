#pragma once
#include <AppRT.h>

class MyApp : public Astra::AppRT {
	void createPipelines() override;
public:
	void run() override;
};