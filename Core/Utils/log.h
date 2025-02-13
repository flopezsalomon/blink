/**
 * @file log.h
 * @brief Módulo de logs del sistema.
 *
 * "Inspirado" en esp-log.
 * TODO: Implementar niveles de log por cada "tag"
 *
 * Utilizar los macros LOG_<nivel>(tag, format, ...).
 *
 * @copyright Krea Mining SpA, 2024
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>

#define CONFIG_LOG_COLORS 1

typedef enum {
  LOG_LEVEL_NONE,
  LOG_LEVEL_FATAL,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARN,
  LOG_LEVEL_INFO,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_VERBOSE
} log_level;

/**
 * @brief Obtener el nivel del log global.
 *
 * @return El nivel del log global.
 */
log_level log_level_get();

/**
 * @brief Setear el nivel del log global.
 *
 * @param level El nivel del log global.
 */
void log_level_set(log_level level);

/**
 * @brief Escribe un mensaje al log.
 *
 * @param level El nivel del mensaje.
 * @param tag El nombre del componente en el que se originó el mensaje.
 * @param format El formato (estilo printf) del mensaje.
 */
void log_write(log_level level, const char *tag, const char *format, ...)
    __attribute__((format(printf, 3, 4)));

#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK "30"
#define LOG_COLOR_RED "31"
#define LOG_COLOR_GREEN "32"
#define LOG_COLOR_BROWN "33"
#define LOG_COLOR_BLUE "34"
#define LOG_COLOR_PURPLE "35"
#define LOG_COLOR_CYAN "36"
#define LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR) "\033[1;" COLOR "m"
#define LOG_RESET_COLOR "\033[0m"
#define LOG_COLOR_F LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_E LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_W LOG_COLOR(LOG_COLOR_PURPLE)
#define LOG_COLOR_I LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V
#else /* CONFIG_LOG_COLORS */
#define LOG_COLOR_F
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif /* CONFIG_LOG_COLORS */

#define LOG_LEVEL_F "FATAL"
#define LOG_LEVEL_E "ERROR"
#define LOG_LEVEL_W "WARN"
#define LOG_LEVEL_I "INFO"
#define LOG_LEVEL_D "DEBUG"
#define LOG_LEVEL_V "VERBOSE"

#define LOG_FORMAT(letter, format)                              \
  LOG_COLOR_##letter "[00/00/00 00:00:00] [" LOG_LEVEL_##letter \
      "] %s: " format LOG_RESET_COLOR "\r\n"

#define LOG_VERBOSE(tag, format, ...)                      \
  log_write(LOG_LEVEL_VERBOSE, tag, LOG_FORMAT(V, format), \
            tag __VA_OPT__(, ) __VA_ARGS__);
#define LOG_DEBUG(tag, format, ...)                      \
  log_write(LOG_LEVEL_DEBUG, tag, LOG_FORMAT(D, format), \
            tag __VA_OPT__(, ) __VA_ARGS__);
#define LOG_INFO(tag, format, ...)                      \
  log_write(LOG_LEVEL_INFO, tag, LOG_FORMAT(I, format), \
            tag __VA_OPT__(, ) __VA_ARGS__);
#define LOG_WARN(tag, format, ...)                      \
  log_write(LOG_LEVEL_WARN, tag, LOG_FORMAT(W, format), \
            tag __VA_OPT__(, ) __VA_ARGS__);
#define LOG_ERROR(tag, format, ...)                      \
  log_write(LOG_LEVEL_ERROR, tag, LOG_FORMAT(E, format), \
            tag __VA_OPT__(, ) __VA_ARGS__);
#define LOG_FATAL(tag, format, ...)                      \
  log_write(LOG_LEVEL_FATAL, tag, LOG_FORMAT(F, format), \
            tag __VA_OPT__(, ) __VA_ARGS__);

#endif /* _LOG_H_ */