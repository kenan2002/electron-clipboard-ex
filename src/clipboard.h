#ifndef ELECTRON_CLIPBOARD_EX_CLIPBOARD_H
#define ELECTRON_CLIPBOARD_EX_CLIPBOARD_H

#include <vector>
#include <string>

std::vector<std::string> ReadFilePaths();

void WriteFilePaths(const std::vector<std::string> &);

#endif //ELECTRON_CLIPBOARD_EX_CLIPBOARD_H
