#ifndef NCURDISP_H
#define NCURDISP_H

#include <internal/buffdisp.h>

#ifdef HAVE_NCURSES

#include <unordered_map>
#include <ncurses.h>

class NcursesDisplay : public BufferedDisplay {

    SCREEN *term;

    bool hasColors;
    std::unordered_map<ushort, int> pairIdentifiers;
    ushort definedPairs;

    bool usesNcursesDraw;

    void getCaretPosition(int &x, int &y);
    uint translateAttributes(uchar attr);
    uint getColorPair(uchar pairKey);

public:

    NcursesDisplay();
    ~NcursesDisplay();

    void reloadScreenInfo() override;
    TPoint getScreenSize() override;
    int getCaretSize() override;

    void clearScreen() override;
    ushort getScreenMode() override;

protected:

    void lowlevelWriteChars(TStringView chars, TCellAttribs attr) override;
    void lowlevelMoveCursor(uint x, uint y) override;
    void lowlevelCursorSize(int size) override;
    void lowlevelFlush() override;

};

#else

class NcursesDisplay : public DisplayStrategy {};

#endif // HAVE_NCURSES

#endif
