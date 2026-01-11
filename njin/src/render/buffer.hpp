#pragma once


namespace njin
{


class Buffer
{
public:
    

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;
private:

};



};