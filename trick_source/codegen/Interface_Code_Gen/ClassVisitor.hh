
#ifndef _CLASSVISITOR_HH_
#define _CLASSVISITOR_HH_

#include <string>
#include <map>
#include <vector>

#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "ClassValues.hh"

class CommentSaver ;
class EnumValues ;
class HeaderSearchDirs ;
class PrintAttributes ;

/**

  This class is a recursive AST visitor that is called when a CXXRecordDecl node
  is found.  Inside of a CXXRecord we are only interested in 4 types of nodes, the
  CXXRecord itself, template specializations, friends, and fields.  If a field is
  found a FieldVisitor is instantiated and parsing of the field continues in the
  field visitor.

  A class visitor is usually instantiated by the top level visitor, TranslationUnitVisitor,
  or the typedef visitor, TypedefVisitor.

  @author Alexander S. Lin

  @date July 2012

 */

class CXXRecordVisitor : public clang::RecursiveASTVisitor<CXXRecordVisitor> {
    public:
        CXXRecordVisitor( clang::CompilerInstance & in_ci ,
         CommentSaver & in_cs ,
         HeaderSearchDirs & in_hsd ,
         PrintAttributes & in_pa ,
         bool in_inherited ,
         bool in_virtual_inherited ,
         bool in_include_virtual_base ,
         unsigned int in_base_class_offset = 0 ) ;

        ~CXXRecordVisitor() ;

        /* A custom traversal that handles only the node types we are interested in. */
        bool TraverseDecl(clang::Decl *D);

        /* VisitDecl and VisitType are here for debug printing. */
        bool VisitDecl(clang::Decl *d) ;
        bool VisitType(clang::Type *t) ;

        /* These routines are called when nodes of the corresponding types are traversed */
        bool VisitCXXRecordDecl(clang::CXXRecordDecl *rec) ;
        bool VisitFriendDecl(clang::FriendDecl *fd) ;

        /** Returns the class data */
        ClassValues * get_class_data() ;

    private:
        /** The compiler instance. */
        clang::CompilerInstance & ci ;

        /** The header search directories */
        HeaderSearchDirs & hsd ;

        /** Holds all comments */
        CommentSaver & cs ;

        /** attributes printer */
        PrintAttributes & pa ;

        /** Holds the class information found, usually returned to caller of this visitor. */
        ClassValues cval ;

        /** For inherited classes this is how many bytes into the derived class we are offset */
        unsigned int base_class_offset ;

        /** Flag to specify if we should process virtual base classes. */
        bool include_virtual_base ;

        /** Flag indicating we have found a public/private/protected keyword  */
        bool access_spec_found ;

} ;

#endif
