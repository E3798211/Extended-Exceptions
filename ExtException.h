#ifndef EXTEXCEPTION_H_INCLUDED
#define EXTEXCEPTION_H_INCLUDED

#include <string>
#include <iostream>

class ExtException
{
private:

    /// Pointer to the previous exception
    // const ExtException* parent_exception_ = nullptr;

    /// String with error description
    std::string description_;

    /// Error code
    int code_ = 0;

public:

    /// Default constructor
    ExtException(){};//: parent_exception_(nullptr) {};

    /// Copy constructor disabled
//    ExtException(const ExtException& copy) = delete;

    /// Constructor with parameters
    /**
        \param [in] err_description                 Description of an error
        \param [in] err_code                        Error code
        \param [in] err_parent                      Pointer to the parent exception
    */
    // ExtException(const char* err_description, const int err_code, /*const*/ ExtException& err_parent/* = ExtException()*/)
    ExtException(const char* err_description, const int err_code, const ExtException& err_parent = ExtException())
    {
        description_ += "Error in \"";
        description_ += __FILE__;
        description_ += "\" on line ";
        description_ += __LINE__;
        description_ += ": function \"";
        description_ += __FUNCTION__;
        description_ += "()\" has thrown: ";
        description_ += err_description;
        description_ += "\". Error code returned: ";
        description_ += std::to_string(code_);

        description_ += err_parent.GetErrorMessage();
        // parent_exception_ = err_parent;
        code_ = err_code;

        std::cout << "constructor\n";
    }

    /*
    /// Gets next exception
    /**
        Returns parent exception
    */
    /*
    const ExtException* GetNext()   const
    {
        return parent_exception_;
    }
    */

    /// Gets error message
    /**
        Returns string containing description of the error
    */
    std::string GetErrorMessage()   const
    {
        return description_;
    }

    /// Gets error code
    /**
        Returns int containing error code
    */
    int GetErrorCode()  const
    {
        return code_;
    }

    /*
    /// Get message about previous error
    /**
        Returns string containing message about error
    */
    /*
    std::string GetParentError()    const
    {
        if(!parent_exception_)      return "";
        else                        return parent_exception_->GetErrorMessage();
    }
    */

    /*
    /// Gets string with all info
    /**
        Returns string containing all info
    */
    /*
    std::string GetAllInfo()    const
    {
        std::string info;
        const ExtException* previous_exception = parent_exception_;
        while(previous_exception)
        {
            info += description_;
            info += "\n";
            // std::cout << "previous_exception = " << previous_exception << "\n";
            previous_exception = previous_exception->GetNext();

            // std::cout << info << std::endl;
        }

        // std::cout << "GetAllInfo()\n";

        return info;
    }*/

    ~ExtException()
    {
         std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
    }
};

#endif // EXTEXCEPTION_H_INCLUDED
