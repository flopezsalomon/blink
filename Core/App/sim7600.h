#ifndef SIM7600_H
#define SIM7600_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { OK = 0, FAIL, WAIT } result_codes_t;

typedef enum {
  AT_CMD_SRESET = 0,
  AT_CMD_DUMMY,
  AT_CMD_TEST,
  AT_CMD_CGSN,
  AT_CMD_CBC,
  AT_CMD_CPMUTEMP,
  AT_CMD_CPIN,
  AT_CMD_CSQ,
  AT_CMD_CREG,
  AT_CMD_CGREG,
  AT_CMD_CEREG,
  AT_CMD_CPSI,
  AT_CMD_CGDCONT,
  AT_CMD_CGACT,
  AT_CMD_CGACT_Q,
  AT_CMD_CSSLCFG_SSLVER,
  AT_CMD_CSSLCFG_AUTH,
  AT_CMD_CSSLCFG_CACERT,
  AT_CMD_CSSLCFG_CLIENTCERT,
  AT_CMD_CSSLCFG_CLIENTKEY,
  AT_CMD_CMQTTSTART,
  AT_CMD_CMQTTACCQ,
  AT_CMD_CMQTTSSLCFG,
  AT_CMD_CMQTTCONNECT,
  AT_CMD_CMQTTTOPIC,
  AT_CMD_CMQTTSETTOPIC,
  AT_CMD_CMQTTPAYLOAD,
  AT_CMD_CMQTTSETMSGPAYLOAD,
  AT_CMD_CMQTTPUB,
  AT_CMD_CMQTTDISC,
  AT_CMD_CMQTTREL,
  AT_CMD_CMQTTSTOP

} at_cmd_codes_t;

typedef struct {
  const char *command;  // Comando AT a enviar
  char *parameters;     // Parámetros opcionales
  result_codes_t (*response_handler)(
      const char *response);  // Callback para manejar la respuesta
  uint16_t timeout;
  uint8_t timeout_counter;
} sim7600_at_command_t;

typedef struct {
  double volt;
  int temp;
  char payload_size[8];
  uint8_t payload[48];
  char client[24];
  uint8_t sn[16];
  char apn[24];
  char topic[36];
  char topic_size[5];
} sim7600_upkeep_t;

// Basic networks commands
result_codes_t at_command_cbc(void);
result_codes_t at_command_cpmutemp(void);
result_codes_t at_command_dummy(void);
result_codes_t at_command_cgmr(void);
result_codes_t at_command_cgsn(void);
result_codes_t at_command_sreset(void);
result_codes_t at_command_test(void);
result_codes_t at_command_cpin(void);
result_codes_t at_command_csq(void);
result_codes_t at_command_creg(void);
result_codes_t at_command_cgreg(void);
result_codes_t at_command_cereg(void);
result_codes_t at_command_cpsi(void);
result_codes_t at_command_cgdcont(void);
result_codes_t at_command_cgact(void);
result_codes_t at_command_cgact_q(void);

// MQTT commands
result_codes_t at_command_cmqttstart(void);
result_codes_t at_command_cmqttaccq(void);
result_codes_t at_command_cmqttsslcfg(void);
result_codes_t at_command_cmqttconnect(void);
result_codes_t at_command_cmqtttopic(void);
result_codes_t at_command_cmqttsettopic(void);
result_codes_t at_command_cmqttpayload(void);
result_codes_t at_command_cmqttsetmsgpayload(void);
result_codes_t at_command_cmqttpub(void);
result_codes_t at_command_cmqttdisc(void);
result_codes_t at_command_cmqttrel(void);
result_codes_t at_command_cmqttstop(void);

// Handlers
result_codes_t at_command_basic_handler(const char *response);
result_codes_t at_command_handler_cpin(const char *response);
result_codes_t at_command_handler_csq(const char *response);
result_codes_t at_command_handler_creg_cgreg_cereg(const char *response);
result_codes_t at_command_handler_cpsi(const char *response);
result_codes_t at_command_handler_cgact(const char *response);
result_codes_t at_command_handler_cmqttstart(const char *response);
result_codes_t at_command_handler_cmqttconnect(const char *response);
result_codes_t at_command_handler_cmqtttopic(const char *response);
result_codes_t at_command_handler_cmqttopic_cmqttpay(const char *response);
result_codes_t at_command_handler_cmqttaccq(const char *response);
result_codes_t at_command_handler_cmqttpub(const char *response);
result_codes_t at_command_handler_cmqttdisc(const char *response);
result_codes_t at_command_handler_cmqttrel(const char *response);
result_codes_t at_command_handler_cmqttstop(const char *response);
result_codes_t at_command_handler_cbc(const char *response);
result_codes_t at_command_handler_cpmutemp(const char *response);
result_codes_t at_command_handler_cgsn(const char *response);

// Getters and Setters
double at_command_get_cbc(void);
int at_command_get_cpmutemp(void);
void at_command_set_cbc(double v);
void at_command_set_cpmutemp(int t);
uint8_t *at_command_get_cgsn(void);
void at_command_set_cgsn(uint8_t *ptr);
void at_command_set_apn(uint8_t *ptr);
void at_command_set_payload(uint8_t *ptr);
void at_command_set_mqtt_topic(uint8_t *ptr);
void at_command_set_client(uint8_t *ptr);
void at_command_set_sname(uint8_t *ptr);
void at_command_set_job(uint8_t *ptr);
void at_command_set_topic(uint8_t *ptr);
void at_command_pwrkey_control(void);

#endif  // SIM7600_H