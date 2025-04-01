#include <tice.h>

int main(void)
{
	/* Clear the homescreen */
	os_ClrHome();

	/* Wait for 5 seconds */
	os_PutStrFull("Waiting...");
	delay(5 * 1000);
	os_PutStrFull(" Done!");
	delay(100);

	return 0;
}
