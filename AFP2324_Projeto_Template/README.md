# AFP2324 Project Template

This is a C program *template* tailored for:

- GCC, GDB, MAKE (via MinGW)
- VS Code IDE


### Makefile

Modules should be added to the `makefile` before compilation.

### Compilation

In a terminal, type:

```console
.\make.bat <directive>
```

where `<directive>` is optional and can be replaced by:

- (empty) - compiles the program normally;
- `debug` - compile with *debug* symbols. Necessary to debug the program;
- `clean` - removes the compiled executable.

### Execution

After compiling, in the terminal, type:

```console
.\prog.exe
```

### Enabling Non-Ascii Characters in PowerShell Terminal

If using **PowerShell** as the terminal, you can issue the following command to enable non-ascii characters for the program *output*.

```console
[Console]::OutputEncoding = [Text.Encoding]::Utf8
```

### Debugging

Set your breakpoint(s) and click on the `Run and Debug` tab on VS Code and click on `gdb - Debug project` (at the top).

This will open a separate terminal window where the program session will execute (for input and output). You can use the debug options inside VS Code.

## Input Module

This template project includes the `input` module. You should use it for *user input* as it provides a relatively robust mechanism to read mixed data and performs validation.

Below is a sample program which exemplifies the usage of this module:

```cpp
#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int main() {

	/* simple data formats with validation examples */
	int value = 0;
	do {
		printf("Integer Value? ");
	} while(!readInteger(&value)); /* loops while invalid */
		
	printf("Integer Value = %d \n", value);

	double value2 = 0;
	do {
		printf("Double Value? ");
	} while(!readDouble(&value2)); /* loops while invalid */
		
	printf("Double Value = %lf \n", value2);

	/* Strings are consumed as-is */
	char text[100];
	printf("Text? ");
	readString(text, 100);
	printf("Text = %s \n", text);

	/* Example of the spliting function; use with CSV files later */
	char line[100] = "Bruno Silva;bruno.silva@estsetubal.ips.pt;;2023/24";

	char** tokens = splitString(line, 4, ";");
	for(int i=0; i<4; i++) {
		printf("Token[%d] = %s \n", i, tokens[i]);
	}

	free(tokens); 

	return 0;
}
```

and an example *user interaction* session:

```markdown
Integer Value? 12d
Integer Value? - 3
Integer Value? -3
Integer Value = -3 
Double Value? 12.4.5
Double Value? -3.14159
Double Value = -3.141590 
Text? This some text and a number 7 
Text = This some text and a number 7 
Token[0] = Bruno Silva 
Token[1] = bruno.silva@estsetubal.ips.pt 
Token[2] =  
Token[3] = 2020/21
```
