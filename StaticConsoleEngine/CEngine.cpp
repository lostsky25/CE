#include "CEngine.h"

CEngine::CEngine(int width, int height) {
    this->width = width;
    this->height = height;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    screenBuffer = new CHAR_INFO[width * height + 1];

    for (size_t i = 0; i < width * height; i++) screenBuffer[i].Char.UnicodeChar = ' ';
    //for (size_t i = 0; i < width * height; i++) screenBuffer[i].Attributes = FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

    SetConsoleSize(width, height);
    //screenBuffer[width * height] = '\0';
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
    std::wcscpy(cfi.FaceName, L"Times New Roman"); // Choose your font
    SetCurrentConsoleFontEx(hStdOut, FALSE, &cfi);

}

void CEngine::addModel(TModel* model) {
    objectsTable.push_back(model);
}

bool CEngine::getState() const {
    return windowState;
}

void CEngine::run() {

    //for (size_t i = 0; i < width * height; i++) screenBuffer[i] = ' ';
    for (auto& model : objectsTable)
    {
        //if ((int)model->y >= 0 && (int)model->y < (height - 1)&& (int)model->x >= 0 && (int)model->x < width) {

        for (int c = 0; c < model->getLength(); c++)
        {
            if (((int)model->y + ((c - c % model->width) / model->width)) >= 0 && ((int)model->y + ((c - c % model->width) / model->width)) < height
                && ((int)model->x + (c % model->width)) >= 0 && ((int)model->x + (c % model->width)) < width) {

                screenBuffer[((int)model->y + ((c - c % model->width) / model->width)) * width + ((int)model->x + (c % model->width))].Char.UnicodeChar = model->screenBuffer[c].Char.UnicodeChar;
            }
        }
    }
}
void CEngine::render() {
    current_ticks = clock();
    SMALL_RECT m_rectWindow;
    m_rectWindow = { 0, 0, (short)50, (short)50 };
    SetConsoleWindowInfo(hStdOut, TRUE, &m_rectWindow);
    //WriteConsole(hStdOut, screenBuffer, wcslen(screenBuffer), NULL, NULL); 
    WriteConsoleOutputW(hStdOut, screenBuffer, { (short)width, (short)height }, { (short)0, (short)0 }, &m_rectWindow);
    delta_ticks = clock() - current_ticks;
    if (delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;

    sprintf(windowTitle, "FPS: %ld", fps);
    SetWindowTextA(GetConsoleWindow(), windowTitle);
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
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut && hStdOut != (HANDLE)-1) {
            if (GetCurrentConsoleFont(hStdOut, FALSE, &fi)) {
                if (GetClientRect(hWnd, &rect)) {
                    w = rect.right - rect.left;
                    h = rect.bottom - rect.top;
                    if (GetWindowRect(hWnd, &rect)) {
                        bw = rect.right - rect.left - w;
                        bh = rect.bottom - rect.top - h;
                        if (GetConsoleScreenBufferInfo(hStdOut, &bi)) {
                            coord.X = bi.dwSize.X;
                            coord.Y = bi.dwSize.Y;
                            if (coord.X < cols || coord.Y < rows) {
                                if (coord.X < cols) {
                                    coord.X = cols;
                                }
                                if (coord.Y < rows) {
                                    coord.Y = rows;
                                }
                                if (!SetConsoleScreenBufferSize(hStdOut, coord)) {
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