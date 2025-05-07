#pragma once

class lcdDisplay{
    public:
        static void lcdInit();
        static void lcdWriteFormatted(String text);
        static void lcdPrintTopBottom(String textTop, String textBottom);
};
