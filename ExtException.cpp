#include "ExtException.h"

/// Prints info about exception in dot format
/**
    \param [in] ex                      Exception to be printed
    \param [in] output                  Output file
*/
int PrintExceptionInfo(const ExtException* ex, FILE* output)
{
    if(!ex)     return UNEXPECTED_NULLPTR;
    if(!output) return UNEXPECTED_NULLPTR;

    fprintf(output, "_%p", ex);

    fprintf(output, BEGIN_DECLARATION);

    fprintf(output, LABELS);
    fprintf(output, NEXT_FIELD);

    fprintf(output, BEGIN_COLUMN);

    fprintf(output, "%s", ex->GetFile().c_str());
    fprintf(output, NEXT_FIELD);
    fprintf(output, "%d", ex->GetLine());
    fprintf(output, NEXT_FIELD);
    fprintf(output, "%s", ex->GetFunction().c_str());
    fprintf(output, NEXT_FIELD);
    fprintf(output, "%s", ex->GetError().c_str());
    fprintf(output, NEXT_FIELD);
    fprintf(output, "%d", ex->GetErrorCode());
    fprintf(output, END_COLUMN);

    fprintf(output, END_DECLARATION);

    return OK;
}

/// Sets connections between nodes
/**
    \param [in] ex                      Exception to be connected with next one
    \param [in] output                  Output file
*/
int SetConnections(const ExtException* ex, FILE* output)
{
    if(!ex)     return UNEXPECTED_NULLPTR;
    if(!output) return UNEXPECTED_NULLPTR;

    if(!ex->GetNext())  return OK;

    fprintf(output, "_%p", ex);
    fprintf(output, TO);
    fprintf(output, "_%p", ex->GetNext());
    fprintf(output, ARROW_COLOR);

    return OK;
}

int ExtException::BuildDependencyGraph(const char* output_filename) const
{
    FILE* dot_output = fopen(DOT_OUTPUT_FILENAME, "w");
    if(!dot_output)     return FILE_NOT_OPENED;

    fprintf(dot_output, BEGIN);
    fprintf(dot_output, SET_RECORD_SHAPE);

    const ExtException* previous_exception = this;
    while(previous_exception)
    {
        PrintExceptionInfo(previous_exception, dot_output);
        previous_exception = previous_exception->GetNext();
    }

    previous_exception = this;
    while(previous_exception)
    {
        SetConnections(previous_exception, dot_output);
        previous_exception = previous_exception->GetNext();
    }

    fprintf(dot_output, END);

    fclose(dot_output);

    std::string dot_call = DOT1;
    dot_call += DOT_OUTPUT_FILENAME;
    dot_call += DOT2;
    dot_call += (output_filename)? output_filename : DEFAULT_OUTPUT_FILENAME;

    system(dot_call.c_str());
    remove(DOT_OUTPUT_FILENAME);

    return OK;
}


