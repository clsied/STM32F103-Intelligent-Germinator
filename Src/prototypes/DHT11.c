uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM, RH, TEMP;
float Temperature = 0;
float Humidity = 0;
uint8_t Presence = 0;
char Temp[4];
char Hum[4];

void delay(uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	while(__HAL_TIM_GET_COUNTER(&htim3) < delay);
}

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT11_Start(void)
{
	Set_Pin_Output(GPIOA,GPIO_PIN_3);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
	delay(20000);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
	delay(30);

}

uint8_t DHT11_Check_Response(void)
{
	int retry = 0;
	Set_Pin_Input(GPIOA,GPIO_PIN_3);
	while((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)) && retry < 100)
	{
		delay(1);
		retry++; // wait for pull down
	}
	if(retry >= 100) return 2; // not response
	else retry = 0;
	while((!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)) && retry < 100)
	{
		delay(1);
		retry++; // wait for pull up
	}
	if(retry >= 100) return 0;
	return 1; // response
}

uint8_t DHT11_Read_Bit(void)  
{

 int retry = 0;

	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) && retry < 100)
	{	
		delay(1); 
		retry++; // wait for pull down
	}
	retry = 0;

	while((!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)) && retry < 100)
	{
		delay(1);
		retry++; // wait for pull up
	}

	delay(40); // wait for data 0 pull down but data 1 pull up

	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3))
		return 1;
	else 
		return 0;   
}

uint8_t DHT11_Read_Byte(void)    
{        
  	uint8_t data = 0;
	for (int i = 0; i < 8; i++) 
	{
		data = data << 1; 
		data = data | DHT11_Read_Bit();
	}    
	return data;
}

void DHT_Read()
{
	DHT11_Start();
	if(DHT11_Check_Response())
	{	
		Rh_byte1=DHT11_Read_Byte();
		Rh_byte2=DHT11_Read_Byte();
		Temp_byte1=DHT11_Read_Byte();
		Temp_byte2=DHT11_Read_Byte();
		SUM=DHT11_Read_Byte();
		Temperature = Temp_byte1;
		Humidity = Rh_byte1;
		snprintf(Temp, sizeof(Temp),"%d",(int)Temperature);
		snprintf(Hum, sizeof(Hum), "%d", (int)Humidity);
	}
}
