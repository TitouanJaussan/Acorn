#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <string>

// This is kind of a separate project, so it does not follow the same conventions as the rest of the engine
// The codestyle approches C because this is meant to be a minimal lib (header only).

/* A few rules to absolutely respect for this API
 * - Always create the block instance within the return
 * - Always initialize the size at initialization (e.g. at 'return')
 * - Always return a new block from a function, never make a function
 *     directly modify a block, even if it's a minor modification
 */

namespace Acorn::tui
{
    using signed_size_t = ptrdiff_t;

    struct Block
    {
        std::vector<std::string> lines{};
        size_t width{0};
        size_t height{0};
    };

    template<typename... Args>
    inline std::string concat(Args&&... args)
    {
        std::string result;
        (result += ... += std::forward<Args>(args));
        return result;
    }

    /* --- String related operations --- */
    inline std::pair<std::string, std::string> cut(std::string in, size_t splitColumn)
    {
        if (in.size() > splitColumn)
            in += std::string(in.size() - splitColumn, ' ');
        else
            in += std::string(splitColumn - in.size(), ' ');

        return std::make_pair(
            in.substr(0, splitColumn),
            in.substr(splitColumn, in.size() - splitColumn));
    }

    inline std::string flatten(Block block)
    {
        std::string out{};

        for (const auto& line: block.lines)
            out += line + "\n";

        return out;
    }

    inline size_t visualWidth(const std::string& string)
    {
        size_t width{0};
        for (auto it = string.begin(); it != string.end() && *it != 0; ++it)
            width += ((*it & 0xc0) != 0x80);

        return width;
    }

    inline size_t computeWidth(const std::vector<std::string>& content)
    {
        size_t w{0};

        for (const auto& line: content)
            w = std::max(visualWidth(line), w);

        return w;
    }

    inline size_t computeHeight(const std::vector<std::string>& content)
    {
        return content.size();
    }

    inline size_t maxWidth(const std::vector<Block>& blocks)
    {
        size_t w{0};
        for (const Block& block: blocks)
            w = std::max(w, block.width);

        return w;
    }

    inline size_t maxHeight(const std::vector<Block>& blocks)
    {
        size_t h{0};
        for (const Block& block: blocks)
            h = std::max(h, block.height);

        return h;
    }

    /* --- Generators --- */
    inline Block empty()
    {
        return Block
        {
            .lines = {},
            .width = 0,
            .height = 0
        };
    }

    inline Block text(const std::string& txt)
    {
        return Block
        {
            .lines = {std::string(txt)},
            .width = visualWidth(txt),
            .height = 1
        };
    }

    inline Block column(std::vector<std::string> elements)
    {
        const size_t w = computeWidth(elements);
        const size_t h = computeHeight(elements);

        return Block
        {
            .lines = std::move(elements),
            .width = w,
            .height = h
        };
    }

    inline Block makeColumn(std::string val, size_t height)
    {
        return column(std::vector(height, val));
    }

    inline std::string makeStringRow(const std::string& val, size_t count)
    {
        std::string result{};

        for (size_t i = 0; i < count; i++)
            result += val;

        return result;
    }

    inline Block makeRow(const std::string& val, size_t count)
    {
        return column(std::vector{makeStringRow(val, count)});
    }

    /* --- Transforms --- */
    inline Block hstack(std::vector<Block> blocks)
    {
        const size_t maxH = maxHeight(blocks);
        std::vector<std::string> lines{};
        lines.reserve(maxH);

        for (size_t i = 0; i < maxH; i++)
        {
            std::string line{};
            for (auto& block: blocks)
            {
                if (i >= block.height)
                {
                    line += std::string(block.width, ' '); //FIXME: Super expensive, fix as soon as possible
                    continue;
                }
                
                line += block.lines[i] +
                    std::string(block.width - visualWidth(block.lines[i]),' ');
            }

            lines.push_back(std::move(line));
        }

        return column(lines);
    }

    inline Block vstack(std::vector<Block> blocks)
    {
        std::vector<std::string> lines{};

        for (const auto& block: blocks)
        {
            lines.insert(
                lines.end(),
                block.lines.begin(),
                block.lines.end()
            );
        }

        return column(lines);
    }

    /*
     * - Reductive transform ∀ dist ∈ℤ & dist < 0
     * - Additive transform ∀ dist ∈ℤ & dist > 0
     * - Identity transform for dist = 0
     */
    inline Block hshift(Block block, const signed_size_t distance)
    {
        if (distance == 0) return block;

        std::vector<std::string> lines{};
        lines.reserve(block.height);

        if (distance > 0)
        {
            for (const auto& line: block.lines)
            {
                lines.push_back(concat(
                    std::string(distance, ' '),
                    line
                ));
            }
        }
        else
        {
            for (const auto& line: block.lines)
                lines.push_back(line.substr(-distance, visualWidth(line) + distance));
        }

        return column(lines);
    }

    /*
     * - Reductive transform ∀ dist ∈ℤ & dist < 0
     * - Additive transform ∀ dist ∈ℤ & dist > 0
     * - Identity transform for dist = 0
     */
    inline Block vshift(Block block, const signed_size_t distance)
    {
        if (distance == 0) return block;
        if (-distance >= (signed_size_t)block.height) return column({});

        std::vector<std::string> lines{};
        lines.reserve(block.height + distance);

        if (distance < 0)
            lines.insert(
                lines.end(), // Or .begin()
                block.lines.begin() - distance,
                block.lines.end()
            );
        else
        {
            for (size_t i = 0; i < (size_t)distance; i++)
                lines.push_back(std::string());

            lines.insert(
                lines.end(),
                block.lines.begin(),
                block.lines.end()
            );
        }

        return column(lines);
    }

    /* Homogeneously destructive transform, of width `object.width + 2` */
    inline Block border(Block block)
    {
        std::vector<std::string> lines{};
        lines.reserve(block.height + 2);

        const std::string lineRow = makeStringRow("─", block.width);

        lines.push_back("┌" + lineRow + "┐");

        for (const auto& line: block.lines)
        {
            const size_t rightPad = block.width - visualWidth(line);
            lines.push_back(concat(
                "│", line,
                std::string(rightPad, ' '),
                "│"));
        }

        lines.push_back("└" + lineRow + "┘");

        return column(lines);
    }

    /* Homogeneously destructive, of width `width` */
    inline Block setWidth(Block block, const size_t width)
    {
        std::vector<std::string> lines{};
        lines.reserve(block.height);

        for (const auto& line: block.lines)
            lines.push_back(cut(line, width).first);

        return column(lines);
    }

    inline Block setHeight(Block block, const size_t height)
    {
        std::vector<std::string> lines{};

        lines.insert(
            lines.begin(),
            block.lines.begin(),
            block.lines.begin() + height
        );

        return column(lines);
    }

    inline Block alignRight(Block block)
    {
        std::vector<std::string> lines{};
        lines.reserve(block.lines.size());

        for (const auto& line: block.lines)
        {
            lines.push_back(concat(
                std::string(block.width - visualWidth(line), ' '),
                line));
        }

        return column(lines);
    }

    /* Homogeneously destructive, of width `desiredWidth` */
    inline Block alignCenter(Block block)
    {
        std::vector<std::string> lines{};
        lines.reserve(block.lines.size());

        for (const auto& line: block.lines)
        {
            const size_t gap = block.width - visualWidth(line);

            lines.push_back(concat(
                std::string(gap / 2, ' '),
                line,
                std::string(gap - gap / 2, ' ')
            ));
        }

        return column(lines);
    }

    inline Block alignRight(Block block, size_t desiredWidth)
    {
        std::vector<std::string> lines{};
        lines.reserve(block.lines.size());

        for (const auto& line: block.lines)
        {
            const size_t gap = desiredWidth - visualWidth(line);
            lines.push_back(concat(
                std::string(gap, ' '), line));
        }

        return column(lines);
    }

    inline Block alignCenter(Block block, size_t desiredWidth)
    {
        if (desiredWidth == block.width) return block;

        block = alignCenter(block);
        if (desiredWidth < block.width)
        {
            const size_t offset = block.width - desiredWidth;
            return setWidth(hshift(block, offset / 2), desiredWidth);
        }
        else
        {
            const size_t offset = desiredWidth - block.width;
            return setWidth(hshift(block, offset / 2), desiredWidth);
        }
    }

    inline std::pair<Block, Block> hsplit(Block block, const size_t splitColumn)
    {
        std::vector<std::string> leftLines{};
        std::vector<std::string> rightLines{};

        leftLines.reserve(block.height);
        rightLines.reserve(block.height);

        for (size_t row = 0; row < block.height; row++)
        {
            auto [left, right] = cut(block.lines[row], splitColumn);
            leftLines.push_back(left);
            rightLines.push_back(right);
        }

        return std::make_pair(column(leftLines), column(rightLines));
    }

    inline std::pair<Block, Block> vsplit(Block block, const size_t splitRow)
    {
        std::vector<std::string> topLines{};
        std::vector<std::string> bottomLines{};

        topLines.reserve(splitRow);
        bottomLines.reserve(block.height - splitRow);

        topLines.insert(
            topLines.begin(),
            block.lines.begin(),
            block.lines.begin() + splitRow
        );

        bottomLines.insert(
            bottomLines.begin(),
            block.lines.begin() + splitRow,
            block.lines.end()
        );

        return std::make_pair(column(topLines), column(bottomLines));
    }
}
