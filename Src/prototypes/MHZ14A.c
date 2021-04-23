uint32_t rise = 0;
uint32_t fall = 0;
uint32_t sub = 0;
uint8_t captured = 0;
char mhz14a[4] = {0};

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)

{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){  // if channel3
	
		if (captured==0) // if the rise not captured
		{
			rise = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read the rise
			captured = 1;  // rise is captured
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);// polarity to fall
		}
		else if (captured == 1)   // if rise is captured
		{
			fall = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);  // read the fall
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
			if (fall > rise)
			{
				sub = fall - rise;
			}
			else if (fall < rise)
			{
				sub = 0xFFFF - rise + fall + 1;
			}
			captured = 0; // set capture to false	
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);// polarity to rise
		}
	}
	sprintf(mhz14a,"%d",(int)((float)sub * 0.2));
}
