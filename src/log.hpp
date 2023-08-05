#include <emscripten.h>

class log {
	public:
		static void info(const char* text) {
			emscripten_log(EM_LOG_CONSOLE | EM_LOG_INFO, text);
		}
		static void error(const char* text) {
			emscripten_log(EM_LOG_CONSOLE | EM_LOG_ERROR, text);
		}
		static void warn(const char* text) {
			emscripten_log(EM_LOG_CONSOLE | EM_LOG_WARN, text);
		}
};