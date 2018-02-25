//
// Created by FyS on 27/06/17.
//

#ifndef FREESOULS_MOCKVERIFIER_HH
#define FREESOULS_MOCKVERIFIER_HH

#include <string>
#include <FysBus.hh>
#include <boost/test/test_tools.hpp>
#include <map>

namespace fys::test {

    template <typename T>
    class MockVerifier {

    private:
        template<typename... T>
        struct MethodCallVerifier {
            std::string _methodName;
            std::size_t _called = 0;
            std::tuple<T...> args;
        };

    public:
        class MockClassVerifier {
        public:
            template<typename... A>
            void addMethdoCall(std::string &&className, std::string &&methodName, A... args) {
                MethodCallVerifier methodCallVerifier;
                std::string key = std::move(className) + std::move(methodName);

                if (_verifiers.find(key) != _verifiers.end())
                    methodCallVerifier = _verifiers.at(key);
                methodCallVerifier._methodName = methodName;
                methodCallVerifier._called += 1;
                _verifiers[key] = methodCallVerifier;
                std::cout << "The method " << key << " has been called " << methodCallVerifier._called << " times" << std::endl;
            }

            bool verify(std::string &&className, std::string &&methodName) const {
                std::string key = std::move(className) + std::move(methodName);

                if (_verifiers.find(key) == _verifiers.end())
                    return false;
                return _verifiers.at(key).called > 0;
            }

            template <typename T, typename... Args>
            bool verify(std::string &&className, std::string &&methodName, T arg, Args... args) const {
                if (_verifiers.find(className + methodName) == _verifiers.end())
                    return false;
                return verify(std::move(className), std::move(methodName), args);
            }

            template <typename... Args>
            bool verify(std::string &&className, std::string &&methodName, Args... args) const {
                std::string key = className + methodName;
                if (_verifiers.find(key) == _verifiers.end())
                    return false;
                return verify(std::move(className), std::move(methodName), args);
            }

        private:
            std::map<std::string, MethodCallVerifier> _verifiers;
        };


    private:


    };

}



#endif //FREESOULS_MOCKVERIFIER_HH
