#ifndef GENERICTOPDOWN_H
#define GENERICTOPDOWN_H

#include "Scenes/TopDown.h"

class GenericTopDown : public TopDown
{
public:
	void UpdateScene(const double elapsedTime) override;
	void RenderScene(const double elapsedTime) override;
	void LoadScene(std::string level) override;
	void UnloadScene() override;
	using TopDown::TopDown;
};

#endif