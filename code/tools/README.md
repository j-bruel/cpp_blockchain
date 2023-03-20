# Centor Tools

C++ tools for Centor project usage.

## What Centor Tools is made of
* Multi-platform warning disabler
* Platform detector

## Build system

> **_NOTE:_**   For now, this library is an header-only library. No build system is available.

## How to use

```c++
#include <centor/tools/warning_disabler.h>
#include <centor/tools/platform.h>

#include <iostream>

int main()
{
	DISABLE_WARNING_PUSH
	DISABLE_WARNING_NAME_OF_THE_WARNING
	// my code with warning I want to disable.
	DISABLE_WARNING_POP

	if (centor::current_platform() == centor::platform::unsupported)
		throw;
}
```