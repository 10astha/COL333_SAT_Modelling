chmod 777 a2
INPUT="$1.graph"
OUPUT="$1.subgraphs"
MINOUT="$1.satoutput"
./a2 $MINOUT < $INPUT > $OUPUT
