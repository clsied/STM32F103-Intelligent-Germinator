/* USER CODE BEGIN EV */
extern uint8_t hc05_data[1];
extern uint8_t hc05_data_last[1];

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	HAL_UART_Receive_IT(&huart1,hc05_data,1);
  /* USER CODE END USART1_IRQn 1 */
}
