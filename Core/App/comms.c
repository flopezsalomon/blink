#include "comms.h"

#define RX_BUF_LEN 128
#define RX_TIMEOUT_MS 100

static UART_HandleTypeDef *uart;
static StreamBufferHandle_t rx_buffer;
static uint8_t rx_char;

int comms_init(UART_HandleTypeDef *huart) {
  uart = huart;
  rx_buffer = xStreamBufferCreate(RX_BUF_LEN, 1);
  if (rx_buffer == NULL) {
    return 0;  // Error en la inicialización
  }
  HAL_UART_Receive_IT(uart, &rx_char, 1);

  return 1;
}

int comms_send_line(const char *command) {
  return HAL_UART_Transmit(uart, (uint8_t *)command, (uint16_t)strlen(command),
                           HAL_MAX_DELAY);
}

int comms_recv_line(char *buf, int buf_len, char end_character) {
  int idx = 0;  // indica el numero de caracteres recibido
  HAL_UART_Receive_IT(uart, &rx_char, 1);

  while (idx < buf_len) {
    int recv_len = (int)xStreamBufferReceive(rx_buffer, &buf[idx], 1,
                                             pdMS_TO_TICKS(RX_TIMEOUT_MS));

    // Hubo timeout?
    if (recv_len == 0) return 0;

    // frame termina las líneas con '\n'
    if (idx > 0 && buf[idx] == end_character) break;
    idx++;
  }

  return idx;
}

int comms_flush(void) { return 1; }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART1) {  // Reemplazar según el UART usado
    xStreamBufferSendFromISR(rx_buffer, &rx_char, 1, NULL);
    HAL_UART_Receive_IT(huart, &rx_char, 1);
  }
}