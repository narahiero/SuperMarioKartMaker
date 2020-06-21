//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "Common/DataChunk.hpp"

#include <memory>

DataChunk::DataChunk(size_t size) :
    m_size{size}
{
    m_data = std::shared_ptr<uint8_t[]>(new uint8_t[size]);
}

DataChunk::DataChunk(const DataChunk& src) :
    m_size{src.m_size},
    m_data{src.m_data}
{

}

DataChunk::DataChunk(DataChunk&& src) :
    m_size{src.m_size},
    m_data{std::move(src.m_data)}
{

}
