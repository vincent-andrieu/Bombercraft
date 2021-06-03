/*
** EPITECH PROJECT, 2021
** indiestudio
** File description:
** Unistd
*/

#ifndef EXPORT_HPP_
#define EXPORT_HPP_

#ifndef EXPORT
  #ifdef _WIN32
    #define EXPORT __declspec (dllexport)
  #else 
    #define EXPORT
  #endif
#endif

#endif /* !EXPORT_HPP_ */
