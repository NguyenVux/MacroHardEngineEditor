#pragma once
#include "result.h"

enum ApplicationInitErrorCode {
	CannotInitGLFW,
	CannotLoadGLFunc
};
using ApplicationInitError = MHTL::error<ApplicationInitErrorCode>;
using ApplicationInitResult = MHTL::result<void,ApplicationInitError>;

class GLFWApplication {
protected:
	struct AccessKey;
private:
	//fteng::connection onUpdateConnection;
	//MHTL::public_signal_t<void(float i_delta), AccessKey> sig_onApplicationUpdate;
	//std::unique_ptr<IDisplay> display;
public:
	GLFWApplication();
	ApplicationInitResult init();
	~GLFWApplication();
};
