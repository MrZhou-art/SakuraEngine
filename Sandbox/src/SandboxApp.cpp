#include <Sakura.h>

class Sandbox : public Sakura::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Sakura::Application * Sakura::createApplication()
{
	return new Sandbox();
}