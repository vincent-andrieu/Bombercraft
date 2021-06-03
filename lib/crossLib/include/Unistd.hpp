/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Unistd
*/

#ifndef UNISTD_HPP_
#define UNISTD_HPP_

#include <string>

#ifdef __linux__ 
    #include <unistd.h>
#elif _WIN32
    #include <io.h>
#endif

namespace Cross
{

#ifdef __linux__ 
    enum aMode {
        fOk = F_OK,
        rOk = R_OK,
        wOk = W_OK,
        rwOk = R_OK | W_OK,
    };
#elif _WIN32
    enum aMode {
        fOk = 00,
        rOk = 04,
        wOk = 02,
        rwOk = 06,
    };
#endif

    class Unistd {
        public:
            static int my_access(const std::string &pathname, const aMode mode) noexcept;

        protected:
        private:
    };    
}

#endif /* !UNISTD_HPP_ */
