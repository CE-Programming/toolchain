#include <tice.h>
#include <keypadc.h>


const char *KeyStrings[57] = {
	"", "Down Arrow", "Left Arrow", "Right Arrow", "Up Arrow", "", "", "", "",
	"Enter", "+", "-", "*", "/", "^", "Clear", "",
	"- Minus", "3", "6", "9", ")", "tan", "vars", "",
	".", "2", "5", "8", "(", "cos", "prgm", "stat",
	"0", "1", "4", "7", ",", "sin", "apps", "XT0n",
	"", "Sto->", "ln", "log", "x^2", "x^-1", "math", "alpha",
	"graph", "trace", "zoom", "window", "y=", "2nd", "mode", "del"
};

/* Function prototypes */
void PrintText(uint8_t xpos, uint8_t ypos, const char *text);

int main(void)
{
	kb_queue_t keyqueue;
	uint8_t curline = 0;
    kb_key_t key = 0;
    const char *erase_string = "                          ";

    /* Clear the homescreen */
    os_ClrHome();

    /* Loop until 2nd is pressed */
	kb_ClearQueue(&keyqueue);
    do
    {
		if (key){
			PrintText(1, curline, erase_string);
			PrintText(1, curline, KeyStrings[key]);
			curline = (curline + 1) % 10;
		} else {
			kb_QueueKeys(&keyqueue);
		}
		key=kb_UnqueueKey(&keyqueue);
    } while (key != sk_Clear);

    return 0;
}

/* Draw text on the homescreen at the given X/Y location */
void PrintText(uint8_t xpos, uint8_t ypos, const char *text)
{
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
