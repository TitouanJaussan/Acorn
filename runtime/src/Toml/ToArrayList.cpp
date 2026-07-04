#include "Acorn/Toml/ToArrayList.hpp"

namespace Acorn::Toml
{
    ArrayList<int64_t> toIntArrayList(const toml::array* arr)
    {
        ArrayList<int64_t> output{};

        if (arr)
        {
            arr->for_each([&output](auto&& el)
            {
                if constexpr (toml::is_number<decltype(el)>)
                    output.append(*el);
            });
        }
        else
        {
            // Maybe I should throw an error instead
            return {};
        }

        return output;
    }

    ArrayList<String> toStringArrayList(const toml::array* arr)
    {
        ArrayList<String> output{};

        if (arr)
        {
            arr->for_each([&output](auto&& el)
            {
                if constexpr (toml::is_string<decltype(el)>)
                    output.append(String(el.get().c_str()));
            });
        }
        else
        {
            // Maybe I should throw an error instead
            return {};
        }

        return output;
    }
}
