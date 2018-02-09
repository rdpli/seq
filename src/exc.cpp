#include "stage.h"
#include "exc.h"

using namespace seq;

exc::SeqException::SeqException(std::string msg) : std::runtime_error(msg)
{
}

exc::StageException::StageException(std::string msg, Stage &stage) :
    std::runtime_error("(stage: " + stage.getName() + ") " + msg)
{
}

exc::MultiLinkException::MultiLinkException(Stage &stage) :
    StageException("stage linked multiple times", stage)
{
}

exc::ValidationException::ValidationException(Stage &stage) :
    StageException("validation failed", stage)
{
}

exc::IOException::IOException(std::string msg) : std::runtime_error(msg)
{
}
