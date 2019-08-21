set data [gets stdin]
scan $data "%d %d" N k

#Create a simulator object
set ns [new Simulator]

$ns rtproto DV

set colors {}
# Generate random colors
while {[llength $colors] < $k} {
    set r [myRand 1 0xFF]
    set g [myRand 1 0xFF]
    set b [myRand 1 0xFF]
    set c [format "#%02x%02x%02x" $r $g $b]
    if {$c ni $colors} {
		$ns color [llength $colors] $c
    	lappend colors $c
    }
}

#Open the nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Define a 'finish' procedure
proc finish {} {
    global ns nf
    $ns flush-trace
    #Close the trace file
    close $nf
    #Executenam on the trace file
    exec nam out.nam &
    exit0
}

for {set i 0} {$i < $N} {incr i} {
	set n($i) [$ns node]
}

#Change the shape of center node in a star topology
$n(0) shape square

#Create links between the nodes
for {set i 1} {$i < $N} {incr i} {
	$ns duplex-link $n(0) $n([expr ($i) % $N]) 512Kb 5ms DropTail
}

for {set i 0} {$i < $k} {incr i} {
	set input [gets stdin]
	scan $input "%d %d" u v
	set tcp [new Agent/TCP]
	$ns attach-agent $n($u) $tcp
	$tcp set class_ $i
	set sink [new Agent/TCPSink]
	$ns attach-agent $n($v) $sink
	$ns connect $tcp $sink
	set ftp0 [new Application/FTP]
	$ftp0 attach-agent $tcp
	$ns at 0.1 "$ftp0 start"
	$ns at 1.5 "$ftp0 stop"

	# Create a CBR traffic source and attach it to tcp0
	set cbr0 [new Application/Traffic/CBR]
	$cbr0 set packetSize_ 500
	$cbr0 set interval_ 0.01
	$cbr0 attach-agent $tcp
}

#Schedule events for the CBR agents
$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"


#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run
