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
 * tempSensor.h : temperature sensor header for clients
 */

typedef void (*TempNotify)();

typedef enum TempEventType{
  TempEventTooCold, /* too cold event */
  TempEventTooHot   /* too hot event */
} TempEventType;

/**
 * calls notifyCallBack() whenever TempNotify occurs
 **/
void registerTempEvent(TempEventType eventType, TempNotify notifyCallBack);

void startSensorEngine();
