# properties.rb -- implements OCI8.properties
#
# Copyright (C) 2010-2013 KUBO Takehiro <kubo@jiubao.org>

#
class OCI8

  # @private
  @@properties = {
    :length_semantics => :byte,
    :bind_string_as_nchar => false,
    :float_conversion_type => OCI8.__get_prop(1) ? :ruby : :oracle,
    :statement_cache_size => 0,
    :events_mode => ((OCI8.__get_prop(2) & 4) != 0) # 4 <- OCI_EVENTS in oci.h
  }

  if OCI8.oracle_client_version < OCI8::ORAVER_9_2
    @@properties[:statement_cache_size] = nil
  end

  # @private
  def @@properties.[](name)
    raise IndexError, "No such property name: #{name}" unless @@properties.has_key?(name)
    super(name)
  end

  # @private
  def @@properties.[]=(name, val)
    raise IndexError, "No such property name: #{name}" unless @@properties.has_key?(name)
    case name
    when :length_semantic
      if val != :byte and val != :char
        raise ArgumentError, "Invalid property value #{val} for :length_semantics."
      end
    when :bind_string_as_nchar
      val = val ? true : false
    when :float_conversion_type
      case val
      when :ruby
        OCI8.__set_prop(1, true)
      when :oracle
        OCI8.__set_prop(1, false)
      else
        raise ArgumentError, "float_conversion_type's value should be either :ruby or :oracle."
      end
    when :statement_cache_size
      if OCI8.oracle_client_version < OCI8::ORAVER_9_2
        raise RuntimeError, ":statement_cache_size is disabled on Oracle 9iR1 client."
      end
      val = val.to_i
      raise ArgumentError, "The property value for :statement_cache_size must not be negative." if val < 0
    when :events_mode
      val = val ? true : false
      if val
        OCI8.__set_prop(2, OCI8.__get_prop(2) | 4) # set OCI_EVENTS
      else
        OCI8.__set_prop(2, OCI8.__get_prop(2) & ~4) # unset OCI_EVENTS
      end
    end
    super(name, val)
  end

  # Returns a Hash which ruby-oci8 global settings.
  # The hash's setter and getter methods are customized to check
  # property names and values.
  #
  #   # get properties
  #   OCI8.properties[:bind_string_as_nchar]  # => false
  #   OCI8.properties[:invalid_property_name] # raises an IndexError
  #
  #   # set properties
  #   OCI8.properties[:bind_string_as_nchar] = true
  #   OCI8.properties[:invalid_property_name] = true # raises an IndexError
  #
  # Supported properties are listed below:
  #
  # [:length_semantics]
  #     
  #     +:char+ when Oracle character length is counted by the number of characters.
  #     +:byte+ when it is counted by the number of bytes.
  #     The default setting is +:byte+ because +:char+ causes unexpected behaviour on
  #     Oracle 9i.
  #     
  #     *Since:* 2.1.0
  #
  # [:bind_string_as_nchar]
  #     
  #     +true+ when string bind variables are bound as NCHAR,
  #     otherwise +false+. The default value is +false+.
  #
  # [:float_conversion_type]
  #     
  #     +:ruby+ when Oracle decimal numbers are converted to ruby Float values
  #     same as Float#to_s does. (default)
  #     +:oracle:+ when they are done by Oracle OCI functions.
  #     
  #     From ruby 1.9.2, a float value converted from Oracle number 15.7 by
  #     the Oracle function OCINumberToReal() makes a string representation
  #     15.700000000000001 by Float#to_s.
  #     See: http://rubyforge.org/forum/forum.php?thread_id=50030&forum_id=1078
  #     
  #     *Since:* 2.1.0
  #
  # [:statement_cache_size]
  #     
  #     The statement cache size per each session. The default size is 0, which
  #     means no statement cache, since 2.1.2. It was 20 in 2.1.1.
  #     This feature is available on Oracle 9iR2 or later.
  #     See: http://docs.oracle.com/cd/E11882_01/appdev.112/e10646/oci09adv.htm#i471377
  #     
  #     *Since:* 2.1.1
  #
  # [:events_mode]
  #     
  #     +true+ when Fast Application Notification (FAN) Support is enabled.
  #     +false+ when it is disabled. The default value is +false+.
  #     This corresponds to {http://php.net/manual/en/oci8.configuration.php#ini.oci8.events +oci8.events+ in PHP}.
  #     
  #     This parameter can be changed only when no OCI methods are called.
  #     
  #       require 'oci8'
  #       OCI8.properties[:events_mode] = true # works fine.
  #       ... call some OCI methods ...
  #       OCI8.properties[:events_mode] = true # raises a runtime error.
  #     
  #     *Since:* 2.1.4
  #
  # @return [a customized Hash]
  # @since 2.0.5
  #
  def self.properties
    @@properties
  end
end
