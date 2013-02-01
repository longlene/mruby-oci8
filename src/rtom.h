/* An attempt to convert the Ruby API to MRuby API */

extern mrb_state *_MRB;

#ifndef RUBY_RTOM_H
#define RUBY_RTOM_H 1
#define VALUE mrb_value
#define ID mrb_sym
#define NORETURN(x) x
#define INT2FIX(x) mrb_fixnum_value(x)
#define rb_external_str_new_with_enc(buf, buflen, enc) mrb_str_new(_MRB, buf, buflen)
#define Qnil mrb_nil_value()
/* can't find the equivalent in MRuby so this does both functions */
#define rb_ensure(f,a,e,b) f(a), e(b)

#define StringValue(v) (v = mrb_string_value(_MRB,&v))
#define SafeStringValue(v) (v = mrb_string_value(_MRB,&v))

#define rb_eArgError E_ARGUMENT_ERROR
#define rb_raise(a,b,c, ...) mrb_raisef(_MRB,a,b,c, ##__VA_ARGS__)

#define T_HASH MRB_TT_HASH
#define Check_Type(p,t) mrb_check_datatype(_MRB,p, 
#endif
