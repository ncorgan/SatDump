#include "usrp_sdr_base.h"

UsrpBase::UsrpBase(const std::string &args):
    usrp(uhd::usrp::multi_usrp::make(args))
{
}

UsrpBase::~UsrpBase() = default;
