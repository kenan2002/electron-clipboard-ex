#include <napi.h>
#include "clipboard.h"

Napi::Array ReadFilePathsJs(const Napi::CallbackInfo &info) {
    auto env = info.Env();
    const auto file_paths = ReadFilePaths();
    auto result = Napi::Array::New(env, file_paths.size());
    for (size_t i = 0; i != file_paths.size(); ++i) {
        result.Set(i, file_paths[i]);
    }
    return result;
}


void WriteFilePathsJs(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expect 1 argument but got 0.")
                .ThrowAsJavaScriptException();
        return;
    }

    auto file_paths_js = info[0].As<Napi::Array>();
    auto file_paths = std::vector<std::string>();
    file_paths.reserve(file_paths_js.Length());
    for (size_t i = 0; i != file_paths_js.Length(); ++i) {
        std::string path = file_paths_js.Get(i).As<Napi::String>();
        if (path.empty()) {
            Napi::TypeError::New(env, "Empty path is not allowed")
                    .ThrowAsJavaScriptException();
            return;
        }
        file_paths.emplace_back(path);
    }
    WriteFilePaths(file_paths);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("readFilePaths", Napi::Function::New(env, ReadFilePathsJs));
    exports.Set("writeFilePaths", Napi::Function::New(env, WriteFilePathsJs));
    return exports;
}

NODE_API_MODULE(clipboard, Init)
