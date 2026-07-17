#ifndef ACORN_MATH_VEC_HPP
#define ACORN_MATH_VEC_HPP

#include <glm/glm/vec2.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec4.hpp>
#include <fmt/format.h>
#include <type_traits>

#include "Acorn/EngineAPI.hpp"
#include "glm/glm/detail/qualifier.hpp"

namespace Acorn::Math
{
    template<typename T>
    struct VecTypeFor : std::false_type
    {};

    template<>
    struct VecTypeFor<float> : std::true_type
    {
        inline static const char* suffix = "f";
    };

    template<>
    struct VecTypeFor<int> : std::true_type
    {
        inline static const char* suffix = "i";
    };

    template<>
    struct VecTypeFor<unsigned int> : std::true_type
    {
        inline static const char* suffix = "u";
    };

    template<typename T>
    concept VecType = requires { VecTypeFor<T>::value; };

    template<size_t N>
    concept ValidVecSize = (N >= 2 && N <= 4);

    template<size_t componentsCount, VecType T>
    class ENGINE_API Vec
    {
        static_assert(componentsCount >= 2 && componentsCount <= 4);

    public:
        Vec() noexcept = default;
        explicit Vec(T scalar)  noexcept;
        Vec(T x, T y)           noexcept requires (componentsCount == 2);
        Vec(T x, T y, T z)      noexcept requires (componentsCount == 3);
        Vec(T x, T y, T z, T w) noexcept requires (componentsCount == 4);

        T& x() noexcept;
        T& y() noexcept;
        T& z() noexcept requires (componentsCount > 2);
        T& w() noexcept requires (componentsCount > 3);

        T x() const noexcept;
        T y() const noexcept;
        T z() const noexcept requires (componentsCount > 2);
        T w() const noexcept requires (componentsCount > 3);

        float length() const noexcept;
        float lengthSqrd() const noexcept;

        static Vec ZERO() noexcept;
        static Vec ONE() noexcept;

    private:
        glm::vec<componentsCount, T, glm::defaultp> m_vec;
    };

    using Vec2f = Vec<2, float>;
    using Vec2i = Vec<2, int>;
    using Vec2u = Vec<2, unsigned int>;

    using Vec3f = Vec<3, float>;
    using Vec3i = Vec<3, int>;
    using Vec3u = Vec<3, unsigned int>;

    using Vec4f = Vec<4, float>;
    using Vec4i = Vec<4, int>;
    using Vec4u = Vec<4, unsigned int>;

    static_assert(sizeof(int) == 4,
        "What kind of exotic machine are you on? This is not compiling here");
    static_assert(sizeof(Vec2f) == sizeof(glm::vec2) , "Vec2f size mismatch");
    static_assert(sizeof(Vec2i) == sizeof(glm::ivec2), "Vec2i size mismatch");
    static_assert(sizeof(Vec2u) == sizeof(glm::uvec2), "Vec2u size mismatch");
}

template<size_t componentsCount, typename T>
struct fmt::formatter<Acorn::Math::Vec<componentsCount, T>>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const Acorn::Math::Vec<componentsCount, T>& v,
        FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), 
            "Vec{}{}({}, {})",
            componentsCount,
            Acorn::Math::VecTypeFor<T>::suffix,
            v.x(), v.y());
    }
};

#include "Acorn/Base/Math/Vec.ipp"

#endif /* ACORN_MATH_VEC2_HPP */
