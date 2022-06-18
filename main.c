#include <stdio.h>
#include <stdlib.h>
#include "rim.h"

int main(int argc, char** argv){
	app_config_t config = {
		.name = "rim_test",
		.desc = "test program for rim arguement parser",
		.creator = "Japroz Saini<sainijaproz@gmail.com>",
		.license = "MIT",
		.version = "0.0.1"
	};
	app_t* app = new_app(config);
	add_flag(app, "--list", "-L", "lists something...");
	add_value(app, "--name", "-N", "name value");
	add_cmd(app, "echo", "echoes something...");
	app_run(app, argc, argv);

	if(rim_passed(app, "--list")){
		printf("list option passed\n");
	}
	if(rim_passed(app, "echo")){
		printf("echo option passed\n");
	}
	if(rim_passed(app, "--name")){
		printf("value of option name :: \"%s\"\n", rim_value(app, "--name"));
	}

	return EXIT_SUCCESS;
}
