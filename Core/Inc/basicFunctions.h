#ifndef BASICFUNCTIONS_H
#define BASICFUNCTIONS_H

#include "define.h"

//Interrupts
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // If the interrupt is triggered by channel 1
			{
		// Read the IC value
		ICValue_Ch1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

		if (ICValue_Ch1 != 0) {
			// calculate the Duty Cycle
			float Duty = (HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2) * 100)
					/ ICValue_Ch1;
			F_Ch1 = 90000000 / ICValue_Ch1;
			Duty_Ch1 = (Freq_Radio * Duty) / F_Ch1;

		}
	}
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) // If the interrupt is triggered by channel 2
			{
		// Read the IC value
		ICValue_Ch2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

		if (ICValue_Ch2 != 0) {
			// calculate the Duty Cycle
			float Duty = 100
					- (HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1) * 100)
							/ ICValue_Ch1;
			F_Ch2 = 90000000 / ICValue_Ch2;
			Duty_Ch2 = (Freq_Radio * Duty) / F_Ch2;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == SLFL_Pin) {
		tag_line_front_l = 1;
		controlMotor(-100, -100);
	}
	if (GPIO_Pin == SLFR_Pin) {
		tag_line_front_r = 1;
		controlMotor(-100, -100);
	}
	/*if (GPIO_Pin == SLBL_Pin) {
	 tag_line_back_r = 1;
	 controlMotor(0, 0);
	 }
	 if (GPIO_Pin == SLBL_Pin) {
	 tag_line_back_r = 1;
	 controlMotor(0, 0);
	 }*/
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	temp = HAL_ADC_GetValue(&hadc1);
	/*If continuousconversion mode is DISABLED uncomment below*/
	HAL_ADC_Start_IT(&hadc1);
}

//read Functions

void readSensors() { //lê sensores
	busca = 0;
	busca = busca | (!HAL_GPIO_ReadPin(GPIOB, SLL_Pin) << 0);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOB, SDL_Pin) << 1);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOB, SD2L_Pin) << 2);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOB, SFL_Pin) << 3);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOB, SFS_Pin) << 4);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOC, SFR_Pin) << 5);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOA, SD2R_Pin) << 6);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOA, SDR_Pin) << 7);
	busca = busca | (!HAL_GPIO_ReadPin(GPIOB, SLR_Pin) << 8);

	/*sensors[0] = !HAL_GPIO_ReadPin(GPIOB, SLL_Pin);
	 sensors[1] = !HAL_GPIO_ReadPin(GPIOB, SDL_Pin);
	 sensors[2] = !HAL_GPIO_ReadPin(GPIOB, SD2L_Pin);
	 sensors[3] = !HAL_GPIO_ReadPin(GPIOB, SFL_Pin);
	 sensors[4] = !HAL_GPIO_ReadPin(GPIOB, SFS_Pin);
	 sensors[5] = !HAL_GPIO_ReadPin(GPIOC, SFR_Pin);
	 sensors[6] = !HAL_GPIO_ReadPin(GPIOA, SD2R_Pin);
	 sensors[7] = !HAL_GPIO_ReadPin(GPIOA, SDR_Pin);
	 sensors[8] = !HAL_GPIO_ReadPin(GPIOB, SLR_Pin);
	 busca = 0;
	 for (int i = 0; i < 9; i++) {
	 busca = busca + sensors[i] * pow(2, i);
	 }*/
}

/*uint8_t readIR() { //1-4 2-15 3-14 cima-31 baixo-42 enter-35
 float delta = 0;
 float tempo = 0;
 while (HAL_GPIO_ReadPin(GPIOC, SF_Pin))
 ; // wait for the pin to go low
 tempo = HAL_GetTick();
 while (!HAL_GPIO_ReadPin(GPIOC, SF_Pin))
 ; // wait for the pin to go high
 delta = HAL_GetTick() - tempo;
 uint8_t data = 0;

 if (delta >= 2) {

 for (int i = 0; i < 12; i++) {
 int count = 0;
 while ((HAL_GPIO_ReadPin(GPIOC, SF_Pin)))
 ; //

 while (!(HAL_GPIO_ReadPin(GPIOC, SF_Pin))) {
 count++;
 }
 if (count >= 2300) // if the space is more than 1.2 ms
 {
 data = data + 1 * (11 - i);
 }

 }
 //printf("\n");
 } else {
 data = 255;
 }
 //HAL_Delay(45);
 return (data);
 }*/

//display Functions
void printSensors() {
	readSensors();

	char str[5];

	sprintf(str, "%03i", busca);
	SSD1306_GotoXY(10, 10);
	SSD1306_Puts(str, &Font_11x18, 1);
	SSD1306_UpdateScreen();

}

void calibrateLinesensor() {
	SSD1306_GotoXY(10, 10);
	SSD1306_Putc(HAL_GPIO_ReadPin(GPIOC, SLFL_Pin) + '0', &Font_11x18, 1);
	SSD1306_Putc(HAL_GPIO_ReadPin(GPIOC, SLFR_Pin) + '0', &Font_11x18, 1);
	//SSD1306_Putc(HAL_GPIO_ReadPin(GPIOC, SLBL_Pin) + '0', &Font_11x18, 1);
	//SSD1306_Putc(HAL_GPIO_ReadPin(GPIOC, SLBR_Pin) + '0', &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

/*void calibrateRadio(float max, float min, char ch) {
 float ant = 7.5; //motor stopped
 float curr; //motor stopped
 SSD1306_GotoXY(10, 10);
 SSD1306_Putc(ch, &Font_11x18, 1);
 SSD1306_UpdateScreen();
 HAL_GPIO_WritePin(GPIOA, LED_Pin, 0);
 HAL_Delay(3000);
 for (int i; i < 1000; i++) {
 curr = Duty_Ch2;
 if (curr > ant)
 max = curr;
 else
 max = ant;
 ant = curr;
 }
 HAL_GPIO_WritePin(GPIOA, LED_Pin, 1);
 HAL_Delay(1000);
 for (int i; i < 1000; i++) {
 curr = Duty_Ch2;
 if (curr < ant)
 min = curr;
 else
 min = ant;
 ant = curr;
 }
 HAL_GPIO_WritePin(GPIOA, LED_Pin, 0);
 }*/

//move Functions
void controlMotor(int velL, int velR) {
	velL = map(velL, 100, -100, 60, 100);
	velR = map(velR, 100, -100, 60, 100);
	htim1.Instance->CCR3 = velR;
	htim1.Instance->CCR1 = velL;
}

void driveMotorsRC() {
	// calculo baseado na frequencia CCR/AAR*100=duty
	if (tag_line_front_l || tag_line_front_r) {
		lineEscape();
	} else {
		vel = map(Duty_Ch1 * 10, 100, 60, 100, -100);
		omega = map(Duty_Ch2 * 10, 100, 60, 100, -100);
		vL = vel - omega;
		vR = vel + omega;
		vL = map(vL, 100, -100, 60, 100);
		vR = map(vR, 100, -100, 60, 100);
		htim1.Instance->CCR3 = vL;
		htim1.Instance->CCR1 = vR;
	}
}
void seteMaisPerfeitoEsquerda() {
	for (int i = 40; i <= 100; i += 20) {
		controlMotor(i * -1, i);
		HAL_Delay(10);
	}
	HAL_Delay(55);
	controlMotor(0, 0);
	HAL_Delay(60);
	controlMotor(100, 100);
	HAL_Delay(130);
	controlMotor(0, 0);
	HAL_Delay(50);
	controlMotor(100, -100);
	HAL_Delay(10);
	controlMotor(0, 0);
}
void seteMaisPerfeitoDireita() {
	for (int i = 40; i <= 100; i += 20) {
		controlMotor(i, i * -1);
		HAL_Delay(10);
	}
	HAL_Delay(55);
	controlMotor(0, 0);
	HAL_Delay(60);
	controlMotor(100, 100);
	HAL_Delay(140);
	controlMotor(0, 0);
	HAL_Delay(20);
	controlMotor(-100, 100);
	HAL_Delay(10);
	controlMotor(0, 0);
}

void setePerfeitoEsquerda() {
	for (int i = 40; i <= 100; i += 20) {
		controlMotor(i * -1, i);
		HAL_Delay(10);
	}
	HAL_Delay(30);
	/*controlMotor(-100, 100);
	 HAL_Delay(35);*/
	controlMotor(0, 0);
	HAL_Delay(50);
	controlMotor(100, 100);
	HAL_Delay(130);
	controlMotor(0, 0);
	HAL_Delay(30);
	controlMotor(100, -100);
	HAL_Delay(30);
	controlMotor(0, 0);
}

void setePerfeitoDireita() {
	for (int i = 40; i <= 100; i += 20) {
		controlMotor(i, i * -1);
		HAL_Delay(10);
	}
	HAL_Delay(30);
	controlMotor(0, 0);
	HAL_Delay(60);
	controlMotor(100, 100);
	HAL_Delay(130);
	controlMotor(0, 0);
	HAL_Delay(20);
	controlMotor(-100, 100);
	HAL_Delay(30);
	controlMotor(0, 0);
}
void seteLinha() {
	controlMotor(100, 100);
	HAL_Delay(120);
	while ((!tag_line_front_l || !tag_line_front_r)
			&& (HAL_GPIO_ReadPin(GPIOA, IR_Pin))) {
		controlMotor(65, 65);
	}
	lineEscape();
	controlMotor(0, 0);
}
void frente() {
	controlMotor(100, 100);
	HAL_Delay(120);
}
void frenteVendo() {
	controlMotor(100, 100);
	tempo = HAL_GetTick();
	while (HAL_GetTick() - tempo < 120) {
		readSensors();
		if (busca != 0)
			break;
	}
}
void desempate() {
	controlMotor(-100, 100);
	HAL_Delay(70);
	controlMotor(0, 0);
	HAL_Delay(30);
}

void seteEsquerda() {
	frente();
	for (int i = 40; i <= 100; i += 20) {
		controlMotor(i, i * -1);
		HAL_Delay(10);
	}
	HAL_Delay(20);

}
void seteDireita() {
	frente();
	for (int i = 40; i <= 100; i += 20) {
		controlMotor(i * -1, i);
		HAL_Delay(10);
	}
	HAL_Delay(20);

}
void inicialMoviment() {
	switch (routine_ini) {
	case 0: //parado + tranquinho
		controlMotor(0, 0);
		routine_search = 0;
		break;
	case 1: //parado + linha
		controlMotor(0, 0);
		routine_search = 1;
		break;
	case 2: //parado + nheconheco
		controlMotor(0, 0);
		routine_search = 2;
		break;
	case 3: //frente + tranquinho
		frente();
		routine_search = 0;
		break;
	case 4: //frente + linha
		frente();
		routine_search = 1;
		break;
	case 5: //frente + nheconheco
		frente();
		routine_search = 2;
		break;
	case 6: //sete esquerda + tranquinho
		setePerfeitoEsquerda();
		routine_search = 0;
		break;
	case 7: //sete esquerda + linha
		setePerfeitoEsquerda();
		routine_search = 1;
		break;
	case 8: //sete esquerda + nheconheco
		setePerfeitoEsquerda();
		routine_search = 2;
		break;
	case 9: //sete direita + tranquinho
		setePerfeitoDireita();
		routine_search = 0;
		break;
	case 10: //sete direita + linha
		setePerfeitoDireita();
		routine_search = 1;
		break;
	case 11: //sete direita + nheconheco
		setePerfeitoDireita();
		routine_search = 2;
		break;
	case 12: //sete esquerda mqp + tranquinho
		seteMaisPerfeitoEsquerda();
		routine_search = 0;
		break;
	case 13: //sete esquerda mqp + linha
		seteMaisPerfeitoEsquerda();
		routine_search = 1;
		break;
	case 14: //sete esquerda mqp + nheconheco
		seteMaisPerfeitoEsquerda();
		routine_search = 2;
		break;
	case 15: //sete direita mqp + tranquinho
		seteMaisPerfeitoDireita();
		routine_search = 0;
		break;
	case 16: //sete direita mqp + linha
		seteMaisPerfeitoDireita();
		routine_search = 1;
		break;
	case 17: //sete direita mqp + nheconheco
		seteMaisPerfeitoDireita();
		routine_search = 2;
		break;
	case 18: // desempate
		desempate();
		routine_search = 0;
		break;
	case 19: //frente vendo + tranquinho
		frenteVendo();
		routine_search = 0;
		break;
	case 20: //frente vendo + linha
		frenteVendo();
		routine_search = 1;
		break;
	case 21: //frente vendo + nheconheco
		frenteVendo();
		routine_search = 2;
	case 22: //sete esquerda + tranquinho
		seteEsquerda();
		routine_search = 0;
		break;
	case 23: //sete esquerda + linha
		seteEsquerda();
		routine_search = 1;
		break;
	case 24: //sete esquerda+ nheconheco
		seteEsquerda();
		routine_search = 2;
	case 25: //sete esquerda + tranquinho
		seteDireita();
		routine_search = 0;
		break;
	case 26: //sete esquerda + linha
		seteDireita();
		routine_search = 1;
		break;
	case 27: //sete esquerda+ nheconheco
		seteDireita();
		routine_search = 2;

	default:
		break;
	}
}

//search Functions
void tranquinho() {
	if (tag_line_front_l || tag_line_front_r) {
		if (tag_line_front_l && !tag_line_front_r && !tagliner) {
			controlMotor(-100, -100);
			HAL_Delay(15);
			controlMotor(100, -100);
			HAL_Delay(65);
			taglinel = 1;

		} else if (!tag_line_front_l && tag_line_front_r && !taglinel) {
			controlMotor(-100, -100);
			HAL_Delay(15);
			controlMotor(-100, 100);
			HAL_Delay(65);
			tagliner = 1;

		} else if (tag_line_front_l && tag_line_front_r) {
			controlMotor(-100, -100);
			HAL_Delay(15);
			controlMotor(100, -100);
			HAL_Delay(70);
		}
		tag_line_front_l = 0;
		tag_line_front_r = 0;

	} else {
		controlMotor(0, 0);
		HAL_Delay(40);
		taglinel = 0;
		tagliner = 0;
		controlMotor(100, 100);
		HAL_Delay(25);
		tempo = HAL_GetTick();
		while (HAL_GetTick() - tempo < 2500 && !tag_line_front_l
				&& !tag_line_front_r) {
			controlMotor(0, 0);
			readSensors();
			if (busca != 0)
				break;
		}
	}
}
void nhecoNheco() {
	if (tag_line_front_l || tag_line_front_r) {
		if (tag_line_front_l && !tag_line_front_r && !tagliner) {
			controlMotor(-100, -100);
			HAL_Delay(15);
			controlMotor(100, -100);
			HAL_Delay(65);
			taglinel = 1;

		} else if (!tag_line_front_l && tag_line_front_r && !taglinel) {
			controlMotor(-100, -100);
			HAL_Delay(15);
			controlMotor(-100, 100);
			HAL_Delay(65);
			tagliner = 1;

		} else if (tag_line_front_l && tag_line_front_r) {
			controlMotor(-100, -100);
			HAL_Delay(15);
			controlMotor(100, -100);
			HAL_Delay(70);
		}
		tag_line_front_l = 0;
		tag_line_front_r = 0;

	} else {
		if (var_nheco) {
			controlMotor(100, 100);
		} else {
			controlMotor(-80, -80);
		}

		HAL_Delay(25);
		tempo = HAL_GetTick();
		while (HAL_GetTick() - tempo < 2500 && !tag_line_front_l
				&& !tag_line_front_r) {
			controlMotor(0, 0);
			readSensors();
			if (busca != 0)
				break;
		}
		var_nheco = !var_nheco;
	}

}

void basicSearch(int velAvc, int velBaixa, int velMedia, int velAlta) {
	if (!HAL_GPIO_ReadPin(GPIOB, SFS_Pin)) {
		if (flagfront < 50) {
			controlMotor(velAvc * 0.6, velAvc * 0.6);
			flagfront++;
		} else if ((flagfront >= 50) && (flagfront < 200)) {
			controlMotor(velAvc * 0.7, velAvc * 0.7);
			flagfront++;
		} else if ((flagfront >= 200) && (flagfront < 350)) {
			controlMotor(velAvc * 0.8, velAvc * 0.8);
			flagfront++;
		} else if (flagfront >= 350) {
			controlMotor(velAvc, velAvc);
		}
		//controlMotor(velAvc, velAvc);
	} else {
		switch (busca) {
		case 0:
			//default_search = 0;
			//busca
			switch (routine_search) {
			case 0:
				//controlMotor(0, 0);
				tranquinho();
				break;
			case 1:
				lineSearch();
				break;
			case 2:
				nhecoNheco();
				break;
			default:
				tranquinho();
				break;
			}
			flagfront = 0;
			break;
		case 1:
			// Lateral Left
			controlMotor(-velAlta, velAlta);
			flagfront = 0;
			break;
		case 3:
			// Lateral Left + Diagonal Left
			controlMotor(-velMedia, velMedia);
			flagfront = 0;
			break;
		case 2:
			// Diagonal Left
			controlMotor(-velMedia, velMedia);
			flagfront = 0;
			break;
		case 6:
			// Diagonal Left + Second Diagonal Left
			controlMotor(-velBaixa, velMedia);
			flagfront = 0;
			break;
		case 4:
			// Second Diagonal Left
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;
		case 7:
			// Lateral Left + Diagonal Left + Second Diagonal Left
			controlMotor(-velBaixa, velMedia);
			flagfront = 0;
			break;
		case 8:
			// Front Left
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;
		case 12:
			// Second Diagonal Left + Frontal Left
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;
		case 14:
			// Diagonal Left + Second Diagonal Left + Frontal Left
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;
		case 15:
			// Lateral Left + Diagonal Left + Second Diagonal Left + Frontal Left
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;

			/*case 16:
			 // Front
			 if (routine_ini == 12)
			 controlMotor(velAvc, velAvc);
			 else {
			 controlMotor(0, 0);
			 flagfront++;
			 if (flagfront >= 500) {
			 controlMotor(100, 100);
			 HAL_Delay(15);
			 }
			 flagfront = 0;
			 }
			 break;
			 case 56:
			 // All Front
			 if (routine_ini == 12)
			 controlMotor(velAvc, velAvc);
			 else {
			 controlMotor(0, 0);
			 flagfront++;
			 if (flagfront >= 500) {
			 controlMotor(100, 100);
			 HAL_Delay(15);
			 }
			 flagfront = 0;
			 }
			 break;*/
		case 24:
			// Frontal Left + Frontal
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;
		case 28:
			// Second Diagonal Left + Frontal Left + Frontal
			controlMotor(-velBaixa, velBaixa);
			flagfront = 0;
			break;
		case 256:
			// Lateral Right
			controlMotor(velAlta, -velAlta);
			flagfront = 0;
			break;
		case 384:
			// Lateral Right + Diagonal Right
			controlMotor(velMedia, -velBaixa);
			flagfront = 0;
			break;
		case 128:
			// Diagonal Right
			controlMotor(velMedia, -velBaixa);
			flagfront = 0;
			break;
		case 192:
			// Diagonal Right + Second Diagonal Right
			controlMotor(velMedia, -velBaixa);
			flagfront = 0;
			break;
		case 64:
			// Second Diagonal Right
			controlMotor(velMedia, -velBaixa);
			flagfront = 0;
			break;
		case 448:
			// Lateral Right + Diagonal Right + Second Diagonal Right
			controlMotor(velMedia, -velBaixa);
			flagfront = 0;
			break;
		case 32:
			// Front Right
			controlMotor(velBaixa, -velBaixa);
			flagfront = 0;
			break;
		case 96:
			// Second Diagonal Right + Frontal Right
			controlMotor(velBaixa, -velBaixa);
			flagfront = 0;
			break;
		case 224:
			// Diagonal Right + Second Diagonal Right + Frontal Right
			controlMotor(velBaixa, -velBaixa);
			flagfront = 0;
			break;
		case 480:
			// Lateral Right + Diagonal Right + Second Diagonal Right + Frontal Right
			controlMotor(velBaixa, -velBaixa);
			flagfront = 0;
			break;
		case 48:
			// Frontal Right + Frontal
			controlMotor(velBaixa, -velBaixa);
			flagfront = 0;
			break;
		case 112:
			// Second Diagonal Right + Frontal Right + Frontal
			controlMotor(velBaixa, -velBaixa);
			flagfront = 0;
			break;
		default:
			controlMotor(0, 0);
			/*default_search = 1;
			 switch (routine_search) {
			 case 0:
			 //controlMotor(0, 0);
			 tranquinho();
			 break;
			 case 1:
			 lineSearch();
			 break;
			 case 2:
			 nhecoNheco();
			 break;
			 default:
			 tranquinho();
			 break;
			 }*/
			break;

		}
	}
}

void lineEscape() {
	if (tag_line_front_l && !tag_line_front_r && !tagliner) {
		controlMotor(-100, -100);
		HAL_Delay(75);
		controlMotor(0, 0);
		HAL_Delay(30);
		for (int i = 40; i <= 100; i += 20) {
			controlMotor(i, i * -1);
			HAL_Delay(10);
		}
		HAL_Delay(50);
		taglinel = 1;

	} else if (!tag_line_front_l && tag_line_front_r && !taglinel) {
		controlMotor(-100, -100);
		HAL_Delay(75);
		controlMotor(0, 0);
		HAL_Delay(20);
		for (int i = 40; i <= 100; i += 20) {
			controlMotor(i * -1, i);
			HAL_Delay(10);
		}
		HAL_Delay(50);
		tagliner = 1;

	} else if (tag_line_front_l && tag_line_front_r) {
		controlMotor(-100, -100);
		HAL_Delay(85);
		controlMotor(0, 0);
		HAL_Delay(30);
		for (int i = 40; i <= 100; i += 20) {
			controlMotor(i * -1, i);
			HAL_Delay(10);
		}
		HAL_Delay(60);

	}
	tag_line_front_l = 0;
	tag_line_front_r = 0;
}

void lineSearch() {
	if (tag_line_front_l || tag_line_front_r) {
		lineEscape();
	} else {
		controlMotor(60, 60);
		tagliner = 0;
		taglinel = 0;
	}
}

//routine Functions
void selectIniRoutine() {
	char str[11];
	while (Duty_Ch2 > 7) {
		if (Duty_Ch1 > 9.5) {
			routine_ini++;
			HAL_Delay(50);
		} else if (Duty_Ch1 <= 6) {
			routine_ini--;
			HAL_Delay(50);
		}
		if (routine_ini >= 40)
			routine_ini = 0;
		sprintf(str, "Rotina: %02i", routine_ini);
		SSD1306_GotoXY(10, 10);
		SSD1306_Puts(str, &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}
	/*while (IR != 35) {
	 IR = readIR();
	 //printf("%i\n",IR);
	 if (IR == 31)
	 routine_ini++;
	 else if (IR == 42)
	 routine_ini--;
	 if (routine_ini >= 5)
	 routine_ini = 0;
	 SSD1306_GotoXY(10, 10);
	 SSD1306_Puts("Rotina I:", &Font_11x18, 1);
	 SSD1306_GotoXY(10, 30);
	 SSD1306_Putc(routine_ini + '0', &Font_11x18, 1);
	 SSD1306_UpdateScreen();

	 }*/
}

// basic functions
float map(float x, float in_max, float in_min, float out_max, float out_min) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif /* BASICFUNCTIONS_H */
