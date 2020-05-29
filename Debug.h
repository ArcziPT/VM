#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>

#ifndef DEBUG_LOG
    #define LOG_MSG(A)
    #define LOG_OBJECT(A)
#else
    #define LOG_MSG(A) std::cout<<"[MSG]: "<<A<<std::endl;
    #define LOG_OBJECT(A) std::cout<<"[OBJECT]: "<<#A<<" -> ("<<A<<")"<<std::endl;
#endif

#ifndef FILE_DEBUG_LOG
    #define OPEN_LOG_FILE(A)
    #define FILE_LOG_ERROR(A)
    #define FILE_LOG_MSG(A)
    #define FILE_LOG_OBJECT(A)
    #define CLOSE_LOG_FILE()
#else
    std::ofstream debug_file;

    #define OPEN_LOG_FILE(A) debug_file.open(A);
    #define FILE_LOG_ERROR(A) debug_file<<"[ERROR]("<<__FILE__<<":"<<__LINE__<<"): "<<A<<std::endl;
    #define FILE_LOG_MSG(A) debug_file<<"[MSG]: "<<A<<std::endl;
    #define FILE_LOG_OBJECT(A) debug_file<<"[OBJECT]: "<<#A<<" = "<<A<<std::endl;
    #define CLOSE_LOG_FILE() debug_file.close();
#endif

#endif