/*
This is a 'Hello-World'-example for the Raspberry Pi.

For remote-debugging it is necessary to add the IP-address of your Pi
to the Debug-Configuration. Go to 'Run' -> 'Debug Configuration' and
select this project. Then click the 'New'-button -> 'SSH only' and
enter the IP in 'Host name'. After clicking 'Debug' you need to enter
your user-name to connect to your Pi. The default user is 'pi' and
you can find the Password on top of your Pi.
*/

#include <stdio.h>

int main(){

	printf("Hallo World\n");

	return 0;
}
