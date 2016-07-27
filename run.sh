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

LD_LIBRARY_PATH=${CurDir}/lib
JAVA_HOME=~/jdk/jdk1.7.0_79 #replace it with your own
CLASS_PATH=${CurDir}/classes

export LD_LIBRARY_PATH
${JAVA_HOME}/bin/java -cp ${CLASS_PATH} -Djava.library.path=${LD_LIBRARY_PATH} jnotify.JNotifyMain
#gdb  ${JAVA_HOME}/bin/java
