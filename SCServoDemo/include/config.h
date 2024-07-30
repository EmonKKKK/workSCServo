
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "../stdafx.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <fstream>

#include <string>
#include <condition_variable>
#include "../SCServo/SCServo.h"
#include "SCSControl.h"


#define M_PI 3.14159265358979323846  // Manually define M_PI if not available
void Init_program_table(void);
extern u16 param[128];
#endif