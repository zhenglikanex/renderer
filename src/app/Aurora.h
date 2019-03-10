#ifndef AURORA_H_
#define AURORA_H_

#include <iostream>
#include <memory>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdint>

#ifndef AURORA_ASSERT
#include <assert.h>
#define AURORA_ASSERT(x) assert(x)
#endif

#include "LogManager.h"

#define CHECK_GL_ERROR_DEBUG() \
do {\
	GLenum __error = glGetError(); \
	if(__error) { \
		LOG_ERROR() << "OpenGL error " << std::hex << __error << std::dec <<  " in " <<  __FILE__ << " " <<  __FUNCTION__  << " " <<  __LINE__ << LOG_END(); \
	}\
}while(false);

#endif