# jnotify
Java - Processing notifications from legacy multithreaded shared library

This project is intended to demonstrate how notifications, generated from a legacy c/c++ shared library, can be propagated to  a java code. Shared library send notifications in a separate thread. JNI attaches the native thread to JVM and call java code on the thread.

setup.sh : build the sources. Edit JAVA_HOME.
run.sh    : run the JNotifyMain class in JVM. Edit JAVA_HOME

Sources are tested on Ubuntu 14.04.4 with  jdk1.7.0_79 

I would like to to develop a framework that would enable the c++ notifications declared in an xml file in future.
