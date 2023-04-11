#pragma once
#include "Window.h"
enum CreateWindowErrorCode {
	CannotLoadGL,
	CannotCreateWindow
};
using CreateWindowError = MHTL::error<CreateWindowErrorCode>;
using CreateWindowResult = MHTL::result<std::shared_ptr<Window>, CreateWindowError>;


class DisplaySystem {
private:
public:
	CreateWindowResult CreateWindow(std::string i_title,int i_width, int i_height);
};