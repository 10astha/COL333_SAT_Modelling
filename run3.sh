chmod 777 a3
INPUT="$1.graph"
OUPUT="$1.mapping"

./a3 $MINOUT < $INPUT > $OUPUT
