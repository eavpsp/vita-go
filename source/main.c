/*
 * main.c
 *
 * Go Lang Main.Main Initializer for PSVita
 *Funcs outside of Main.Main must be patched, IE runtime.main
 *
 * Copyright (C) 2024 Elisha Victor
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "utils/settings.h"
#include "utils/logger.h"

#include <psp2/kernel/threadmgr.h>





#include <vitasdk.h>
#include <stdio.h>
#include <string.h>


int _newlib_heap_size_user = 256 * 1024 * 1024;

#ifdef USE_SCELIBC_IO
int sceLibcHeapSize = 4 * 1024 * 1024;
#endif

typedef void (*func_ptr_t)(void);
int main() 
{

	sceSysmoduleLoadModule(SCE_SYSMODULE_RAZOR_CAPTURE);//Debug Module
	SceAppUtilInitParam appUtilParam;//App Util Params
	SceAppUtilBootParam appUtilBootParam;//Boot Util Params
	memset(&appUtilParam, 0, sizeof(SceAppUtilInitParam));//Set Memory
	memset(&appUtilBootParam, 0, sizeof(SceAppUtilBootParam));
	sceAppUtilInit(&appUtilParam, &appUtilBootParam);//Init App Util
	func_ptr_t GOLANG_MAIN = (func_ptr_t)0x81070ad8;
	GOLANG_MAIN();
	log_debug("ended go func");
	sceKernelExitDeleteThread(0);
}


