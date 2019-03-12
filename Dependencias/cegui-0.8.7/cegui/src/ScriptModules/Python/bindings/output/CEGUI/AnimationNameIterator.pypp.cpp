// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "AnimationNameIterator.pypp.hpp"

namespace bp = boost::python;

struct ConstVectorIterator_less__std_scope_set_less_CEGUI_scope_String_comma__CEGUI_scope_StringFastLessCompare_comma__std_scope_allocator_less_CEGUI_scope_String_greater___greater___greater__wrapper : CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >, bp::wrapper< CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > > > {

    ConstVectorIterator_less__std_scope_set_less_CEGUI_scope_String_comma__CEGUI_scope_StringFastLessCompare_comma__std_scope_allocator_less_CEGUI_scope_String_greater___greater___greater__wrapper(CEGUI::ConstVectorIterator<std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > > const & arg )
    : CEGUI::ConstVectorIterator<std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >( arg )
      , bp::wrapper< CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > > >(){
        // copy constructor
        
    }

    ConstVectorIterator_less__std_scope_set_less_CEGUI_scope_String_comma__CEGUI_scope_StringFastLessCompare_comma__std_scope_allocator_less_CEGUI_scope_String_greater___greater___greater__wrapper( )
    : CEGUI::ConstVectorIterator<std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >( )
      , bp::wrapper< CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > > >(){
        // null constructor
    
    }

    virtual ::CEGUI::String getCurrentValue(  ) const  {
        if( bp::override func_getCurrentValue = this->get_override( "getCurrentValue" ) )
            return func_getCurrentValue(  );
        else{
            return this->CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >::getCurrentValue(  );
        }
    }
    
    ::CEGUI::String default_getCurrentValue(  ) const  {
        return CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >::getCurrentValue( );
    }

};

void Iterator_next(::CEGUI::ConstVectorIterator<std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >& t)
{
    t++;
}

void Iterator_previous(::CEGUI::ConstVectorIterator<std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >& t)
{
    t--;
}

void register_AnimationNameIterator_class(){

    { //::CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >
        typedef bp::class_< ConstVectorIterator_less__std_scope_set_less_CEGUI_scope_String_comma__CEGUI_scope_StringFastLessCompare_comma__std_scope_allocator_less_CEGUI_scope_String_greater___greater___greater__wrapper, bp::bases< CEGUI::ConstBaseIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> >, CEGUI::String > > > AnimationNameIterator_exposer_t;
        AnimationNameIterator_exposer_t AnimationNameIterator_exposer = AnimationNameIterator_exposer_t( "AnimationNameIterator", bp::no_init );
        bp::scope AnimationNameIterator_scope( AnimationNameIterator_exposer );
        AnimationNameIterator_exposer.def( bp::init< >("*************************************************************************\n\
           No default construction available\n\
        *************************************************************************\n") );
        { //::CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >::getCurrentValue
        
            typedef CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > > exported_class_t;
            typedef ::CEGUI::String ( exported_class_t::*getCurrentValue_function_type )(  ) const;
            typedef ::CEGUI::String ( ConstVectorIterator_less__std_scope_set_less_CEGUI_scope_String_comma__CEGUI_scope_StringFastLessCompare_comma__std_scope_allocator_less_CEGUI_scope_String_greater___greater___greater__wrapper::*default_getCurrentValue_function_type )(  ) const;
            
            AnimationNameIterator_exposer.def( 
                "getCurrentValue"
                , getCurrentValue_function_type(&::CEGUI::ConstVectorIterator< std::set<CEGUI::String, CEGUI::StringFastLessCompare, std::allocator<CEGUI::String> > >::getCurrentValue)
                , default_getCurrentValue_function_type(&ConstVectorIterator_less__std_scope_set_less_CEGUI_scope_String_comma__CEGUI_scope_StringFastLessCompare_comma__std_scope_allocator_less_CEGUI_scope_String_greater___greater___greater__wrapper::default_getCurrentValue) );
        
        }
        AnimationNameIterator_exposer.def("next", &::Iterator_next);
        AnimationNameIterator_exposer.def("previous", &::Iterator_previous);
    }

}
