/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   FreeSerif_ttf;
    const int            FreeSerif_ttfSize = 621136;

    extern const char*   FreeSerifBold_ttf;
    const int            FreeSerifBold_ttfSize = 198992;

    extern const char*   FreeMono_ttf;
    const int            FreeMono_ttfSize = 293572;

    extern const char*   FreeSerifItalic_ttf;
    const int            FreeSerifItalic_ttfSize = 154900;

    extern const char*   FreeMonoBoldOblique_ttf;
    const int            FreeMonoBoldOblique_ttfSize = 128384;

    extern const char*   FreeSansBoldOblique_ttf;
    const int            FreeSansBoldOblique_ttfSize = 95508;

    extern const char*   FreeMonoBold_ttf;
    const int            FreeMonoBold_ttfSize = 175016;

    extern const char*   FreeMonoOblique_ttf;
    const int            FreeMonoOblique_ttfSize = 175484;

    extern const char*   FreeSansBold_ttf;
    const int            FreeSansBold_ttfSize = 91432;

    extern const char*   FreeSans_ttf;
    const int            FreeSans_ttfSize = 264072;

    extern const char*   default_font_ttf;
    const int            default_font_ttfSize = 618684;

    extern const char*   FreeSerifBoldItalic_ttf;
    const int            FreeSerifBoldItalic_ttfSize = 126456;

    extern const char*   FreeSansOblique_ttf;
    const int            FreeSansOblique_ttfSize = 110740;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 13;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
