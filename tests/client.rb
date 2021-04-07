require 'socket'


s = TCPSocket.new 'localhost', 8080

s.write("./tests/testfiles/f#{ARGV[0]}.txt\n")
s.each_line do |line|
    puts line
end

s.close