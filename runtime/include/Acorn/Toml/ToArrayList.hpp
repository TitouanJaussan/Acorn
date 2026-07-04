#ifndef ACORN_TOML_TO_ARRAYLIST_HPP
#define ACORN_TOML_TO_ARRAYLIST_HPP

#define TOML_HEADER_ONLY 0
#include <tomlplusplus/toml.hpp>

#include "Acorn/EngineAPI.hpp"
#include "Acorn/Templates/ArrayList.hpp"
#include "Acorn/Templates/String.hpp"

namespace Acorn::Toml
{
    ENGINE_API ArrayList<int64_t> toIntArrayList(const toml::array* arr);
    ENGINE_API ArrayList<String> toStringArrayList(const toml::array* arr);
}

#endif /* ACORN_TOML_TO_ARRAYLIST_HPP */
