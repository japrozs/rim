# Rim

<p align="center">
<img src="assets/rim.png">
<p>
## Usage

You can get started using `rim` by including the `rim.h` and `rim.c` files in your project and then importing them to use the library.

Here's a sample peice of code using `rim`

```c
#include <stdio.h>
#include <stdlib.h>
#include "rim.h"

int main(int argc, char** argv){
	app_t* app = new_app((app_config_t){
                .name = "rim_test",
                .desc = "test program for rim arguement parser",
                .creator = "Japroz Saini<sainijaproz@gmail.com>",
                .license = "MIT",
                .version = "0.0.1"
        });
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
```

-   First, we create an `app_config_t` object to add basic information information regarding the CLI like name, license, creator, version and so on.

-   Then we create an `app_t` `app` object. This app object will be used to manage your CLI throughout the project.

Then, there are some commmands to add certain flag, options or values to your CLI.

### `add_flag`

The `add_flag` function has the following signature:

```c
void add_flag(app_t* app, char* name, char* alias, char* desc);
```

You can use this to create flags for your CLI which can be accessed via their name as `--<name>` or their alias as `-<alias>`

### `add_value`

The `add_value` function has the following signature:

```c
void add_value(app_t* app, char* name, char* alias, char* desc);
```

You can use this to create value options for your CLI which take a value as so:

```
$ ./cli --name=John # option name get the value John
$ ./cli --name John # option name get the value John
$ ./cli -N John # referenced here by the alias
$ ./cli -N=John # also referenced here by the alias
```

### `add_cmd`

The `add_cmd` function has the following signature:

```c
void add_cmd(app_t* app, char* name, char* desc);
```

You can use this to create a command for your CLI and then check if it has been passed using the `rim_passed` function.

### `rim_passed`

You can use the `rim_passed` function to check if a flag/option/command has been passed by the user to the CLI by passing a pointer to the `app_t` object and the name/alias of the flag/option/value that you want to check.

### `rim_value`

This function can be used only for `values` in your CLI to get the value passed to them. This function returns a value if a value is passed, otherwise just returns an empty string.

### `app_run`

This is the main function that parses all the CLI options. You use it by passing the `app_t` object and `argc and argv` provided to you by your compiler.

## Build Instructions

```shell
git clone https://github.com/japrozs/rim
cd rim
./make.sh
./out/mains
```

### License : `MIT`
