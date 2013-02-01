MRuby::Gem::Specification.new('mruby-oci8') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Nick Townsend <nick.townsend@mac.com']
  spec.cc.flags << "-I/usr/include/oracle/11.2/client64"
  spec.cc.flags << "-I#{dir}/src" # to allow <oci8.h> ref in apiwrap.h to work
#  spec.linker.libraries << 'external_lib'
 
=begin
  spec.rbfiles = Dir.glob("#{dir}/mrblib/oci8/*.rb")
  spec.rbfiles << Dir.glob("#{dir}/mrblib/dbd/*.rb")
  spec.rbfiles << "#{dir}/mrblib/oci.rb"
  cfiles = %w{oci8lib env error oci8 ocihandle
	    connection_pool stmt bind metadata attr
	    lob oradate ocinumber ocidatetime object
	    apiwrap encoding oranumber_util thread_util }
  spec.objs = cfiles.map{|f| "#{dir}/src/#{f}.o" }

  cfiles.each do |f|
    file "#{dir}/src/#{f}.o"=> "#{dir}/src/#{f}.c"

  end
=end
  ENV['MRUBYGEM'] = 'yes'
  sh "ruby #{File.dirname(__FILE__)}/src/extconf.rb"

end
