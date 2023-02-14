#include "CEngine.h"

CEngine::CEngine(int width, int height) {
    this->width = width;
    this->height = height;

    screenBuffer = new char[width * height + 1];

    for (size_t i = 0; i < width * height; i++) screenBuffer[i] = ' ';
    SetConsoleSize(width, height);
    screenBuffer[width * height] = '\0';
    // To read/write Chinese characters, we set code page to 936.
    SetConsoleCP(936);
    SetConsoleOutputCP(936);
    windowState = true;
}

void CEngine::setPixelSize(int width, int height) {
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = width;                   // Width of each character in the font
    cfi.dwFontSize.Y = height;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

}

void CEngine::addModel(TModel* model) {
    objectsTable.push_back(model);
}

bool CEngine::getState() const {
    return windowState;
}

void CEngine::run() {

    for (size_t i = 0; i < width * height; i++) screenBuffer[i] = ' ';
    for (auto& model : objectsTable)
    {
        //if ((int)model->y >= 0 && (int)model->y < (height - 1)&& (int)model->x >= 0 && (int)model->x < width) {

        for (int c = 0; c < model->getLength(); c++)
        {
            if (((int)model->y + ((c - c % model->width) / model->width)) >= 0 && ((int)model->y + ((c - c % model->width) / model->width)) < height
                && ((int)model->x + (c % model->width)) >= 0 && ((int)model->x + (c % model->width)) < width) {

                screenBuffer[((int)model->y + ((c - c % model->width) / model->width)) * width + ((int)model->x + (c % model->width))] = model->screenBuffer[c];
            }
        }
    }
}

void CEngine::render() {
    printf(screenBuffer);
}

bool CEngine::detectCollision(TModel first, TModel second) {
    float a_l = 0;
    float b_l = 0;

    if (first.getPosition().x < second.getPosition().x) {
        a_l = first.getSize().width;
    }
    else {
        a_l = second.getSize().width;
    }

    if (first.getPosition().y < second.getPosition().y) {
        b_l = first.getSize().height;
    }
    else {
        b_l = second.getSize().height;
    }
    if ((abs(first.getPosition().x - second.getPosition().x) <= a_l) &&
        (abs(first.getPosition().y - second.getPosition().y) <= b_l)) {
        return true;
    }
    else {
        return false;
    }
}

BOOL CEngine::SetConsoleSize(int cols, int rows) {
    int w, h, bw, bh;
    RECT rect = { 0, 0, 0, 0 };
    COORD coord = { 0, 0 };

    hWnd = GetConsoleWindow();

    if (hWnd) {
        hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConOut && hConOut != (HANDLE)-1) {
            if (GetCurrentConsoleFont(hConOut, FALSE, &fi)) {
                if (GetClientRect(hWnd, &rect)) {
                    w = rect.right - rect.left;
                    h = rect.bottom - rect.top;
                    if (GetWindowRect(hWnd, &rect)) {
                        bw = rect.right - rect.left - w;
                        bh = rect.bottom - rect.top - h;
                        if (GetConsoleScreenBufferInfo(hConOut, &bi)) {
                            coord.X = bi.dwSize.X;
                            coord.Y = bi.dwSize.Y;
                            if (coord.X < cols || coord.Y < rows) {
                                if (coord.X < cols) {
                                    coord.X = cols;
                                }
                                if (coord.Y < rows) {
                                    coord.Y = rows;
                                }
                                if (!SetConsoleScreenBufferSize(hConOut, coord)) {
                                    return FALSE;
                                }
                            }
                            return SetWindowPos(hWnd, NULL, rect.left, rect.top, cols * fi.dwFontSize.X + bw, rows * fi.dwFontSize.Y + bh, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}