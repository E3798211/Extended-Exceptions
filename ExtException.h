#ifndef EXTEXCEPTION_H_INCLUDED
#define EXTEXCEPTION_H_INCLUDED

#include <string>
#include <iostream>

#define CALL_PARAMETERS __FILE__, __FUNCTION__, __LINE__

class ExtException
{
private:

    /// Pointer to the previous exception
    const ExtException* parent_exception_ = nullptr;

    /// String with error description
    std::string description_;

    /// Error code
    int code_ = 0;

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
                 const ExtException* err_parent = nullptr)
    {
        description_ += "Error in \"";
        description_ += file;
        description_ += "\" on line ";
        description_ += std::to_string(line);
        description_ += ":\tfunction \"";
        description_ += func;
        description_ += "()\" has thrown: \"";
        description_ += err_description;
        description_ += "\".\nError code returned: ";
        description_ += std::to_string(code_);

        parent_exception_ = err_parent;
        code_ = err_code;
    }

    /// Gets next exception
    /**
        Returns parent exception
    */
    const ExtException* GetNext()   const
    {
        return parent_exception_;
    }

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
            info += previous_exception->description_ + "\n\n";
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
};

#endif // EXTEXCEPTION_H_INCLUDED
