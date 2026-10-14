// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the tlRender project.

#include <tlRender/Timeline/TimelineOptions.h>

#include <ftk/Core/Error.h>
#include <ftk/Core/String.h>

#include <algorithm>
#include <sstream>
#include <thread>

namespace tl
{
    FTK_ENUM_IMPL(
        ImageSeqAudio,
        "None",
        "Ext",
        "FileName");

    FTK_ENUM_IMPL(
        Spatial,
        "None",
        "Coordinates",
        "Normalize");

    size_t getDefaultReadThreadCount()
    {
        // Not one for every core. Reading is mostly waiting on the disk, and
        // every read in flight shares it: reading 4K EXRs, thirty-two threads
        // read no more frames a second than eight, and each frame took several
        // times as long, up to seconds for the last of them, so the frame the
        // playhead needed waited behind the others and was dropped. A format
        // that is expensive to decode can use more, and the setting is there
        // for it.
        //
        // From a fast SSD, though, decoding is the limit rather than the
        // disk: 2560x1440 half float OpenEXR frames read 315 a second on
        // eight threads and 509 on sixteen when ZIP compressed. Half the
        // cores, up to sixteen, and at least eight where there are that
        // many: the playhead's frame is asked for first, so the frames in
        // flight beside it are no longer what it waits behind.
        const unsigned int cores = std::thread::hardware_concurrency();
        return std::clamp(std::max(cores / 2, std::min(cores, 8u)), 1u, 16u);
    }

}
