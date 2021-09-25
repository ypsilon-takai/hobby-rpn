#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <fp64lib.h>
#include <EEPROM.h>
//#include "font/Voyager7seg9pt7b.h"
#include "font/davinci_14x9.h"
#include "font/dc10b_14x9.h"

//davinci_14x9 : default
#define FONT1 1
//dc10b_14x9
#define FONT2 2

#define SEP_NO 0
#define SEP_3 3
#define SEP_4 4

#define EEPROM_FONTNUM 0
#define EEPROM_SEPARATOR 1

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET    -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 500000, 100000);

#define MAX_DIGIT     10

#define DISP_LMARGIN 4
#define DISP_UPPERLINE_BASE 13
#define DISP_LOWERLINE_BASE 30

#define GFX_BLACK 0
#define GFX_WHITE 1

byte pin_col[] = {0, 1, 2, 3};   // PD
byte pin_row[] = {3, 2, 1, 0};   // PC

float64_t x, y, z, t;
float64_t x_sig, x_exp;
float64_t lastx, plastx;

byte last_pushed_key_type = 0;    // 0:numeral 1:operator 2:enter

boolean shift_mode = false;
boolean exp_input = false;

enum angle_type {degree, radian, grad};
enum angle_type angle_mode = degree;

int separator_type = 0;

//const GFXfont* digit_area_font = &davinci_14x9_hr;
const GFXfont* digit_area_font = &davinci_14x9;
//const GFXfont* digit_area_font = &Voyager7seg9pt7b;



void push() {
    t = z;
    z = y;
    y = x;
}

void pop() {
    x = y;
    y = z;
    z = t;
}

char key_scan() {
    PORTD |= _BV(pin_col[0]) | _BV(pin_col[1]) | _BV(pin_col[2]) | _BV(pin_col[3]); // set high

    for (byte i = 0; i < 4; i++) {
        PORTD &= ~_BV(pin_col[i]);  // set low

        for (byte j = 0; j < 4; j++) {
            if ((PINC & _BV(pin_row[j])) == LOW) {
                switch (4 * j + i) {
                    case  0: return '7';
                    case  1: return '8';
                    case  2: return '9';
                    case  3: return '/';

                    case  4: return '4';
                    case  5: return '5';
                    case  6: return '6';
                    case  7: return '*';

                    case  8: return '1';
                    case  9: return '2';
                    case 10: return '3';
                    case 11: return '-';

                    case 12: return '0';
                    case 13: return '.';
                    case 14: return '=';
                    case 15: return '+';
                }
            }
        }
        PORTD |= _BV(pin_col[i]);   // set high
    }
    return 0;
}

void blink_display() {
    display.clearDisplay();
    display.display();
    delay(20);
}

void draw_mode_area() {
    if (angle_mode == radian) {
        // draw 'R" with lines
        display.drawLine(124, 1, 126, 1, GFX_WHITE);
        display.drawLine(124, 1, 124, 6, GFX_WHITE);
        display.drawPixel(127, 2, GFX_WHITE);
        display.drawLine(124, 3, 126, 3, GFX_WHITE);
        display.drawLine(127, 4, 127, 6, GFX_WHITE);
    }

    /* Separator indicator : Not so good.
    if (separator_type == 4) {
        display.drawRect(124, 10, 4, 6, GFX_WHITE);
    }
    else if (separator_type == 3) {
        display.fillTriangle(124, 10, 127, 10, 124, 16, GFX_WHITE);
    }
    */
    
    if (shift_mode == true) {
        display.fillRect(124, 20, 4, 6, GFX_WHITE);
    }
}    

void init_display() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);

    display.clearDisplay();

    draw_mode_area();
        
    display.setFont(digit_area_font);
    display.setTextSize(1);

    display.setCursor(DISP_LMARGIN, DISP_LOWERLINE_BASE);
    display.print("0");
    display.display();
}

void update_display(String x_disp, String y_disp, boolean is_two_line) {
    display.clearDisplay();

    draw_mode_area();
    
    display.setFont(digit_area_font);

    // upper row
    display.setCursor(DISP_LMARGIN, DISP_UPPERLINE_BASE);
    display.print(separated_digits(y_disp));

    // lower row
    display.setCursor(DISP_LMARGIN, DISP_LOWERLINE_BASE);
    if (x_disp == "") {
        x_disp = "0";
    }
    display.print(separated_digits(x_disp));

    display.display();
}

String separated_digits(String digits) {
    if (separator_type == 0) {
        return digits;
    }

    int base_pos = digits.indexOf('.');
    if (base_pos == -1) {
        // no period
        base_pos = digits.indexOf('E');
        if (base_pos == -1) {
            // not exponential notation
            base_pos = digits.length();
        }
    }

    int stop = 0;
    if (digits.charAt(0) == '-') {
        stop = 1;
    }
    String s = digits;
    for (int i=base_pos-1; i > stop; i--) {
        if ((base_pos - i) % separator_type == 0) {
            s = s.substring(0, i) + "^" + s.substring(i);
        }
    }
    return s;
}

String fp64_to_string_wrap(float64_t n) {
    if (fp64_signbit(n)) {  // minus
        return fp64_to_string(n, MAX_DIGIT, MAX_DIGIT - 3);
    }
    else {
        return fp64_to_string(n, MAX_DIGIT, MAX_DIGIT - 2);
    }
}

float64_t deg2rad(float64_t deg) {
    return fp64_div(fp64_mul(deg,float64_NUMBER_PI), fp64_sd(180));
}

float64_t rad2deg(float64_t rad) {
    return fp64_div(fp64_mul(rad, fp64_sd(180)), float64_NUMBER_PI);
}

void setup() {
    CLKPR = 0x80; 
    CLKPR = 0x1;    // 8MHz

    // col
    DDRD  |= _BV(pin_col[0]) | _BV(pin_col[1]) | _BV(pin_col[2]) | _BV(pin_col[3]);     // OUTPUT
    PORTD |= _BV(pin_col[0]) | _BV(pin_col[1]) | _BV(pin_col[2]) | _BV(pin_col[3]);     // HIGH

    // row
    DDRC  &= ~(_BV(pin_row[0]) | _BV(pin_row[1]) | _BV(pin_row[2]) | _BV(pin_row[3]));  // INPUT
    PORTC |=   _BV(pin_row[0]) | _BV(pin_row[1]) | _BV(pin_row[2]) | _BV(pin_row[3]);   // PULLUP

    byte fnum = EEPROM.read(EEPROM_FONTNUM);
    if (fnum == FONT1) {
        //digit_area_font = &Voyager7seg9pt7b;        
        digit_area_font = &dc10b_14x9;
    }
    else if (fnum == FONT2) {
        //digit_area_font = &Voyager7seg9pt7b;
        digit_area_font = &davinci_14x9; 
    }
    else {        
        //digit_area_font = &Voyager7seg9pt7b;
        digit_area_font = &davinci_14x9;         
    }

    separator_type = EEPROM.read(EEPROM_SEPARATOR);
    
    init_display();
    
    x = y = z = t = 0;
    lastx = plastx = 0;
}

void loop() {
    static String x_disp = "";
    static String y_disp = "";
    static String x_sig_str = "";
    static String x_exp_str = "";
    static char prev_loop_key = 0;
    static byte prev_pushed_key_type = 0;    // 0:numeral 1:operator 2:enter

    // key scan
    char key = key_scan();
    if (key != 0 && key != prev_loop_key) {

        plastx = x;
        
        // detect long push
        boolean long_push = false;
        unsigned long pushed_time = millis();
        while (key_scan() == key) {
            if (millis() - pushed_time > 1000 / 5) {    // 1sec
                long_push = true;
                break;
            }
        }

        if (key == '+') {
            if (long_push) {
                if (shift_mode) {
                    shift_mode = false;
                }
                else {
                    shift_mode = true;
                }
            }
            // - substruct
            else {
                float64_t acc1 = x;
                pop();
                float64_t acc2 = x;

                x = fp64_add(acc2, acc1);

                x_disp = fp64_to_string_wrap(x);
                prev_pushed_key_type = 1;
                blink_display();
            }
        }
        // sqrt or multiply
        else if (key == '*') {
            // square root
            if (long_push) {
                x = fp64_sqrt(x);
                prev_pushed_key_type = 1;
            }
            // - substruct
            else {
                float64_t acc1 = x;
                pop();
                float64_t acc2 = x;

                x = fp64_mul(acc2, acc1);
                prev_pushed_key_type = 1;
            }
            x_disp = fp64_to_string_wrap(x);
        }
        // chsgn or substruct
        else if (key == '-') {
            // -/+ change sign
            if (long_push) {
                if (exp_input) {
                    if (x_exp_str.startsWith("-")) {
                        x_exp_str = x_exp_str.substring(1);
                    }
                    else {
                        x_exp_str = "-" + x_exp_str;
                    }
                    x_disp = x_sig_str + "E" + x_exp_str;                    
                    x = fp64_atof((char*)x_disp.c_str());                    
                }
                else {
                    x = fp64_neg(x);
                    prev_pushed_key_type = last_pushed_key_type;
                    x_disp = fp64_to_string_wrap(x);                                    
                }
            }
            // - substruct
            else {
                float64_t acc1 = x;
                pop();
                float64_t acc2 = x;

                x = fp64_sub(acc2, acc1);
                prev_pushed_key_type = 1;
                x_disp = fp64_to_string_wrap(x);                
            }
        }
        // '/' or x<>y
        else if (key == '/') {
            // swap x and y
            if (long_push) {
                float64_t tmp = x;
                x = y;
                y = tmp;
            }
            // '/' key
            else {
                float64_t acc1 = x;
                pop();
                float64_t acc2 = x;
    
                x = fp64_div(acc2, acc1);
            }
            x_disp = fp64_to_string_wrap(x);            
            prev_pushed_key_type = 1;            
            blink_display();
        }
        // clear or enter
        else if (key == '=') {
            // clear
            if (long_push) {
                if (x == 0) {
                    pop();
                    x_disp = fp64_to_string_wrap(x);
                }
                else {
                    x = 0;
                    x_disp = "";

                    x_sig_str = x_exp_str = "";
                    x_sig = x_exp = 0;

                    exp_input = false;
                }
                prev_pushed_key_type = 0;                
            }
            // enter
            else {
                push();

                x_disp = fp64_to_string_wrap(x);
                prev_pushed_key_type = 2;
            }
            blink_display();
        }
        // numeral or .
        else {
            if (shift_mode) {
                shift_mode = false;

                if (key == '7') {
                    byte fnum = EEPROM.read(EEPROM_FONTNUM);
                    if (fnum == FONT1) {
                        //digit_area_font = &Voyager7seg9pt7b;
                        digit_area_font = &davinci_14x9;
                        EEPROM.write(EEPROM_FONTNUM, FONT2);
                    }
                    else {
                        digit_area_font = &dc10b_14x9;
                        EEPROM.write(EEPROM_FONTNUM, FONT1);
                    }
                }
                else if (key == '8') {
                    if (angle_mode == degree) {
                        angle_mode = radian;
                    }
                    else if (angle_mode == radian) {
                        angle_mode = degree;
                    }
                }
                else if (key == '9') {
                    if (separator_type == 0) {
                        separator_type = 3;
                    }
                    else if (separator_type == 3) {
                        separator_type = 4;
                    }
                    else {
                        separator_type = 0;
                    }
                    EEPROM.write(EEPROM_SEPARATOR, separator_type);
                }
            }
            else if (long_push) {
                if(key == '0') {
                    // lastx
                    push();
                    x = lastx;
                    prev_pushed_key_type = 2;
                }
                // start exponential input
                else if(key == '.') {
                    if (x != 0 && ! exp_input) {
                        exp_input = true;

                        x_sig_str = x_disp;
                        x_exp_str = "0";
                        x_sig = x;
                        x_exp = 0;
                    }
                }

                // Trigonometric functions
                else if(key == '7') {
                    if (angle_mode == degree) x = deg2rad(x);
                    x = fp64_sin(x);
                    prev_pushed_key_type = 1;
                }
                else if(key == '8') {
                    if (angle_mode == degree) x = deg2rad(x);
                    x = fp64_cos(x);
                    prev_pushed_key_type = 1;
                }
                else if(key == '9') {
                    if (angle_mode == degree) x = deg2rad(x);
                    x = fp64_tan(x);
                    prev_pushed_key_type = 1;
                }
                else if(key == '4') {
                    x = fp64_asin(x);
                    if (angle_mode == degree) x = rad2deg(x);
                    prev_pushed_key_type = 1;
                }
                else if(key == '5') {
                    x = fp64_acos(x);
                    if (angle_mode == degree) x = rad2deg(x);
                    prev_pushed_key_type = 1;
                }
                else if(key == '6') {
                    x = fp64_atan(x);
                    if (angle_mode == degree) x = rad2deg(x);
                    prev_pushed_key_type = 1;
                }
                // logarithm
                else if(key == '1') {
                    x = fp64_log10(x);
                    prev_pushed_key_type = 1;
                }
                else if(key == '2') {
                    x = fp64_log(x);
                    prev_pushed_key_type = 1;
                }
                // power
                else if(key == '3') {
                    float64_t acc1 = x;
                    pop();
                    float64_t acc2 = x;

                    x = fp64_pow(acc2, acc1);

                    x_disp = fp64_to_string_wrap(x);
                    prev_pushed_key_type = 1;
                    prev_pushed_key_type = 1;
                }
                if (exp_input) {
                    x_disp = x_sig_str + "E" + x_exp_str;
                }
                else {
                    x_disp = fp64_to_string_wrap(x);
                }
                blink_display();
            }
            else {
                
                if (prev_pushed_key_type == 1) push();          // operator
                if (prev_pushed_key_type > 0) {
                    x_disp = "";      // operator or enter
                    exp_input = false;
                }
            
                if (x_disp.length() < MAX_DIGIT) {
                    if (exp_input) {
                        if (key != '.') {
                            if (x_exp_str == "0")  x_exp_str = "";
                            x_exp_str.concat(key);
                            x_disp = x_sig_str + "E" + x_exp_str;
                            x = fp64_atof((char*)x_disp.c_str());
                        }
                    }
                    else if (x_disp.indexOf(".") == -1 || key != '.') {
                        // Issue #6 モード変更すると0がのこってしまう。
                        // Issue #13 小数の表示が xxのようにならないように。
                        // TODO: よりよい対応があるんじゃないかな。                        
                        if (x_disp == "0") x_disp = "";
                        if (x_disp == "" && key == '.') x_disp = "0";
                        x_disp.concat(key);
                        x = fp64_atof((char*)x_disp.c_str());
                    }
                }
                prev_pushed_key_type = 0;
            }
        }
        
        if (prev_pushed_key_type == 1) lastx = plastx;

        // display
        y_disp = fp64_to_string_wrap(y);
        update_display(x_disp, y_disp, true);
    }
    last_pushed_key_type = prev_pushed_key_type;
    prev_loop_key = key;
    delay(1);
}
