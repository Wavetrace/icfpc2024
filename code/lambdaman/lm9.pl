#!/usr/bin/raku

for (0..24) -> $i {
#    say $i;
    print "R" x 49;
    print "D";
    print "L" x 49;
    if ($i != 24) {
        print "D";
    }
}

