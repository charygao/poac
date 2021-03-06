#ifndef POAC_IO_CLI_HPP
#define POAC_IO_CLI_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>

#include "../util/pretty.hpp"
#include "../util/termcolor2.hpp"

namespace poac::io::cli {
    // Clear screen
    constexpr auto clr_screen = termcolor2::make_string("\x1b[2J");
    // Clear from the cursor position to the right end
    constexpr auto clr_right = termcolor2::make_string("\x1b[0K");
    // Clear from the cursor position to the left end
    constexpr auto clr_left = termcolor2::make_string("\x1b[1K");
    // Clear the line at the cursor position
    constexpr auto clr_line = termcolor2::make_string("\x1b[2K");

    inline void set_left(int&& n) {
        std::cout << std::setw(n) << std::left;
    }

    constexpr auto status = termcolor2::to_green("==> ");
    constexpr auto fetched = termcolor2::to_green("  ●  ");
    constexpr auto fetch_failed = termcolor2::to_red("  ●  ");

    constexpr auto warning = termcolor2::to_yellow("WARN: ");
    constexpr auto error = termcolor2::to_red("ERROR: ");
    constexpr auto info = termcolor2::to_blue("info: ");
    constexpr auto debug_m = termcolor2::to_gray("[debug] ");

    inline void status_done() {
        std::cout << status << "Done." << std::endl;
    }


    const std::vector<std::string> spinners{
        "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"
    };
    std::string to_spinner(const size_t& index) {
        return spinners[index % spinners.size()];
    }
    const std::vector<std::string> pointers{ ".  ", ".. ", "..." };
    std::string to_pointer(const size_t& index) {
        if      (index <= 2) return pointers[0];
        else if (index <= 5) return pointers[1];
        else                 return pointers[2];
    }

    // Create progress bar, [====>   ]
    std::string to_progress(const int& max_count, int now_count) {
        if (now_count > max_count) {
            now_count = max_count;
        }

        const int bar_size = 50;
        const int percent = (now_count * 100) / max_count;
        const int bar_pos = percent / 2;

        std::string bar = "[";
        if (now_count >= max_count) {
            for (int i = 0; i < (bar_size - 1); ++i) {
                bar += "=";
            }
            bar += ">]";
        } else if ((bar_pos - 1) > 0) {
            for (int i = 0; i < (bar_pos - 1); ++i) {
                bar += "=";
            }
            bar += ">";
            for (int i = 0; i < (bar_size - bar_pos); ++i) {
                bar += " ";
            }
            bar += "]";
        } else if (bar_pos == 1) {
            bar += ">";
            for (int i = 0; i < (bar_size - 1); ++i) {
                bar += " ";
            }
            bar += "]";
        } else {
            for (int i = 0; i < bar_size; ++i) {
                bar += " ";
            }
            bar += "]";
        }
        return bar;
    }
    // Print byte progress bar, [====>   ] 10.21B/21.28KB
    void echo_byte_progress(const int& max_count, const int& now_count) {
        const auto [ parsed_max_byte, max_byte_unit ] = util::pretty::to_byte(max_count);
        const auto [ parsed_now_byte, now_byte_unit ] = util::pretty::to_byte(now_count);
        std::cout << cli::to_progress(max_count, now_count) << " ";
        std::cout << std::fixed;
        std::cout << std::setprecision(2) << parsed_now_byte << now_byte_unit << "/";
        std::cout << std::setprecision(2) << parsed_max_byte << max_byte_unit << std::flush;
    }

    template <typename... T>
    inline void debugln([[maybe_unused]] const T&... s) {
#ifdef DEBUG
        ((std::cout << debug_m) << ... << s) << std::endl;
#endif
    }
    template <typename... T>
    inline void debug([[maybe_unused]] const T &... s) {
#ifdef DEBUG
        ((std::cout << debug_m) << ... << s);
#endif
    }
} // end namespace
#endif // !POAC_IO_CLI_HPP
