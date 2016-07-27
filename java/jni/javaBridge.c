/**
 * Copyright 2016 Amarendranatha(Amar) Gorla
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

#include <tempSensor.h>

#include "javaBridge.h"

static JavaVM    *s_javaVM = NULL;
static JNIEnv    *s_env = NULL;

static jclass     s_jBridgeCls;
static jobject    s_jBridgeObj;
static jmethodID  s_notifyCbMethod;

static void checkAndClearException(JNIEnv *env){
  if (  (*env)->ExceptionCheck(env) ){
    printf("Exception Occured in JNI layer of JavaBridge\n");
    (*env)->ExceptionClear(env);
  }
}

static void tempatureTooColdHdlr(){
  JNIEnv *env = NULL;

  (*s_javaVM)->AttachCurrentThread(s_javaVM, (void **) &env, NULL);
  checkAndClearException(env);

  (*env)->CallVoidMethod(env, s_jBridgeObj, s_notifyCbMethod, (jint) 0);
  checkAndClearException(env);

  (*s_javaVM)->DetachCurrentThread(s_javaVM);
}

static void tempatureTooHotHdlr(){
  JNIEnv *env = NULL;

  (*s_javaVM)->AttachCurrentThread(s_javaVM, (void **)&env, NULL);
  checkAndClearException(env);

  (*env)->CallVoidMethod(env, s_jBridgeObj, s_notifyCbMethod, (jint) 1);
  checkAndClearException(env);

  (*s_javaVM)->DetachCurrentThread(s_javaVM);
}

JNIEXPORT void JNICALL 
Java_jnotify_JavaBridge_startTemparatureSensorEngine(JNIEnv *env, jobject obj){
  s_env = env;
  (*env)->GetJavaVM(env, &s_javaVM);
  checkAndClearException(env);

  s_jBridgeObj = obj;
  s_jBridgeCls = (*env)->GetObjectClass(env, obj);
  checkAndClearException(env);
  s_notifyCbMethod = (*env)->GetMethodID(env,
                      s_jBridgeCls, "notifyCallback", "(I)V");
  checkAndClearException(env);

  registerTempEvent(TempEventTooCold, tempatureTooColdHdlr);
  registerTempEvent(TempEventTooHot, tempatureTooHotHdlr);
  startSensorEngine();
}
