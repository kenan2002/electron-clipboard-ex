#ifndef ELECTRON_CLIPBOARD_EX_CLIPBOARD_H
#define ELECTRON_CLIPBOARD_EX_CLIPBOARD_H

#include <vector>
#include <string>

std::vector<std::string> ReadFilePaths();

void WriteFilePaths(const std::vector<std::string> &file_paths);

void ClearClipboard();

bool SaveClipboardImageAsJpeg(const std::string &target_path, float compression_factor);

bool SaveClipboardImageAsPng(const std::string &target_path);

bool PutImageIntoClipboard(const std::string &image_path);

bool ClipboardHasImage();

#endif //ELECTRON_CLIPBOARD_EX_CLIPBOARD_H
