#pragma once

#include <boost/asio/io_context.hpp>

std::shared_ptr<boost::asio::io_context> GetIoContext();