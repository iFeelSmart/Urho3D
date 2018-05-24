/*
    SDL_android_main.c, placed in the public domain by Sam Lantinga  3/13/14
<<<<<<< HEAD
=======
*/

// Modified by Lasse Oorni and Yao Wei Tjong for Urho3D

// Urho3D - use SDK include dir
#include <SDL/SDL_internal.h>

#ifdef __ANDROID__

/* Include the SDL main definition header */ // Urho3D - use SDK include dir
#include <SDL/SDL_main.h>

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
#include <jni.h>

// Urho3D: added extra filesDir parameter
/* Called before SDL_main() to initialize JNI bindings in SDL library */
extern void SDL_Android_Init(JNIEnv* env, jclass cls, jstring filesDir, jstring cacheDir);

/* This prototype is needed to prevent a warning about the missing prototype for global function below */
JNIEXPORT int JNICALL Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject array, jstring filesDir, jstring cacheDir);

/* Start up the SDL app */
JNIEXPORT int JNICALL Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject array, jstring filesDir, jstring cacheDir)
{
    int i;
    int argc;
    int status;
    int len;
    char** argv;

    /* This interface could expand with ABI negotiation, callbacks, etc. */
    SDL_Android_Init(env, cls, filesDir, cacheDir);
>>>>>>> Add a method to get cache dir on Android

    As of SDL 2.0.6 this file is no longer necessary.
*/

/* vi: set ts=4 sw=4 expandtab: */
