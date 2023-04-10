#include <memory>
#include "Application.h"
#include <iostream>


Application::Application()
{
	//onUpdateConnection = i_system.lock()->GetSystemLifeCycle()->sig_onUpdate.connect<&Application::Update>(this);
	//auto createDisplayResult = i_system.lock()->GetDisplaySystem()->CreateDisplay(IDisplaySystem::GraphicAPI::OPENGL);
	//if (createDisplayResult == MHTL::success)
	//{
	//	display = createDisplayResult.extract_payload();
	//	auto initDisplayResult =  display->Init("OpenGL32", 800, 600);
	//	if (initDisplayResult != MHTL::success)
	//	{
	//		display.reset();
	//		std::cout << "Error Init display: " << initDisplayResult.error().what() << std::endl;
	//		return;
	//	}
	//	display->Show();
	//}
}
void Application::Update(float i_delta) {
	//MHTL::access<AccessKey>(sig_onApplicationUpdate).emit(i_delta);
	//display->Present();
}

Application::~Application() {
	std::cout << "Application Destroyed" << std::endl;
}