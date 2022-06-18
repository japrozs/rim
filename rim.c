#include "rim.h"

char *lower(char *str, size_t len)
{
	char *str_l = calloc(len + 1, sizeof(char));

	for (size_t i = 0; i < len; ++i)
	{
		str_l[i] = tolower((unsigned char)str[i]);
	}
	return str_l;
}

void gen_help_msg(app_t* app){
	printf(
		"%s %s\n"
		"%s\n\n"
		"Usage: %s [options] [command]\n\n"
		"Options:\n"
		"\t-V, --version              output the version number\n"
		"\t-h, --help                 display help message\n",
		app->name, app->ver, app->desc, app->name
	);

	for(int i = 0;i < app->opts_len;i++){
		if(app->options[i].type == FLAG){
			printf("\t%s, %-22s %s\n", app->options[i].alias, app->options[i].name, app->options[i].desc);
		}
		else if(app->options[i].type == VALUE){
			printf("\t%s, %-22s %s\n", app->options[i].alias, strcat(app->options[i].name, " <value>"), app->options[i].desc);
		}
	}
	printf("\nCommands:\n");
	for(int i = 0;i < app->opts_len;i++){
		if(app->options[i].type == COMMAND){
			printf("\t%-22s %s\n", app->options[i].name, app->options[i].desc);
		}
	}
	printf("\thelp [command]         display help message\n");
}

void gen_version_msg(app_t* app){
	printf("%s %s\n", app->name ,app->ver);
}

app_t *new_app(app_config_t cfg)
{
	app_t *app = (app_t *)malloc(sizeof(app_t));
	strcpy(app->name, cfg.name);
	strcpy(app->desc, cfg.desc);
	strcpy(app->ver, cfg.version);
	strcpy(app->license, cfg.license);
	strcpy(app->creator, cfg.creator);
	app->options = malloc(MAX_BUF * sizeof(option_t));
	app->opts_len = 0;

	return app;
}

void add_flag(app_t *app, char *name, char *alias, char *desc)
{
	int i = 0;
	while (app->options[i].name != NULL)
		i++;

	app->options[i].name = malloc(sizeof(char) * 256);
	app->options[i].desc = malloc(sizeof(char) * 256);
	app->options[i].alias = malloc(sizeof(char) * 256);

	app->options[i].name = lower(name, strlen(name));
	app->options[i].desc = desc;
	app->options[i].alias = alias;
	app->options[i].type = FLAG;
	app->options[i].passed = false;
	app->opts_len += 1;
}

void add_cmd(app_t *app, char *name, char *desc)
{
	int i = 0;
	while (app->options[i].name != NULL)
		i++;

	app->options[i].name = malloc(sizeof(char) * 256);
	app->options[i].desc = malloc(sizeof(char) * 256);
	app->options[i].alias = malloc(sizeof(char) * 256);

	app->options[i].name = lower(name, strlen(name));
	app->options[i].desc = desc;
	app->options[i].type = COMMAND;
	app->options[i].passed = false;
	app->opts_len += 1;
}

void add_value(app_t *app, char *name, char *alias, char *desc)
{
	int i = 0;
	while (app->options[i].name != NULL)
		i++;

	app->options[i].name = malloc(sizeof(char) * 256);
	app->options[i].desc = malloc(sizeof(char) * 256);
	app->options[i].alias = malloc(sizeof(char) * 256);
	app->options[i].value = malloc(sizeof(char) * 256);

	app->options[i].name = lower(name, strlen(name));
	app->options[i].desc = desc;
	app->options[i].alias = alias;
	app->options[i].value = "";
	app->options[i].type = VALUE;
	app->options[i].passed = false;
	app->opts_len += 1;
}

void app_run(app_t *app, const int argc, char **argv)
{
	if(	argc == 1 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0){
		gen_help_msg(app);
		exit(EXIT_SUCCESS);
	}

	if(	argc == 1 || strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0){
		gen_version_msg(app);
		exit(EXIT_SUCCESS);
	}

	for (int i = 1; i < argc; i++)
	{
		char *arg = argv[i];
		if (arg[0] == '-')
		{
			option_t opt;
			int idx = 0;
			if (arg[1] == '-')
			{
				bool contains_equal = false;
				for(int j = 0;j < (int)strlen(arg);j++){
					if(arg[j] == '=')
						contains_equal = true;
				}

				if(contains_equal){
					char* str = strtok(arg, "=");
					char* val = strtok(NULL, "=");

					for (int j = 0; j < app->opts_len; j++)
					{
						if (strcmp(app->options[j].name, str) == 0)
						{
							opt = app->options[j];
							idx = j;
							break;
						}
					}
					if(opt.type == FLAG){
						printf("error :: supplied value for a flag!\n");
						exit(0);
					}else{
						app->options[idx].passed = true;
						app->options[idx].value = val;
					}
				}else{
					for (int k = 0; k < app->opts_len; k++)
					{
						if (strcmp(app->options[k].name, arg) == 0)
						{
							opt = app->options[k];
							idx = k;
							break;
						}
					}

					if (opt.type == FLAG)
					{
						app->options[idx].passed = true;
					} else if(opt.type == VALUE){
						if(i < (argc - 1)){
							app->options[idx].passed = true;
							app->options[idx].value = argv[i + 1];
							i++;
						}else{
							printf("error :: no value supplied for option \"%s\"\n", opt.name);
						}
					}
				}
			}
			else
			{
				bool contains_equal = false;
				for(int j = 0;j < (int)strlen(arg);j++){
					if(arg[j] == '=')
						contains_equal = true;
				}

				if(contains_equal){
					char* str = strtok(arg, "=");
					char* val = strtok(NULL, "=");

					for (int j = 0; j < app->opts_len; j++)
					{
						if (strcmp(app->options[j].alias, str) == 0)
						{
							opt = app->options[j];
							idx = j;
							break;
						}
					}
					if(opt.type == FLAG){
						printf("error :: supplied value for a flag!\n");
						exit(0);
					}else{
						app->options[idx].passed = true;
						app->options[idx].value = val;
					}
				}else{
					for (int k = 0; k < app->opts_len; k++)
					{
						if (strcmp(app->options[k].alias, arg) == 0)
						{
							opt = app->options[k];
							idx = k;
							break;
						}
					}

					if (opt.type == FLAG)
					{
						app->options[idx].passed = true;
					} else if(opt.type == VALUE){
						if(i < (argc - 1)){
							app->options[idx].passed = true;
							app->options[idx].value = argv[i + 1];
							i++;
						}else{
							printf("error :: no value supplied for option \"%s\"\n", opt.name);
						}
					}
				}
			}
		}else {
			for (int j = 0; j < app->opts_len; j++)
			{
				if (strcmp(app->options[j].name, arg) == 0)
				{
					app->options[j].passed = true;
					break;
				}
			}	
		}
	}
}

bool rim_passed(app_t *app, const char *name)
{
	for (int k = 0; k < app->opts_len; k++)
	{
		if (strcmp(app->options[k].name, name) == 0 || strcmp(app->options[k].alias, name) == 0)
		{
			return app->options[k].passed;
		}
	}

	return false;
}

char *rim_value(app_t *app, const char *name)
{
	for (int k = 0; k < app->opts_len; k++)
	{
		if (strcmp(app->options[k].name, name) == 0 || strcmp(app->options[k].alias, name) == 0)
		{
			if(app->options[k].type == FLAG){
				printf("error :: tried to retreive value of flag \"%s\"\n", app->options[k].name);
				exit(0);
			}
			return app->options[k].value;
		}
	}

	return "";
}
