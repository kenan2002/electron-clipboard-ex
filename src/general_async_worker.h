#ifndef ELECTRON_CLIPBOARD_EX_ASYNC_WORKER_H
#define ELECTRON_CLIPBOARD_EX_ASYNC_WORKER_H

#include <napi.h>
#include <tuple>
#include <type_traits>

namespace clipboard_ex_internal_ns {
    template<typename T>
    std::vector<napi_value> GetResult(Napi::Env env, T ret) {
        return {env.Null(), ret};
    }

    template<>
    std::vector<napi_value> GetResult(Napi::Env env, bool ret) {
        return {env.Null(), Napi::Boolean::New(env, ret)};
    }
}

template<typename Func, typename... Args>
class GeneralAsyncWorker : public Napi::AsyncWorker {
    using ArgsTuple = std::tuple<Args...>;
public:
    GeneralAsyncWorker(const Napi::Function &callback, const Func &func, const ArgsTuple &data)
            : AsyncWorker(callback), _func(func), _data(data) {}

    ~GeneralAsyncWorker() override = default;

    void Execute() override {
        _return_value = std::apply(_func, _data);
    }

    std::vector<napi_value> GetResult(Napi::Env env) override {
        return clipboard_ex_internal_ns::GetResult(env, _return_value);
    }

private:
    std::function<Func> _func;
    ArgsTuple _data;
    std::invoke_result_t<Func, Args...> _return_value;
};

#endif //ELECTRON_CLIPBOARD_EX_ASYNC_WORKER_H
