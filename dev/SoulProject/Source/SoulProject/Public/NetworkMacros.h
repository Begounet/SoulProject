#pragma once

#define DEFAULT_SERVER_VALIDATE_IMPL(functionNameWithParameters) \
	bool functionNameWithParameters \
	{ \
		return (true); \
	}
	