# jnotify
##Java - Processing notifications from legacy multithreaded shared library
This project is intended to demonstrate how notifications, generated from a legacy c/c++ shared library, can be propagated to java code. Shared library sends notifications in a separate native thread. JNI attaches the native thread to JVM and call java code on the thread.

- setup.sh : build the sources. Edit JAVA_HOME.
- run.sh   : run the JNotifyMain class in JVM. Edit JAVA_HOME

Sources are tested on Ubuntu 14.04.4 with jdk1.7.0_79 

I would like to to improve this framework to support arbitrary c++ notifications from native library by declaring them in xml file.
