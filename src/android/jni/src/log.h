#include <android/log.h>

#define LOGV(...) \
    ((void)__android_log_print(ANDROID_LOG_VERBOSE, "Zipper::", __VA_ARGS__))

#define LOGD(...) \
    ((void)__android_log_print(ANDROID_LOG_DEBUG, "Zipper::", __VA_ARGS__))

#define LOGI(...) \
    ((void)__android_log_print(ANDROID_LOG_INFO, "Zipper::", __VA_ARGS__))

#define LOGW(...) \
    ((void)__android_log_print(ANDROID_LOG_WARN, "Zipper::", __VA_ARGS__))

#define LOGE(...) \
    ((void)__android_log_print(ANDROID_LOG_ERROR, "Zipper::", __VA_ARGS__))
