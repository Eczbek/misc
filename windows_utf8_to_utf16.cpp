#include <string>
#include <windows.h>

std::wstring utf8_to_utf16(std::string_view utf8_str) {
    // MultiByteToWideChar does not accept empty strings
    if (utf8_str.empty()) {
        return {};
    }

    std::wstring utf16_str;
    utf16_str.resize_and_overwrite(utf8_str.length(), [data = utf8_str.data()](wchar_t* buffer, size_t length) {
        int len = static_cast<int>(length);
        return ::MultiByteToWideChar(CP_UTF8, 0, data, len, buffer, len);
    });
    return utf16_str;
}

std::string utf16_to_utf8(std::wstring_view utf16_str) {
    // WideCharToMultiByte does not accept empty strings
    if (utf16_str.empty()) {
        return {};
    }

    const size_t length = utf16_str.length();

    std::string utf8_str;
    // a UTF-16 sequence can convert to a UTF-8 sequence with at most triple the code units
    utf8_str.resize_and_overwrite(3 * length, [length, data = utf16_str.data()](char* buffer, size_t capacity) {
        int len = static_cast<int>(length);
        int cap = static_cast<int>(capacity);
        return ::WideCharToMultiByte(CP_UTF8, 0, data, len, buffer, cap, nullptr, nullptr);
    });
    return utf8_str;
}

int main() {}
