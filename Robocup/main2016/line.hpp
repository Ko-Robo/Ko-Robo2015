/**
 * @file   : line.h (1.0)
 * @brief  : find white line
 * @author : Shinnosuke KOIKE
 * @date   : 2015/10/23
 */

#ifndef LINE_H
#define LINE_H

#include "mbed.h"

class Line {
public:
    Line(PinName right, PinName back, PinName left);
    char find_on_line(void);

private:
    BusIn line_data;
};

Line::Line(PinName right, PinName back, PinName left):
    line_data(right, back, left) {
}

char Line::find_on_line(void) {
    char data = line_data;
    return data;
}

#endif /* LINE_H */
