#include <string.h>
#include <jni.h>
#include <unistd.h>

#include "zipper.h"
#include "log.h"

extern "C" JNIEXPORT jint JNICALL
Java_com_plugin_zipper_ZipperJni_compress(JNIEnv* env,
                                            jobject thiz,
                                            jint overwrite,
                                            jint exclude,
                                            jstring zipfile,
                                            jstring file
                                            ) {
    const char *zipfilePath = env->GetStringUTFChars(zipfile, 0);
    const char *filePath = env->GetStringUTFChars(file, 0);     
    int res = compress(overwrite, exclude, std::string(filePath), std::string(zipfilePath));
    env->ReleaseStringUTFChars(file, filePath);
    env->ReleaseStringUTFChars(zipfile, zipfilePath);
    return res;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_plugin_zipper_ZipperJni_uncompress(JNIEnv* env,
                                            jobject thiz,
                                            jint overwrite,
                                            jstring zipfile,
                                            jstring targetpath
                                            ) {
    const char *zipfileStr = env->GetStringUTFChars(zipfile, 0);
    const char *targetpathStr = env->GetStringUTFChars(targetpath, 0);
   
    int res = uncompress(overwrite, zipfileStr, targetpathStr);

    env->ReleaseStringUTFChars(zipfile, zipfileStr);
    env->ReleaseStringUTFChars(zipfile, targetpathStr);

    return res;
}