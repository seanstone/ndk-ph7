#include <jni.h>
#include <string.h>

// jclass      javaClassRef;
// jmethodID   javaMethodRef;
//
// JavaVM *vm;
// JNIEnv *env;
// JavaVMInitArgs vm_args;
//
// jint JNI_OnLoad(JavaVM* aVm, void* aReserved)
// {
//      // cache java VM
//      vm = aVm;
//      if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
//         return -1;
// }
//
// void init()
// {
//     static bool initialized = false;
//     if (!initialized)
//     {
//         jclass dataClass    = env->FindClass("org/bitbucket/seanstone5923/ndkexample/JniConsole");
//         javaClassRef        = (jclass) env->NewGlobalRef(dataClass);
//         javaMethodRef       = env->GetMethodID(javaClassRef, "print", "(Ljava/lang/String;)V");
//         initialized = true;
//     }
// }
//
// void call()
// {
//     // Construct a String
//     jstring jstr = env->NewStringUTF("This string comes from JNI");
//
//     jobject javaObjectRef = env->NewObject(javaClassRef, javaMethodRef);
//     env->CallVoidMethod(javaObjectRef, javaMethodRef, jstr);
// }

jstring Java_com_github_seanstone_ndkexample_JniConsole_stringFromJNI (JNIEnv* env, jobject thiz)
{
    return (*env)->NewStringUTF(env, "Hello from JNI !");
}
