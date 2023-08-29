/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryDataTools
{
    extern const char*   label_apply_png;
    const int            label_apply_pngSize = 1151;

    extern const char*   quit_png;
    const int            quit_pngSize = 436;

    extern const char*   new_png;
    const int            new_pngSize = 524;

    extern const char*   undo_png;
    const int            undo_pngSize = 854;

    extern const char*   open_png;
    const int            open_pngSize = 867;

    extern const char*   stamp_png;
    const int            stamp_pngSize = 405;

    extern const char*   text_png;
    const int            text_pngSize = 361;

    extern const char*   label_select_png;
    const int            label_select_pngSize = 1023;

    extern const char*   shapes_png;
    const int            shapes_pngSize = 246;

    extern const char*   magic_png;
    const int            magic_pngSize = 610;

    extern const char*   redo_png;
    const int            redo_pngSize = 695;

    extern const char*   eraser_png;
    const int            eraser_pngSize = 467;

    extern const char*   print_png;
    const int            print_pngSize = 470;

    extern const char*   lines_png;
    const int            lines_pngSize = 437;

    extern const char*   fill_png;
    const int            fill_pngSize = 632;

    extern const char*   save_png;
    const int            save_pngSize = 811;

    extern const char*   speak_png;
    const int            speak_pngSize = 769;

    extern const char*   sfx_png;
    const int            sfx_pngSize = 525;

    extern const char*   brush_png;
    const int            brush_pngSize = 358;

    extern const char*   label_png;
    const int            label_pngSize = 636;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 20;

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
