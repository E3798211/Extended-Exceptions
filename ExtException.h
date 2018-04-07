#ifndef EXTEXCEPTION_H_INCLUDED
#define EXTEXCEPTION_H_INCLUDED

#include <string>
#include <iostream>
#include <stdio.h>

#include "DotSyntax.h"

#define CALL_PARAMETERS __FILE__, __FUNCTION__, __LINE__

const char DEFAULT_OUTPUT_FILENAME[] = "Dependency.ps";
const char     DOT_OUTPUT_FILENAME[] = "Dependency.dot";

class ExtException
{
private:

    /// Pointer to the previous exception
    const ExtException* parent_exception_ = nullptr;

    /// Description of the error
    std::string error_;

    /// File
    std::string file_;

    /// Function
    std::string func_;

    /// Line
    int line_ = 0;

    /// Error code
    int code_ = 0;

    /// Whole error description
    std::string whole_description_;

public:

    /// Default constructor
    ExtException(){};

    /// Copy constructor disabled
    ExtException(const ExtException& copy) = delete;

    /// Constructor with parameters
    /**
        \param [in] err_description                 Description of an error
        \param [in] err_code                        Error code
        \param [in] err_parent                      Pointer to the parent exception
    */
    ExtException(const char* err_description, const int err_code,
                 const char* file, const char* func, const int line,
                 const ExtException* err_parent = nullptr):
                 parent_exception_  (err_parent),
                 error_             (err_description),
                 file_              (file),
                 func_              (func),
                 line_              (line),
                 code_              (err_code)
    {
        whole_description_ += "Error in \"";
        whole_description_ += file;
        whole_description_ += "\" on line ";
        whole_description_ += std::to_string(line);
        whole_description_ += ":\tfunction \"";
        whole_description_ += func;
        whole_description_ += "()\" has thrown: \"";
        whole_description_ += err_description;
        whole_description_ += "\".\nError code returned: ";
        whole_description_ += std::to_string(code_);
    }

    const ExtException* GetNext()   const
    {
        return parent_exception_;
    }

    std::string GetError()  const
    {
        return error_;
    }

    std::string GetFile()   const
    {
        return file_;
    }

    std::string GetFunction()   const
    {
        return func_;
    }

    int GetLine()  const
    {
        return line_;
    }

    int GetErrorCode()  const
    {
        return code_;
    }

    std::string GetErrorMessage()   const
    {
        return whole_description_;
    }

    /// Get message about previous error
    /**
        Returns string containing message about error
    */
    std::string GetParentError()    const
    {
        if(!parent_exception_)      return "";
        else                        return parent_exception_->GetErrorMessage();
    }

    /// Gets string with all info
    /**
        Returns string containing all info
    */
    std::string GetAllInfo()    const
    {
        std::string info;
        const ExtException* previous_exception = this;

        while(previous_exception){
            info += previous_exception->whole_description_ + "\n";
            previous_exception = previous_exception->GetNext();
        }

        return info;
    }

    /// Destructor
    /**
        Deletes parent exceptions if they exist
    */
    ~ExtException()
    {
        if(parent_exception_)   delete parent_exception_;
    }

    /// Builds graph with all information available
    int BuildDependencyGraph(const char* output_filename = nullptr) const;
};

enum ERR_CODES
{
    OK = 0,
    FILE_NOT_OPENED,
    UNEXPECTED_NULLPTR
};

#endif // EXTEXCEPTION_H_INCLUDED
