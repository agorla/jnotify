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
 *
 *
 * tempSensor.c : Simple implementation of notification engine 
 * for testing the java code.
 * Handling of errors and race conds are vomited to make src simple
 *
 * compile: gcc -c -Wall -fpic -o tempSensor.o tempSensor.c
 * build shared lib: gcc -shared -o libtempSersor.so -Wl,--version-script=libtempSersor.version tempSensor.o 
 */
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "tempSensor.h"

TempNotify s_notifyTooCold = NULL;
TempNotify s_notifyTooHot = NULL;

void *callNotifyCallBack(void *type){
  TempEventType *pType = type;

  if (pType == NULL){
    return NULL;
  }

  if (*pType == TempEventTooCold){
    if (s_notifyTooCold) s_notifyTooCold();
  } else if (*pType == TempEventTooHot){
    if (s_notifyTooHot) s_notifyTooHot();
  }

  return NULL;
}

/**
 * 
 **/
void startSensorEngine(){
  int sTime = 0;
  while(1){
    pthread_t tId;
    TempEventType *pType = NULL;
    sTime = rand();
    sleep(sTime%5+1);
    pType = malloc(sizeof(TempEventType));
    *pType = (TempEventType)(rand()%2);
    pthread_create(&tId, NULL, callNotifyCallBack, pType);
    pthread_join(tId, NULL);
    free(pType);
  }
}


void registerTempEvent(TempEventType type, TempNotify notifyCB){
  if (type == TempEventTooCold){
    s_notifyTooCold = notifyCB;
  }else{
    s_notifyTooHot = notifyCB;
  }
}
