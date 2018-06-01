#include "stdafx.h"
#include "SPLogger.h"

#include <string>
#include <chrono>
#include <ctime>

namespace SLG
{

    SPLogger::SPLogger(std::string path)
    {
        _output.open(path);
    }
    SPLogger::SPLogger(std::ostream& os)
    {
        _output.set_rdbuf(os.rdbuf());
    }


    std::string CurrentTime() {
        return "";
    }
    std::string LogLvlName(SPLogLevel lvl)
    {
        switch (lvl)
        {
        case SPLogLevel::Trace    :
            return "TRACE";
        case SPLogLevel::Debug    :
            return "DEBUG";
        case SPLogLevel::Info     :
            return "INFO";
        case SPLogLevel::Notice   :
            return "NOTICE";
        case SPLogLevel::Warning  :
            return "WARNING";
        case SPLogLevel::Error    :
            return "FATAL";
        case SPLogLevel::Fatal    :
            return "ERROR";
        default:
            break;
        }
    }
    void SPLogger::Write(std::stringstream const& os, LogLvl lvl)
    {
        if (!_useDebug && (lvl <= L_DEBUG))
            return;

        _output << CurrentTime() << "|";

        _output << os.str() << std::endl;
    }

    SPLogger::SPLoggerStream SPLogger::operator()(LogLvl lvl)
    {
        return{ *this, lvl };
    }



}