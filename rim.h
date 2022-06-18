#ifndef RIM_H
#define RIM_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MAX_BUF 256
#define STR_LEN 1024

typedef enum {
	FLAG,
	VALUE,
	COMMAND
} opt_enum;

typedef struct
{
	char* name;
	char* desc;
	char* alias;
	char* value;
	bool passed;
	opt_enum type;
} option_t;

typedef struct
{
	char name[MAX_BUF];
	char ver[16];
	char desc[STR_LEN];
	option_t* options;
	char license[MAX_BUF];
	char creator[MAX_BUF];
	int opts_len;
} app_t;

typedef struct{
	char name[MAX_BUF];
	char version[16];
	char desc[STR_LEN];
	char license[MAX_BUF];
	char creator[MAX_BUF];
} app_config_t;

app_t* new_app(app_config_t cfg);
void add_flag(app_t* app, char* name, char* alias, char* desc);
void add_value(app_t* app, char* name, char* alias, char* desc);
void add_cmd(app_t* app, char* name, char* desc);
void app_run(app_t* app, const int argc, char** argv);
bool rim_passed(app_t* app, const char* name);
char* rim_value(app_t* app, const char* name);

#endif // RIM_H
