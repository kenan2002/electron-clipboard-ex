#include <Windows.h>
#include <ShlObj.h>
#include "clipboard.h"

std::string Utf16CStringToUtf8String(LPCWSTR input, UINT len) {
    int target_len = WideCharToMultiByte(CP_UTF8, 0, input, len, NULL, 0, NULL, NULL);
    std::string result(target_len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, input, len, result.data(), target_len, NULL, NULL);
    return result;
}

std::vector<std::string> ReadFilePaths() {
    auto result = std::vector<std::string>();

    if (!OpenClipboard(NULL)) {
        return result;
    }

    HDROP drop_files_handle = (HDROP)GetClipboardData(CF_HDROP);
    if (drop_files_handle) {
        UINT file_count = DragQueryFileW(drop_files_handle, 0xFFFFFFFF, NULL, 0);
        result.reserve(file_count);
        for (UINT i = 0; i < file_count; ++i) {
            UINT path_len = DragQueryFileW(drop_files_handle, i, NULL, 0);
            UINT buffer_len = path_len + 1;
            LPWSTR buffer = new WCHAR[buffer_len];
            path_len = DragQueryFileW(drop_files_handle, i, buffer, buffer_len);
            result.emplace_back(Utf16CStringToUtf8String(buffer, path_len));
            delete [] buffer;
        }
    }

    CloseClipboard();

    return result;
}

std::wstring Utf8StringToUtf16String(const std::string &input) {
    int target_len = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), input.size(), NULL, 0);
    std::wstring result(target_len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), input.size(), result.data(), target_len);
    return result;
}

std::vector<std::wstring> Utf8StringToUtf16String(const std::vector<std::string> &input) {
    auto result = std::vector<std::wstring>();
    result.reserve(input.size());
    for (auto p = input.cbegin(); p != input.cend(); ++p) {
        result.emplace_back(Utf8StringToUtf16String(*p));
    }
    return result;
}

void WriteFilePaths(const std::vector<std::string> &file_paths) {
    const std::vector<std::wstring> file_paths_unicode = Utf8StringToUtf16String(file_paths);

    // size of DROPFILES structure followed by file paths in double null-terminated string
    SIZE_T structure_size_in_bytes = sizeof(DROPFILES);
    for (auto p = file_paths_unicode.cbegin(); p != file_paths_unicode.cend(); ++p) {
        structure_size_in_bytes += (p->size() + 1) * sizeof(WCHAR);
    }
    structure_size_in_bytes += sizeof(WCHAR);

    HANDLE data_handle = GlobalAlloc(GMEM_MOVEABLE, structure_size_in_bytes);
    if (!data_handle) {
        return;
    }

    BYTE *data_pointer = static_cast<BYTE *>(GlobalLock(data_handle));
    if (!data_pointer) {
        return;
    }

    DROPFILES *drop_files_pointer = reinterpret_cast<DROPFILES *>(data_pointer);
    drop_files_pointer->pFiles = sizeof(DROPFILES);
    drop_files_pointer->fWide = TRUE;

    SIZE_T current_offset_in_bytes = sizeof(DROPFILES);
    for (auto p = file_paths_unicode.cbegin(); p != file_paths_unicode.cend(); ++p) {
        WCHAR *target_path = reinterpret_cast<WCHAR *>(data_pointer + current_offset_in_bytes);
        SIZE_T offset_in_chars = p->size() + 1;
        SIZE_T offset_in_bytes = offset_in_chars * sizeof(WCHAR);
        memcpy(target_path, p->c_str(), offset_in_bytes);
        current_offset_in_bytes += offset_in_bytes;
    }

    WCHAR *tail = reinterpret_cast<WCHAR *>(data_pointer + current_offset_in_bytes);
    *tail = L'\0';

    GlobalUnlock(data_handle);

    if (!OpenClipboard(NULL)) {
        GlobalFree(data_handle);
        return;
    }

    EmptyClipboard();

    if (!SetClipboardData(CF_HDROP, data_handle)) {
        GlobalFree(data_handle);
        return;
    }

    CloseClipboard();
}
