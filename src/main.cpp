#include <jni.h>
#include <string.h>
#include <string>

JavaVM *jvm;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    jvm = vm;
    return JNI_VERSION_1_6;
}

void print(jobject obj, char* str)
{
    JNIEnv *env;
    jvm->GetEnv((void**)&env, JNI_VERSION_1_6);

    jstring     jstr        = env->NewStringUTF(str);
    jclass      clazz       = env->FindClass("com/github/seanstone/ndkexample/JniConsole");
    jmethodID   method      = env->GetMethodID(clazz, "print", "(Ljava/lang/String;)V");
    env->CallVoidMethod(obj, method, jstr);
}

extern "C" void Java_com_github_seanstone_ndkexample_JniConsole_init (jobject obj, JNIEnv* env)
{
    char* str = "Hello!";
    print(obj, str);
}
