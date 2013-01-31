#--
# connection_pool.rb -- OCI8::ConnectionPool
#
# Copyright (C) 2010 KUBO Takehiro <kubo@jiubao.org>
#++

#
class OCI8

  # Connection pooling is the use of a group (the pool) of reusable
  # physical connections by several sessions to balance loads.
  # See: {Oracle Call Interface Manual}[http://docs.oracle.com/cd/E11882_01/appdev.112/e10646/oci09adv.htm#sthref1479]
  #
  # This is equivalent to Oracle JDBC Driver {OCI Connection Pooling}[http://docs.oracle.com/cd/E11882_01/java.112/e16548/ociconpl.htm#JJDBC28789].
  #
  # Usage:
  #   # Create a connection pool.
  #   # username and password are required to establish an implicit primary session.
  #   cpool = OCI8::ConnectionPool.new(1, 5, 2, username, password, database)
  #   
  #   # Get a session from the pool.
  #   # Pass the connection pool to the third argument.
  #   conn1 = OCI8.new(username, password, cpool)
  #   
  #   # Get another session.
  #   conn2 = OCI8.new(username, password, cpool)
  #
  class ConnectionPool

    # Connections idle for more than this time value (in seconds) are
    # terminated, to maintain an optimum number of open
    # connections. If it is zero, the connections are never timed out.
    # The default value is zero.
    #
    # <b>Note:</b> Shrinkage of the pool only occurs when there is a network
    # round trip. If there are no operations, then the connections
    # stay alive.
    #
    # @return [Integer]
    def timeout
      attr_get_ub4(OCI_ATTR_CONN_TIMEOUT)
    end

    # Changes the timeout in seconds to terminate idle connections.
    #
    # @param [Integer] val
    def timeout=(val)
      attr_set_ub4(OCI_ATTR_CONN_TIMEOUT, val)
    end

    # If true, an error is thrown when all the connections in the pool
    # are busy and the number of connections has already reached the
    # maximum. Otherwise the call waits till it gets a connection.
    # The default value is false.
    def nowait?
      attr_get_ub1(OCI_ATTR_CONN_NOWAIT) != 0
    end

    # Changes the behavior when all the connections in the pool
    # are busy and the number of connections has already reached the
    # maximum.
    #
    # @param [Boolean] val
    def nowait=(val)
      attr_set_ub1(OCI_ATTR_CONN_NOWAIT, val ? 1 : 0)
    end

    # Returns the number of busy physical connections.
    #
    # @return [Integer]
    def busy_count
      attr_get_ub4(OCI_ATTR_CONN_BUSY_COUNT)
    end

    # Returns the number of open physical connections.
    #
    # @return [Integer]
    def open_count
      attr_get_ub4(OCI_ATTR_CONN_OPEN_COUNT)
    end

    # Returns the number of minimum physical connections.
    #
    # @return [Integer]
    def min
      attr_get_ub4(OCI_ATTR_CONN_MIN)
    end

    # Returns the number of maximum physical connections.
    #
    # @return [Integer]
    def max
      attr_get_ub4(OCI_ATTR_CONN_MAX)
    end

    # Returns the connection increment parameter.
    #
    # @return [Integer]
    def incr
      attr_get_ub4(OCI_ATTR_CONN_INCR)
    end

    # 
    def destroy
      free
    end
  end
end
