# 3.24.1 is bundled in Visual Studio 2022 v17.4
# 3.24.1 is also bundled in CLion as of 2023
cmake_minimum_required(VERSION 3.24.1)

# This is the name of your plugin
# This cannot have spaces (but PRODUCT_NAME can)
set(PROJECT_NAME "TuxPaintVST")

# Set the plugin formats you'll be building here.
# Valid formats: AAX Unity VST AU AUv3 Standalone
set(FORMATS AU VST3 AUv3)

# This must be set before the project() call
# see: https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Support macOS down to High Sierra")

# Reads in our VERSION file and sticks in it CURRENT_VERSION variable
# Be sure the file has no newlines!
file(STRINGS VERSION CURRENT_VERSION)

# For simplicity, the name of the project is also the name of the target
project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

# By default we don't want Xcode schemes to be made for modules, etc
set(CMAKE_XCODE_GENERATE_SCHEME OFF)

# Building universal binaries on macOS increases build time
# This is set on CI but not during local dev
if ((DEFINED ENV{CI}) AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    message("Building for Apple Silicon and x86_64")
    set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)
endif ()

# Adds all the module sources so they appear correctly in the IDE
# Must be set before JUCE is added as a sub-dir (or any targets are made)
# https://github.com/juce-framework/JUCE/commit/6b1b4cf7f6b1008db44411f2c8887d71a3348889
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# Create a /Modules directory in the IDE with the JUCE Module code
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Show all module sources in IDE projects" ON)

# JUCE is setup as a submodule in the /JUCE folder
# Locally, you'll need to run `git submodule update --init --recursive` once
# and `git submodule update --remote --merge` to keep it up to date
# On Github Actions, it's managed by actions/checkout
add_subdirectory(JUCE)

# Check the readme at `docs/CMake API.md` in the JUCE repo for full config
juce_add_plugin("${PROJECT_NAME}"
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME Wildergarden
    BUNDLE_ID com.wildergarden.tuxpaintVST
    # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
    # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE                # On MacOS, plugin will be copied to /Users/you/Library/Audio/Plug-Ins/
    PLUGIN_MANUFACTURER_CODE Awbb               # This has to be one uppercase, rest lower for AU formats
    PLUGIN_CODE TP01                            # A unique four-character plugin id with at least one upper-case character
    FORMATS "${FORMATS}"
    PRODUCT_NAME "${PROJECT_NAME}")             # The name of the final executable, which can differ from the target name

# C++20, please
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)

# Manually list all .h and .cpp files for the plugin
set(SourceFiles
    ./Source/InfoPanel.h
    ./Source/PluginProcessor.cpp
    ./Source/TuxPaint.cpp
    ./Source/OptionPanels/OptionsPanel.h
    ./Source/PluginEditor.h
    ./Source/OptionPanels/OptionsPanel.cpp
    ./Source/InfoPanel.cpp
    ./Source/PluginEditor.cpp
    ./Source/Canvas/CanvasPanel.h
    ./Source/ToolsPanel.h
    ./Source/Canvas/CanvasPanel.cpp
    ./Source/ToolsPanel.cpp
    ./Source/ColorsPanel.h
    ./Source/ColorsPanel.cpp
    ./Source/TuxPaint.h
    ./Source/PluginProcessor.h
    ./Source/TuxConstants.h
    ./Source/TitlePanel.cpp
    ./Source/TitlePanel.h
    ./Source/ToolButton.cpp
    ./Source/ToolButton.h
    ./Source/ColorButton.cpp
    ./Source/ColorButton.h
    ./Source/NamedToolButton.cpp
    ./Source/NamedToolButton.h
    ./Source/ScrollButton.cpp
    ./Source/ScrollButton.h

    ./Source/OptionPanels/ShapesOptionsPanel.cpp
    ./Source/OptionPanels/ShapesOptionsPanel.h
    ./Source/OptionPanels/ButtonSelector.cpp
    ./Source/OptionPanels/ButtonSelector.h
    ./Source/OptionPanels/FillOptionsPanel.cpp
    ./Source/OptionPanels/FillOptionsPanel.h
    ./Source/OptionPanels/EraserOptionPanel.cpp
    ./Source/OptionPanels/EraserOptionPanel.h
    ./Source/OptionPanels/BrushesOptionsPanel.cpp
    ./Source/OptionPanels/BrushesOptionsPanel.h
    ./Source/OptionPanels/MagicOptionPanel.cpp
    ./Source/OptionPanels/MagicOptionPanel.h

    ./Source/Canvas/GraphicsBase.cpp
    ./Source/Canvas/GraphicsBase.h
    ./Source/Canvas/FillGraphics.cpp
    ./Source/Canvas/FillGraphics.h
    ./Source/Canvas/EraserGraphics.cpp
    ./Source/Canvas/EraserGraphics.h
    ./Source/Canvas/BrushGraphics.cpp
    ./Source/Canvas/BrushGraphics.h
    ./Source/Canvas/MagicGraphics.cpp
    ./Source/Canvas/MagicGraphics.h

    ./Source/Canvas/Magic/MagicModes.h
    ./Source/Canvas/Magic/MagicConstants.h
    ./Source/Canvas/Magic/MagicBase.h
    ./Source/Canvas/Magic/MirrorFlip.h
    ./Source/Canvas/Magic/MirrorFlip.cpp
    ./Source/Canvas/Magic/Flip.h
    ./Source/Canvas/Magic/Mirror.h
    ./Source/Canvas/Magic/Distortion.cpp
    ./Source/Canvas/Magic/Distortion.h
    ./Source/Canvas/Magic/Blocks.cpp
    ./Source/Canvas/Magic/Blocks.h

    ./Source/BinaryDataHeaders/BinaryDataBrushes.h
    ./Source/BinaryDataHeaders/BinaryDataFills.h
    ./Source/BinaryDataHeaders/BinaryDataFonts.h
    ./Source/BinaryDataHeaders/BinaryDataUI.h
    ./Source/BinaryDataHeaders/BinaryDataMagicIcons.h
)
target_sources("${PROJECT_NAME}" PRIVATE ${SourceFiles})

# No, we don't want our source buried in extra nested folders
set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")

# The Xcode source tree should uhhh, still look like the source tree, yo
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Source PREFIX "" FILES ${SourceFiles})

juce_add_binary_data(MagicIcons
    HEADER_NAME BinaryDataMagicIcons.h
    NAMESPACE BinaryDataMagicIcons
    SOURCES
    ./Source/data/magicicons/smooth.png
    ./Source/data/magicicons/blur.png
    ./Source/data/magicicons/foam_data.png
    ./Source/data/magicicons/rails_four.png
    ./Source/data/magicicons/realrainbow-roygbiv-colors.png
    ./Source/data/magicicons/googly-eyes-bkgd.png
    ./Source/data/magicicons/3dglasses.png
    ./Source/data/magicicons/rainbow.png
    ./Source/data/magicicons/rails_one.png
    ./Source/data/magicicons/tv.png
    ./Source/data/magicicons/fretwork.png
    ./Source/data/magicicons/tint.png
    ./Source/data/magicicons/rails.png
    ./Source/data/magicicons/colornwhite.png
    ./Source/data/magicicons/swirls_circles.png
    ./Source/data/magicicons/largebrick.png
    ./Source/data/magicicons/grass_data.png
    ./Source/data/magicicons/metalpaint.png
    ./Source/data/magicicons/kaleido-8.png
    ./Source/data/magicicons/puzzle.png
    ./Source/data/magicicons/checkerboard.png
    ./Source/data/magicicons/realrainbow-roygbiv.png
    ./Source/data/magicicons/ripples.png
    ./Source/data/magicicons/swirls_fur.png
    ./Source/data/magicicons/fold.png
    ./Source/data/magicicons/string_art_angles.png
    ./Source/data/magicicons/smallbrick.png
    ./Source/data/magicicons/fretwork_three.png
    ./Source/data/magicicons/tornado.png
    ./Source/data/magicicons/tornado_base.png
    ./Source/data/magicicons/symmetric_updown.png
    ./Source/data/magicicons/rails_three.png
    ./Source/data/magicicons/halftone.png
    ./Source/data/magicicons/alien.png
    ./Source/data/magicicons/snowball.png
    ./Source/data/magicicons/blind.png
    ./Source/data/magicicons/loops.png
    ./Source/data/magicicons/calligraphy_brush.png
    ./Source/data/magicicons/rivulet-brush-sub.png
    ./Source/data/magicicons/Snow_flake4.png
    ./Source/data/magicicons/mosaic.png
    ./Source/data/magicicons/glasstile.png
    ./Source/data/magicicons/distortion.png
    ./Source/data/magicicons/stretch.png
    ./Source/data/magicicons/rush.png
    ./Source/data/magicicons/kalidescope.png
    ./Source/data/magicicons/fisheye.png
    ./Source/data/magicicons/realrainbow.png
    ./Source/data/magicicons/reflection.png
    ./Source/data/magicicons/string_art_full_by_offset.png
    ./Source/data/magicicons/emboss.png
    ./Source/data/magicicons/rails_corner.png
    ./Source/data/magicicons/fretwork_one.png
    ./Source/data/magicicons/confetti.png
    ./Source/data/magicicons/light.png
    ./Source/data/magicicons/rivulet-angles.png
    ./Source/data/magicicons/xor.png
    ./Source/data/magicicons/kaleido-6.png
    ./Source/data/magicicons/flower_base.png
    ./Source/data/magicicons/blocks.png
    ./Source/data/magicicons/bloom.png
    ./Source/data/magicicons/sharpen.png
    ./Source/data/magicicons/thin.png
    ./Source/data/magicicons/googlyeyes-sm.png
    ./Source/data/magicicons/string_art_triangles.png
    ./Source/data/magicicons/swirls_rays.png
    ./Source/data/magicicons/realrainbow-colors.png
    ./Source/data/magicicons/foam.png
    ./Source/data/magicicons/opposite.png
    ./Source/data/magicicons/rivulet.png
    ./Source/data/magicicons/saturate.png
    ./Source/data/magicicons/fade.png
    ./Source/data/magicicons/toothpaste.png
    ./Source/data/magicicons/googly-eyes-pupil.png
    ./Source/data/magicicons/kal_tiles.png
    ./Source/data/magicicons/wavelet.png
    ./Source/data/magicicons/calligraphy.png
    ./Source/data/magicicons/waves.png
    ./Source/data/magicicons/tornado_cloud.png
    ./Source/data/magicicons/darken.png
    ./Source/data/magicicons/googlyeyes.png
    ./Source/data/magicicons/perspective.png
    ./Source/data/magicicons/panels.png
    ./Source/data/magicicons/Snow_flake5.png
    ./Source/data/magicicons/squiggles.png
    ./Source/data/magicicons/zoom.png
    ./Source/data/magicicons/rosette.png
    ./Source/data/magicicons/clone.png
    ./Source/data/magicicons/rivulet-brush-add.png
    ./Source/data/magicicons/desaturate.png
    ./Source/data/magicicons/picasso.png
    ./Source/data/magicicons/cartoon.png
    ./Source/data/magicicons/symmetric_leftright.png
    ./Source/data/magicicons/flower_petals.png
    ./Source/data/magicicons/mirror.png
    ./Source/data/magicicons/pixels.png
    ./Source/data/magicicons/doublevision.png
    ./Source/data/magicicons/flip.png
    ./Source/data/magicicons/flower.png
    ./Source/data/magicicons/fretwork_four.png
    ./Source/data/magicicons/rain.png
    ./Source/data/magicicons/drip.png
    ./Source/data/magicicons/mosaic_shaped_irregular.png
    ./Source/data/magicicons/noise.png
    ./Source/data/magicicons/edges.png
    ./Source/data/magicicons/rivulet-brush-alpha.png
    ./Source/data/magicicons/wetpaint.png
    ./Source/data/magicicons/fretwork_corner.png
    ./Source/data/magicicons/flower_leaf.png
    ./Source/data/magicicons/smudge.png
    ./Source/data/magicicons/thick.png
    ./Source/data/magicicons/shift.png
    ./Source/data/magicicons/mosaic_shaped_hex.png
    ./Source/data/magicicons/mosaic_shaped_square.png
    ./Source/data/magicicons/grass.png
    ./Source/data/magicicons/googly-eyes-reflection.png
    ./Source/data/magicicons/kaleido-4.png
    ./Source/data/magicicons/remove_color.png
    ./Source/data/magicicons/tilezoom.png
    ./Source/data/magicicons/colorsep.png
    ./Source/data/magicicons/ribbon.png
    ./Source/data/magicicons/keep_color.png
    ./Source/data/magicicons/silhouette.png
    ./Source/data/magicicons/snowflake.png
    ./Source/data/magicicons/negative.png
    ./Source/data/magicicons/maze.png
    ./Source/data/magicicons/kal_pattern.png
    ./Source/data/magicicons/chalk.png
    ./Source/data/magicicons/lightning.png
    )

juce_add_binary_data(Tools
    HEADER_NAME BinaryDataTools.h
    NAMESPACE BinaryDataTools
    SOURCES
    ./Source/data/images/tools/label_apply.png
    ./Source/data/images/tools/quit.png
    ./Source/data/images/tools/new.png
    ./Source/data/images/tools/undo.png
    ./Source/data/images/tools/open.png
    ./Source/data/images/tools/stamp.png
    ./Source/data/images/tools/text.png
    ./Source/data/images/tools/label_select.png
    ./Source/data/images/tools/shapes.png
    ./Source/data/images/tools/magic.png
    ./Source/data/images/tools/redo.png
    ./Source/data/images/tools/eraser.png
    ./Source/data/images/tools/print.png
    ./Source/data/images/tools/lines.png
    ./Source/data/images/tools/fill.png
    ./Source/data/images/tools/save.png
    ./Source/data/images/tools/speak.png
    ./Source/data/images/tools/sfx.png
    ./Source/data/images/tools/brush.png
    ./Source/data/images/tools/label.png
    )

juce_add_binary_data(Brushes
        HEADER_NAME BinaryDataBrushes.h
        NAMESPACE BinaryDataBrushes
        SOURCES
        ./Source/data/brushes/heart.png
        ./Source/data/brushes/flower_6_small.png
        ./Source/data/brushes/slash_10_lt.png
        ./Source/data/brushes/aa_round_fuzz.png
        ./Source/data/brushes/slash_20_lt.png
        ./Source/data/brushes/rotating_dash.png
        ./Source/data/brushes/kuroneko.png
        ./Source/data/brushes/hexagon.png
        ./Source/data/brushes/lines-angled.png
        ./Source/data/brushes/spray.png
        ./Source/data/brushes/aa_round_seethru_10.png
        ./Source/data/brushes/slash_20_rt.png
        ./Source/data/brushes/spiral.png
        ./Source/data/brushes/square_fuzz.png
        ./Source/data/brushes/aa_round_03.png
        ./Source/data/brushes/aa_round_36.png
        ./Source/data/brushes/square_12.png
        ./Source/data/brushes/tiny.png
        ./Source/data/brushes/flower_7.png
        ./Source/data/brushes/diamond.png
        ./Source/data/brushes/flower_6.png
        ./Source/data/brushes/slash_10_rt.png
        ./Source/data/brushes/aa_round_24.png
        ./Source/data/brushes/slash_16_rt.png
        ./Source/data/brushes/aa_round_seethru_05.png
        ./Source/data/brushes/square_seethru.png
        ./Source/data/brushes/square_06.png
        ./Source/data/brushes/splat.png
        ./Source/data/brushes/cutout_square_diamond.png
        ./Source/data/brushes/aa_round_06.png
        ./Source/data/brushes/triangle_up.png
        ./Source/data/brushes/squirrel.png
        ./Source/data/brushes/vine.png
        ./Source/data/brushes/pentagon.png
        ./Source/data/brushes/triangle_down.png
        ./Source/data/brushes/footprints-paws.png
        ./Source/data/brushes/arrow.png
        ./Source/data/brushes/sphere.png
        ./Source/data/brushes/footprints-human-shoes.png
        ./Source/data/brushes/arrow_triangles.png
        ./Source/data/brushes/lozenge.png
        ./Source/data/brushes/aa_round_12.png
        ./Source/data/brushes/flower_5_small.png
        ./Source/data/brushes/footprints-human.png
        ./Source/data/brushes/slash_16_lt.png
        ./Source/data/brushes/chisle.png
        ./Source/data/brushes/blob.png
        ./Source/data/brushes/x.png
        ./Source/data/brushes/sparkles.png
        ./Source/data/brushes/cutout_star_circle.png
        ./Source/data/brushes/dog.png
        ./Source/data/brushes/oval.png
        ./Source/data/brushes/flower_5.png
        ./Source/data/brushes/square_36.png
        ./Source/data/brushes/inksplat.png
        ./Source/data/brushes/aa_round_seethru.png
        ./Source/data/brushes/square_24.png
        ./Source/data/brushes/star.png
        )
juce_add_binary_data(Fonts
        HEADER_NAME BinaryDataFonts.h
        NAMESPACE BinaryDataFonts
        SOURCES
        ./Source/data/fonts/FreeSerif.ttf
        ./Source/data/fonts/FreeSerifBold.ttf
        ./Source/data/fonts/FreeMono.ttf
        ./Source/data/fonts/FreeSerifItalic.ttf
        ./Source/data/fonts/FreeMonoBoldOblique.ttf
        ./Source/data/fonts/FreeSansBoldOblique.ttf
        ./Source/data/fonts/FreeMonoBold.ttf
        ./Source/data/fonts/FreeMonoOblique.ttf
        ./Source/data/fonts/FreeSansBold.ttf
        ./Source/data/fonts/FreeSans.ttf
        ./Source/data/fonts/default_font.ttf
        ./Source/data/fonts/FreeSerifBoldItalic.ttf
        ./Source/data/fonts/FreeSansOblique.ttf
        )
juce_add_binary_data(Fills
        HEADER_NAME BinaryDataFills.h
        NAMESPACE BinaryDataFills
        SOURCES
        ./Source/data/images/fills/gradient_linear.png
        ./Source/data/images/fills/solid.png
        ./Source/data/images/fills/gradient_shaped.png
        ./Source/data/images/fills/gradient_radial.png
        ./Source/data/images/fills/brush.png
        )

juce_add_binary_data(Shapes
        HEADER_NAME BinaryDataShapes.h
        NAMESPACE BinaryDataShapes
        SOURCES
        ./Source/data/images/shapes/circle.png
        ./Source/data/images/shapes/heptagon.png
        ./Source/data/images/shapes/star4p_f.png
        ./Source/data/images/shapes/hexagon.png
        ./Source/data/images/shapes/square_f.png
        ./Source/data/images/shapes/star4p.png
        ./Source/data/images/shapes/heptagon_f.png
        ./Source/data/images/shapes/square.png
        ./Source/data/images/shapes/diamond.png
        ./Source/data/images/shapes/rectangle.png
        ./Source/data/images/shapes/oval_f.png
        ./Source/data/images/shapes/star5p_f.png
        ./Source/data/images/shapes/rectangle_f.png
        ./Source/data/images/shapes/pentagon.png
        ./Source/data/images/shapes/star3p.png
        ./Source/data/images/shapes/circle_f.png
        ./Source/data/images/shapes/triangle.png
        ./Source/data/images/shapes/star5p.png
        ./Source/data/images/shapes/hexagon_f.png
        ./Source/data/images/shapes/diamond_f.png
        ./Source/data/images/shapes/octagon_f.png
        ./Source/data/images/shapes/triangle_f.png
        ./Source/data/images/shapes/oval.png
        ./Source/data/images/shapes/star3p_f.png
        ./Source/data/images/shapes/pentagon_f.png
        ./Source/data/images/shapes/octagon.png
        )

juce_add_binary_data(ui
        HEADER_NAME BinaryDataUI.h
        NAMESPACE BinaryDataUI
        SOURCES
        ./Source/data/images/ui/printer.png
        ./Source/data/images/ui/cmix.png
        ./Source/data/images/ui/rotate.png
        ./Source/data/images/ui/paintcan.png
        ./Source/data/images/ui/color_btn_up.png
        ./Source/data/images/ui/cursor_up.png
        ./Source/data/images/ui/magic_fullscreen.png
        ./Source/data/images/ui/btn_off.png
        ./Source/data/images/ui/shapes_corner.png
        ./Source/data/images/ui/btnsm_hold.png
        ./Source/data/images/ui/slideshow.png
        ./Source/data/images/ui/trash.png
        ./Source/data/images/ui/play.png
        ./Source/data/images/ui/scroll_down_off.png
        ./Source/data/images/ui/btnsm_off.png
        ./Source/data/images/ui/erase.png
        ./Source/data/images/ui/select_digits.png
        ./Source/data/images/ui/prev.png
        ./Source/data/images/ui/color_picker_val.png
        ./Source/data/images/ui/progress.png
        ./Source/data/images/ui/no_title_large.png
        ./Source/data/images/ui/btnsm_up.png
        ./Source/data/images/ui/open.png
        ./Source/data/images/ui/save_over.png
        ./Source/data/images/ui/no.png
        ./Source/data/images/ui/osk_enter.png
        ./Source/data/images/ui/btnsm_down.png
        ./Source/data/images/ui/color_btn_down.png
        ./Source/data/images/ui/grow.png
        ./Source/data/images/ui/btn_down.png
        ./Source/data/images/ui/cursor_starter_up.png
        ./Source/data/images/ui/brush_anim.png
        ./Source/data/images/ui/dead40x40.png
        ./Source/data/images/ui/color_grab.png
        ./Source/data/images/ui/cursor_down_large.png
        ./Source/data/images/ui/title_large.png
        ./Source/data/images/ui/osk_capslock.png
        ./Source/data/images/ui/csel.png
        ./Source/data/images/ui/btn_nav.png
        ./Source/data/images/ui/back.png
        ./Source/data/images/ui/magic_paint.png
        ./Source/data/images/ui/paintwell.png
        ./Source/data/images/ui/next.png
        ./Source/data/images/ui/italic.png
        ./Source/data/images/ui/btnsm_nav.png
        ./Source/data/images/ui/yes.png
        ./Source/data/images/ui/color_picker.png
        ./Source/data/images/ui/cursor_up_large.png
        ./Source/data/images/ui/mouse_click.png
        ./Source/data/images/ui/mirror.png
        ./Source/data/images/ui/cursor_down.png
        ./Source/data/images/ui/cursor_starter_down.png
        ./Source/data/images/ui/brush_dir.png
        ./Source/data/images/ui/osk_tab.png
        ./Source/data/images/ui/flip.png
        ./Source/data/images/ui/bold.png
        ./Source/data/images/ui/shapes_center.png
        ./Source/data/images/ui/scroll_up_off.png
        ./Source/data/images/ui/title.png
        ./Source/data/images/ui/template.png
        ./Source/data/images/ui/no_title.png
        ./Source/data/images/ui/mouse.png
        ./Source/data/images/ui/popup_arrow.png
        ./Source/data/images/ui/gif_export.png
        ./Source/data/images/ui/btn_hold.png
        ./Source/data/images/ui/sparkles-old.png
        ./Source/data/images/ui/color_picker_icon.png
        ./Source/data/images/ui/btn_up.png
        ./Source/data/images/ui/pict_export.png
        ./Source/data/images/ui/osk_delete.png
        ./Source/data/images/ui/printer_wait.png
        ./Source/data/images/ui/osk_shift.png
        ./Source/data/images/ui/scroll_down.png
        ./Source/data/images/ui/scroll_up.png
        ./Source/data/images/ui/shrink.png
        )
# Required for Linux happiness:
# See https://forum.juce.com/t/loading-pytorch-model-using-binarydata/39997/2
set_target_properties(MagicIcons PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Brushes PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Fonts PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Fills PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(ui PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Tools PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(Shapes PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

# Clean up folder organization on Xcode.
# It tucks the Plugin varieties into a "Targets" folder and generate an Xcode Scheme manually
# Xcode scheme generation is turned off globally to limit noise from other targets
# The non-hacky way of doing this is via the global PREDEFINED_TARGETS_FOLDER property
# However that doesn't seem to be working in Xcode
# Not all plugin types (au, vst) available on each build type (win, macos, linux)
foreach (target ${FORMATS} "All")
    if (TARGET ${PROJECT_NAME}_${target})
        set_target_properties(${PROJECT_NAME}_${target} PROPERTIES
            # Tuck the actual plugin targets into a folder where they won't bother us
            FOLDER "Targets"

            # MacOS only: Sets the default executable that Xcode will open on build
            # For this exact path to to work, manually build the AudioPluginHost.xcodeproj in the JUCE subdir
            XCODE_SCHEME_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/extras/AudioPluginHost/Builds/MacOSX/build/Debug/AudioPluginHost.app"

            # Let us build the target in Xcode
            XCODE_GENERATE_SCHEME ON)
    endif ()
endforeach ()

set_target_properties(MagicIcons PROPERTIES FOLDER "Targets")
set_target_properties(Brushes PROPERTIES FOLDER "Targets")
set_target_properties(Fonts PROPERTIES FOLDER "Targets")
set_target_properties(Fills PROPERTIES FOLDER "Targets")
set_target_properties(ui PROPERTIES FOLDER "Targets")
set_target_properties(Tools PROPERTIES FOLDER "Targets")
set_target_properties(Shapes PROPERTIES FOLDR "Targets")
target_compile_definitions("${PROJECT_NAME}"
    PUBLIC
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries("${PROJECT_NAME}"
    PUBLIC
    MagicIcons
    Brushes
    Fonts
    Fills
    ui
    Tools
    Shapes)
target_link_libraries("${PROJECT_NAME}"
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_dsp)

# When present, use Intel IPP for performance on Windows
if (WIN32) # Can't use MSVC here, as it won't catch Clang on Windows
    find_package(IPP)
    if (IPP_FOUND)
        target_link_libraries("${PROJECT_NAME}" PUBLIC IPP::ipps IPP::ippcore IPP::ippi IPP::ippcv)
        message("IPP LIBRARIES FOUND")
        target_compile_definitions("${PROJECT_NAME}" PUBLIC PAMPLEJUCE_IPP=1)
    else ()
        message("IPP LIBRARIES *NOT* FOUND")
    endif ()
endif ()

# Color our warnings and errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif ()
