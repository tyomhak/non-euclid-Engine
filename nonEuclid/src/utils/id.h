#pragma once

template<typename T>
struct ID
{
    uint64_t id{-1};


    ID() : ID(uninitialized())
    {}

    static ID create()
    {
        static uint64_t last_id = 0;
        return ID(++last_id);
    }

    static ID uninitialized()
    { 
        return ID(); 
    }

    bool is_valid() const 
    { 
        return *this == uninitialized(); 
    }

private:
    ID(uint64_t value) : id(value)
    {}
};