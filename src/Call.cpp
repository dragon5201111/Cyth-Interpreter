#include "Call.h"
#include "Env.h"
#include "Interpreter.h"

Value UserFunction::call(Interpreter &interpreter, const std::vector<Value> &args) {
    check_arity(args);

    if (const auto enclosing = enclosing_env.lock()) {
        const auto new_env = std::make_shared<Env>(enclosing);

        for (size_t i = 0; i < args.size(); ++i) {
            new_env->bind(function_decl.parameters[i], args[i]);
        }
        try {
            interpreter.execute_stmnts_in_new_env(function_decl.body, new_env);
        }catch (ReturnException& return_exception) {
            return return_exception.value;

        }

        return Value();
    }

    throw std::runtime_error("Error, enclosing environment has been freed!");

}
