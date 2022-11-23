#ifndef DEFINE_H
#define DEFINE_H

//includes
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "ssd1306.h"
#include "fonts.h"
#include "test.h"
#include "math.h"
#include "stdbool.h"

//variable Sensors
int sensors[9];
uint16_t sensores();
uint8_t IR = 0;
uint8_t routine_ini = 0;
uint8_t routine_search = 0;
volatile bool tag_line_front_l = 0;
volatile bool tag_line_front_r = 0;
volatile bool tagliner = 0;
volatile bool taglinel = 0;
float tempAmb = 27.5;
float temp = 27.5;
float tempMax = 0;
uint16_t a = 0;
uint32_t tempo = 0;
uint32_t delta = 0;

//variable RC
volatile float Duty_Ch1 = 0;
volatile float Duty_Ch2 = 0;
volatile uint32_t ICValue_Ch1 = 0;
volatile uint32_t ICValue_Ch2 = 0;
volatile float F_Ch1 = 0;
volatile float F_Ch2 = 0;
int Freq_Radio = 50;
float vL = 0;
float vR = 0;

//varible movement
float vel;
float omega;
float max_th = 10;
float min_th = 6;
float max_st = 10;
float min_st = 6;
uint16_t busca = 0;
int flagAvanco = 0;
int flagfront = 0;
bool var_nheco = 0;
int flagLeft = 0;
bool default_search=0;

//constants robot
const int R = 21;
const int L = 157;
const float vel_max = 100 * R;
const float omega_max = 200 * R / L;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
ADC_HandleTypeDef hadc1;

//prototipe
void readSensors();
void driveMotorsRC();
uint8_t readIR();
float map(float, float, float, float, float);
void controlMotor(int, int);
void inicialMoviment();
void basicSearch(int, int, int, int);
void selectIniRoutine();
void selectSearchRoutine();
void printSensors();
void calibrateRadio(float, float, char);
void lineSearch();
void lineEscape();
void readTemp();
void tranquinho();
void nhecoNheco();

#endif /* DEFINE_H */
