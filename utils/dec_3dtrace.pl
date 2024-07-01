#!/usr/bin/raku

my $in = $*IN.slurp;
# my $in = $*IN.get;
# my $in = $*IN.readchars(1);

sub tr_str($in) {
    my $proc = run "./tr_str", "-n", :in;
    $proc.in.say: $in;
    $proc.in.close;
}

if ($in.substr(0, 1) === 'S') {
    say "str";
    tr_str($in);
    # my $proc = run "./tr_str", "-n", "<", $in, :out;
    # my $proc = run "cat", "<", $in, :out;
    # my $proc = shell(<echo $in | cat>);
    # $proc.out.slurp(:close).say;
} else {
    say "trace";
    my @ops = $in.split(/\s/);
    # say @ops;
    my $i = 0;
    for @ops -> $op {
        # say $i++, ' ', $op;
    }
    
    my $str = @ops[35].substr(1);
    my $int = @ops[36].substr(1);
    
    # say "$str                   <- $int";
    # say $str.chars;

    my $num = 0;
    while ($int.chars) {
        # $l = $int.substr(0, 1);
        my $d = $int.ord - '!'.ord;
        $int = $int.substr(1);
        # say "digit: $d";
        $num = $num * 94 + $d;
        #say $val;
    }
    say "num: $num";
    
    my $len = $str.chars;
    my $out = "";
    while ($num > 0) {
        my $off = $num % $len;
        # print $str.substr($off, 1);
        $out ~= $str.substr($off, 1);
        $num = $num div $len;
    }
    # $out.=reverse;
    tr_str($out.flip);
    
}