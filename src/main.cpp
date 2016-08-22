#include <jni.h>
#include <string.h>
#include <string>

#include "print.hpp"

JavaVM *jvm;
jobject gobj;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    jvm = vm;
    return JNI_VERSION_1_6;
}

void print(char* str)
{
    JNIEnv *env;
    jvm->GetEnv((void**)&env, JNI_VERSION_1_6);

    jstring     jstr        = env->NewStringUTF(str);
    jclass      clazz       = env->FindClass("com/github/seanstone/ndkexample/JniConsole");
    jmethodID   method      = env->GetMethodID(clazz, "print", "(Ljava/lang/String;)V");
    env->CallVoidMethod(gobj, method, jstr);
}

extern "C" void Java_com_github_seanstone_ndkexample_JniConsole_init (JNIEnv* env, jobject obj)
{
    gobj = obj;
    intro();
}
