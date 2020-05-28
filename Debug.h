#ifndef DEBUG_H
#define DEBUG_H

#ifndef DEBUG_LOG
    #define LOG_FUNC_MSG(A)
    #define LOG_MSG(A)
    #define LOG_TAG_MSG(A, B)
    #define LOG_CALL()
#else
    #define LOG_FUNC_MSG(A) std::cout<<__PRETTY_FUNCTION__<<": "<<A<<std::endl;
    #define LOG_MSG(A) std::cout<<A<<std::endl;
    #define LOG_TAG_MSG(A, B) std::cout<<A<<": "<<B<<std::endl;
    #define LOG_CALL() std::cout<<__PRETTY_FUNCTION__<<" called"<<std::endl;
#endif

#endif