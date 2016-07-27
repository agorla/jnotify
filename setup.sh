##########################################################################
# Copyright 2016 Amarendranatha(Amar) Gorla
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
############################################################################

#!/bin/sh

CurDir=`pwd`

#build c sources
GCC=gcc   #replace it with your own

rm -rf lib
mkdir lib
cd legacy
${GCC} -c -Wall -fpic -o tempSensor.o tempSensor.c
${GCC} -shared -o ../lib/libtempSersor.so -Wl,--version-script=libtempSersor.version tempSensor.o

#build java sources
JAVA_HOME=~/jdk/jdk1.7.0_79 #replace it with your own

cd ${CurDir}
rm -rf classes
mkdir classes
cd ${CurDir}/java
${JAVA_HOME}/bin/javac jnotify/*.java -d ../classes

#generate jni header
rm -rf jni/javaBridge.h
${JAVA_HOME}/bin/javah -o jni/javaBridge.h -cp ${CurDir}/classes jnotify.JavaBridge

#compile and link jni library
cd ${CurDir}/java/jni
${GCC} -c -g -Wall -fpic -o javaBridge.o -I../../legacy -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux javaBridge.c
${GCC} -shared -o ../../lib/libjavaBridge.so -Wl,--version-script=libjavaBridge.version javaBridge.o -L../../lib -ltempSersor
