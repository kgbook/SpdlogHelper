//
// Created by cory on 2023/11/11.
//

#ifndef SPDLOGHELPER_ALOGL_H
#define SPDLOGHELPER_ALOGL_H

#ifdef ENABLE_SPDLOG

#ifdef __cplusplus

extern "C" {

#endif

void __ComLog(int level, const char* tag, const char* func, int line, const char* fmt, ...);

#define   LOGV(TAG, FMT, ...)  __ComLog(0, TAG, __func__, __LINE__, FMT, ##__VA_ARGS__)
#define   LOGD(TAG, FMT, ...)  __ComLog(1, TAG, __func__, __LINE__, FMT, ##__VA_ARGS__)
#define   LOGI(TAG, FMT, ...)  __ComLog(2, TAG, __func__, __LINE__, FMT, ##__VA_ARGS__)
#define   LOGW(TAG, FMT, ...)  __ComLog(3, TAG, __func__, __LINE__, FMT, ##__VA_ARGS__)
#define   LOGE(TAG, FMT, ...)  __ComLog(4, TAG, __func__, __LINE__, FMT, ##__VA_ARGS__)

#define   ALOGV(FMT, ARGS...) LOGV(LOG_TAG, FMT, ##ARGS)
#define   ALOGD(FMT, ARGS...) LOGD(LOG_TAG, FMT, ##ARGS)
#define   ALOGI(FMT, ARGS...) LOGI(LOG_TAG, FMT, ##ARGS)
#define   ALOGW(FMT, ARGS...) LOGW(LOG_TAG, FMT, ##ARGS)
#define   ALOGE(FMT, ARGS...) LOGE(LOG_TAG, FMT, ##ARGS)

#ifdef __cplusplus
}
#endif

#else
#include <stdio.h>
#define   LOGV(TAG, FMT, ARGS...)   printf("[" TAG "]" FMT "\n", ##ARGS )
#define   LOGD(TAG, FMT, ARGS...)   printf("[" TAG "]" FMT "\n", ##ARGS )
#define   LOGI(TAG, FMT, ARGS...)   printf("[" TAG "]" FMT "\n", ##ARGS )
#define   LOGW(TAG, FMT, ARGS...)   printf("[" TAG "]" FMT "\n", ##ARGS )
#define   LOGE(TAG, FMT, ARGS...)   printf("[" TAG "]" FMT "\n", ##ARGS )
#endif // ENABLE_SPDLOG

#endif //SPDLOGHELPER_ALOGL_H