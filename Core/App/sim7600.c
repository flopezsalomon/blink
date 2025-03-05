#include "sim7600.h"

sim7600_upkeep_t sim7600_upkeep_values;

sim7600_at_command_t at_commands[] = {
    {"AT+CRESET\r", NULL, at_command_basic_handler, 1000, 0},
    {NULL, NULL, NULL, 1000, 0},  // para funcion dummy
    {"ATE0\r", NULL, at_command_basic_handler, 1000, 0},
    {"AT+CGSN\r", NULL, at_command_handler_cgsn, 1000, 0},
    {"AT+CBC\r", NULL, at_command_handler_cbc, 1000, 0},
    {"AT+CPMUTEMP\r", NULL, at_command_handler_cpmutemp, 1000, 0},
    {"AT+CPIN?\r", NULL, at_command_handler_cpin, 1000, 0},
    {"AT+CSQ\r", NULL, at_command_handler_csq, 1000, 0},
    {"AT+CREG?\r", NULL, at_command_handler_creg_cgreg_cereg, 1000, 0},
    {"AT+CGREG?\r", NULL, at_command_handler_creg_cgreg_cereg, 1000, 0},
    {"AT+CEREG?\r", NULL, at_command_handler_creg_cgreg_cereg, 1000, 0},
    {"AT+CPSI?\r", NULL, at_command_handler_cpsi, 1000, 0},
    {"AT+CGDCONT=1,\"IP\",", sim7600_upkeep_values.apn,
     at_command_basic_handler, 1000, 0},
    {"AT+CGACT=1,1\r", NULL, at_command_basic_handler, 1000, 0},
    {"AT+CGACT?\r", NULL, at_command_handler_cgact, 1000, 0},
    {"AT+CSSLCFG=\"sslversion\",0,4\r", NULL, at_command_basic_handler, 1000,
     0},
    {"AT+CSSLCFG=\"authmode\",0,2\r", NULL, at_command_basic_handler, 1000, 0},
    {"AT+CSSLCFG=\"cacert\",0,\"AmazonRootCA1.pem\"\r", NULL,
     at_command_basic_handler, 1000, 0},
    {"AT+CSSLCFG=\"clientcert\",0,\"device.pem\"\r", NULL,
     at_command_basic_handler, 1000, 0},
    {"AT+CSSLCFG=\"clientkey\",0,\"private.pem\"\r", NULL,
     at_command_basic_handler, 1000, 0},
    {"AT+CMQTTSTART\r", NULL, at_command_handler_cmqttstart, 1000, 0},
    {"AT+CMQTTACCQ=0,", sim7600_upkeep_values.client,
     at_command_handler_cmqttaccq, 1000, 0},
    {"AT+CMQTTSSLCFG=0,0\r", NULL, at_command_basic_handler, 1000, 0},
    {"AT+CMQTTCONNECT=0,\"tcp://"
     "a38me2dorr9eny-ats.iot.us-east-1.amazonaws.com:8883\",60,1\r",
     NULL, at_command_handler_cmqttconnect, 1000, 0},
    {"AT+CMQTTTOPIC=0,", sim7600_upkeep_values.topic_size,
     at_command_handler_cmqttopic_cmqttpay, 1000, 0},
    {(const char *)sim7600_upkeep_values.topic, NULL, at_command_basic_handler,
     1000, 0},
    {"AT+CMQTTPAYLOAD=0,", sim7600_upkeep_values.payload_size,
     at_command_handler_cmqttopic_cmqttpay, 1000, 0},
    {(const char *)sim7600_upkeep_values.payload, NULL,
     at_command_basic_handler, 1000, 0},
    {"AT+CMQTTPUB=0,1,60\r", NULL, at_command_handler_cmqttpub, 1000, 0},
    {"AT+CMQTTDISC=0,120\r", NULL, at_command_handler_cmqttdisc, 1000, 0},
    {"AT+CMQTTREL=0\r", NULL, at_command_handler_cmqttrel, 1000, 0},
    {"AT+CMQTTSTOP\r", NULL, at_command_handler_cmqttstop, 1000, 0}};

/**
 * @brief Executes the AT command to read the voltage value of the power supply.
 */
result_codes_t at_command_cbc(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CBC]));
}

/**
 * @brief Executes the AT command to read the temperature of the module.
 */
result_codes_t at_command_cpmutemp(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CPMUTEMP]));
}

/**
 * @brief Executes the AT command to ask for firmware version.
 */
result_codes_t at_command_cgmr(void) { return 0; }

/**
 * @brief Executes the AT command to ask for IMEI.
 */
result_codes_t at_command_cgsn(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CGSN]));
}

result_codes_t at_command_dummy(void) {
  static int status = 0;
  status = (status + 1) % 100;
  int result = (status == 0) ? OK : WAIT;
  return result;
}

/**
 * @brief Executes the AT command to perform a software reset.
 */
result_codes_t at_command_sreset(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_SRESET]));
}

/**
 * @brief Executes the AT command to test modem connectivity.
 */
result_codes_t at_command_test(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_TEST]));
}

/**
 * @brief Executes the AT command to check the SIM card status.
 */
result_codes_t at_command_cpin(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CPIN]));
}

/**
 * @brief Executes the AT command to get the signal strength.
 */
result_codes_t at_command_csq(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CSQ]));
}

/**
 * @brief Executes the AT command to check the network registration status
 * (2G/3G).
 */
result_codes_t at_command_creg(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CREG]));
}

/**
 * @brief Executes the AT command to check GPRS network registration status.
 */
result_codes_t at_command_cgreg(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CGREG]));
}

/**
 * @brief Executes the AT command to check LTE network registration status.
 */
result_codes_t at_command_cereg(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CEREG]));
}

/**
 * @brief Executes the AT command to retrieve cellular system information.
 */
result_codes_t at_command_cpsi(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CPSI]));
}

/**
 * @brief Executes the AT command to configure the APN.
 */
result_codes_t at_command_cgdcont(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CGDCONT]));
}

/**
 * @brief Executes the AT command to activate a PDP data context.
 */
result_codes_t at_command_cgact(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CGACT]));
}

/**
 * @brief Executes the AT command to query the activation status of a PDP
 * context.
 */
result_codes_t at_command_cgact_q(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CGACT_Q]));
}

/**
 * @brief Executes the AT command to set ssl version.
 */
result_codes_t at_command_csslcfg_sslver(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CSSLCFG_SSLVER]));
}

/**
 * @brief Executes the AT command to set auth mode.
 */
result_codes_t at_command_csslcfg_auth(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CSSLCFG_AUTH]));
}

/**
 * @brief Executes the AT command to set ca cert.
 */
result_codes_t at_command_csslcfg_cacert(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CSSLCFG_CACERT]));
}

/**
 * @brief Executes the AT command to set client cert.
 */
result_codes_t at_command_csslcfg_clientcert(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CSSLCFG_CLIENTCERT]));
}

/**
 * @brief Executes the AT command to set ssl version.
 */
result_codes_t at_command_csslcfg_clientkey(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CSSLCFG_CLIENTKEY]));
}

/**
 * @brief Executes the AT command to start the MQTT service.
 */
result_codes_t at_command_cmqttstart(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTSTART]));
}

/**
 * @brief Executes the AT command to set the MQTT client.
 */
result_codes_t at_command_cmqttaccq(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTACCQ]));
}

/**
 * @brief Executes the AT command to set the first SSL context to be used in the
 * SSL connection.
 */
result_codes_t at_command_cmqttsslcfg(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTSSLCFG]));
}

/**
 * @brief Executes the AT command to connect to an MQTT broker.
 */
result_codes_t at_command_cmqttconnect(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTCONNECT]));
}

/**
 * @brief Executes the AT command to define the MQTT topic.
 */
result_codes_t at_command_cmqtttopic(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTTOPIC]));
}

/**
 * @brief Set the topic name.
 */
result_codes_t at_command_cmqttsettopic(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTSETTOPIC]));
}

/**
 * @brief Executes the AT command to define the MQTT payload.
 */
result_codes_t at_command_cmqttpayload(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTPAYLOAD]));
}

/**
 * @brief set the message that will be published.
 */
result_codes_t at_command_cmqttsetmsgpayload(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTSETMSGPAYLOAD]));
}

/**
 * @brief Executes the AT command to publish an MQTT message.
 */
result_codes_t at_command_cmqttpub(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTPUB]));
}

/**
 * @brief Executes the AT command to disconnect from the MQTT broker.
 */
result_codes_t at_command_cmqttdisc(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTDISC]));
}

/**
 * @brief Executes the AT command to release the MQTT client.
 */
result_codes_t at_command_cmqttrel(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTREL]));
}

/**
 * @brief Executes the AT command to stop the MQTT service.
 */
result_codes_t at_command_cmqttstop(void) {
  return (sim7600_comm_handler(&at_commands[AT_CMD_CMQTTSTOP]));
}

result_codes_t at_command_basic_handler(const char *response) {
  int result = -1;
  if (strncmp("OK\r\n", response, 4) == 0) {
    result = OK;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }

  return result;
}

result_codes_t at_command_handler_cpin(const char *response) {
  int result = -1;
  if (strncmp("+CPIN: READY\r\n", response, 14) == 0) {
    result = OK;
  } else if (strcmp("ERROR\r\n", response) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }

  return result;
}

result_codes_t at_command_handler_csq(const char *response) {
  int signal_strength, error_rate, result;
  if (sscanf(response, "+CSQ: %d,%d", &signal_strength, &error_rate) != 0) {
    if (signal_strength >= 10 && signal_strength <= 31) {  // good signal
      result = OK;

    } else if (signal_strength >= 2 && signal_strength < 10) {  // week
      result = WAIT;
    } else {
      result = FAIL;  // bad signal or not enough
    }
  } else if (strcmp("ERROR\r\n", response) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }

  return result;
}

result_codes_t at_command_handler_creg_cgreg_cereg(const char *response) {
  int mode, status, result;
  if ((sscanf(response, "+CREG: %d,%d", &mode, &status) == 2) ||
      (sscanf(response, "+CGREG: %d,%d", &mode, &status) == 2) ||
      (sscanf(response, "+CEREG: %d,%d", &mode, &status) == 2)) {
    switch (status) {
      case 0:  // Registro denegado
      case 3:  // Estado desconocido
      case 4:  // No registrado, el módem no está intentando conectarse
      case 6:
      case 7:
      case 8:
        result = FAIL;
        break;
      case 1:  // Registrado en la red doméstica
      case 5:  // Registrado en una red de roaming
        result = OK;
        break;
      case 2:  // No registrado, pero el módem está intentando conectarse
        result = WAIT;
        break;
      default:  // Estado de registro desconocido
        result = FAIL;
        break;
    }
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }
  return result;
}

result_codes_t at_command_handler_cpsi(const char *response) { return 0; }

result_codes_t at_command_handler_cgact(const char *response) {
  /*Indicates the state of PDP context activation:
  0 – deactivated
  1 – activated*/

  int state, cid, result;
  if ((sscanf(response, "+CGACT: %d,%d", &state, &cid) == 2)) {
    switch (state) {
      case 0:
        result = FAIL;  // fail
        break;
      case 1:
        result = OK;  // return OK state.
        break;

      default:
        break;
    }
  } else {
    result = WAIT;
  }
  return result;
}

result_codes_t at_command_handler_cmqttstart(const char *response) {
  int err, result;
  if ((sscanf(response, "+CMQTTSTART: %d", &err) == 1)) {
    switch (err) {
      case 0:         // success
        result = OK;  // return OK state
        break;

      default:          // any other value means error
        result = FAIL;  // return FAIL state
        break;
    }
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }
  return result;
}
result_codes_t at_command_handler_cmqttconnect(const char *response) {
  int client_index, err, result;
  if ((sscanf(response, "+CMQTTCONNECT: %d,%d", &client_index, &err) == 2)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }
  return result;
}

result_codes_t at_command_handler_cmqttopic_cmqttpay(const char *response) {
  int client_index, err, result;
  if (strncmp(">", response, 1) == 0) {
    result = OK;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else if ((sscanf(response, "+CMQTTTOPIC: %d,%d", &client_index, &err) ==
              2)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else {
    result = WAIT;  // wait
  }
  return result;
}

result_codes_t at_command_handler_cmqttaccq(const char *response) {
  int client_index, err, result;
  if (strncmp("OK", response, 2) == 0) {
    result = OK;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else if ((sscanf(response, "+CMQTTACCQ: %d,%d", &client_index, &err) ==
              2)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else {
    result = WAIT;  // wait
  }
  return result;
}

result_codes_t at_command_handler_cmqttpub(const char *response) {
  int client_index, err, result;
  if (strncmp("OK", response, 2) == 0) {
    result = WAIT;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = 1;
  } else if ((sscanf(response, "+CMQTTPUB: %d,%d", &client_index, &err) == 2)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else {
    result = WAIT;  // wait
  }
  return result;
}

result_codes_t at_command_handler_cmqttdisc(const char *response) {
  int client_index, err, result;
  if (strncmp("OK", response, 2) == 0) {
    result = WAIT;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else if ((sscanf(response, "+CMQTTDISC: %d,%d", &client_index, &err) ==
              2)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else {
    result = WAIT;  // wait
  }
  return result;
}

result_codes_t at_command_handler_cmqttrel(const char *response) {
  int client_index, err, result;
  if (strncmp("OK", response, 2) == 0) {
    result = OK;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else if ((sscanf(response, "+CMQTTREL: %d,%d", &client_index, &err) == 2)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else {
    result = WAIT;  // wait
  }
  return result;
}

result_codes_t at_command_handler_cmqttstop(const char *response) {
  int err, result;
  if (strncmp("OK", response, 2) == 0) {
    result = WAIT;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else if ((sscanf(response, "+CMQTTSTOP: %d", &err) == 1)) {
    switch (err) {
      case 0:
        result = OK;
        break;

      default:
        result = FAIL;
        break;
    }
  } else {
    result = WAIT;  // wait
  }
  return result;
}

result_codes_t at_command_handler_cbc(const char *response) {
  int result;
  double volt;
  uint8_t volt_str[6];

  if ((sscanf(response, "+CBC: %15[^V]V", volt_str) == 1)) {
    volt = atof((const char *)volt_str);
    at_command_set_cbc(volt);  // guardar valor de volt
    result = OK;
  } else if (strncmp("OK\r\n", response, 4) == 0) {
    result = WAIT;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }

  return result;
}

result_codes_t at_command_handler_cpmutemp(const char *response) {
  int temp, result;
  if ((sscanf(response, "+CPMUTEMP: %d", &temp) == 1)) {
    at_command_set_cpmutemp(temp);  // guardar valor de temp
    result = OK;
  } else if (strncmp("OK\r\n", response, 4) == 0) {
    result = WAIT;
  } else if (strncmp("ERROR\r\n", response, 7) == 0) {
    result = FAIL;
  } else {
    result = WAIT;
  }

  return result;
}

result_codes_t at_command_handler_cgsn(const char *response) {
  int i = 0;
  if (response[0] == '\0' || response[0] == '\r' || response[0] == '\n') {
    return WAIT;  // Cadena vacía no es numérica o comienza con \r o \n
  }
  while (i < 15) {
    if (response[i] < '0' || response[i] > '9') {
      return FAIL;  // Carácter no numérico encontrado
    }
    i++;
  }
  at_command_set_cgsn((uint8_t *)response);  // guardar sn
  return OK;
}

double at_command_get_cbc(void) { return sim7600_upkeep_values.volt; }

void at_command_set_cbc(double v) { sim7600_upkeep_values.volt = v; }

int at_command_get_cpmutemp(void) { return sim7600_upkeep_values.temp; }

void at_command_set_cpmutemp(int t) { sim7600_upkeep_values.temp = t; }

uint8_t *at_command_get_cgsn(void) { return (&sim7600_upkeep_values.sn[0]); }

void at_command_set_cgsn(uint8_t *ptr) {
  memcpy(sim7600_upkeep_values.sn, ptr, 15);
  sim7600_upkeep_values.sn[15] = '\0';
  at_command_set_client(sim7600_upkeep_values.sn);
  at_command_set_topic(sim7600_upkeep_values.sn);
}

void at_command_set_apn(uint8_t *ptr) {
  // atajar aca posible error de largo, que no exceda valor de tamano de buffer
  // apn
  sim7600_upkeep_values.apn[0] = '"';
  memcpy(&sim7600_upkeep_values.apn[1], ptr, strlen((const char *)ptr));
  sim7600_upkeep_values.apn[strlen((const char *)ptr) + 1] = '"';
  sim7600_upkeep_values.apn[strlen((const char *)ptr) + 2] = '\r';
  sim7600_upkeep_values.apn[strlen((const char *)ptr) + 3] = '\0';
}

void at_command_set_payload(uint8_t *ptr) {
  int lenght = snprintf(sim7600_upkeep_values.payload_size, 8, "%d",
                        strlen((const char *)ptr));
  sim7600_upkeep_values.payload_size[lenght] = '\r';
  sim7600_upkeep_values.payload_size[lenght + 1] = '\0';
  memcpy(sim7600_upkeep_values.payload, ptr, strlen((const char *)ptr));
  sim7600_upkeep_values.payload[strlen((const char *)ptr) + 1] = '\0';
}

void at_command_set_sname(uint8_t *ptr) {
  memcpy(sim7600_upkeep_values.topic, ptr, strlen((const char *)ptr));
  sim7600_upkeep_values.topic[strlen((const char *)ptr)] = '/';
  sim7600_upkeep_values.topic[strlen((const char *)ptr) + 1] = '\0';
}

void at_command_set_job(uint8_t *ptr) {
  int hlength = strlen(sim7600_upkeep_values.topic);
  memcpy(&sim7600_upkeep_values.topic[hlength], ptr, strlen((const char *)ptr));
  sim7600_upkeep_values.topic[4 + strlen((const char *)ptr)] = '/';
  sim7600_upkeep_values.topic[4 + strlen((const char *)ptr) + 1] = '\0';
}

void at_command_set_topic(uint8_t *ptr) {
  int i = 0;
  for (i = 4; i < sizeof(sim7600_upkeep_values.topic); i++) {
    if (sim7600_upkeep_values.topic[i] == '/') {
      break;
    }
  }

  int joblength = i;  // strlen((const char *)sim7600_upkeep_values.topic);
  int snlength = strlen((const char *)ptr);

  memcpy(&sim7600_upkeep_values.topic[joblength + 1], ptr, snlength);
  sim7600_upkeep_values.topic[joblength + snlength + 1] = '\0';

  int topiclenght = snprintf(sim7600_upkeep_values.topic_size, 5, "%d",
                             strlen((const char *)sim7600_upkeep_values.topic));
  sim7600_upkeep_values.topic_size[topiclenght] = '\r';
  sim7600_upkeep_values.topic_size[topiclenght + 1] = '\0';
}

void at_command_set_client(uint8_t *ptr) {
  sim7600_upkeep_values.client[0] = '"';
  memcpy(&sim7600_upkeep_values.client[1], ptr, strlen((const char *)ptr));
  sim7600_upkeep_values.client[strlen((const char *)ptr) + 1] = '"';
  sim7600_upkeep_values.client[strlen((const char *)ptr) + 2] = ',';
  sim7600_upkeep_values.client[strlen((const char *)ptr) + 3] =
      '1';  // indica sesion mqtt(s)
  sim7600_upkeep_values.client[strlen((const char *)ptr) + 4] = '\r';
  sim7600_upkeep_values.client[strlen((const char *)ptr) + 5] = '\0';
}

void at_command_pwrkey_control(void) {}