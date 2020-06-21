//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <memory>

class DataChunk final
{

public:

    DataChunk(size_t size);
    DataChunk(const DataChunk& src);
    DataChunk(DataChunk&& src);
    ~DataChunk();

private:

    size_t m_size;
    std::shared_ptr<uint8_t[]> m_data;
};
