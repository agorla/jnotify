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

package jnotify;

public class JavaBridge{
  public enum TemparatureEven{ TooCold, TooHot };
  

  private static final int TempEventTooCold = 0;
  private static final int TempEventTooHot  = 1;
  private static JavaBridge s_instance = null;
  private TemparatureEvent m_tempEventHandler = null;

  private JavaBridge(){
    System.loadLibrary("javaBridge");
  }

  public synchronized static JavaBridge getInstance(){
    if (s_instance == null){
      s_instance = new JavaBridge();
    }
    return s_instance;
  }

  public void registerTemperatureEvent(TemparatureEvent eventHandler){
    m_tempEventHandler = eventHandler;
  }

  public native void startTemparatureSensorEngine();

  public void notifyCallback(int type){
    try{
      if (type == TempEventTooCold){
        m_tempEventHandler.tooCold();
      }else{
        m_tempEventHandler.tooHot();
      }
    }catch(Throwable t){
      t.printStackTrace();
    }
  }
}
