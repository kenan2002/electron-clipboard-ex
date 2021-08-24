#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "clipboard.h"

std::vector<std::string> ReadFilePaths() {
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSArray<NSURL *> *urls = [pasteboard readObjectsForClasses:@[NSURL.class] options:@{
            NSPasteboardURLReadingFileURLsOnlyKey: @YES,
    }];

    if (!urls) {
        return {};
    }

    auto result = std::vector<std::string>();
    result.reserve(urls.count);
    for (NSURL *url in urls) {
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

void ClearClipboard() {
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
}

NSBitmapImageRep *getBitmapImageRepFromPasteboard() {
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSArray<NSImage *> *images = [pasteboard readObjectsForClasses:@[NSImage.class] options: nil];
    if (!images || images.count == 0) {
        return nil;
    }

    NSImage *image = [images firstObject];
    NSBitmapImageRep *bitmapRep = nil;
    NSData *tiffData = [image TIFFRepresentation];
    if (tiffData) {
        bitmapRep = [NSBitmapImageRep imageRepWithData:tiffData];
    }

    return bitmapRep;
}

bool SaveClipboardImageAsJpeg(const std::string &target_path, float compression_factor) {
    NSBitmapImageRep *bitmapRep = getBitmapImageRepFromPasteboard();
    if (!bitmapRep) {
        return false;
    }

    NSData *imageData = [bitmapRep representationUsingType:NSBitmapImageFileTypeJPEG properties:@{
            NSImageCompressionFactor: @(compression_factor)
    }];
    if (!imageData) {
        return false;
    }

    return [imageData writeToFile:[NSString stringWithUTF8String:target_path.c_str()] atomically:YES];
}

bool SaveClipboardImageAsPng(const std::string &target_path) {
    NSBitmapImageRep *bitmapRep = getBitmapImageRepFromPasteboard();
    if (!bitmapRep) {
        return false;
    }

    NSData *imageData = [bitmapRep representationUsingType:NSBitmapImageFileTypePNG properties:@{}];
    if (!imageData) {
        return false;
    }

    return [imageData writeToFile:[NSString stringWithUTF8String:target_path.c_str()] atomically:YES];
}

bool PutImageIntoClipboard(const std::string &image_path) {
    NSImage *image = [[NSImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:image_path.c_str()]];
    if (!image) {
        return false;
    }

    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    return [pasteboard writeObjects:@[image]];
}

bool ClipboardHasImage() {
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    return [pasteboard canReadObjectForClasses:@[NSImage.class] options:nil];
}
