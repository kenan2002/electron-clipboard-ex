#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "clipboard.h"

std::vector<std::string> ReadFilePaths() {
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSArray *urls = [pasteboard readObjectsForClasses:@[NSURL.class] options:@{
            NSPasteboardURLReadingFileURLsOnlyKey: @YES,
    }];

    if (!urls) {
        return {};
    }

    auto result = std::vector<std::string>();
    result.reserve(urls.count);
    for (size_t i = 0; i != urls.count; ++i) {
        NSURL *url = urls[i];
        result.emplace_back([url.path UTF8String]);
    }

    return result;
}

void WriteFilePaths(const std::vector<std::string> &file_paths) {
    NSMutableArray *urls = [[NSMutableArray alloc] initWithCapacity:file_paths.size()];
    for (const auto &path : file_paths) {
        NSString *pathStr = [NSString stringWithUTF8String:path.c_str()];
        [urls addObject:[NSURL fileURLWithPath:pathStr]];
    }

    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    [pasteboard writeObjects:urls];
}
