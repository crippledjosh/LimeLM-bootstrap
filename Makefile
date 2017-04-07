compile:
	gcc Bootstrap.c -c
	gcc -dynamiclib -current_version 1.0 libTurboActivate.dylib  Bootstrap.o  -o turboActivateBootstrap.dylib

clean:
	rm -f Bootstrap.o turboActivateBootstrap.dylib