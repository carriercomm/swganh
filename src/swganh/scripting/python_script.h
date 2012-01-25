
#ifndef SWGANH_SCRIPTING_PYTHON_SCRIPT_H_
#define SWGANH_SCRIPTING_PYTHON_SCRIPT_H_

#include <string>
#include <memory>

#include <boost/python.hpp>

namespace swganh {
namespace scripting {

    class PythonScript
    {
    public:
        PythonScript(const std::string& filename);

        void Run();

        template<typename T>
        void SetContext(const std::string& key, T value)
        {
	        try{
                globals_["context"][key.c_str()] = value;
            } 
            catch (error_already_set &) 
            {
                PyErr_Print();
            }   
        }

    private:
        PythonScript();

        void ReadFileContents();

        std::string filename_;
        std::string filecontents_;
        boost::python::object file_object_;
        boost::python::object globals_;
    };

}}  // namespace swganh::scripting

#endif  // SWGANH_SCRIPTING_PYTHON_SCRIPT_H_
