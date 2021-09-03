#include <napi.h>
#include <tuple>
#include "clipboard.h"
#include "general_async_worker.h"

Napi::Array ReadFilePathsInner(const Napi::Env &env) {
    const auto file_paths = ReadFilePaths();
    auto result = Napi::Array::New(env, file_paths.size());
    for (size_t i = 0; i != file_paths.size(); ++i) {
        result.Set(i, file_paths[i]);
    }
    return result;
}

Napi::Array ReadFilePathsJs(const Napi::CallbackInfo &info) {
    auto env = info.Env();
    return ReadFilePathsInner(env);
}


Napi::Value WriteFilePathsJs(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expect 1 argument but got 0.")
                .ThrowAsJavaScriptException();
        return env.Null();
    }

    auto file_paths_js = info[0].As<Napi::Array>();
    auto file_paths = std::vector<std::string>();
    file_paths.reserve(file_paths_js.Length());
    for (size_t i = 0; i != file_paths_js.Length(); ++i) {
        std::string path = file_paths_js.Get(i).As<Napi::String>();
        if (path.empty()) {
            Napi::TypeError::New(env, "Empty path is not allowed")
                    .ThrowAsJavaScriptException();
            return env.Null();
        }
        file_paths.emplace_back(path);
    }
    WriteFilePaths(file_paths);

    return ReadFilePathsInner(env);
}

void ClearClipboardJs(const Napi::CallbackInfo &info) {
    ClearClipboard();
}

Napi::Boolean SaveClipboardImageAsJpegSync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Expect 2 arguments.")
                .ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    std::string target_path = info[0].As<Napi::String>();
    float compression_factor = info[1].As<Napi::Number>();
    bool result = SaveClipboardImageAsJpeg(target_path, compression_factor);

    return Napi::Boolean::New(env, result);
}

void SaveClipboardImageAsJpegAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
        Napi::TypeError::New(env, "Expect at least 2 arguments.")
                .ThrowAsJavaScriptException();
        return;
    }

    std::string target_path = info[0].As<Napi::String>();
    float compression_factor = info[1].As<Napi::Number>();

    Napi::Function callback;
    if (info.Length() > 2) {
        callback = info[2].As<Napi::Function>();
    }

    auto worker = new GeneralAsyncWorker(callback, SaveClipboardImageAsJpeg,
                                         std::make_tuple(target_path, compression_factor));
    worker->Queue();
}

Napi::Boolean SaveClipboardImageAsPngSync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expect 1 argument but got 0.")
                .ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    std::string target_path = info[0].As<Napi::String>();
    bool result = SaveClipboardImageAsPng(target_path);

    return Napi::Boolean::New(env, result);
}

void SaveClipboardImageAsPngAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expect at least 1 argument but got 0.")
                .ThrowAsJavaScriptException();
        return;
    }

    std::string target_path = info[0].As<Napi::String>();

    Napi::Function callback;
    if (info.Length() > 1) {
        callback = info[1].As<Napi::Function>();
    }

    auto worker = new GeneralAsyncWorker(callback, SaveClipboardImageAsPng, std::make_tuple(target_path));
    worker->Queue();
}

Napi::Boolean PutImageIntoClipboardSync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expect 1 argument but got 0.")
                .ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    std::string image_path = info[0].As<Napi::String>();
    bool result = PutImageIntoClipboard(image_path);

    return Napi::Boolean::New(env, result);
}

void PutImageIntoClipboardAsync(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expect at least 1 argument but got 0.")
                .ThrowAsJavaScriptException();
        return;
    }

    std::string image_path = info[0].As<Napi::String>();

    Napi::Function callback;
    if (info.Length() > 1) {
        callback = info[1].As<Napi::Function>();
    }

    auto worker = new GeneralAsyncWorker(callback, PutImageIntoClipboard, std::make_tuple(image_path));
    worker->Queue();
}

Napi::Boolean ClipboardHasImageJs(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    bool result = ClipboardHasImage();
    return Napi::Boolean::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("readFilePaths", Napi::Function::New(env, ReadFilePathsJs));
    exports.Set("writeFilePaths", Napi::Function::New(env, WriteFilePathsJs));
    exports.Set("clear", Napi::Function::New(env, ClearClipboardJs));
    exports.Set("saveImageAsJpegSync", Napi::Function::New(env, SaveClipboardImageAsJpegSync));
    exports.Set("saveImageAsJpegAsync", Napi::Function::New(env, SaveClipboardImageAsJpegAsync));
    exports.Set("saveImageAsPngSync", Napi::Function::New(env, SaveClipboardImageAsPngSync));
    exports.Set("saveImageAsPngAsync", Napi::Function::New(env, SaveClipboardImageAsPngAsync));
    exports.Set("putImageSync", Napi::Function::New(env, PutImageIntoClipboardSync));
    exports.Set("putImageAsync", Napi::Function::New(env, PutImageIntoClipboardAsync));
    exports.Set("hasImage", Napi::Function::New(env, ClipboardHasImageJs));
    return exports;
}

NODE_API_MODULE(clipboard, Init)
