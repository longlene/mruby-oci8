MRuby::Gem::Specification.new('mruby-oci8') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Nick Townsend <nick.townsend@mac.com']
  spec.rbfiles = Dir.glob("#{dir}/mrblib/oci8/*.rb")
  spec.rbfiles << Dir.glob("#{dir}/mrblib/dbd/*.rb")
  spec.rbfiles << "#{dir}/mrblib/oci.rb"
  objs = %w{oci8lib.o env.o error.o oci8.o ocihandle.o
	    connection_pool.o stmt.o bind.o metadata.o attr.o
	    lob.o oradate.o ocinumber.o ocidatetime.o object.o 
	    apiwrap.o encoding.o oranumber_util.o thread_util.o }
  spec.objs = objs.map{|o| "#{dir}/src/#{o}" }
end
# spec.cflags (C compiler flags for this GEM)
# spec.mruby_cflags (global C compiler flags for everything)
# spec.mruby_ldflags (global linker flags for everything)
# spec.mruby_libs (global libraries for everything)
# spec.mruby_includes (global includes for everything)
# spec.test_rbfiles (Ruby test files for integration into mrbtest)
# spec.test_objs (Object test files for integration into mrbtest)
# spec.test_preload (Initialization files for mrbtest)
