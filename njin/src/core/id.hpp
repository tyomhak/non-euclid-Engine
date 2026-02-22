#pragma once

#include <vector>

namespace njin
{

template<typename Tag>
struct ID
{
    using value_type = uint32_t;
    value_type value = invalid();

    constexpr ID() noexcept = default;
    constexpr explicit ID(value_type v) noexcept : value(v) {}

    static constexpr value_type invalid() noexcept { return std::numeric_limits<value_type>::max(); }
    constexpr bool is_valid() const noexcept { return value != invalid(); }
    constexpr explicit operator bool() const noexcept { return is_valid(); }
    constexpr value_type to_raw() const noexcept { return value; }

    friend constexpr bool operator==(ID a, ID b) noexcept { return a.value == b.value; }
    friend constexpr bool operator!=(ID a, ID b) noexcept { return a.value != b.value; }
    friend constexpr bool operator<(ID a, ID b) noexcept { return a.value < b.value; }
};

} // namespace njin

namespace std
{
    template<typename Tag>
    struct hash<njin::ID<Tag>>
    {
        size_t operator()(njin::ID<Tag> const& id) const noexcept
        {
            return std::hash<typename njin::ID<Tag>::value_type>()(id.to_raw());
        }
    };
}