/* An attempt to convert the Ruby API to MRuby API */

#ifndef RUBY_RTOM_H
#define RUBY_RTOM_H 1

#include "mruby.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/data.h"
#include "mruby/hash.h"

/* The interpreter state global */

extern mrb_state *mrb;

/* VALUE  was a 64 bit int, now a struct */
#define VALUE mrb_value

#define ID mrb_sym

#define NORETURN(x) x
#define INT2FIX(x) mrb_fixnum_value(x)
#define rb_external_str_new_with_enc(buf, buflen, enc) mrb_str_new(mrb, buf, buflen)
#define Qnil mrb_nil_value()

/* can't find the equivalent in MRuby so this does both functions */
/* this is not equivalent and should be fixed !!! */

#define rb_ensure(f,a,e,b) f(a), e(b)

#define StringValue(v) (v = mrb_string_value(mrb,&v))
#define SafeStringValue(v) (v = mrb_string_value(mrb,&v))

#define rb_eArgError E_ARGUMENT_ERROR 
#define rb_eRuntimeError E_RUNTIME_ERROR 
#define rb_eTypeError E_TYPE_ERROR 

#define rb_raise(a,b, ...) mrb_raisef(mrb,a,b, ##__VA_ARGS__)

/* To get the type of an MRuby object use mrb_type(p) macro */
#define T_HASH MRB_TT_HASH
#define T_ARRAY MRB_TT_ARRAY

#define Check_Type(p,t) mrb_check_type(mrb, p, t)

#define rb_hash_aref(hash,key) mrb_hash_get(mrb,hash,key)

#define ID2SYM(x) (mrb_symbol_value(x))
#define rb_intern(name) mrb_intern(mrb,name)

#define NUM2INT(x) mrb_fixnum(x)
#define NUM2UINT(x) (unsigned)mrb_fixnum(x)

#define RB_EQUAL(a,b) mrb_equal(mrb,a,b)

#define RTEST(v) mrb_nil_p(v)

#define rb_str_new(buf,len) mrb_str_new(mrb, buf, len)

#define rb_float_new(d) mrb_float_value(d)

#define RFLOAT_VALUE(x) mrb_float(x)

#define rb_Float(v) mrb_Float(mrb,v)

#define NIL_P(x) mrb_nil_p(x)

#define rb_funcall(self, fn_sym, argc, ...) mrb_funcall(mrb, self, mrb_sym2name(mrb,fn_sym), argc, ##__VA_ARGS__)

#define rb_ary_new2(size) mrb_ary_new_capa(mrb, size)

#define rb_ary_store(ary, idx, val) mrb_ary_set(mrb, ary, idx, val)


#define xmalloc(x) mrb_malloc(mrb, x)
#define xfree(x) mrb_free(mrb, x)
#define rb_gc_mark(x) mrb_gc_mark(mrb,mrb_basic(x))


#define rb_define_private_method(k,n,f,a) rb_define_method(k,n,f,a)

#define rb_obj_is_kind_of(o,k) mrb_obj_is_kind_of(mrb, o, mrb_obj_class(mrb, k))

#define rb_class2name(k) mrb_obj_classname(mrb, k)
/* take a value returns a value */
#define CLASS_OF(k) mrb_class_path(mrb, mrb_obj_class(mrb, k))

/* Because C functions to be called from Ruby don't now contain the args
 * new ones must be written prefixed by mrb_. This macro converts calls.
 */
#define rb_define_method(klass, name, fn, argc) mrb_define_method(mrb, mrb_obj_class(mrb, klass), name, mrb_##fn, argc)

#define rb_scan_args(argc,argv,fmt, ...) mrb_get_args(mrb, fmt, ##__VA_ARGS__)

#endif /* RUBY_RTOM_h */
