#include <jni.h>
#include <GLRenderer.h>

static GLRenderer* renderer = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learnopengl_MyGLRenderer_onInit(JNIEnv *env, jobject thiz) {
    renderer = new GLRenderer();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learnopengl_MyGLRenderer_onSizeChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    renderer->OnSizeChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learnopengl_MyGLRenderer_onDraw(JNIEnv *env, jobject thiz) {
    renderer->OnDraw();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_learnopengl_MyGLRenderer_onDestroy(JNIEnv *env, jobject thiz) {
    renderer->OnDestroy();
    delete renderer;
}