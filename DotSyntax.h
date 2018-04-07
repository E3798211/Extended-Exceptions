#ifndef DOTSYNTAX_H_INCLUDED
#define DOTSYNTAX_H_INCLUDED

const char DOT1[] = "dot -Tps ";
const char DOT2[] = " -o ";

const char             BEGIN[]  = "digraph G\n{\n";
const char               END[]  = "}\n";

const char  SET_RECORD_SHAPE[]  = "node[shape = record];\n";

const char BEGIN_DECLARATION[]  = " [label = \"";
const char   END_DECLARATION[]  = "\"];\n";
const char      BEGIN_COLUMN[]  = "{ ";
const char        END_COLUMN[]  = " }";
const char        NEXT_FIELD[]  = " | ";
const char            LABELS[]  = "{ file | Line | Function | Error description | Error code } ";

const char                TO[]  = " -> ";
const char       ARROW_COLOR[]  = " [color = green];\n";


#endif // DOTSYNTAX_H_INCLUDED
