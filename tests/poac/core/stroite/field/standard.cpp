#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <poac/core/stroite/field/standard.hpp>
#include <poac/core/except.hpp>


// inline std::string version_prefix(const bool& enable_gnu) noexcept
BOOST_AUTO_TEST_CASE( poac_core_stroite_field_standard_version_prefix_test )
{
    using poac::core::stroite::field::standard::version_prefix;
    BOOST_TEST( version_prefix(false) == "-std=c++" );
    BOOST_TEST( version_prefix(true) == "-std=gnu++" );
}

// std::string apple_llvm_convert(const std::uint8_t& cpp_version, const bool& enable_gnu)
BOOST_AUTO_TEST_CASE( poac_core_stroite_field_standard_apple_llvm_convert_test )
{
    using poac::core::stroite::field::standard::apple_llvm_convert;
    using poac::core::except::error;

    BOOST_TEST( apple_llvm_convert(98, false) == "-std=c++98" );
    BOOST_TEST( apple_llvm_convert(98, true) == "-std=gnu++98" );

    BOOST_TEST( apple_llvm_convert(3, false) == "-std=c++11" );
    BOOST_TEST( apple_llvm_convert(3, true) == "-std=gnu++11" );

    BOOST_TEST( apple_llvm_convert(11, false) == "-std=c++11" );
    BOOST_TEST( apple_llvm_convert(11, true) == "-std=gnu++11" );

    BOOST_TEST( apple_llvm_convert(14, false) == "-std=c++14" );
    BOOST_TEST( apple_llvm_convert(14, true) == "-std=gnu++14" );

    BOOST_TEST( apple_llvm_convert(17, false) == "-std=c++17" );
    BOOST_TEST( apple_llvm_convert(17, true) == "-std=gnu++17" );

    BOOST_CHECK_THROW( apple_llvm_convert(20, false), error );
    BOOST_CHECK_THROW( apple_llvm_convert(6, true), error );
}

// std::string gcc_convert(const std::uint8_t& cpp_version, const std::string& compiler_version, const bool& enable_gnu)
BOOST_AUTO_TEST_CASE( poac_core_stroite_field_standard_gcc_convert_test )
{
    using poac::core::stroite::field::standard::gcc_convert;
    using poac::core::except::error;

    BOOST_TEST( gcc_convert(98, "1.0.0", false) == "" );
    BOOST_TEST( gcc_convert(98, "1.0.0", true) == "" );

    BOOST_CHECK_THROW( gcc_convert(3, "4.2", false), error );
    BOOST_TEST( gcc_convert(3, "4.3", false) == "-std=c++0x" );
    BOOST_TEST( gcc_convert(3, "4.5", true) == "-std=gnu++0x" );
    BOOST_TEST( gcc_convert(3, "4.7", false) == "-std=c++11" );
    BOOST_TEST( gcc_convert(3, "8.0", true) == "-std=gnu++11" );

    BOOST_CHECK_THROW( gcc_convert(11, "4.2", false), error );
    BOOST_TEST( gcc_convert(11, "4.3", false) == "-std=c++0x" );
    BOOST_TEST( gcc_convert(11, "4.5", true) == "-std=gnu++0x" );
    BOOST_TEST( gcc_convert(11, "4.7", false) == "-std=c++11" );
    BOOST_TEST( gcc_convert(11, "8.0", true) == "-std=gnu++11" );

    BOOST_CHECK_THROW( gcc_convert(14, "4.7", false), error );
    BOOST_TEST( gcc_convert(14, "4.8", false) == "-std=c++1y" );
    BOOST_TEST( gcc_convert(14, "4.8.3", true) == "-std=gnu++1y" );
    BOOST_TEST( gcc_convert(14, "4.9", false) == "-std=c++14" );
    BOOST_TEST( gcc_convert(14, "8.0", true) == "-std=gnu++14" );

    BOOST_CHECK_THROW( gcc_convert(17, "4.9", false), error );
    BOOST_TEST( gcc_convert(17, "5.0", false) == "-std=c++17" );
    BOOST_TEST( gcc_convert(17, "8.0", true) == "-std=gnu++17" );

    BOOST_CHECK_THROW( gcc_convert(20, "7", false), error );
    BOOST_TEST( gcc_convert(20, "8.0", false) == "-std=c++2a" );
    BOOST_TEST( gcc_convert(20, "10.0", true) == "-std=gnu++2a" );

    BOOST_CHECK_THROW( gcc_convert(9, "1.0.0", false), error );
}

// std::string clang_convert(const std::uint8_t& cpp_version, const std::string& compiler_version, const bool& enable_gnu)
BOOST_AUTO_TEST_CASE( poac_core_stroite_field_standard_clang_convert_test )
{
    using poac::core::stroite::field::standard::clang_convert;
    using poac::core::except::error;

    BOOST_TEST( clang_convert(98, "1.0.0", false) == "" );
    BOOST_TEST( clang_convert(98, "1.0.0", true) == "" );

    BOOST_TEST( clang_convert(3, "1.0", false) == "-std=c++11" );
    BOOST_TEST( clang_convert(3, "1.0", true) == "-std=gnu++11" );
    BOOST_TEST( clang_convert(3, "7.0", false) == "-std=c++11" );
    BOOST_TEST( clang_convert(3, "7.0", true) == "-std=gnu++11" );

    BOOST_TEST( clang_convert(11, "1.0", false) == "-std=c++11" );
    BOOST_TEST( clang_convert(11, "1.0", true) == "-std=gnu++11" );
    BOOST_TEST( clang_convert(11, "7.0", false) == "-std=c++11" );
    BOOST_TEST( clang_convert(11, "7.0", true) == "-std=gnu++11" );

    BOOST_CHECK_THROW( clang_convert(14, "3.1", false), error );
    BOOST_TEST( clang_convert(14, "3.2", false) == "-std=c++1y" );
    BOOST_TEST( clang_convert(14, "3.4", true) == "-std=gnu++1y" );
    BOOST_TEST( clang_convert(14, "3.5", false) == "-std=c++14" );
    BOOST_TEST( clang_convert(14, "7.0", true) == "-std=gnu++14" );

    BOOST_CHECK_THROW( clang_convert(17, "3.4.0", false), error );
    BOOST_TEST( clang_convert(17, "3.5.0", false) == "-std=c++1z" );
    BOOST_TEST( clang_convert(17, "4.9.0", true) == "-std=gnu++1z" );
    BOOST_TEST( clang_convert(17, "5.0", false) == "-std=c++17" );
    BOOST_TEST( clang_convert(17, "7.0", true) == "-std=gnu++17" );

    BOOST_CHECK_THROW( clang_convert(20, "5.9.0", false), error );
    BOOST_TEST( clang_convert(20, "6.0", false) == "-std=c++2a" );
    BOOST_TEST( clang_convert(20, "7.0", true) == "-std=gnu++2a" );

    BOOST_CHECK_THROW( clang_convert(12, "1.0.0", false), error );
}

// std::string icc_convert(const std::uint8_t& cpp_version)
BOOST_AUTO_TEST_CASE( poac_core_stroite_field_standard_icc_convert_test )
{
    using poac::core::stroite::field::standard::icc_convert;
    using poac::core::except::error;

    BOOST_TEST( icc_convert(98) == "" );
#ifndef _WIN32
    BOOST_TEST( icc_convert(3) == "-std=c++11" );
    BOOST_TEST( icc_convert(11) == "-std=c++11" );
    BOOST_TEST( icc_convert(14) == "-std=c++14" );
    BOOST_TEST( icc_convert(17) == "-std=c++17" );
#else
    BOOST_TEST( icc_convert(3) == "/Qstd:c++11" );
    BOOST_TEST( icc_convert(11) == "/Qstd:c++11" );
    BOOST_TEST( icc_convert(14) == "/Qstd:c++14" );
    BOOST_TEST( icc_convert(17) == "/Qstd:c++17" );
#endif
    BOOST_CHECK_THROW( icc_convert(20), error );
    BOOST_CHECK_THROW( icc_convert(15), error );
}

// std::string msvc_convert(const std::uint8_t& cpp_version)
BOOST_AUTO_TEST_CASE( poac_core_stroite_field_standard_msvc_convert_test )
{
    using poac::core::stroite::field::standard::msvc_convert;
    using poac::core::except::error;

    BOOST_TEST( msvc_convert(98) == "" );
    BOOST_TEST( msvc_convert(3) == "" );
    BOOST_TEST( msvc_convert(11) == "" );
    BOOST_TEST( msvc_convert(14) == "/std:c++14" );
    BOOST_TEST( msvc_convert(17) == "/std:c++17" );
    BOOST_CHECK_THROW( msvc_convert(20), error );
    BOOST_CHECK_THROW( msvc_convert(18), error );
}
