#include "cutf.h"
#ifdef _WIN32
    #include <windows.h>
    #include <debugapi.h>
#endif

#define ok(statement) \
    r |= checkOk(statement, #statement);

int checkOk( bool b, const char* statement )
{
    if (b)
        return 0;

#ifdef _WIN32
    if (IsDebuggerPresent())
        DebugBreak();
#endif

    printf("Failed statement: %s\n", statement);
    return 1;
}

int simpleStringTest()
{
    const wchar_t* chineseText = L"主体";
    auto s = widetoutf8(chineseText);
    size_t r = 0;

    printf("simple string test:  ");

    ok( s.length() == 6 );
    uint8_t utf8_array[] = { 0xE4, 0xB8, 0xBB, 0xE4, 0xBD, 0x93 };

    for(int i = 0; i < 6; i++)
        ok(((uint8_t)s[i]) == utf8_array[i]);

    auto ws = utf8towide(s);
    ok(ws.length() == 2);
    ok(ws == chineseText);

    if( r == 0 )
        printf("ok.\n");

    // Zero termination
    wchar_t wbuf[20];
    utf8towchar("test", SIZE_MAX, wbuf, sizeof(wbuf));
    ok(wbuf[4] == 0);

    char cbuf[20];
    wchartoutf8(L"test", SIZE_MAX, cbuf, sizeof(cbuf));
    ok(cbuf[4] == 0);

    return (int)r;
}

