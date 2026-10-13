// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the tlRender project.

#include <tlRender/Timeline/IRender.h>

namespace tl
{
    IRender::~IRender()
    {}

    void IRender::setAlphaBlendResolver(
        const std::function<std::optional<ftk::AlphaBlend>(
            const std::string& path)>&)
    {}
}
