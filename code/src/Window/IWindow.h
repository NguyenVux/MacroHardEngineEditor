#pragma once
#include "signal.h"


class IWinwdow {
protected:
	struct AccessKey;
public:
	MHTL::public_signal_t<void(), AccessKey> sig_onKeyEvent;
};