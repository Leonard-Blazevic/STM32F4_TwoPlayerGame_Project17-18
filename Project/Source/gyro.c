#include <main.h>
#include <gyro.h>

void GyroInit () 
{
  L3GD20_InitTypeDef L3GD20_InitStruct;
  L3GD20_FilterConfigTypeDef L3GD20_FilterStruct;

  L3GD20_InitStruct.Power_Mode = L3GD20_MODE_ACTIVE;
  L3GD20_InitStruct.Output_DataRate = L3GD20_OUTPUT_DATARATE_4;						// ODR = 760 Hz
  L3GD20_InitStruct.Axes_Enable = 0x03;																		// enable X and Y axis
  L3GD20_InitStruct.Band_Width = L3GD20_BANDWIDTH_1;											
  L3GD20_InitStruct.BlockData_Update = L3GD20_BlockDataUpdate_Continous;
  L3GD20_InitStruct.Endianness = L3GD20_BLE_LSB;													// Little Endian (default)
  L3GD20_InitStruct.Full_Scale = L3GD20_FULLSCALE_2000;										// 250 dps
  L3GD20_Init(&L3GD20_InitStruct);
  
  L3GD20_FilterStruct.HighPassFilter_Mode_Selection =L3GD20_HPM_NORMAL_MODE_RES;	
  L3GD20_FilterStruct.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_0;						// 7.2 Hz (max)
  L3GD20_FilterConfig(&L3GD20_FilterStruct) ;
  
  L3GD20_FilterCmd(L3GD20_HIGHPASSFILTER_ENABLE);
}


void ReadAngRate(float* GyroData)
{
  uint8_t tmpbuffer[4] ={0};
  int16_t tmpdata[2] = {0};
  int i;
  
	L3GD20_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,4);			
	// L3GD20_OUT_X_L_ADDR = 28h ; read 28h - 2Bh
	// 28h, 29h -> x axis angular rate
	// 2Ah, 2Bh -> y axis angular rate
  
	for(i=0; i<2; i++)
    {
      tmpdata[i]=(int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
			GyroData[i]=(float)tmpdata[i]/L3G_Sensitivity_250dps;
			// divide by sensitivity
    }
}


Direction GetDirection () 
{
	float xangle=0;
	float yangle=0;
	float Buffer[2];
	float xabs, yabs;
	int i;
	
	for (i=0; i<GyroSampleNum; i++) {
		ReadAngRate(Buffer);
		
		xangle+=Buffer[0]/GyroSampleNum;
		yangle+=Buffer[1]/GyroSampleNum;
	}
	
	xabs=fabs(xangle);
	yabs=fabs(yangle);

	if(xabs>=yabs) {
    if (xangle>Xangle_down) return DOWN;
    else if (xangle<Xangle_up) return UP;
    else return NOCHANGE;
	}

	else {
    if (yangle>Yangle_left) return LEFT;
    else if (yangle<Yangle_right) return RIGHT;
    else return NOCHANGE;
	}
}


