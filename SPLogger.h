#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace SLG
{

    class SPLogger
    {
    public:

        enum class LogLvl { Trace = -2  // Production Only (code smell)
                          , Debug       // Debug & Production
                          , Info        // User-driven Information
                          , Notice      // Default; log for event not errors
                          , Warning     // Event that could lead to an error
                          , Error       // Errors, (internal or not) recovarable if possible
                          , Fatal       // Fatal error that will lead to a programm exit
                          };
        explicit SPLogger(std::ostream& os = std::cout);
        explicit SPLogger(std::string path);

        inline void AllowDebugOutput(bool b) { _useDebug = b; }

        void Write(std::stringstream const& os, LogLvl lvl);

        class SPLoggerStream {
        public:
            SPLoggerStream(SPLogger& log, LogLvl lvl) : _log(log), _lvl(lvl) {};
            SPLoggerStream(SPLoggerStream&&) = default;
            ~SPLoggerStream() { _log.Write(ss, _lvl); }
            template<typename T> inline void Write(T const& t) { ss << t << " "; }
        private:
            SPLogger& _log;
            LogLvl _lvl;
            std::stringstream ss;
        };

        /// Return a SLogStream to control the input line
        /// using the given level
        /// Default lvl is Trace
        SPLoggerStream operator()(LogLvl lvl = LogLvl::Notice);
    private:
        std::ofstream _output;
        bool _useDebug = false;

    };
    
    

typedef SPLogger::SPLoggerStream SPLogStream;
typedef SPLogger::LogLvl SPLogLevel;

#define L_TRACE     ::SLG::SPLogLevel::Trace
#define L_DEBUG     ::SLG::SPLogLevel::Debug
#define L_INFO      ::SLG::SPLogLevel::Info
#define L_NOTICE    ::SLG::SPLogLevel::Notice
#define L_WARNING   ::SLG::SPLogLevel::Warning
#define L_ERROR     ::SLG::SPLogLevel::Error
#define L_FATAL     ::SLG::SPLogLevel::Fatal

    
    template <typename T>
    [[deprecated("Deprecated use of SLG::SPLogger. Use SPLogStream by calling operator()")]]
        SPLogger& operator <<(SPLogger& os, T t) { os() << t; return os; }
    
    template <typename T> SPLogStream& operator<<(SPLogStream& os, T const& t) { os.Write(t); return os; }



} // Namespace SLog



/*
TODO : [Note, this is to stay a simple .h/.cpp library, not a framework
 * TIME [...]
    - Add Time to the output
    - Add Structure to control the time for the output
        ¤ Show it or not
        ¤ In which format
        ¤ With which precision

  * Effects [...]
    - Define a string to show at the start of each line
    -  Ex: my_logger.SetStartingLine([ProjectCode]);
    - ?Allow function to personnalize differents levels
    
  * FILE [NO]
    - Allow to Change the output
    - Roll all the output on a certain date

  * Manipulators [YES]
    - A Base class interface
    - Ex: Manipulator to display info on the pc
    
  * ?Multiple Output files ? [NO]
    - One for errors only ?
    - The log file will also display errors but no details on them
   

*/