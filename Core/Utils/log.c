/**
 * @file log.c
 * @brief Módulo de logs del sistema.*
 * Utilizar los macros LOG_<nivel>(tag, format, ...).
 *
 *
 */
#include "log.h"

#include <stdio.h>

static log_level global_log_level = LOG_LEVEL_VERBOSE;

log_level log_level_get() { return global_log_level; }

void log_level_set(log_level level) { global_log_level = level; }

void log_write(log_level level, const char *tag, const char *format, ...) {
  (void)tag;

  if (level > global_log_level) return;

  va_list list;
  va_start(list, format);
  vprintf(format, list);
  va_end(list);
}