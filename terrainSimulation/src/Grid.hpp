#pragma once
#include <vector>
#include <cstdint>

class Grid{
    public:
        Grid(int width, int height);
        void toggleCell(int x, int y);
        void setCell(int x, int y, bool on);
        bool isOn(int x, int y) const;

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        void buildColorBuffer(std::vector<uint8_t>& outBuffer) const;
    private:
        int m_width, m_height;
        std::vector<uint8_t> m_cells; // 0 = off, 1 = on
        int index(int x, int y) const { return y * m_width + x;}
};