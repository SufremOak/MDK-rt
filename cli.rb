#!/usr/bin/env ruby

require 'thor'

class MdkCli < Thor
    def runb(bin)
        puts "Goin to run: #{bin}"
    end
end

MdkCli.start(ARGV)