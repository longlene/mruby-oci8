/* An attempt to convert the Ruby API to MRuby API */

#ifndef RUBY_RTOM_H
#define RUBY_RTOM_H 1

#include "mruby.h"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/data.h"
#include "mruby/hash.h"
#include "mruby/string.h"
#include "mruby/variable.h"

/* The interpreter state global */

extern mrb_state *mrb;

#define VALUE mrb_value
#define ID mrb_sym

#define NORETURN(x) x
#define OBJ_TAINT(x)

/* Constants */

#define Qnil mrb_nil_value()
#define Qtrue mrb_true_value()
#define Qfalse mrb_false_value()

/* Predicates */

#define RTEST(v) mrb_nil_p(v)
#define NIL_P(x) mrb_nil_p(x)
#define FIXNUM_P(x) mrb_fixnum_p(x)

/* Conversions C->Ruby */

#define INT2FIX(x) mrb_fixnum_value(x)
#define UINT2NUM(x) mrb_fixnum_value(x)
#define rb_float_new(d) mrb_float_value(d)

/* Conversions Ruby->C */

#define NUM2LONG(x) mrb_fixnum(x)
#define NUM2INT(x) mrb_fixnum(x)
#define NUM2UINT(x) (unsigned)mrb_fixnum(x)
#define RFLOAT_VALUE(x) mrb_float(x)
#define FIX2INT(x) mrb_fixnum(x)

/* Conversions Ruby->Ruby */

#define rb_Float(v) mrb_Float(mrb,v)

/* Strings */

#define rb_external_str_new_with_enc(buf, buflen, enc) mrb_str_new(mrb, buf, buflen)
#define rb_str_new(buf,len) mrb_str_new(mrb, buf, len)
#define rb_obj_as_string(value) mrb_obj_as_string(mrb, value)

#define StringValue(v) (v = mrb_string_value(mrb,&v))
#define SafeStringValue(v) (v = mrb_string_value(mrb,&v))

/* Symbols */

#define ID2SYM(x) (mrb_symbol_value(x))
#define rb_intern(name) mrb_intern(mrb,name)

/* Arrays */

#define rb_ary_new2(size) mrb_ary_new_capa(mrb, size)
#define rb_ary_store(ary, idx, val) mrb_ary_set(mrb, ary, idx, val)
#define rb_ary_new() mrb_ary_new(mrb)
#define rb_ary_push(a, b) mrb_ary_push(mrb, a, b)
#define rb_ary_join(a, b) a; mrb_ary_concat(mrb, a, b)

/* Hashes */

#define rb_hash_aref(hash,key) mrb_hash_get(mrb,hash,key)

/* Exceptions */

/* Ruby needs the class object, MRuby the class data struct */

#define rb_raise(a,b, ...) mrb_raisef(mrb, mrb_class(mrb, a), b, ##__VA_ARGS__)

#define rb_eArgError mrb_obj_value(E_ARGUMENT_ERROR)
#define rb_eRuntimeError mrb_obj_value(E_RUNTIME_ERROR)
#define rb_eTypeError mrb_obj_value(E_TYPE_ERROR)
#define rb_eRangeError mrb_obj_value(E_RANGE_ERROR)
#define rb_eNameError mrb_obj_value(E_NAME_ERROR)

/* Types */

#define T_HASH MRB_TT_HASH
#define T_ARRAY MRB_TT_ARRAY
#define T_STRING MRB_TT_STRING
#define TYPE(p) mrb_type(p)

#define Check_Type(p,t) mrb_check_type(mrb, p, t)

/* Language Features */

#define rb_eval_string(s) mrb_load_string(mrb, s)
#define rb_ivar_get(objval,sym) mrb_iv_get(mrb, objval, sym)
#define rb_ivar_set(objval,sym,val) mrb_iv_set(mrb, objval, sym, val)
#define rb_ivar_defined(objval,sym) (mrb_iv_defined(mrb, objval, sym)?mrb_true_value():mrb_false_value())

/* can't find the equivalent in MRuby so this does both functions */
/* this is not equivalent and should be fixed !!! */

#define rb_ensure(f,a,e,b) f(a), e(b)

#define rb_funcall(self, fn_sym, argc, ...) mrb_funcall(mrb, self, mrb_sym2name(mrb,fn_sym), argc, ##__VA_ARGS__)

#define xmalloc(x) mrb_malloc(mrb, x)
#define xfree(x) mrb_free(mrb, x)
#define rb_gc_mark(x) mrb_gc_mark(mrb,mrb_basic(x))


#define rb_define_private_method(k,n,f,a) rb_define_method(k,n,f,a)

/* Types */
#define rb_cObject mrb_obj_value(mrb->object_class)

/* Class introspection */

#define rb_obj_is_kind_of(o,k) mrb_obj_is_kind_of(mrb, o, mrb_obj_class(mrb, k))
#define rb_class2name(k) mrb_obj_classname(mrb, k)

/* take a value returns a value */
#define CLASS_OF(k) mrb_class_path(mrb, mrb_obj_class(mrb, k))

#define rb_class_superclass(k) mrb_obj_value(RCLASS_SUPER(k))

/* Defining Ruby types */

#define rb_define_class_under(o,name,k) mrb_obj_value(mrb_define_class_under(mrb, mrb_obj_class(mrb,o),name,mrb_obj_class(mrb,k)))

/* Because C functions to be called from Ruby don't now contain the args
 * new ones must be written prefixed by mrb_. This macro converts calls.
 */
#define rb_define_method(klass, name, fn, argc) mrb_define_method(mrb, mrb_obj_class(mrb, klass), name, mrb_##fn, argc)

/* since the format lists don't match, and the call sequence is different do this manually */
#define rb_scan_args(argc,argv,fmt, ...)

#define rb_define_alias(k,n1,n2) mrb_define_alias(mrb, mrb_obj_class(mrb,k), n1, n2)

#endif /* RUBY_RTOM_h */
