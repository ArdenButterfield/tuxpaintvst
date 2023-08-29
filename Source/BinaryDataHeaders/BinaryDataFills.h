/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryDataFills
{
    extern const char*   gradient_linear_png;
    const int            gradient_linear_pngSize = 1024;

    extern const char*   solid_png;
    const int            solid_pngSize = 695;

    extern const char*   gradient_shaped_png;
    const int            gradient_shaped_pngSize = 1829;

    extern const char*   gradient_radial_png;
    const int            gradient_radial_pngSize = 1395;

    extern const char*   brush_png;
    const int            brush_pngSize = 790;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

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
