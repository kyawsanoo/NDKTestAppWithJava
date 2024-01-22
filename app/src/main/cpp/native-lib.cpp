#include <jni.h>
#include <string>
#include <android/log.h>

// Android log function wrappers
static const char *kTAG = "native-lib";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

extern "C" JNIEXPORT jstring JNICALL
Java_kso_android_ndktestapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndktestapp_MainActivity_add(JNIEnv *env, jobject thiz, jint a, jint b) {
    jint sum = a + b;
    LOGI("add() sum - %d", sum);
    LOGW("add() sum - %d", sum);
    LOGE("add() sum - %d", sum);
    return sum;
}
extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndktestapp_MainActivity_getStrLen(JNIEnv *env, jobject thiz, jstring s_) {
    const char *s = env->GetStringUTFChars(s_, 0);

    jint len=strlen(s);

    env->ReleaseStringUTFChars(s_, s);
    return len;

}
extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndktestapp_MainActivity_addArray(JNIEnv *env, jobject thiz, jintArray jarr) {
    jint *arr = env->GetIntArrayElements(jarr, NULL);
    int res=0;
    int size = env->GetArrayLength(jarr);
    for(int i=0;i<size;i++)
        res+=arr[i];

    env->ReleaseIntArrayElements(jarr, arr, 0);
    return res;

}

jintArray gl_arr;
extern "C"
JNIEXPORT void JNICALL
Java_kso_android_ndktestapp_MainActivity_saveArray(JNIEnv *env, jobject thiz, jintArray int_arr) {
    gl_arr = (jintArray )env->NewGlobalRef((jobject) int_arr);
}
extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndktestapp_MainActivity_addSavedArray(JNIEnv *env, jobject thiz) {
    jint *arr = env->GetIntArrayElements(gl_arr, NULL);
    int res=0;
    int size = env->GetArrayLength(gl_arr);
    for(int i=0;i<size;i++)
        res+=arr[i];

    env->ReleaseIntArrayElements(gl_arr, arr, 0);
    env->DeleteGlobalRef(gl_arr);
    return res;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_kso_android_ndktestapp_Helper_greetingFromJNI(JNIEnv *env, jobject thiz) {
    std::string name = "Kyaw San Oo";
    return env->NewStringUTF(name.c_str());
}
extern "C"
JNIEXPORT jobject JNICALL
Java_kso_android_ndktestapp_MainActivity_getEmployeeFromJNI(JNIEnv *env, jobject thiz) {
    std::string name = "Kyaw San Oo";

    jclass employee_class = env->FindClass( "kso/android/ndktestapp/Employee");
    jmethodID employee_constructor = env->GetMethodID( employee_class,  "<init>", "()V" );
    jobject employee_obj = env->NewObject( employee_class, employee_constructor );

    jmethodID set_name_method = env->GetMethodID( employee_class,  "setName", "(Ljava/lang/String;)V" );
    jstring jstr = env->NewStringUTF( name.c_str() );
    env->CallVoidMethod( employee_obj, set_name_method, jstr );
    return employee_obj;
}



extern "C"
JNIEXPORT jstring JNICALL
Java_kso_android_ndktestapp_MainActivity_getInfo(JNIEnv *env, jobject thiz) {
    const jclass mainActivityClz =  env ->GetObjectClass(thiz);
    const jmethodID jmethodId = env->GetMethodID(mainActivityClz, "getMessage", ("()Ljava/lang/String;"));
    if(jmethodId == nullptr){
        return env->NewStringUTF("");
    }
    const jobject result = env->CallObjectMethod(thiz, jmethodId);
    const std::string java_msg = env->GetStringUTFChars((jstring) result, JNI_FALSE);
    const std::string jni_msg = " JNI";
    const std::string message = java_msg + jni_msg;
    return env->NewStringUTF(message.c_str());

}