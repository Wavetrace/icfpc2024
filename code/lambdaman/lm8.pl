#!/usr/bin/raku

my $w = 98;
my $h = 102;


my $len = 2;
for (0..23) -> $i {
    say "D"x$len;
    say "L"x$len;
    $len += 2;
    say "U"x$len;
    say "R"x$len;
    $len += 2;
    # say $i;
}
say "D"x$len;
say "L"x$len;

# say 'hi'

