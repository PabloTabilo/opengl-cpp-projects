#include "Grid.hpp"
#include <algorithm>

Grid::Grid(int width, int height)
    : m_width(width), m_height(height), m_cells(width * height, 0)
{
}

void Grid::toggleCell(int x, int y)
{
    if(x < 0 || x >= m_width || y < 0 || y >= m_height) return;
    int idx = index(x, y);
    m_cells[idx] = m_cells[idx] ? 0 : 1;
}

void Grid::setCell(int x, int y, bool on) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
    m_cells[index(x, y)] = on ? 1 : 0;
}


bool Grid::isOn(int x, int y) const
{
    if(x < 0 || x >= m_width || y < 0 || y >= m_height) return false;
    int idx = index(x, y);
    return m_cells[idx] != 0;
}

void Grid::buildColorBuffer(std::vector<uint8_t>& outBuffer) const {
    outBuffer.resize(m_width * m_height * 4); // RGBA

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            int gridY = m_height - 1 - y; // <-- invertir eje Y
            int idx  = index(x, gridY);
            bool on  = m_cells[idx] != 0;

            bool dark = ((x + y) % 2 == 0);
            uint8_t r, g, b;
            uint8_t a = 255;

            if (on) {
                r = 255; g = 230; b = 50;
            } else {
                if (dark) { r = g = b = 30; }
                else      { r = g = b = 50; }
            }

            int base = (y * m_width + x) * 4;
            outBuffer[base + 0] = r;
            outBuffer[base + 1] = g;
            outBuffer[base + 2] = b;
            outBuffer[base + 3] = a;
        }
    }
}

